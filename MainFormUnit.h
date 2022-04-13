//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TActionList *ActionList1;
        TStatusBar *StatusBar1;
        TAction *ExitAction;
        TOpenPictureDialog *OpenPictureDialog1;
        TAction *LoadImageAction;
        TAction *FilterAction;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        void __fastcall ExitActionExecute(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall LoadImageActionExecute(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall FilterActionExecute(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        __fastcall bool LoadImage(AnsiString FileName);
        __fastcall void DeleteActiveChildForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
