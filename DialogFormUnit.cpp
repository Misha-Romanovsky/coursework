//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialogFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDialogForm *DialogForm;
//---------------------------------------------------------------------------
__fastcall TDialogForm::TDialogForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
