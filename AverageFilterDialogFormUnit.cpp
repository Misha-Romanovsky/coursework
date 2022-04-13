//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AverageFilterDialogFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DialogFormUnit"
#pragma resource "*.dfm"
TAverageFilterDialogForm *AverageFilterDialogForm;
//---------------------------------------------------------------------------
__fastcall TAverageFilterDialogForm::TAverageFilterDialogForm(TComponent* Owner)
        : TDialogForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAverageFilterDialogForm::Edit1KeyPress(TObject *Sender,
      char &Key)
{
 if ((Key < '0') || (Key > '9'))
  Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAverageFilterDialogForm::FormShow(TObject *Sender)
{
 Edit1->SetFocus();        
}
//---------------------------------------------------------------------------
