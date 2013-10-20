// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CFormView)

BEGIN_MESSAGE_MAP(CToolView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolView::OnWaveImport)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolView::OnLoadScript)
	ON_BN_CLICKED(IDC_PLAY, &CToolView::OnPlay)
	ON_BN_CLICKED(IDC_STOP, &CToolView::OnStop)
	ON_BN_CLICKED(IDC_PAUSE, &CToolView::OnPause)
	ON_BN_CLICKED(IDC_SOURCEINPUT, &CToolView::OnSourceInput)
	ON_BN_CLICKED(IDC_EXPORT, &CToolView::OnScriptExport)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, &CToolView::OnSourceSelect)
	ON_BN_CLICKED(IDC_CHECK1, &CToolView::OnLoopCheak)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CToolView::OnPositionX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CToolView::OnPositionY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CToolView::OnPositionZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CToolView::OnVelocityX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CToolView::OnVelocityY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CToolView::OnVelocityZ)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CToolView::OnPitch)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CToolView::OnGain)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CToolView::OnLPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &CToolView::OnLPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CToolView::OnLPosZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &CToolView::OnLVeloX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, &CToolView::OnLVeloY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, &CToolView::OnLVeloZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN16, &CToolView::OnUPX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN17, &CToolView::OnUPY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN18, &CToolView::OnUPZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN13, &CToolView::OnForX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN14, &CToolView::OnForY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN15, &CToolView::OnForZ)
	ON_BN_CLICKED(IDC_RADIO1, &CToolView::OnBGMClick)
	ON_BN_CLICKED(IDC_RADIO2, &CToolView::OnBWaveClick)
	ON_BN_CLICKED(IDC_RADIO3, &CToolView::OnVoiceClick)
	ON_BN_CLICKED(IDC_BUTTON9, &CToolView::OnOggInput)
	ON_BN_CLICKED(IDC_BUTTON10, &CToolView::OnBGMSourceInput)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolView::OnBGMPlay)
	ON_BN_CLICKED(IDC_BUTTON7, &CToolView::OnBGMExport)
	ON_BN_CLICKED(IDC_BUTTON6, &CToolView::OnBGMStop)
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	: CFormView(CToolView::IDD)
	, m_Attribute(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

void CToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, m_BufferBox);
	DDX_Control(pDX, IDC_LIST6, m_SourceBox);
	DDX_Control(pDX, IDC_CHECK1, m_LoopCheak);
	DDX_Control(pDX, IDC_SLIDER1, m_Source);
	DDX_Control(pDX, IDC_SLIDER2, m_Gain);
	DDX_Control(pDX, IDC_SPIN1, m_SamplePosX);
	DDX_Control(pDX, IDC_SPIN2, m_SamplePosY);
	DDX_Control(pDX, IDC_SPIN3, m_SamplePosZ);
	DDX_Control(pDX, IDC_SPIN4, m_SampleVeloX);
	DDX_Control(pDX, IDC_SPIN5, m_SampleVeloY);
	DDX_Control(pDX, IDC_SPIN6, m_SampleVeloZ);
	DDX_Control(pDX, IDC_SPIN7, m_LPosX);
	DDX_Control(pDX, IDC_SPIN8, m_LPosY);
	DDX_Control(pDX, IDC_SPIN9, m_LPosZ);
	DDX_Control(pDX, IDC_SPIN10, m_LVeloX);
	DDX_Control(pDX, IDC_SPIN11, m_LVeloY);
	DDX_Control(pDX, IDC_SPIN12, m_LVeloZ);
	DDX_Control(pDX, IDC_SPIN13, m_LForX);
	DDX_Control(pDX, IDC_SPIN14, m_LForY);
	DDX_Control(pDX, IDC_SPIN15, m_LForZ);
	DDX_Control(pDX, IDC_SPIN16, m_LUpX);
	DDX_Control(pDX, IDC_SPIN17, m_LUpY);
	DDX_Control(pDX, IDC_SPIN18, m_LUpZ);
	DDX_Control(pDX, IDC_LIST2, m_BGMBuffer);
	DDX_Control(pDX, IDC_LIST1, m_BGMSource);
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}



void CToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


	LV_COLUMN lvcolumn;
	m_BufferBox.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString listcolumn[] = {_T("No"),_T("No1")};
	listcolumn[0] = "File Name";
	listcolumn[1] = "Buffer ID";

	int  width[] = {250,110};

	for(int i=0 ; i < 2 ; i++)
	{
		lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT ;
		lvcolumn.pszText = (LPSTR)(LPCTSTR)listcolumn[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];
		m_BufferBox.InsertColumn(i,&lvcolumn);
	}
	m_BufferBox.DeleteAllItems();

	m_SourceBox.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString listSource[] = {_T("No"),_T("No1"),_T("No2"),_T("No3"),_T("No4"),_T("No5"),_T("No6")};
	listSource[0] = "Source ID";
	listSource[1] = "Buffer Name";
	listSource[2] = "Buffer ID";
	listSource[3] = "Pitch";
	listSource[4] = "Gain";
	listSource[5] = "Loop";
	listSource[6] = "Attribute";
	int  Sourcewidth[] = {65,220,65,50,50,60,65};
		
	for(int i=0 ; i < 7 ; i++)
	{
		lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT ;
		lvcolumn.pszText = (LPSTR)(LPCTSTR)listSource[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = Sourcewidth[i];
		m_SourceBox.InsertColumn(i,&lvcolumn);
	}
	m_SourceBox.DeleteAllItems();

	m_BGMBuffer.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString BGMBuffer[] = {_T("No"),_T("No1")};
	BGMBuffer[0] = "File Name";
	BGMBuffer[1] = "Buffer ID";

	int  BGMBufferwidth[] = {250,110};

	for(int i=0 ; i < 2 ; i++)
	{
		lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT ;
		lvcolumn.pszText = (LPSTR)(LPCTSTR)BGMBuffer[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = BGMBufferwidth[i];
		m_BGMBuffer.InsertColumn(i,&lvcolumn);
	}
	m_BGMBuffer.DeleteAllItems();


	m_BGMSource.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString BGMSource[] = {_T("No"),_T("No1"),_T("No2"),_T("No3")};
	BGMSource[0] = "Source ID";
	BGMSource[1] = "Buffer Name";
	BGMSource[2] = "Buffer ID";
	BGMSource[3] = "Loop";

	int  BGMSourcewidth[] = {80,300,70,70};

	for(int i=0 ; i < 4 ; i++)
	{
		lvcolumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT ;
		lvcolumn.pszText = (LPSTR)(LPCTSTR)BGMSource[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = BGMSourcewidth[i];
		m_BGMSource.InsertColumn(i,&lvcolumn);
	}
	m_BGMSource.DeleteAllItems();


	m_Source.SetRange(0,200);
	m_Source.SetPos(100);


	m_Gain.SetRange(0,200);
	m_Gain.SetPos(100);



	memset(m_vPosition, 0, sizeof(D3DXVECTOR3));
	memset(m_vVelocity, 0, sizeof(D3DXVECTOR3));
	memset(m_ListenPos, 0, sizeof(D3DXVECTOR3));
	memset(m_ListenVelo, 0, sizeof(D3DXVECTOR3));
	memset(m_ListenForward, 0, sizeof(D3DXVECTOR3));
	memset(m_ListenUp, 0, sizeof(D3DXVECTOR3));

	m_ListenForward.z = -1.0f;
	m_ListenUp.y = 1.0f;

	m_SamplePosX.SetRange(0,10000);
	m_SamplePosX.SetPos(5000);
	m_SamplePosY.SetRange(0,10000);
	m_SamplePosY.SetPos(5000);
	m_SamplePosZ.SetRange(0,10000);
	m_SamplePosZ.SetPos(5000);

	m_SampleVeloX.SetRange(0,10000);
	m_SampleVeloX.SetPos(5000);
	m_SampleVeloY.SetRange(0,10000);
	m_SampleVeloY.SetPos(5000);
	m_SampleVeloZ.SetRange(0,10000);
	m_SampleVeloZ.SetPos(5000);

	InitListener();
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기

void CToolView::OnWaveImport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();


	CFileDialog dlg(TRUE,"*.Wav","",OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, "Wave File(*.Wav) |*.Wav;|",NULL);

	if(dlg.DoModal()==IDOK)
	{ 
		CString str = dlg.GetPathName();
		CString str2 = dlg.GetFileName();

		LV_ITEM lvitem; 
		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem=0; 
		lvitem.pszText = LPSTR(LPCTSTR(str2)); 
		m_BufferBox.InsertItem(&lvitem);

		CString  BufferID;
		UINT ID= g_AudioEngine.m_Parser.m_BufferManager.m_Buffer.size();
		BufferID.Format("%d",ID);
			
		
		lvitem.mask=LVIF_TEXT; 
		lvitem.iItem=0; 
		lvitem.iSubItem = 1 ; 
		lvitem.pszText = LPSTR(LPCTSTR(BufferID)); 

		
		m_BufferBox.SetItem(&lvitem); 


		char* ss = LPSTR(LPCTSTR(str)); 
		char* temp = LPSTR(LPCTSTR(str2));
		g_AudioEngine.m_Parser.BufferImport(ss, temp);

		//m_BufferBox.SetItemText(0,0,str2);
		//m_BufferBox.SetItemText(0,1,"1");



	}
}

void CToolView::OnLoadScript()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	CFileDialog dlg(TRUE,"*.JST","",OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, "Sound Tool Script File(*.JST) |*.JST;|",NULL);

	if(dlg.DoModal()==IDOK)
	{ 
		CString str = dlg.GetPathName();
		CString str2 = dlg.GetFileName();
		char* ss = LPSTR(LPCTSTR(str)); 
		char* temp = LPSTR(LPCTSTR(str2));
		UINT BufferSize = g_AudioEngine.m_Parser.m_pAudioBuffer.size();
		UINT SourceSize = g_AudioEngine.m_Parser.m_pSourceInfo.size();
		int  Buffer;
		int Source;
		

		g_AudioEngine.m_Parser.AudioLoader(ss);
		// 버퍼 사이즈 만큼 버퍼가 추가
		// 버퍼에 올라와 있는 데이터가 있을 때
		Buffer = m_BufferBox.GetItemCount();
		if (BufferSize  == 0)
		{
			for ( UINT  i = 0; i < g_AudioEngine.m_Parser.m_pAudioBuffer.size(); i++)
			{
				LV_ITEM lvitem; 
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem=0; 
				lvitem.pszText = g_AudioEngine.m_Parser.m_pAudioBuffer[BufferSize+i]->BufferName;
				m_BufferBox.InsertItem(&lvitem);

				char temp[50];
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 1 ; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pAudioBuffer[BufferSize+i]->BufferID);
				lvitem.pszText = temp; 
				m_BufferBox.SetItem(&lvitem); 
			}
		}
		else
		{
			for ( UINT  i = 0; i < g_AudioEngine.m_Parser.m_pAudioBuffer.size()-1; i++)
			{
				LV_ITEM lvitem; 
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem=0; 
				lvitem.pszText = g_AudioEngine.m_Parser.m_pAudioBuffer[BufferSize+i]->BufferName;
				m_BufferBox.InsertItem(&lvitem);

				char temp[50];
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 1 ; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pAudioBuffer[BufferSize+i]->BufferID);
				lvitem.pszText = temp; 
				m_BufferBox.SetItem(&lvitem); 
			}
		}
		
		Source = m_SourceBox.GetItemCount();
		// 소스 사이즈 만큼 소스 추가 

		if (SourceSize  == 0)
		{
			for (UINT  i = 0;  i < g_AudioEngine.m_Parser.m_pSourceInfo.size(); i++)
			{
				char temp[50];
				LV_ITEM lvitem; 
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem=0; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceID);
				lvitem.pszText = temp;
				m_SourceBox.InsertItem(&lvitem);

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 1 ; 
				lvitem.pszText =  
					g_AudioEngine.m_Parser.
					m_pAudioBuffer[g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceRef]->BufferName; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 2 ; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceRef);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 3 ; 
				sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Picth);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 4 ; 
				sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Gain);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 5 ; 
				if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Loop)
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
				if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->attribute == BACKGROUNDMUSIC)
				{
					sprintf(temp,"BGM");
				}
				else if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->attribute == WAVEFILE)
				{
					sprintf(temp,"WAVE");
				}
				else
				{
					sprintf(temp,"Voice");
				}
				lvitem.pszText = temp; 
				m_SourceBox.SetItem(&lvitem); 

			}
		}
		else
		{
			for (UINT  i = 0;  i < g_AudioEngine.m_Parser.m_pSourceInfo.size()-1; i++)
			{
				char temp[50];
				LV_ITEM lvitem; 
				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem=0; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceID);
				lvitem.pszText = temp;
				m_SourceBox.InsertItem(&lvitem);


				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 1 ; 
				lvitem.pszText =  
				g_AudioEngine.m_Parser.
					m_pAudioBuffer[g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceRef]->BufferName; 

				m_SourceBox.SetItem(&lvitem);

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 2 ; 
				sprintf(temp,"%d",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->SourceRef);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 3 ; 
				sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Picth);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 4 ; 
				sprintf(temp,"%.2f",g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Gain);
				lvitem.pszText = temp; 

				m_SourceBox.SetItem(&lvitem); 

				lvitem.mask=LVIF_TEXT; 
				lvitem.iItem=0; 
				lvitem.iSubItem = 5 ; 
				if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->Loop)
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
				if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->attribute == BACKGROUNDMUSIC)
				{
					sprintf(temp,"BGM");
				}
				else if (g_AudioEngine.m_Parser.m_pSourceInfo[SourceSize+i]->attribute == WAVEFILE)
				{
					sprintf(temp,"WAVE");
				}
				else
				{
					sprintf(temp,"Voice");
				}
				lvitem.pszText = temp; 
				m_SourceBox.SetItem(&lvitem); 


			}
		}

	}
}

void CToolView::OnSourceInput()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	m_pTemp = NULL;
	// Document 를 얻어온다 

	pDoc = (CToolDoc*)pFrame->GetActiveDocument();
	CString  temp;

	int select;
	select = m_BufferBox.GetSelectionMark();

	if ( select < 0)
	{

	}
	else
	{

		CString  temp;
		temp = m_BufferBox.GetItemText(select,1);
		SourceInfoInput(atoi(temp));
	}
}






LRESULT CToolView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::DefWindowProc(message, wParam, lParam);
}


void CToolView::OnBGMExport()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Document 를 얻어온다 
	pDoc = (CToolDoc*)pFrame->GetActiveDocument();

	CFileDialog dlg(FALSE,"*.BGM","",OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT  | OFN_FILEMUSTEXIST, 
		"BGM Tool(*.BGM) |*.BGM;|",NULL);

	if(dlg.DoModal()==IDOK)
	{ 
		CString str = dlg.GetPathName();
		char* ss = LPSTR(LPCTSTR(str));
		g_AudioEngine.m_Save.FileBgmExport(ss, g_AudioEngine.m_Parser.m_OggData);
	}
}

void CToolView::OnBGMStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	g_AudioEngine.Stop_BGM();
}
