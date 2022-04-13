//---------------------------------------------------------------------------

#ifndef ChildFormUnitH
#define ChildFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------
struct TVertex
{
 int X;
 int Y;

 TVertex()
 {
  X = 0;
  Y = 0;
 }
};
typedef std::vector<TVertex> TShapeVector;
//---------------------------------------------------------------------------
struct TTemplate
{
 TShapeVector Vec;
 char Symb;

 bool operator==(const TTemplate& Template) const
 {
  UINT Size = Vec.size();
  if (Template.Vec.size() < Size)
   Size = Template.Vec.size();
  for (UINT i = 0; i < Size; i++)
  {
   if ((Vec[i].X != Template.Vec[i].X) || (Vec[i].Y != Template.Vec[i].Y))
    return false;
  }
  return true;
 }

};
typedef std::vector<TTemplate> TTemplates;
extern TTemplates Templates;

extern TTemplate* FindTemplate(TShapeVector Vec);

//---------------------------------------------------------------------------
class TChildForm : public TForm
{
__published:	// IDE-managed Components
        TSplitter *Splitter1;
        TMemo *Memo1;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TChildForm(TComponent* Owner);
        bool __fastcall LoadImage(AnsiString FileName);
        void __fastcall AverageFilter();
        void __fastcall OSR();
};
//---------------------------------------------------------------------------
extern PACKAGE TChildForm *ChildForm;
//---------------------------------------------------------------------------
#endif
