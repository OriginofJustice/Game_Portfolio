#include "stdafx.h"
#include "MixStringClass//Korean/Mix_Korean.h"



//////////////////////////////////////////////////////////////////////////


namespace Virtual_Keyboard
{
	//////////////////////////////////////////////////////////////////////////
	MixKorean::MixKorean(void)
		: m_ResultChar		( 0 )
		, m_KorReslutMo		( 0 )
		, m_KorReslutFi		( 0 )
		, m_TempCharacter	( -1)
		, m_StoregeCh		( 0 )
	{
		Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	MixKorean::~MixKorean(void)
	{
	}


	//=======================================================================
	// Name :	Reset
	//
	// Desc :	
	//=======================================================================
	void	MixKorean::Reset( )
	{
		for (	int i = 0 ;	 i < 5 ;	i++ )
		{
			m_KorChar[ i ]		= -1;
		}
		m_KorReslutMo			= 0;
		m_KorReslutFi			= 0;
		m_ResultChar			= 0;
	}

	//=======================================================================
	// Name :	InputChild
	//
	// Desc :	자음이 그려저져 있는 버튼을 클릭 했을때 
	//=======================================================================
	int		MixKorean::InputChild( int Child )
	{
		CharacterCheck( );
		// 이미 입력된 글자가 있었을 경우 (모음)

		// 중성이 입력 되었는지 확인해서 없으면 지금 현재 글자 출력한다. 
		if ( m_KorChar[ 0 ]	== -1	&&	m_KorChar[ 1 ]	!=	-1 )
		{
			// 입력받은 글자 출력한다
			m_StoregeCh			= Child + 4352;
			return	1;
		}

		// 지금 입력하는 글자가 초성인 경우 
		if ( m_KorChar[ 0 ]	== -1 )
		{
			m_ResultChar		= Child + 4352;
			m_StoregeCh			= Child + 4352;
			m_KorChar[ 0 ]		= Child;
			return	0;
		}

		if ( m_KorChar[ 1 ]	== -1 )
		{
			// 입력받은 글자 출력한다
			m_StoregeCh			= Child + 4352;
			return	1;
		}

		// 중성이 입력 되었을 경우 종성으로 입력 해준다.
		if ( m_KorChar[ 3 ]	== -1 )
		{
			// 종성으로 입력
			if ( MakeLastChild( Child ) )
			{
				m_KorReslutFi	= MakeJaum( Child );
				m_KorChar[ 3 ]	= m_KorReslutFi;
				m_StoregeCh		= Child + 4352;
				m_ResultChar	= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	m_KorReslutFi + 44032;

				return 0;

			}
			// 종성으로 입력 될수 없는 글자
			else
			{
				m_ResultChar	= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	44032;

				// 한글자 입력 해줄수 있는 상태로 만들것 
				m_StoregeCh		= Child	+	 4352;

				return	1;
			}
		}
		if ( m_KorChar[4]		!= -1 )
		{
			m_ResultChar		= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	m_KorReslutFi	+	44032;
			m_StoregeCh		= Child	+	 4352;
			return 1;
		}

		// 조합이 가능한 글자인지 판단
		if ( MixChild( Child ) )
		{
			m_KorChar[ 4 ]		= Child;

			//  종성 조합
			Mix_Last_Child( );

			m_ResultChar		= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	m_KorReslutFi	+	44032;

		}

		else
		{
			// 현재 글자 출력해주고 입력된 글자를 다음 글자로 출력해준다. 
			m_StoregeCh			= Child	+	4352;
			return 1;
		}
		return 0;
	}

	//=======================================================================
	// Name :	InputMother
	//
	// Desc :	모음이 입력이 되었을때...
	//=======================================================================
	int		MixKorean::InputMother( int Mother )
	{
		CharacterCheck( );
		// 초성이 입력이 안되었을 경우
		if ( m_KorChar[ 0 ]	==	-1 )
		{
			// 그런데 모음이 입력 되어 있을 경우
			if ( m_KorChar[ 1 ]	!=	-1 )
			{
				//	조합 가능한지?
				if ( MixMother( Mother ) )
				{
					//	현재 글자에 모음이 두개가 조합된 모음일 경우 
					if ( m_KorReslutMo	!=	m_KorChar[ 1 ] )
					{
						m_StoregeCh		=	Mother		+	4449;
						return 2;
					}
					// 조합이 가능한경우 
					else
					{
						m_KorChar[ 2 ]	=	Mother;
						// 조합
						Mix_Mother( );
						m_ResultChar	=	m_KorReslutMo	+	4449;
						return 0;
					}
				}
				// 조합도 불가능 하니 다음 글자로 입력해준다.
				else
				{
					//m_ResultChar		=	Mother	+	4449;
					m_StoregeCh			=	Mother	+	4449;
					m_KorChar[ 1 ]		=	Mother;
					m_KorReslutMo		=	Mother;
					return	4 ;
				}
			}
			// 처음 시작 할때 이거나 스페이스키를 눌러 
			else
			{
				m_ResultChar			=	Mother + 4449;
				m_StoregeCh				=	m_ResultChar;
				m_KorChar[ 1 ]			=	Mother;
				m_KorReslutMo			=	Mother;
				return	0;
			}
		}

		// 초성만 입력 되었을 경우
		if ( m_KorChar[ 1 ]	==	-1 )
		{
			m_KorChar[ 1 ]				=	Mother;
			m_KorReslutMo				=	Mother;
			m_ResultChar				=	( m_KorChar[0] * 588 )	+	( m_KorReslutMo * 28 )	+	44032;
			return 0; 
		}
		//  종성이 입력되어 있을 경우
		if ( m_KorChar[ 3 ]	!=	-1)
		{
			m_StoregeCh					=	Mother	+	4449;
			return 2;
		}

		// 중성이 완성되어 입력 되어 있을경우 
		if ( m_KorChar[ 2 ]	!=	-1 )
		{
			m_StoregeCh					=	Mother	+	4449;
			return 2;
		}
		// 초성입력 되어 있고 모음과 조합이 가능한경우
		if ( MixMother( Mother )	)
		{
			// 조합을 한다. 
			m_KorChar[ 2 ]				=	Mother;

			// 조합
			Mix_Mother( );

			m_ResultChar				=	( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	44032;
			return 0;
		}
		else
		{
			m_StoregeCh					=	Mother	+	4449;
			return 2;
		}
		return  0;
	}

	//=======================================================================
	// Name :	MakeLastChild
	//
	// Desc :	종성으로 사용할수 없는 글자를 확인한다. 
	//=======================================================================

	bool	MixKorean::MakeLastChild( int Kchar )
	{
		if (	Kchar	==	4	||	Kchar	==	8	||	Kchar	==	13	)
			return false;

		return true;
	}


	//=======================================================================
	// Name :	MixMother
	//
	// Desc :	이전에 모음이 나중에 입력된 모음과 조합이 되는지 확인을 한다.
	//=======================================================================
	bool	MixKorean::MixMother( int Kchar )
	{
		switch( m_KorChar[ 1 ] )
		{
		case 8:
			if (	Kchar	==	0	||	Kchar	==	1	||	Kchar	==	20	)
				return true;
			break;
		case 13:
			if (	Kchar	==	4	||	Kchar	==	5	||	Kchar	==	20 )
				return true;
			break;
		case 18:
			if (	Kchar	==	20 )
				return true;
			break;
		default:
			break;
		}
		return false;
	}


	//=======================================================================
	// Name :	MixChild
	//
	// Desc :	두개의 자음이 서로 조합이 가능한지 확인을 한다. 
	//=======================================================================

	bool	MixKorean::MixChild( int Kchar )
	{
		switch( m_KorChar[ 3 ] )
		{
		case 1:
			if (	Kchar	==	9	)
				return true;

			break;
		case 4:
			if (	Kchar	==	12	||	Kchar	==	18	)
				return true;

			break;
		case 8:
			if (	Kchar	==	0	||	Kchar	==	6	||	Kchar	==	7	|| 	Kchar	==	9	||
					Kchar	==	16	||	Kchar	==	17	||	Kchar	==	18	)
				return true;

			break;
		case 17:
			if (	Kchar	==	9	)
				return true;

			break;
		}
		return false;
	}


	//=======================================================================
	// Name :	Mix_Last_Child
	//
	// Desc :	두개의 자음을 서로 조합한다. 
	//=======================================================================

	void	MixKorean::Mix_Last_Child( )
	{
		switch( m_KorChar[ 3 ] )
		{
		case 1:				if ( m_KorChar[ 4 ]	==	9  )				m_KorReslutFi	= 3;				break;
		case 4:				if ( m_KorChar[ 4 ]	==	12 )				m_KorReslutFi	= 5;
							if ( m_KorChar[ 4 ]	==	18 )				m_KorReslutFi	= 6;				break;
		case 8:				if ( m_KorChar[ 4 ]	==	0  )				m_KorReslutFi	= 9;
							if ( m_KorChar[ 4 ]	==	6  )				m_KorReslutFi	= 10;
							if ( m_KorChar[ 4 ]	==	7  )				m_KorReslutFi	= 11;
							if ( m_KorChar[ 4 ]	==	9  )				m_KorReslutFi	= 12;
							if ( m_KorChar[ 4 ]	==	16 )				m_KorReslutFi	= 13;
							if ( m_KorChar[ 4 ]	==	17 )				m_KorReslutFi	= 14;
							if ( m_KorChar[ 4 ]	==	18 )				m_KorReslutFi	= 15;				break;
		case 17:			if ( m_KorChar[ 4 ]	==	9  )				m_KorReslutFi	= 18;				break;
		default:																							break;
		}
	}

	//=======================================================================
	// Name :	Mix_Mother
	//
	// Desc :	두개의 모음을 서로 조합한다. 
	//=======================================================================

	void	MixKorean::Mix_Mother()
	{
		switch( m_KorChar[ 1 ] )
		{
		case 8:				if ( m_KorChar[ 2 ]	==	0  )			m_KorReslutMo	= 9;
							if ( m_KorChar[ 2 ]	==	1  )			m_KorReslutMo	= 10;
							if ( m_KorChar[ 2 ]	==	20 )			m_KorReslutMo	= 11;				break;
		case 13:			if ( m_KorChar[ 2 ]	==	4  )			m_KorReslutMo	= 14;
							if ( m_KorChar[ 2 ]	==	5  )			m_KorReslutMo	= 15;
							if ( m_KorChar[ 2 ]	==	20 )			m_KorReslutMo	= 16;				break;
		case 18:			if ( m_KorChar[ 2 ]	==	20 )			m_KorReslutMo	= 19;				break;
		default:																						break;
		}
	}


	//=======================================================================
	// Name :	MakeJaum
	//
	// Desc :	기본적으로 자음을 초성을 바탕으로 유니코드를 사용하기에 
	//			종성에 맞는 코드로 바꾸는 부분
	//=======================================================================

	TCHAR	MixKorean::MakeJaum( int Kchar )
	{
		TCHAR	temp = -1;
		switch( Kchar )
		{
		case 0:
		case 1:				temp	=	Kchar + 1;			break;
		case 2:				temp	=	4;					break;
		case 3:				temp	=	7;				    break;
		case 5:				temp	=	8;				    break;
		case 6:				temp	=	16;					break;
		case 7:				temp	=	17;					break;
		case 9:
		case 10:
		case 11:
		case 12:			temp	=	Kchar +10;			break;
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:			temp	=	Kchar + 9;			break;
		default:											break;
		}
		return temp;
	}

	//=======================================================================
	// Name :	UnMakeJaum
	//
	// Desc :	종성으로 들어갔던 자음을 초성에서 사용할 수  있도록
	//			만들어준다.
	//=======================================================================

	void	MixKorean::UnMakeJaum( int	Jaum )
	{
		switch( Jaum )
		{
		case 1:				m_TempCharacter		= 0;							break;
		case 2:				m_TempCharacter		= 1;							break;
		case 4:				m_TempCharacter		= 2;							break;
		case 7:				m_TempCharacter		= 3;							break;
		case 8:				m_TempCharacter		= 5;							break;
		case 16:			m_TempCharacter		= 6;							break;
		case 17:			m_TempCharacter		= 7;							break;
		case 19:
		case 20:
		case 21:
		case 22:			m_TempCharacter		= Jaum	-10;					break;
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:			m_TempCharacter		= Jaum - 9;						break;
		default:																break;
		}
	}

	//=======================================================================
	// Name :	JaUmInput
	//
	// Desc :	
	//=======================================================================

	void	MixKorean::JaUmInput( )
	{
		m_ResultChar		= m_StoregeCh;
		m_KorChar[ 0 ]		= m_StoregeCh - 4352;
		m_StoregeCh			= NULL;
	}


	//=======================================================================
	// Name :	MoUmInput
	//
	// Desc :	
	//=======================================================================

	void	MixKorean::MoUmInput( )
	{
		if ( m_StoregeCh	== NULL )
		{
			m_KorChar[ 1 ]	= -1;
		}
		else
		{
			m_KorChar[ 1 ]	= m_StoregeCh - 4449;
			m_KorReslutMo	= m_KorChar[ 1 ];
		}

		if ( m_KorChar[ 1 ]	== -1)
		{
			m_ResultChar	= NULL;
		}
		else if (m_KorChar[ 0 ] == -1)
		{
			m_ResultChar	= m_StoregeCh;

		}
		else
		{
			m_ResultChar	= ( m_KorChar[ 0 ]*588 ) + ( m_KorChar[ 1 ] * 28 ) + 44032;
		}
		m_StoregeCh			= NULL;
	}


	//=======================================================================
	// Name :	ResultAfter
	//
	// Desc :	
	//=======================================================================

	void	MixKorean::ResultAfter( )
	{
		if (m_KorChar[ 4 ]	!= -1)
		{
			m_TempCharacter		= m_KorChar[ 4 ] ;
			m_KorReslutFi		= m_KorChar[ 3 ];
			m_KorChar[ 4 ]		= -1;

			m_ResultChar		= ( m_KorChar[ 0 ] * 588 ) + ( m_KorReslutMo * 28 ) + m_KorReslutFi + 44032;

		}
		else if ( m_KorChar[ 3 ]	!= -1)
		{
			UnMakeJaum( m_KorChar [ 3 ] );
			//m_TempCharacter		= m_KorChar [ 3 ];
			m_KorChar[ 3 ]		= -1;
			m_ResultChar		= ( m_KorChar[ 0 ] * 588 ) + ( m_KorReslutMo * 28 )  + 44032;
		}
	}

	//=======================================================================
	// Name :	AfterJaum
	//
	// Desc :	
	//=======================================================================

	void	MixKorean::AfterJaum( )
	{
		//UnMakeJaum( );

		m_KorChar[ 0 ]			= m_TempCharacter;

		m_TempCharacter			= -1;
	}

	//=======================================================================
	// Name :	ResetCheck
	//
	// Desc :	조합되는 문자가 비어 있는지 확인한다. 
	//=======================================================================

	bool	MixKorean::ResetCheck( )
	{
		for (	int i = 0	;	i < 5	;	i++	)
		{
			if ( m_KorChar[ i ]	!= -1	)
				return false;
		}
		return true;
	}


	//=======================================================================
	// Name :	CharacterCheck
	//
	// Desc :	조합되는 문자에 잘못된 값을 입력할 경우 그 값을 초기화 해준다
	//=======================================================================

	void	MixKorean::CharacterCheck( )
	{
		for (	int i = 0	;	i < 5	;	i++	)
		{
			if (	m_KorChar[ i ]	<	-1	)
				m_KorChar[ i ]	=	-1;
		}
	}

	//=======================================================================
	// Name :	OnlyMoumMix
	//
	// Desc :	
	//=======================================================================

	bool	MixKorean::OnlyMoumMix()
	{
		if (	m_KorChar[ 0 ]		==	-1	)
		{
			if (	m_KorChar[ 1 ]	!=	-1	 )
			{
				switch(m_KorChar[ 1 ])
				{
				case 8:						if ( m_KorChar[ 2 ]	== 0  )			m_KorReslutMo	= 9;
											if ( m_KorChar[ 2 ]	== 1  )			m_KorReslutMo	= 10;
											if ( m_KorChar[ 2 ]	== 20 )			m_KorReslutMo	= 11;						break;
				case 13:					if ( m_KorChar[ 2 ]	== 4  )			m_KorReslutMo	= 14;
											if ( m_KorChar[ 2 ]	== 5  )			m_KorReslutMo	= 15;
											if ( m_KorChar[ 2 ]	== 20 )			m_KorReslutMo	= 16;						break;
				case 18:					if ( m_KorChar[ 2 ]	== 20 )			m_KorReslutMo	= 19;						break;
				default:																									break;
				}
				m_ResultChar	=	m_KorReslutMo + 4449;
			}
		}
		return true;
	}

	//=======================================================================
	// Name :	BackSpace
	//
	// Desc :	현재 조합하고 있는 문자가 존재 할 경우 하나의 자모단위로 지워준다.
	//=======================================================================

	bool	MixKorean::BackSpace()
	{
		if ( m_KorChar[ 4 ] != -1 )
		{
			m_KorChar[ 4 ]		= -1;
			m_KorReslutFi		= m_KorChar[ 3 ];
			m_ResultChar		= ( m_KorChar[ 0 ]*588 ) + ( m_KorReslutMo * 28 ) + m_KorReslutFi + 44032;
			return true;
		}
		else if ( m_KorChar[ 3 ] != -1 )
		{
			m_KorChar[ 3 ]		= -1;
			m_KorReslutFi		= 0;
			m_ResultChar		= ( m_KorChar[ 0 ]*588 ) + ( m_KorReslutMo * 28 ) + 44032;
			return true;
		}
		else if ( m_KorChar[ 2 ] != -1 )
		{
			m_KorChar[ 2 ]		= -1;
			if	( m_KorChar[ 0 ] != -1 )
			{
				m_KorChar[ 2 ]		= -1;
				m_KorReslutMo		= m_KorChar[ 1 ];
				m_ResultChar		= ( m_KorChar[ 0 ]*588 ) + ( m_KorReslutMo * 28 ) + 44032;
			}
			else
			{
				m_KorReslutMo		= m_KorChar[ 1 ];
				m_ResultChar		= m_KorReslutMo	+ 4449;
			}
			return true;
		}
		else if ( m_KorChar[ 1 ] != -1 )
		{
			m_KorChar[ 1 ] = -1;
			if	( m_KorChar[ 0 ] != -1 )
			{
				m_ResultChar		= m_KorChar[ 0 ] +4352;
			}
			else
			{
				m_ResultChar		= NULL;
				Reset();
			}
			return true;
		}
		else if ( m_KorChar [ 0 ] != -1)
		{
			m_ResultChar		= NULL;
			Reset();
			return true;
		}
		return false;
	}
}

