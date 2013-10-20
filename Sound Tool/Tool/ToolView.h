// ToolView.h : CToolView 클래스의 인터페이스
//


#pragma once
#include "MainFrm.h"
#include "afxwin.h"
#include "afxcmn.h"

class CToolView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

public:
	enum{ IDD = IDD_TOOL_FORM };

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

	CToolDoc* pDoc;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWaveImport();
	afx_msg void OnLoadScript();
	CListCtrl m_BufferBox;
	CListCtrl m_SourceBox;
	Source_Info* m_pTemp;
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnSourceInput();

	afx_msg void OnScriptExport();

	void SourceInfoInput(int ref);
	void SourceListInput();
	afx_msg void OnSourceSelect(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLoopCheak();
	afx_msg void OnPositionX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPositionY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPositionZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVelocityX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVelocityY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVelocityZ(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_LoopCheak;
	afx_msg void OnPitch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnGain(NMHDR *pNMHDR, LRESULT *pResult);
	void InitListener();

	CSliderCtrl m_Source;
	CSliderCtrl m_Gain;
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3	m_vVelocity;
	D3DXVECTOR3	m_ListenPos;
	D3DXVECTOR3 m_ListenVelo;
	D3DXVECTOR3 m_ListenForward;
	D3DXVECTOR3 m_ListenUp;

	CSpinButtonCtrl m_SamplePosX;
	CSpinButtonCtrl m_SamplePosY;
	CSpinButtonCtrl m_SamplePosZ;
	CSpinButtonCtrl m_SampleVeloX;
	CSpinButtonCtrl m_SampleVeloY;
	CSpinButtonCtrl m_SampleVeloZ;
	CSpinButtonCtrl m_LPosX;
	CSpinButtonCtrl m_LPosY;
	CSpinButtonCtrl m_LPosZ;
	CSpinButtonCtrl m_LVeloX;
	CSpinButtonCtrl m_LVeloY;
	CSpinButtonCtrl m_LVeloZ;
	CSpinButtonCtrl m_LForX;
	CSpinButtonCtrl m_LForY;
	CSpinButtonCtrl m_LForZ;
	CSpinButtonCtrl m_LUpX;
	CSpinButtonCtrl m_LUpY;
	CSpinButtonCtrl m_LUpZ;
	afx_msg void OnLPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLVeloX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLVeloY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLVeloZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUPX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUPY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUPZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnForX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnForY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnForZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBGMClick();
	afx_msg void OnBWaveClick();
	afx_msg void OnVoiceClick();
	int m_Attribute;
	CListCtrl m_BGMBuffer;
	CListCtrl m_BGMSource;
	afx_msg void OnOggInput();
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBGMSourceInput();
	afx_msg void OnBGMPlay();
	afx_msg void OnBGMExport();
	afx_msg void OnBGMStop();
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

