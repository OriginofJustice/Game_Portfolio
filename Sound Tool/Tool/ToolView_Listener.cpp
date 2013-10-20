#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"


void CToolView::SourceInfoInput(int ref)
{		
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	g_AudioEngine.SourceInput(ref);
	SourceListInput();
	// 다이얼 로그에 추가 
}


void CToolView::OnLPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();


	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenPos.x = ((float)(m_LPosX.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenPos.x);
	SetDlgItemText(IDC_LPOSX,temp);
	g_AudioEngine.m_Listener.SetListenerPos(&m_ListenPos);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnLPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenPos.y = ((float)(m_LPosY.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenPos.y);
	SetDlgItemText(IDC_LPOSY,temp);
	g_AudioEngine.m_Listener.SetListenerPos(&m_ListenPos);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnLPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenPos.z = ((float)(m_LPosZ.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenPos.z);
	SetDlgItemText(IDC_LPOSZ,temp);
	g_AudioEngine.m_Listener.SetListenerPos(&m_ListenPos);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnLVeloX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenVelo.x = ((float)(m_LVeloX.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenVelo.x);
	SetDlgItemText(IDC_LVELOX,temp);
	g_AudioEngine.m_Listener.SetListenerVelo(&m_ListenVelo);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnLVeloY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenVelo.y = ((float)(m_LVeloY.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenVelo.y);
	SetDlgItemText(IDC_LVELOY,temp);
	g_AudioEngine.m_Listener.SetListenerVelo(&m_ListenVelo);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnLVeloZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenVelo.z = ((float)(m_LVeloZ.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenVelo.z);
	SetDlgItemText(IDC_LVELOZ,temp);
	g_AudioEngine.m_Listener.SetListenerVelo(&m_ListenVelo);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnUPX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenUp.x = ((float)(m_LUpX.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenUp.x);
	SetDlgItemText(IDC_UPX,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnUPY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenUp.y = ((float)(m_LUpY.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenUp.y);
	SetDlgItemText(IDC_UPY,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnUPZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenUp.z = ((float)(m_LUpZ.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenUp.z);
	SetDlgItemText(IDC_UPZ,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnForX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenForward.x = ((float)(m_LForX.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenForward.x);
	SetDlgItemText(IDC_FORWARDX,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnForY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenForward.y = ((float)(m_LForY.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenForward.y);
	SetDlgItemText(IDC_FORWARDY,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}

void CToolView::OnForZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	m_ListenForward.z = ((float)(m_LForZ.GetPos()-65535)-2000.0f)/100.0f;

	CString temp;
	temp.Format("%.2f",m_ListenForward.z);
	SetDlgItemText(IDC_FORWARDZ,temp);
	g_AudioEngine.m_Listener.SetListenerOrien(&m_ListenForward, &m_ListenUp);
	g_AudioEngine.m_Listener.SetListener();
	*pResult = 0;
}
