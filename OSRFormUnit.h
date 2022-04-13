//---------------------------------------------------------------------------

#ifndef OSRFormUnitH
#define OSRFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOSRForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBevel *Bevel1;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TOSRForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOSRForm *OSRForm;
//---------------------------------------------------------------------------
#endif
