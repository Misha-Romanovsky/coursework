//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <fstream.h>
#include "ChildFormUnit.h"
#include "MainFormUnit.h"
#include "AverageFilterDialogFormUnit.h"
#include "OSRFormUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChildForm *ChildForm;
TTemplates Templates;
//---------------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TChildForm::LoadImage(AnsiString FileName)
{
 try
 {
  Image1->Picture->LoadFromFile(FileName);
 }
 catch (EInvalidGraphic& Exception)
 {
  AnsiString Error = "Помилка завантаження зображення! Помилка системи: ";
  Error += Exception.Message;
  MessageBox(this->Handle, Error.c_str(), "Помилка", MB_OK | MB_ICONERROR);
  return false;
 }

 if (Image1->Picture->Bitmap->PixelFormat != pf8bit)
 {
  MessageBox(Handle,"Такий тип файлу не підтримується...",
                    "Не продумав я таке(",MB_OK | MB_ICONSTOP | MB_APPLMODAL);
  return false;
 }

 return true;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 MainForm->DeleteActiveChildForm();
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::AverageFilter()
{
 AverageFilterDialogForm = new TAverageFilterDialogForm(this);
 if (AverageFilterDialogForm->ShowModal() == mrCancel)
 {
  delete AverageFilterDialogForm;
  return;
 }

 int Value = atoi(AverageFilterDialogForm->Edit1->Text.c_str());

 delete AverageFilterDialogForm;

 Byte* PrevisionLine = NULL;
 Byte* CurrentLine = NULL;
 Byte* NextLine = NULL;
 int I = 0, J = 0;
 int Summ = 0;

 for (I = 0; I <= Image1->Picture->Bitmap->Height - 1; I++)
 {
  CurrentLine = (Byte*)Image1->Picture->Bitmap->ScanLine[I];
  for (J = 0; J <= Image1->Picture->Bitmap->Width - 1; J++)
  {
   Summ = 0;

   if (I > 0)
   {
    PrevisionLine = (Byte*)Image1->Picture->Bitmap->ScanLine[I - 1];
    if (J > 0)
    {
     Summ += PrevisionLine[J - 1];
    }

    Summ = Summ + PrevisionLine[J];

    if (J + 1 < Image1->Picture->Bitmap->Width)
    {
     Summ += PrevisionLine[J + 1];
    }
   }

   if (J > 0)
   {
    Summ += CurrentLine[J - 1];
   }

   Summ += CurrentLine[J];

   if (J + 1 < Image1->Picture->Bitmap->Width)
   {
    Summ += CurrentLine[J + 1];
   }

   if (I + 1 < Image1->Picture->Bitmap->Height)
   {
    NextLine = (Byte*)Image1->Picture->Bitmap->ScanLine[I + 1];
    if (J > 0)
    {
     Summ += NextLine[J - 1];
    }

    Summ += NextLine[J];

    if (J + 1 < Image1->Picture->Bitmap->Width)
    {
     Summ += NextLine[J + 1];
    }
   }

   if ((int)(Summ / 9) <= Value)
    CurrentLine[J] = (Byte) Summ / 9;
  }
 }
 Image1->Visible = false;
 Image1->Visible = true;
}
//---------------------------------------------------------------------------
// РВідстань між двома точками
int Distance(TVertex& V1, TVertex& V2)
{
 int a = abs(V1.Y - V2.Y);
 int b = abs(V1.X - V2.X);
 return sqrt(a*a + b*b);
}

//---------------------------------------------------------------------------
void __fastcall TChildForm::OSR()
{
 // Максимальна відстань для відтворення спрещеної фігури
 const int Treshold = 5;

 // Тут зберігається результат розпізнавання
 AnsiString Result;

 // Відладочна форма з зобреженням для роботи
 OSRForm = new TOSRForm(this);

 // Напрямок руху "жука"
 typedef enum {North, East, South, West} TDirectional;
 TDirectional Direct;     

 // Координати першої зустрічі з об'єктом
 int X,Y;

 // Тимчасово використовуємо їх для задання нового розміру робочого зображення
 X = OSRForm->Width - OSRForm->Image1->Width;
 Y = OSRForm->Height - OSRForm->Image1->Height;
 OSRForm->Image1->Picture->Bitmap->Assign(Image1->Picture->Bitmap);
 OSRForm->Width = OSRForm->Image1->Width + X;
 OSRForm->Height = OSRForm->Image1->Height + Y;
 OSRForm->Image1->Canvas->Rectangle(0, 0, OSRForm->Image1->Width - 1,
                                    OSRForm->Image1->Height - 1);

 Graphics::TBitmap* FromImage = Image1->Picture->Bitmap;
 Graphics::TBitmap* ToImage = OSRForm->Image1->Picture->Bitmap;

 // Поточні координати маркера
 int cX,cY;

 // Максимальні координати, які займає фігура
 int MaxX = 0;
 int MaxY = FromImage->Height;

 // Від цієї координати починається нове сканування по Y
 int BeginY = 0;

 // Обробка лінії
 Byte *Line, *ToLine;

 char Symb = 'А';

 // Поточний байт
 Byte B = 0;

 bool SkipMode = false;
 while (true)
 {
  // Список координат поточного об'єкту
  TShapeVector ShapeVector;
  // Тимчасова структура координат точки
  TVertex Vertex;

  // Пошук будь-якого об'єкту
  // Шукаєм до тих пір, поки не зустрінемчорну область
  for (X = MaxX; X < FromImage->Width; X++)
  {
   for (Y = BeginY; Y < MaxY; Y++)
   {
    Line = (Byte*)FromImage->ScanLine[Y];
    if (Line[X] < 255)
     goto FindedLabel;
   }

   if ((X + 1 == FromImage->Width) && (Y == FromImage->Height))
   {
    X++;
    goto FindedLabel;
   }

   // Якщо до самого правого краю, розширяєм межі пошуку донизу
   if (X + 1 == FromImage->Width)
   {
    X = 0;
    MaxX = 0;
    BeginY = MaxY;
    MaxY = FromImage->Height;
   }

  }
FindedLabel:

  // Якщо не знайшли жодного чорного пікселя, то виходимо з процедури
  if ((X == FromImage->Width) && (Y == FromImage->Height))
   break;

  // Зпочатку задача знайти максимальні межі знайденої фігури,
  // щоб потім від неї почати будувати склет
  // Також шукаєм саму верхню точку фігури, для початку будування
  int MinX = Image1->Picture->Width;  // Сама ліва координата

  MaxX = 0;
  MaxY = 0;

  // Сама верхня точка
  TVertex TopPoint;
  TopPoint.Y = Image1->Picture->Height;

  // Повертаєм наліво (новий напрямок - північ)
  cX = X;
  cY = Y - 1;

  Direct = North;
  Line = (Byte*)FromImage->ScanLine[cY];

  // Поки не прийдем в початкову точку, виділяєм контур об'єкта
  while ((cX != X) || (cY != Y))
  {
   // В залежності від поточного напрямку жука
   switch (Direct)
   {
     // Північ
    case North:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      Direct = West;
      cX--;
      // Якщо це сама ліва коордната
      if (MinX > cX)
       MinX = cX;
     }
     // Інакше повертаєм направо
     else
     {
      Direct = East;
      cX++;
      if (MaxX < cX)
       MaxX = cX;

     }
    }
    break;

    // Схід
    case East:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
      // Якщо це сама верхня точка
      if (TopPoint.Y > cY)
      {
       TopPoint.Y = cY;
       TopPoint.X = cX;
      }
     }
     // Інакше повертаєм направо
     else
     {
      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
      if (MaxY < cY)
       MaxY = cY;
     }
    }
    break;

    // Південь
    case South:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      Direct = East;
      cX++;
      if (MaxX < cX)
       MaxX = cX;
     }
     // Інакше повертаєм направо
     else
     {
      Direct = West;
      cX--;
      // Якщо це сама ліва координата
      if (MinX > cX)
       MinX = cX;
     }
    }
    break;

    // Запад
    case West:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
      if (MaxY < cY)
       MaxY = cY;
     }
     // Інакше повертаєм направо
     else
     {
      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
      // Якщо це сама верхня точка
      if (TopPoint.Y > cY)
      {
       TopPoint.Y = cY;
       TopPoint.X = cX;
      }
     }
    }
   }
  }

  TopPoint.X++;

  if ((!TopPoint.X) && (!TopPoint.Y))
  {
   TopPoint.X = X;
   TopPoint.Y = Y;
  }
  else
  {
   X = TopPoint.X;
   Y = TopPoint.Y;
  }

  // Побудова скеета
  ToLine = (Byte*)ToImage->ScanLine[Y];
  ToLine[X] = 0;

  // Повертаєи наліво (новий напрямок - південь)
  cX = X;
  cY = Y;

  Vertex.X = X;
  Vertex.Y = Y;
  ShapeVector.push_back(Vertex);

  Direct = East;
  Line = (Byte*)FromImage->ScanLine[cY];

  // Поки не прийдем в початкову точку, виділяєм контур
  do
  {
   // В залежності від поточного напрямку жука
   switch (Direct)
   {
     // Північ
    case North:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      ToLine = (Byte*)ToImage->ScanLine[cY];
      ToLine[cX] = 0;

      Vertex.X = cX;
      Vertex.Y = cY;
      if (Distance(Vertex, ShapeVector[ShapeVector.size() - 1]) >= Treshold)
       ShapeVector.push_back(Vertex);

      Direct = West;
      cX--;
     }
     // Інакше повертаєм направо
     else
     {
      Direct = East;
      cX++;
     }
    }
    break;

    // Схід
    case East:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      ToLine = (Byte*)ToImage->ScanLine[cY];
      ToLine[cX] = 0;

      Vertex.X = cX;
      Vertex.Y = cY;
      if (Distance(Vertex, ShapeVector[ShapeVector.size() - 1]) >= Treshold)
       ShapeVector.push_back(Vertex);

      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
     }
     // Інакше повертаєм направо
     else
     {
      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
     }
    }
    break;

    // Південь
    case South:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      ToLine = (Byte*)ToImage->ScanLine[cY];
      ToLine[cX] = 0;

      Vertex.X = cX;
      Vertex.Y = cY;
      if (Distance(Vertex, ShapeVector[ShapeVector.size() - 1]) >= Treshold)
       ShapeVector.push_back(Vertex);

      Direct = East;
      cX++;
     }
     // Інакше, повертаєм направо
     else
     {
      Direct = West;
      cX--;
     }
    }
    break;

    // Захід
    case West:
    {
     B = Line[cX];
     // Якщо елемент чорний, повертаєм наліво
     if (B < 255)
     {
      ToLine = (Byte*)ToImage->ScanLine[cY];
      ToLine[cX] = 0;

      Vertex.X = cX;
      Vertex.Y = cY;
      if (Distance(Vertex, ShapeVector[ShapeVector.size() - 1]) >= Treshold)
       ShapeVector.push_back(Vertex);

      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
     }
     // Інакше, повертаєм направо
     else
     {
      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
     }
    }
   }
  } while ((cX != X) || (cY != Y));

  Vertex.X = X;
  Vertex.Y = Y;
  ShapeVector.push_back(Vertex);

  ToImage->Canvas->Pen->Color = clRed;
  ToImage->Canvas->MoveTo(ShapeVector[0].X, ShapeVector[0].Y);
  for (UINT i = 1; i < ShapeVector.size(); i++)
  {
   ToImage->Canvas->LineTo(ShapeVector[i].X, ShapeVector[i].Y);
  }

  for (UINT i = 0; i < ShapeVector.size(); i++)
  {
   ShapeVector[i].X -= MinX;
   ShapeVector[i].Y -= Y;
  }

/*
  if (Symb == 'Й')
  {
   Symb++;
  }

  if (Symb == 'а')
  {
   // Symb = 'A';
   break;
  }

  if ((Symb != 'Ы') && (!SkipMode))
  {
   AnsiString FileName = ExtractFilePath(Application->ExeName) + "TPL\\";
   FileName += Symb;

   ofstream OutFile(FileName.c_str());
   for (UINT i = 0; i < ShapeVector.size(); i++)
   {
    OutFile << IntToStr(ShapeVector[i].X).c_str() << endl;
    OutFile << IntToStr(ShapeVector[i].Y).c_str() << endl;
   }
   OutFile.close();

   Symb++;
  }
  else
  {
   if (SkipMode)
   {
    SkipMode = false;
    Symb++;
   }
   else if (Symb == 'Ы')
    SkipMode = true;
  }
*/

  TTemplate* Template = FindTemplate(ShapeVector);
  if (Template)
   Result += Template->Symb;
 }

 //OSRForm->Show();
 delete OSRForm;

 Memo1->Text = Result;
}
//---------------------------------------------------------------------------
TTemplate* FindTemplate(TShapeVector Vec)
{
 TTemplate Template;
 Template.Vec = Vec;
 for (UINT i = 0; i < Templates.size(); i++)
 {
  if (Templates[i] == Template)
   return &Templates[i];
 }

 return NULL;
}
//---------------------------------------------------------------------------

