#include "stdafx.h"
#include "MixStringClass/Key_Input.h"



#include "MixStringClass/Korean/Mix_Korean.h"
#include "MixStringClass/English/English_OutPut.h"





namespace Virtual_Keyboard
{

	//////////////////////////////////////////////////////////////////////////

	CKey_Input::CKey_Input(void)
		: m_pVSString	( new VSString)
		, m_pMix		( new MixKorean )
		, m_pEnglish	( new MixEnglish )
	{
		m_pVSString->Clear();
	}

	//////////////////////////////////////////////////////////////////////////


	CKey_Input::~CKey_Input( void )
	{
		SAFE_DELETE( m_pVSString );
		SAFE_DELETE( m_pMix );
		SAFE_DELETE( m_pEnglish );
	}


	//=======================================================================
	// Name :	AddString
	//
	// Desc :	2바이트로 입력된 언어의 글자를 출력해주는 처리를 한다. 
	//=======================================================================

	void	CKey_Input::AddString( int Language, int Index , bool	Jamo)
	{
		int		state = MIXRESULT_OK ;

		switch( Language )
		{
			// 한국어일경우
			case LANGUAGE_KOREAN:
				if (Jamo)
				{
					state = m_pMix->InputChild( Index );
				}
				else
				{
					state = m_pMix->InputMother( Index );
				}
				break;

		}
		InputException( state );
	}


	//=======================================================================
	// Name :	BackSpace
	//
	// Desc :	백스페이스를 눌렀을시 문자열 삭제 
	//=======================================================================

	void	CKey_Input::BackSpace( )
	{
		if ( !m_pMix->ResetCheck() )
			m_pMix->BackSpace();
		else
			m_pVSString->Backspace( );
	}


	//=======================================================================
	// Name :	Space
	//
	// Desc :	공백 문자 추가한다.
	//=======================================================================

	void	CKey_Input::Space( )
	{
		// 이전에 한글을 입력해주던 중이었다면 한글을 문자열에 강제로 추가 시킨다. 
		EnforceKoreanInput( );

		tstring		Space;
		Space.clear( );
		Space.push_back( L' ' );
		m_pVSString->AddString( toMultiByte( Space.c_str( ) ), static_cast< unsigned int > ( Space.size() ) );
	}

	//=======================================================================
	// Name :	EnforceKoreanInput
	//
	// Desc :	한글 문자가 완성 되지 않았음에도 불구하고 강제 입력한다.
	//=======================================================================

	void	CKey_Input::EnforceKoreanInput()
	{
		tstring		KoreanChar;
		if ( m_pMix->ResetCheck( ) )
		{
		}
		else
		{
			KoreanChar = m_pMix->ResultCharacter( );
			m_pVSString->AddString( toMultiByte( KoreanChar.c_str() ) , 2 );
			m_pMix->Reset( );
		}
	}


	//=======================================================================
	// Name :	AddChar
	//
	// Desc :	영문자의 추가
	//=======================================================================

	void	CKey_Input::AddChar(int Index, bool bSize)
	{
		EnforceKoreanInput();
		tchar Tempch = m_pEnglish->ReturnAlphabet( bSize, Index );
		m_pVSString->AddChar(  toMultiByte( & Tempch )[0] );
	}



	//=======================================================================
	// Name :	Number_Input
	//
	// Desc :	숫자 및 기호의 추가 
	//=======================================================================

	void	CKey_Input::Number_Input(  int Index )
	{
		EnforceKoreanInput();
		tchar Tempch = m_pEnglish->ReturnNumber( Index );
		m_pVSString->AddChar(  toMultiByte( & Tempch )[0] ) ;	
	}

	//=======================================================================
	// Name :	InputException
	//
	// Desc :	키 입력을 받았을때 각종 예외 상황들을 처리한다. 
	//=======================================================================
	void	CKey_Input::InputException( int State )
	{
		tstring		ExceString;
		ExceString		=	m_pMix->ResultCharacter( );
		switch(State)
		{
		case MIXRESULT_OK:
			// 정상일 경우 아무일도 하지 않는다. 
			break;
		case MIXRESLUT_ADDJAUM:
			// 이전 글자가 완성되어 있는 상태에서 다음 글자가 자음 하나로 표기 될때 사용한다. 
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			m_pMix		->		JaUmInput( ) ;
			break;
		case MIXRESLUT_ADDMOUM:
			// 첫 글자가 모음으로 문자열에 추가되어야 할 경우 사용된다. 
			m_pMix		->		ResultAfter( );
			ExceString	=		m_pMix->ResultCharacter( );
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			m_pMix		->		AfterJaum( );
			m_pMix		->		MoUmInput( );
			break;
		case MIXRESLUT_TEMP:
			// ?? 사용하지 않음  임시용 예외처리 코드 
			m_pMix		->		ResultAfter( );
			ExceString	=		m_pMix->ResultCharacter( );
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			break;
		case MIXRESLUT_NOTMIX:
			// 초성이 입력이 안 되었으면서 이전 글자가 모음만으로 이루어 지고 이전 글자와 현재 글자가 조합이 되지 않을 경우
			m_pMix		->		ResultAfter( );
			m_pVSString	->		AddString(toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			m_pMix		->		AfterJaum( );
			m_pMix		->		MoUmInput( );
			break;
		default:
			break;
		}
	}


	//=======================================================================
	// Name :	AsciiCodeInput
	//
	// Desc :	아스키 코드 관련 문자 추가
	//=======================================================================

	void		CKey_Input::AsciiCodeInput(int Index)
	{
		EnforceKoreanInput();
		m_pVSString->AddChar( static_cast < char > (Index) ) ;
		//tchar Tempch = m_pEnglish->ReturnAscii( Index );
		//m_pVSString->AddChar(  toMultiByte ( &Tempch )[0] ) ;	
	}


	TCHAR		CKey_Input::GetTempChar()
	{
		return m_pMix->ResultCharacter();
	}


	//=======================================================================
	// Name :	UniCodeCharAdd
	//
	// Desc :	유니 코드 관련 문자 추가
	//=======================================================================

	void		CKey_Input::UniCodeCharAdd(tchar TempChar)
	{
		EnforceKoreanInput();
		m_pVSString->AddString( toMultiByte( &TempChar ) , 2 );
	}
}

