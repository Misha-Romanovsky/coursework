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
  AnsiString Error = "������� ������������ ����������! ������� �������: ";
  Error += Exception.Message;
  MessageBox(this->Handle, Error.c_str(), "�������", MB_OK | MB_ICONERROR);
  return false;
 }

 if (Image1->Picture->Bitmap->PixelFormat != pf8bit)
 {
  MessageBox(Handle,"����� ��� ����� �� �����������...",
                    "�� �������� � ����(",MB_OK | MB_ICONSTOP | MB_APPLMODAL);
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
// �³������ �� ����� �������
int Distance(TVertex& V1, TVertex& V2)
{
 int a = abs(V1.Y - V2.Y);
 int b = abs(V1.X - V2.X);
 return sqrt(a*a + b*b);
}

//---------------------------------------------------------------------------
void __fastcall TChildForm::OSR()
{
 // ����������� ������� ��� ���������� �������� ������
 const int Treshold = 5;

 // ��� ���������� ��������� ������������
 AnsiString Result;

 // ³�������� ����� � ����������� ��� ������
 OSRForm = new TOSRForm(this);

 // �������� ���� "����"
 typedef enum {North, East, South, West} TDirectional;
 TDirectional Direct;     

 // ���������� ����� ������� � ��'�����
 int X,Y;

 // ��������� ������������� �� ��� ������� ������ ������ �������� ����������
 X = OSRForm->Width - OSRForm->Image1->Width;
 Y = OSRForm->Height - OSRForm->Image1->Height;
 OSRForm->Image1->Picture->Bitmap->Assign(Image1->Picture->Bitmap);
 OSRForm->Width = OSRForm->Image1->Width + X;
 OSRForm->Height = OSRForm->Image1->Height + Y;
 OSRForm->Image1->Canvas->Rectangle(0, 0, OSRForm->Image1->Width - 1,
                                    OSRForm->Image1->Height - 1);

 Graphics::TBitmap* FromImage = Image1->Picture->Bitmap;
 Graphics::TBitmap* ToImage = OSRForm->Image1->Picture->Bitmap;

 // ������ ���������� �������
 int cX,cY;

 // ���������� ����������, �� ����� ������
 int MaxX = 0;
 int MaxY = FromImage->Height;

 // ³� ���� ���������� ���������� ���� ���������� �� Y
 int BeginY = 0;

 // ������� ��
 Byte *Line, *ToLine;

 char Symb = '�';

 // �������� ����
 Byte B = 0;

 bool SkipMode = false;
 while (true)
 {
  // ������ ��������� ��������� ��'����
  TShapeVector ShapeVector;
  // ��������� ��������� ��������� �����
  TVertex Vertex;

  // ����� ����-����� ��'����
  // ����� �� ��� ��, ���� �� ������������� �������
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

   // ���� �� ������ ������� ����, ��������� ��� ������ ������
   if (X + 1 == FromImage->Width)
   {
    X = 0;
    MaxX = 0;
    BeginY = MaxY;
    MaxY = FromImage->Height;
   }

  }
FindedLabel:

  // ���� �� ������� ������� ������� ������, �� �������� � ���������
  if ((X == FromImage->Width) && (Y == FromImage->Height))
   break;

  // �������� ������ ������ ���������� ��� �������� ������,
  // ��� ���� �� �� ������ �������� �����
  // ����� ����� ���� ������ ����� ������, ��� ������� ���������
  int MinX = Image1->Picture->Width;  // ���� ��� ����������

  MaxX = 0;
  MaxY = 0;

  // ���� ������ �����
  TVertex TopPoint;
  TopPoint.Y = Image1->Picture->Height;

  // �������� ����� (����� �������� - ����)
  cX = X;
  cY = Y - 1;

  Direct = North;
  Line = (Byte*)FromImage->ScanLine[cY];

  // ���� �� ������� � ��������� �����, ������� ������ ��'����
  while ((cX != X) || (cY != Y))
  {
   // � ��������� �� ��������� �������� ����
   switch (Direct)
   {
     // ϳ���
    case North:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
     if (B < 255)
     {
      Direct = West;
      cX--;
      // ���� �� ���� ��� ���������
      if (MinX > cX)
       MinX = cX;
     }
     // ������ �������� �������
     else
     {
      Direct = East;
      cX++;
      if (MaxX < cX)
       MaxX = cX;

     }
    }
    break;

    // ����
    case East:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
     if (B < 255)
     {
      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
      // ���� �� ���� ������ �����
      if (TopPoint.Y > cY)
      {
       TopPoint.Y = cY;
       TopPoint.X = cX;
      }
     }
     // ������ �������� �������
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

    // ϳ�����
    case South:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
     if (B < 255)
     {
      Direct = East;
      cX++;
      if (MaxX < cX)
       MaxX = cX;
     }
     // ������ �������� �������
     else
     {
      Direct = West;
      cX--;
      // ���� �� ���� ��� ����������
      if (MinX > cX)
       MinX = cX;
     }
    }
    break;

    // �����
    case West:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
     if (B < 255)
     {
      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
      if (MaxY < cY)
       MaxY = cY;
     }
     // ������ �������� �������
     else
     {
      Direct = North;
      cY--;
      Line = (Byte*)FromImage->ScanLine[cY];
      // ���� �� ���� ������ �����
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

  // �������� ������
  ToLine = (Byte*)ToImage->ScanLine[Y];
  ToLine[X] = 0;

  // �������� ����� (����� �������� - ������)
  cX = X;
  cY = Y;

  Vertex.X = X;
  Vertex.Y = Y;
  ShapeVector.push_back(Vertex);

  Direct = East;
  Line = (Byte*)FromImage->ScanLine[cY];

  // ���� �� ������� � ��������� �����, ������� ������
  do
  {
   // � ��������� �� ��������� �������� ����
   switch (Direct)
   {
     // ϳ���
    case North:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
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
     // ������ �������� �������
     else
     {
      Direct = East;
      cX++;
     }
    }
    break;

    // ����
    case East:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
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
     // ������ �������� �������
     else
     {
      Direct = South;
      cY++;
      Line = (Byte*)FromImage->ScanLine[cY];
     }
    }
    break;

    // ϳ�����
    case South:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
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
     // ������, �������� �������
     else
     {
      Direct = West;
      cX--;
     }
    }
    break;

    // �����
    case West:
    {
     B = Line[cX];
     // ���� ������� ������, �������� �����
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
     // ������, �������� �������
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
  if (Symb == '�')
  {
   Symb++;
  }

  if (Symb == '�')
  {
   // Symb = 'A';
   break;
  }

  if ((Symb != '�') && (!SkipMode))
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
   else if (Symb == '�')
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

