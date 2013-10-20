#pragma once

#include "TString.h"
#include "VSString.h"

#include <string>

typedef TCHAR						tchar;
typedef std::basic_string< tchar >	tstring;






namespace Virtual_Keyboard
{
	class MixKorean;
	class MixEnglish;

}




namespace Virtual_Keyboard
{

	//=======================================================================
	// Name :	CKey_Input
	//
	// Desc :	이벤트를 입력 받았을 경우 지정된 문자열에 글자를 추가해주는 클래스
	//=======================================================================

	enum  
	{
		LANGUAGE_ENGLISH,
		LANGUAGE_KOREAN,

		LANGUAGE_MAX
	};
	class CKey_Input
	{
		VSString				*	m_pVSString;



		Virtual_Keyboard::MixKorean				*	m_pMix;
		Virtual_Keyboard::MixEnglish			*	m_pEnglish;



	public:
		CKey_Input(void);
		virtual ~CKey_Input(void);

		void							AddChar					( int Index , bool	bSize);
		void							AddString				( int Language, int	Index , bool bJamo ); 

		void							BackSpace				( );
		void							Space					( );

		void							Number_Input			( int Index );

		void							AsciiCodeInput			( int Index );

		void							EnforceKoreanInput		( );

		void							InputException			( int State );

		void							UniCodeCharAdd			( tchar TempChar );


		VSString		*				GetIME					( )											{ return m_pVSString;  }
		std::string						GetString				( )											
		{ 
			return m_pVSString->GetString();
		}
		TCHAR							GetTempChar				( );
	};
}


