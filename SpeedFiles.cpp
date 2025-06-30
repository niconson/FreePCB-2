#include "stdafx.h"
#include "PathDialog.h"
#include "SpeedFiles.h"
#define MxPOS 8
extern CFreePcbApp theApp;
CArray <CString> m_ProjectFiles;


void ClearSpeedFiles( CFreePcbDoc * doc )
{
	CMenu* pMenu = &theApp.m_main;
	CMenu* smenu = pMenu->GetSubMenu(0); // file menu
	if( smenu )
	{
		CMenu* ssmenu = smenu->GetSubMenu(2); // open from project folder menu
		if( ssmenu )
		{
			while( ssmenu->GetMenuItemCount() > 3 )
			{
				// delete menu
				int pos = 0;
				CMenu*  sub[MxPOS];
				if( sub[0] = ssmenu->GetSubMenu(0) )
				{
					do
					{
						while( sub[pos+1] = sub[pos]->GetSubMenu(0) )
							pos++;
						pos--;
						if( pos >= 0 )
							sub[pos]->RemoveMenu(0,MF_BYPOSITION);	// DeleteMenu
					} while( pos >= 0 );
					sub[0]->RemoveMenu(0,MF_BYPOSITION);	// DeleteMenu
				}
				ssmenu->RemoveMenu(0,MF_BYPOSITION);	// DeleteMenu		
			}
		}
	}
	CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
	if( frm )
	{
		frm->SetMenu( &theApp.m_main );
	}
	m_ProjectFiles.RemoveAll();
}

void LoadSpeedFiles( CFreePcbDoc * doc )
{
	if( m_ProjectFiles.GetSize() )
		return;
	struct _stat buf;
	if( doc->m_parent_folder.Right(1) == "\\" )
		doc->m_parent_folder = doc->m_parent_folder.Left(doc->m_parent_folder.GetLength() - 1);
	int err = _stat( doc->m_parent_folder, &buf );//ok
	if( err && doc->m_parent_folder.GetLength() > 3 )
	{
		int isep = doc->m_app_dir.ReverseFind( '\\' );
		if( isep == -1 )
			isep = doc->m_app_dir.ReverseFind( ':' );
		if( isep == -1 )
			ASSERT(0);		// unable to parse path
		CString app = doc->m_app_dir.Left(isep+1);
		doc->m_parent_folder = app + "Projects\\";
	}
	//
	CMenu* pMenu = &theApp.m_main;
	CMenu* smenu = pMenu->GetSubMenu(0); // file menu
	int pos = 0;
	int n_menu = 0;
	int n_item = 0;
	BOOL bWorking[MxPOS];
	CFileFind finder[MxPOS];
	CString search_str[MxPOS];
	CString Path = doc->m_parent_folder;
	int CDSFileFound = 0;
	if( smenu )
	{
		CMenu* ssmenu[MxPOS];
		ssmenu[pos] = smenu->GetSubMenu(2); // open from project folder menu
		if( ssmenu )
		{
			int win = Path.Find("Windows");
			int mcnt = ssmenu[pos]->GetMenuItemCount();
			if( mcnt == 3 && win == -1 )
			{
				search_str[pos] = Path + "\\*";
				bWorking[pos] = finder[pos].FindFile( search_str[pos] );
				while ( bWorking[pos] )
				{
					bWorking[pos] = finder[pos].FindNextFile();
					CString name = finder[pos].GetFileName();
					win = max( win, name.Find("Windows") );
					if( finder[pos].IsDots() ||
						finder[pos].IsHidden() ||
						finder[pos].IsSystem() ||
						win >= 0 )
					{
					}
					else
					{
						CString fn = finder[pos].GetFilePath();
						if( !finder[pos].IsDirectory() )
						{
							if( name.Right(4) == ".fpc" )
							{
								n_item++;
								CDSFileFound = n_item;
								n_menu++;
								ssmenu[pos]->InsertMenu(0, MF_BYPOSITION, ID_FILE_OPEN_FROM_START+n_menu, name );
								m_ProjectFiles.Add( fn );
							}
						}
						else if( pos >= 0 && pos < (MxPOS-1) )
						{
							n_item++;
							MENUITEMINFO MenuItem; 
							MenuItem.cbSize=sizeof(MENUITEMINFO);
							MenuItem.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
							MenuItem.fType=MFT_STRING;
							MenuItem.fState=MFS_ENABLED;		
							MenuItem.dwTypeData = name.GetBuffer();
							MenuItem.cch = name.GetLength()+1;
							MenuItem.wID = ID_FILE_OPEN_FROM_START;//ПОПРАВИТЬ НА НУЖНЫЙ ID
							MenuItem.hSubMenu=CreatePopupMenu();
							InsertMenuItem( ssmenu[pos]->GetSafeHmenu(), 0, 1, &MenuItem );
							ssmenu[pos+1] = ssmenu[pos]->GetSubMenu(0);
							pos++;
							search_str[pos] = fn + "\\*";
							Path += ("\\" + name);	
							bWorking[pos] = finder[pos].FindFile( search_str[pos] );
						}
					}
					while( !bWorking[pos] || !ssmenu[pos] )
					{
						pos--;
						if( pos < 0 )
							break;
						if( n_item > CDSFileFound )
						{
							// delete menu
							ssmenu[pos]->RemoveMenu( 0, MF_BYPOSITION );
							n_item--;
						}
						int rf = Path.ReverseFind('\\');
						if( rf > 0 )
							Path = Path.Left(rf);
					}
					if( pos < 0 || n_menu >= (ID_FILE_OPEN_FROM_END - ID_FILE_OPEN_FROM_START) )
						break;
				}
			}
			if( win >= 0 )
				AfxMessageBox(G_LANGUAGE == 0 ? 
					"Project folder and file names cannot contain the reserved word <Windows>":
					"Имена папок и файлов проекта не могут содержать зарезервированное слово <Windows>");
		}
	}
	
	CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
	if( frm )
	{
		frm->SetMenu( &theApp.m_main );
		if( doc->m_project_open == 0 )
			frm->DisableMenuItems( &theApp.m_main );
	}
}

void SelectFolder( CFreePcbDoc * doc )
{
	CPathDialog dlg(G_LANGUAGE == 0 ? "Select Folder" : "Выбор папки", 
					G_LANGUAGE == 0 ? "Select default project folder" : "Выберите папку", doc->m_parent_folder );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		doc->m_parent_folder = dlg.GetPathName();
		ClearSpeedFiles( doc );
		LoadSpeedFiles( doc );
		doc->SaveOptions();
	}
}

void RunSpeedFile( CFreePcbDoc * doc, int CMD )
{
	UINT m_file_index = CMD - ID_FILE_OPEN_FROM_START - 1;
	if( m_file_index >= m_ProjectFiles.GetSize() )
		return;
	doc->FileOpen( LPCTSTR( m_ProjectFiles.GetAt(m_file_index) ) );
}