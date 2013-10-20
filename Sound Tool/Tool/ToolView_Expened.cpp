#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"


//버튼 관련 이벤트 처리기 

void CToolView::OnPlay()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	m_pTemp = NULL;
	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine
		.m_Parser.m_pAudioBuffer.empty())
	{
		CString  temp;

		int select;
		select = m_SourceBox.GetSelectionMark();
		temp = m_SourceBox.GetItemText(select,0);

		m_pTemp = g_AudioEngine.m_Parser.m_pSourceInfo[atoi(temp)];
		m_pTemp->Position = m_vPosition;
		m_pTemp->Velocity = m_vVelocity;
		//Source_Info* pTemp1  =  g_AudioEngine.m_Parser.m_pSourceInfo[];
		ALenum result;
		if (g_AudioEngine.m_Parser.m_pSourceInfo[atoi(temp)]->attribute == VOICEFILE)
		{
			m_pTemp->Source = g_AudioEngine.m_Source.AddVoice(g_AudioEngine.m_Parser.
				m_pAudioBuffer[m_pTemp->SourceRef]->Buffer,m_pTemp);
			alSourcePlay(m_pTemp->Source); 
			g_AudioEngine.m_Source.DeleteVoice();
		}
		else if (g_AudioEngine.m_Parser.m_pSourceInfo[atoi(temp)]->attribute == WAVEFILE)
		{
			m_pTemp->Source = g_AudioEngine.m_Source.AddSource(g_AudioEngine.m_Parser.
				m_pAudioBuffer[m_pTemp->SourceRef]->Buffer,m_pTemp);
			alSourcePlay(m_pTemp->Source); 
			g_AudioEngine.m_Source.DeleteWave();
		}

		if ((result = alGetError()) != AL_NO_ERROR)
		{
			char temp[260];
			//strcpy(temp,ss.c_str());
			int kkk =1;
		}
	}
}	

void CToolView::OnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.
		m_Parser.m_pAudioBuffer.empty())
	{
		CString  temp;

		int select;
		select = m_SourceBox.GetSelectionMark();
		temp = m_SourceBox.GetItemText(select,0);

		m_pTemp = g_AudioEngine.m_Parser.m_pSourceInfo[atoi(temp)];
		alSourceStop(m_pTemp->Source);
	}
}

void CToolView::OnPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.
		m_Parser.m_pAudioBuffer.empty())
	{
		CString  temp;

		int select;
		select = m_SourceBox.GetSelectionMark();
		temp = m_SourceBox.GetItemText(select,0);

		m_pTemp = g_AudioEngine.m_Parser.m_pSourceInfo[atoi(temp)];
		alSourcePause(m_pTemp->Source);
	}
}

void CToolView::InitListener()
{
	CString temp;
	temp.Format("%.2f",m_ListenPos.x);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LPOSX,temp);

	temp.Format("%.2f",m_ListenPos.y);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LPOSY,temp);	

	temp.Format("%.2f",m_ListenPos.z);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LPOSZ,temp);

	temp.Format("%.2f",m_ListenVelo.x);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LVELOX,temp);

	temp.Format("%.2f",m_ListenVelo.y);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LVELOY,temp);	

	temp.Format("%.2f",m_ListenVelo.z);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_LVELOZ,temp);

	temp.Format("%.2f",m_ListenForward.x);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_FORWARDX,temp);

	temp.Format("%.2f",m_ListenForward.y);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_FORWARDY,temp);	

	temp.Format("%.2f",m_ListenForward.z);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_FORWARDZ,temp);

	temp.Format("%.2f",m_ListenUp.x);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_UPX,temp);

	temp.Format("%.2f",m_ListenUp.y);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_UPY,temp);	

	temp.Format("%.2f",m_ListenUp.z);
	//temp.Format("%d",m_SamplePosX.GetPos());
	SetDlgItemText(IDC_UPZ,temp);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	// Listener 셋팅 
	g_AudioEngine.m_Listener.SetListenerPos(&m_ListenPos);
	g_AudioEngine.m_Listener.SetListenerVelo(&m_ListenVelo);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward,&m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();



	m_LPosX.SetRange(0,4000);
	m_LPosY.SetRange(0,4000);
	m_LPosZ.SetRange(0,4000);
	m_LVeloX.SetRange(0,4000);
	m_LVeloY.SetRange(0,4000);
	m_LVeloZ.SetRange(0,4000);
	m_LForX.SetRange(0,4000);
	m_LForY.SetRange(0,4000);
	m_LForZ.SetRange(0,4000);
	m_LUpX.SetRange(0,4000);
	m_LUpY.SetRange(0,4000);
	m_LUpZ.SetRange(0,4000);

	m_LPosX.SetPos((UINT)((m_ListenPos.x*100.0f)+2000.0f));
	m_LPosY.SetPos((UINT)((m_ListenPos.y*100.0f)+2000.0f));
	m_LPosZ.SetPos((UINT)((m_ListenPos.z*100.0f)+2000.0f));
	m_LVeloX.SetPos((UINT)((m_ListenVelo.x*100.0f)+2000.0f));
	m_LVeloY.SetPos((UINT)((m_ListenVelo.y*100.0f)+2000.0f));
	m_LVeloZ.SetPos((UINT)((m_ListenVelo.z*100.0f)+2000.0f));
	m_LForX.SetPos((UINT)((m_ListenForward.x*100.0f)+2000.0f));
	m_LForY.SetPos((UINT)((m_ListenForward.y*100.0f)+2000.0f));
	m_LForZ.SetPos((UINT)((m_ListenForward.z*100.0f)+2000.0f));
	m_LUpX.SetPos((UINT)((m_ListenUp.x*100.0f)+2000.0f));
	m_LUpY.SetPos((UINT)((m_ListenUp.y*100.0f)+2000.0f));
	m_LUpZ.SetPos((UINT)((m_ListenUp.z*100.0f)+2000.0f));
}

void CToolView::OnScriptExport()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	CFileDialog dlg(FALSE,"*.JST","",OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT  | OFN_FILEMUSTEXIST, 
		"J  Sound Tool(*.JST) |*.JST;|",NULL);

	if(dlg.DoModal()==IDOK)
	{ 
		CString str = dlg.GetPathName();
		char* ss = LPSTR(LPCTSTR(str));
		g_AudioEngine.m_Save.FileSave(ss, g_AudioEngine.m_Parser.m_pAudioBuffer,
			g_AudioEngine.m_Parser.m_pSourceInfo);
	}
}

void CToolView::OnBGMClick()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.
		m_Parser.m_pAudioBuffer.empty())
	{
		char temp[260];
		int select;
		int Source;
		LV_ITEM lvitem; 
		select = m_SourceBox.GetSelectionMark();
		Source =  atoi(m_SourceBox.GetItemText(select,0)) ;

		if (select >= 0)
		{
			lvitem.mask=LVIF_TEXT; 
			lvitem.iItem=select; 
			lvitem.iSubItem = 6 ; 
			g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute = BACKGROUNDMUSIC;
			{
				sprintf(temp,"BGM");
			}
			lvitem.pszText = temp; 
			m_SourceBox.SetItem(&lvitem); 
		}
	}
}

void CToolView::OnBWaveClick()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.
		m_Parser.m_pAudioBuffer.empty())
	{
		char temp[260];
		int select;
		int Source;
		LV_ITEM lvitem; 
		select = m_SourceBox.GetSelectionMark();
		Source =  atoi(m_SourceBox.GetItemText(select,0)) ;
		
		if (select >= 0)
		{
			lvitem.mask=LVIF_TEXT; 
			lvitem.iItem=select; 
			lvitem.iSubItem = 6 ; 
			g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute = WAVEFILE;
			{
				sprintf(temp,"WAVE");
			}
			lvitem.pszText = temp; 
			m_SourceBox.SetItem(&lvitem); 
		}
	}
}

void CToolView::OnVoiceClick()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	if (!g_AudioEngine.m_Parser.m_pSourceInfo.empty() && !g_AudioEngine.
		m_Parser.m_pAudioBuffer.empty())
	{
		char temp[260];
		int select;
		int Source;
		LV_ITEM lvitem; 
		select = m_SourceBox.GetSelectionMark();
		Source =  atoi(m_SourceBox.GetItemText(select,0)) ;
		
		if (select >= 0)
		{
			lvitem.mask=LVIF_TEXT; 
			lvitem.iItem=select; 
			lvitem.iSubItem = 6 ; 
			g_AudioEngine.m_Parser.m_pSourceInfo[Source]->attribute = VOICEFILE;
			{
				sprintf(temp,"Voice");
			}
			lvitem.pszText = temp; 
			m_SourceBox.SetItem(&lvitem); 
		}
	}
}