//---------------------------------------------------------------------------

#ifndef DialogFormUnitH
#define DialogFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDialogForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TDialogForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDialogForm *DialogForm;
//---------------------------------------------------------------------------
#endif
