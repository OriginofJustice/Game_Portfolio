// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "MixString.h"

namespace MixString 
{
	CMixStirng::CMixStirng()
		: m_pKeyInput ( new Virtual_Keyboard::CKey_Input )
	{

	}

	CMixStirng::~CMixStirng()
	{
		SAFE_DELETE ( m_pKeyInput );
	}



	System::String ^	CMixStirng::getString()
	{
		System::String ^ temp;

		if (m_pKeyInput->GetTempChar() == 0)
		{
			temp = gcnew System::String( m_pKeyInput->GetString().c_str() ) ;
		}
		else
		{
			std::string resultString = m_pKeyInput->GetString();
			tchar unicode_temp [16];

			memset(unicode_temp , 0 , sizeof(tchar)*16);
			unicode_temp[0]=  m_pKeyInput->GetTempChar();
			resultString += toMultiByte( unicode_temp);
			temp = gcnew System::String( resultString.c_str() ) ;
		}
		
		return temp;
	}

	void				CMixStirng::asciiCodeInput( int code )
	{
		m_pKeyInput->AsciiCodeInput( static_cast < int > ( code ) );
	}

	void				CMixStirng::BackSpace()
	{
		m_pKeyInput->BackSpace();
	}
	void				CMixStirng::Space()
	{
		m_pKeyInput->Space();
	}

	// 한글 자음 입력
	void				CMixStirng::AddKoreanJaum( int index )
	{
		m_pKeyInput->AddString( Virtual_Keyboard::LANGUAGE_KOREAN , index , true );
	}

	// 한글 모음 입력
	void				CMixStirng::AddKoreanMoum( int index )
	{
		m_pKeyInput->AddString( Virtual_Keyboard::LANGUAGE_KOREAN , index , false );
	}
}
