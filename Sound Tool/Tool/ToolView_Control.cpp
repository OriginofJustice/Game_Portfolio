#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"


// 루프 버튼 체크 여부 
void CToolView::OnLoopCheak()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	m_pTemp = NULL;
	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	char temp[50];
	LV_ITEM lvitem; 
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.m_Parser.m_pAudioBuffer.empty())
	{
		int select;
		int temp2;
		char temp[260];
		select = m_SourceBox.GetSelectionMark();
		temp2 = atoi(m_SourceBox.GetItemText(select,0));
		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=select; 
		lvitem.iSubItem = 5 ; 
		int stat;
		stat = m_LoopCheak.GetCheck();
		switch(stat)
		{
		case BST_UNCHECKED:
			sprintf(temp,"FALSE");
			g_AudioEngine.m_Parser.m_pSourceInfo[temp2]->Loop = FALSE;
			break;
		case BST_CHECKED:
			sprintf(temp,"TRUE");
			g_AudioEngine.m_Parser.m_pSourceInfo[temp2]->Loop = TRUE;
			break;
		case BST_INDETERMINATE:
			sprintf(temp,"FALSE");
			g_AudioEngine.m_Parser.m_pSourceInfo[temp2]->Loop = FALSE;
			break;
		}
		lvitem.pszText = temp; 
		m_SourceBox.SetItem(&lvitem); 
	}
}



// 포지션과 속도값 체크 여부 
void CToolView::OnPositionX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float sample;
	CString temp;
	sample = ((float)(m_SamplePosX.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_POSX,temp);

	m_vPosition.x = sample;
	
	*pResult = 0;
}

void CToolView::OnPositionY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float sample;
	CString temp;
	sample = ((float)(m_SamplePosY.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	SetDlgItemText(IDC_POSY,temp);
	m_vPosition.y = sample;

	*pResult = 0;
}

void CToolView::OnPositionZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float sample;
	CString temp;
	sample = ((float)(m_SamplePosZ.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	SetDlgItemText(IDC_POSZ,temp);

	m_vPosition.z = sample;
	*pResult = 0;
}

void CToolView::OnVelocityX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float sample;
	CString temp;
	sample = ((float)(m_SampleVeloX.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	SetDlgItemText(IDC_VELOX,temp);

	m_vVelocity.x = sample;
	*pResult = 0;
}

void CToolView::OnVelocityY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float sample;
	CString temp;
	sample = ((float)(m_SampleVeloY.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	SetDlgItemText(IDC_VELOY,temp);
	m_vVelocity.y = sample;

	*pResult = 0;
}

void CToolView::OnVelocityZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	float sample;
	CString temp;
	sample = ((float)(m_SampleVeloZ.GetPos()-65535)-5000.0f)/100.0f;
	temp.Format("%.2f",sample);
	SetDlgItemText(IDC_VELOZ,temp);
	m_vVelocity.z = sample;

	*pResult = 0;
}

void CToolView::OnPitch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.m_Parser.m_pAudioBuffer.empty())
	{
		int box;
		box =  m_SourceBox.GetSelectionMark();
		if (box >= 0)
		{
			float temp;
			char temp1[260];
			temp = (((float)m_Source.GetPos()/100.0f-2.0)*-1.0f);
			CString szfloat;
			szfloat.Format("%.2f",temp);
			SetDlgItemText(IDC_PITCH,szfloat);

			CString  cstemp;
			cstemp = m_SourceBox.GetItemText(box,0);
			int SourceID;
			SourceID = atoi(cstemp);
			g_AudioEngine.m_Parser.m_pSourceInfo[SourceID]->Picth = temp;

			LV_ITEM lvitem; 
			lvitem.mask=LVIF_TEXT; 
			lvitem.iItem= box; 
			lvitem.iSubItem = 3 ; 
			sprintf(temp1,"%.2f",temp);
			lvitem.pszText = temp1; 
			m_SourceBox.SetItem(&lvitem); 
		}

	}
	*pResult = 0;
}

void CToolView::OnGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.m_Parser.m_pAudioBuffer.empty())
	{
		int box;
		box =  m_SourceBox.GetSelectionMark();
		if (box >= 0)
		{
			float temp;
			char temp1[260];
			temp = (((float)m_Gain.GetPos()/100.0f-2.0)*-1.0f);
			CString szfloat;
			szfloat.Format("%.2f",temp);
			SetDlgItemText(IDC_GAIN,szfloat);

			CString  cstemp;
			cstemp = m_SourceBox.GetItemText(box,0);
			int SourceID;
			SourceID = atoi(cstemp);
			g_AudioEngine.m_Parser.m_pSourceInfo[SourceID]->Gain = temp;

			LV_ITEM lvitem; 
			lvitem.mask=LVIF_TEXT; 
			lvitem.iItem= box; 
			lvitem.iSubItem = 4 ; 
			sprintf(temp1,"%.2f",temp);
			lvitem.pszText = temp1; 
			m_SourceBox.SetItem(&lvitem); 
		}

	}
	*pResult = 0;
}
