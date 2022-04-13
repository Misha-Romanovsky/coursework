//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream.h>
#include "MainFormUnit.h"
#include "ChildFormUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitActionExecute(TObject *Sender)
{
 if (MessageBox(this->Handle, "Ви хочете вийти з програми?", "Вийти",
     MB_YESNO | MB_ICONQUESTION) == IDYES)
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caNone;
 ExitAction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadImageActionExecute(TObject *Sender)
{
 if (OpenPictureDialog1->Execute())
 {
  this->LoadImage(OpenPictureDialog1->FileName);
 }
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::LoadImage(AnsiString FileName)
{
 TChildForm* ChildForm = new TChildForm(this);
 if (!ChildForm->LoadImage(FileName))
 {
  delete ChildForm;
  return false;
 }
 return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteActiveChildForm()
{
 delete this->ActiveMDIChild;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender)
{
 this->DeleteActiveChildForm();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FilterActionExecute(TObject *Sender)
{
 ChildForm = (TChildForm*)this->ActiveMDIChild;
 ChildForm->AverageFilter();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N9Click(TObject *Sender)
{
 ChildForm = (TChildForm*)this->ActiveMDIChild;
 ChildForm->OSR();
}
//---------------------------------------------------------------------------
void LoadTemplate(char Symb, AnsiString& FileName)
{
 char Buf[256];
 TTemplate Template;
 TVertex Vertex;
 ifstream InFile(FileName.c_str());
 if (InFile.is_open())
 {
  while (!InFile.eof())
  {
   InFile >> Buf;
   Vertex.X = atoi(Buf);
   InFile >> Buf;
   Vertex.Y = atoi(Buf);
   Template.Symb = Symb;
   Template.Vec.push_back(Vertex);
  }
  InFile.close();
  Templates.push_back(Template);
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
 AnsiString Path = ExtractFilePath(Application->ExeName) + "TPL\\";
 AnsiString FileName;

 for (char Symb = 'A'; Symb <= 'Z'; Symb++)
 {
  FileName = Path + Symb;
  LoadTemplate(Symb, FileName);
 }

 for (char Symb = 'А'; Symb <= 'Я'; Symb++)
 {
  FileName = Path + Symb;
  LoadTemplate(Symb, FileName);
 }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N6Click(TObject *Sender)
{
        ChildForm->Memo1->Lines->SaveToFile("result.txt");
              
}
//---------------------------------------------------------------------------

