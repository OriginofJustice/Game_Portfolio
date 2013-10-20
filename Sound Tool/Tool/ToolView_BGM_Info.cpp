#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"



void CToolView::OnOggInput()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	CFileDialog dlg(TRUE,"*.OGG","",OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT  | OFN_FILEMUSTEXIST, 
		"OGG(*.OGG) |*.OGG;|",NULL);

	if(dlg.DoModal()==IDOK)
	{ 
		CString str = dlg.GetFileName();
		CString str1 = dlg.GetPathName();

		LV_ITEM lvitem; 
		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem=0; 
		lvitem.pszText = LPSTR(LPCTSTR(str)); 
		m_BGMBuffer.InsertItem(&lvitem);

		CString  BufferID;
		UINT ID= g_AudioEngine.m_Parser.m_OggData.size();
		BufferID.Format("%d",ID);


		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem = 1 ; 
		lvitem.pszText = LPSTR(LPCTSTR(BufferID)); 

		m_BGMBuffer.SetItem(&lvitem); 
		g_AudioEngine.m_Parser.BgmDataInput( LPSTR(LPCTSTR(str1)),  LPSTR(LPCTSTR(str)));
	}
}

void CToolView::OnBGMSourceInput()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	UINT SourceSize = g_AudioEngine.m_Parser.m_OggData.size();
	int select, Source;
	select = m_BGMBuffer.GetSelectionMark();
	if (select >= 0 )
	{
		LV_ITEM lvitem;
		
	
		CString  Name = m_BGMBuffer.GetItemText(select,0);
		Source =  atoi(m_BGMBuffer.GetItemText(select,1));
		int  sourceNum;
		sourceNum = m_BGMSource.GetItemCount();

		char temp[50];
		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem=0; 
		sprintf(temp,"%d",sourceNum);
		lvitem.pszText = temp;
		m_BGMSource.InsertItem(&lvitem);

		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem = 1 ; 
		lvitem.pszText =  LPSTR(LPCTSTR(Name)); 

		m_BGMSource.SetItem(&lvitem);


		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem = 2 ; 
		sprintf(temp,"%d",Source);
		lvitem.pszText = temp; 

		m_BGMSource.SetItem(&lvitem);


		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem = 3; 
		sprintf(temp,"TRUE");

		lvitem.pszText = temp; 
		m_BGMSource.SetItem(&lvitem); 
	}
}



void CToolView::OnBGMPlay()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	int select;
	select = m_BGMSource.GetSelectionMark();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	int id  = atoi(m_BGMSource.GetItemText(select,2));
	if (select >=0)
	{
		g_AudioEngine.Play_BGM(id);
	}

	
}
