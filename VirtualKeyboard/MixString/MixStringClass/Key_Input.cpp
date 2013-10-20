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
	// Desc :	2����Ʈ�� �Էµ� ����� ���ڸ� ������ִ� ó���� �Ѵ�. 
	//=======================================================================

	void	CKey_Input::AddString( int Language, int Index , bool	Jamo)
	{
		int		state = MIXRESULT_OK ;

		switch( Language )
		{
			// �ѱ����ϰ��
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
	// Desc :	�齺���̽��� �������� ���ڿ� ���� 
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
	// Desc :	���� ���� �߰��Ѵ�.
	//=======================================================================

	void	CKey_Input::Space( )
	{
		// ������ �ѱ��� �Է����ִ� ���̾��ٸ� �ѱ��� ���ڿ��� ������ �߰� ��Ų��. 
		EnforceKoreanInput( );

		tstring		Space;
		Space.clear( );
		Space.push_back( L' ' );
		m_pVSString->AddString( toMultiByte( Space.c_str( ) ), static_cast< unsigned int > ( Space.size() ) );
	}

	//=======================================================================
	// Name :	EnforceKoreanInput
	//
	// Desc :	�ѱ� ���ڰ� �ϼ� ���� �ʾ������� �ұ��ϰ� ���� �Է��Ѵ�.
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
	// Desc :	�������� �߰�
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
	// Desc :	���� �� ��ȣ�� �߰� 
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
	// Desc :	Ű �Է��� �޾����� ���� ���� ��Ȳ���� ó���Ѵ�. 
	//=======================================================================
	void	CKey_Input::InputException( int State )
	{
		tstring		ExceString;
		ExceString		=	m_pMix->ResultCharacter( );
		switch(State)
		{
		case MIXRESULT_OK:
			// ������ ��� �ƹ��ϵ� ���� �ʴ´�. 
			break;
		case MIXRESLUT_ADDJAUM:
			// ���� ���ڰ� �ϼ��Ǿ� �ִ� ���¿��� ���� ���ڰ� ���� �ϳ��� ǥ�� �ɶ� ����Ѵ�. 
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			m_pMix		->		JaUmInput( ) ;
			break;
		case MIXRESLUT_ADDMOUM:
			// ù ���ڰ� �������� ���ڿ��� �߰��Ǿ�� �� ��� ���ȴ�. 
			m_pMix		->		ResultAfter( );
			ExceString	=		m_pMix->ResultCharacter( );
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			m_pMix		->		AfterJaum( );
			m_pMix		->		MoUmInput( );
			break;
		case MIXRESLUT_TEMP:
			// ?? ������� ����  �ӽÿ� ����ó�� �ڵ� 
			m_pMix		->		ResultAfter( );
			ExceString	=		m_pMix->ResultCharacter( );
			m_pVSString	->		AddString( 	toMultiByte( ExceString.c_str( ) ) , 2 );
			m_pMix		->		Reset( );
			break;
		case MIXRESLUT_NOTMIX:
			// �ʼ��� �Է��� �� �Ǿ����鼭 ���� ���ڰ� ���������� �̷�� ���� ���� ���ڿ� ���� ���ڰ� ������ ���� ���� ���
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
	// Desc :	�ƽ�Ű �ڵ� ���� ���� �߰�
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
	// Desc :	���� �ڵ� ���� ���� �߰�
	//=======================================================================

	void		CKey_Input::UniCodeCharAdd(tchar TempChar)
	{
		EnforceKoreanInput();
		m_pVSString->AddString( toMultiByte( &TempChar ) , 2 );
	}
}

