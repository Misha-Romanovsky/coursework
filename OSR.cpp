//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("OSR.res");
USEFORM("MainFormUnit.cpp", MainForm);
USEFORM("ChildFormUnit.cpp", ChildForm);
USEFORM("DialogFormUnit.cpp", DialogForm);
USEFORM("AverageFilterDialogFormUnit.cpp", AverageFilterDialogForm);
USEFORM("OSRFormUnit.cpp", OSRForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
