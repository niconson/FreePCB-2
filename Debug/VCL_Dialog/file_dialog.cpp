//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "fstream.h"
#include "clipbrd.hpp"
#include "file_dialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Caption = "File dialog";
ShowWindow(Application->Handle,SW_MINIMIZE);
Application->ProcessMessages();
HWND FPC = GetForegroundWindow();
OpenDialog->Title = "File dialog";
SaveDialog->Title = "File dialog";
Edit->Text = "";
Edit->PasteFromClipboard();
AnsiString A = Edit->Text;
int ALength = A.Length();

// import
if( A.SubString(1,ALength) == "cds_imp" )
        OpenDialog->Filter = "Schematic Project|*.cds|Schematic Backup|*.cds.b";
else if( A.SubString(1,ALength) == "pag_imp" )
        OpenDialog->Filter = "Schematic page|*.cds|Schematic Backup|*.cds.b";
else if( A.SubString(1,ALength) == "grp_imp" )
        OpenDialog->Filter = "Any FreePcb project file|*.fpc*";
else if( A.SubString(1,ALength) == "pic_imp" )
        OpenDialog->Filter = "JPEG color picture|*.jp*|BITMAP background picture for copying|*.bmp";
else if( A.SubString(1,ALength) == "fpc_imp" )
        OpenDialog->Filter = "FreePcb Project|*.fpc|FreePcb Backup|*.fpc.b|FreePcb Library|*.fpl";
else if( A.SubString(1,ALength) == "ses_imp" )
        OpenDialog->Filter = "Ses File|*.ses";
else if( A.SubString(1,ALength) == "mod_imp" )
        OpenDialog->Filter = "Mod File|*.mod";
else if( A.SubString(1,ALength) == "net_imp" )
        OpenDialog->Filter = "Netlist (PADSPCB)|*.net|TXT (PADSPCB)|*.txt";
else if( A.SubString(1,ALength) == "doc_imp" )
        OpenDialog->Filter = "PDF file|*.pdf|Microsoft Word file|*.docx|Word 2003|*.doc|Text file|*.txt";
else    OpenDialog->Filter = "All files|*.*";

// export
if( A.SubString(1,ALength) == "cds_exp" )
        SaveDialog->Filter = "Schematic Project|*.cds";
else if( A.SubString(1,ALength) == "grp_exp" )
        SaveDialog->Filter = "Semi-finished projects, group blocks, parts|*.*";
else if( A.SubString(1,ALength) == "dsn_exp" )
        SaveDialog->Filter = "FreeRouting App|*.dsn";
else if( A.SubString(1,ALength) == "fpc_exp" )
        SaveDialog->Filter = "FreePcb Project|*.fpc";
else if( A.SubString(1,ALength) == "net_exp" )
        SaveDialog->Filter = "Netlist (PADSPCB)|*.net|TXT (PADSPCB)|*.txt";
else    SaveDialog->Filter = "All files|*.*";

//
AnsiString pth = ExtractFilePath(Application->ExeName);
char ch[512];
ch[0] = '\0';
if( ALength )
        {
        ifstream Rpath((pth+A).c_str());
        Rpath.getline(ch,sizeof(ch));
        Rpath.close();
        }
AnsiString Text = "";
if( A.SubString(5,1) == "e" )
        {
        SaveDialog->InitialDir = ch;
        if( SaveDialog->Execute()  )
                Text = SaveDialog->FileName;
        }
else    {
        OpenDialog->InitialDir = ch;
        if( OpenDialog->Execute()  )
                Text = OpenDialog->FileName;
        }
ofstream Wr((pth+"file_dialog.pth").c_str());
Wr << Text.c_str();
Wr.close();
if( ALength && Text.Length() > 3 )
        {
        ofstream Wrm((pth+A).c_str());
        Wrm << (ExtractFilePath(Text)).c_str();
        Wrm.close();
        }
if(FPC)
        SetForegroundWindow(FPC);
exit(0);
}
//---------------------------------------------------------------------------

