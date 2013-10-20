#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"

// 리스트 박스 관련 함수 모음집

void CToolView::SourceListInput()
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	UINT SourceSize = g_AudioEngine.m_Parser.m_pSourceInfo.size();

	char temp[50];
	LV_ITEM lvitem; 
	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem=0; 
	sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->SourceID);
	lvitem.pszText = temp;
	m_SourceBox.InsertItem(&lvitem);

	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 1 ; 
	lvitem.pszText =  
		g_AudioEngine.m_Parser.
		m_pAudioBuffer[g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->SourceRef]->BufferName; 

	m_SourceBox.SetItem(&lvitem);

	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 2 ; 
	sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->SourceRef);
	lvitem.pszText = temp; 

	m_SourceBox.SetItem(&lvitem); 

	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 3 ; 
	sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->Picth);
	lvitem.pszText = temp; 

	m_SourceBox.SetItem(&lvitem); 

	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 4 ; 
	sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->Gain);
	lvitem.pszText = temp; 

	m_SourceBox.SetItem(&lvitem); 

	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 5 ; 
	if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->Loop)
	{
		sprintf(temp,"TRUE");
	}
	else
	{
		sprintf(temp,"FALSE");
	}
	lvitem.pszText = temp; 
	m_SourceBox.SetItem(&lvitem); 
	lvitem.mask=LVIF_TEXT; 
	lvitem.iItem=0; 
	lvitem.iSubItem = 6 ; 
	if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->attribute == BACKGROUNDMUSIC)
	{
		sprintf(temp,"BGM");
	}
	else if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize-1]->attribute == WAVEFILE)
	{
		sprintf(temp,"WAVE");
	}
	else
	{
		sprintf(temp,"Voice");
	}
	lvitem.pszText = temp; 
	m_SourceBox.SetItem(&lvitem); 



	// 속성 값 입력 하기

}

void CToolView::OnSourceSelect(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	m_pTemp = NULL;
	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.m_Parser.m_pAudioBuffer.empty())
	{
		int select;
		CString  temp;
		int Source;
		select = m_SourceBox.GetSelectionMark();
		Source =  atoi(m_SourceBox.GetItemText(select,0)) ;
		temp = m_SourceBox.GetItemText(select,1);
		SetDlgItemText(IDC_BUFFERNAME, temp);

		m_Gain.SetPos((g_AudioEngine.m_Parser.m_pSourceInfo[Source]->Gain*-1.0f+2.0f)*100.0f);
		m_Source.SetPos((g_AudioEngine.m_Parser.m_pSourceInfo[Source]->Picth*-1.0f+2.0f)*100.0f);

		CButton *pCheck;



		
		if (g_AudioEngine.m_Parser.m_pSourceInfo[Source]->Loop ==TRUE)
		{
			m_LoopCheak.SetCheck(TRUE);
		}
		else
		{
			m_LoopCheak.SetCheck(FALSE);
		}

		// 속성값 셋팅
		if (g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute == BACKGROUNDMUSIC)
		{
			pCheck=(CButton *)GetDlgItem(IDC_RADIO1);
			pCheck->SetCheck(TRUE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO2);
			pCheck->SetCheck(FALSE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO3);
			pCheck->SetCheck(FALSE);
		}
		else if (g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute == WAVEFILE)
		{
			pCheck=(CButton *)GetDlgItem(IDC_RADIO1);
			pCheck->SetCheck(FALSE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO2);
			pCheck->SetCheck(TRUE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO3);
			pCheck->SetCheck(FALSE);
		}
		else if (g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute == VOICEFILE)
		{
			pCheck=(CButton *)GetDlgItem(IDC_RADIO1);
			pCheck->SetCheck(FALSE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO2);
			pCheck->SetCheck(FALSE);
			pCheck=(CButton *)GetDlgItem(IDC_RADIO3);
			pCheck->SetCheck(TRUE);
		}

	}

	*pResult = 0;
}

