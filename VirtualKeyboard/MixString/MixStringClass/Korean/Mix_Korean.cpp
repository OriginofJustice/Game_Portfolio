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
	// Desc :	������ �׷����� �ִ� ��ư�� Ŭ�� ������ 
	//=======================================================================
	int		MixKorean::InputChild( int Child )
	{
		CharacterCheck( );
		// �̹� �Էµ� ���ڰ� �־��� ��� (����)

		// �߼��� �Է� �Ǿ����� Ȯ���ؼ� ������ ���� ���� ���� ����Ѵ�. 
		if ( m_KorChar[ 0 ]	== -1	&&	m_KorChar[ 1 ]	!=	-1 )
		{
			// �Է¹��� ���� ����Ѵ�
			m_StoregeCh			= Child + 4352;
			return	1;
		}

		// ���� �Է��ϴ� ���ڰ� �ʼ��� ��� 
		if ( m_KorChar[ 0 ]	== -1 )
		{
			m_ResultChar		= Child + 4352;
			m_StoregeCh			= Child + 4352;
			m_KorChar[ 0 ]		= Child;
			return	0;
		}

		if ( m_KorChar[ 1 ]	== -1 )
		{
			// �Է¹��� ���� ����Ѵ�
			m_StoregeCh			= Child + 4352;
			return	1;
		}

		// �߼��� �Է� �Ǿ��� ��� �������� �Է� ���ش�.
		if ( m_KorChar[ 3 ]	== -1 )
		{
			// �������� �Է�
			if ( MakeLastChild( Child ) )
			{
				m_KorReslutFi	= MakeJaum( Child );
				m_KorChar[ 3 ]	= m_KorReslutFi;
				m_StoregeCh		= Child + 4352;
				m_ResultChar	= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	m_KorReslutFi + 44032;

				return 0;

			}
			// �������� �Է� �ɼ� ���� ����
			else
			{
				m_ResultChar	= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	44032;

				// �ѱ��� �Է� ���ټ� �ִ� ���·� ����� 
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

		// ������ ������ �������� �Ǵ�
		if ( MixChild( Child ) )
		{
			m_KorChar[ 4 ]		= Child;

			//  ���� ����
			Mix_Last_Child( );

			m_ResultChar		= ( m_KorChar[ 0 ] * 588 )	+	( m_KorReslutMo * 28 )	+	m_KorReslutFi	+	44032;

		}

		else
		{
			// ���� ���� ������ְ� �Էµ� ���ڸ� ���� ���ڷ� ������ش�. 
			m_StoregeCh			= Child	+	4352;
			return 1;
		}
		return 0;
	}

	//=======================================================================
	// Name :	InputMother
	//
	// Desc :	������ �Է��� �Ǿ�����...
	//=======================================================================
	int		MixKorean::InputMother( int Mother )
	{
		CharacterCheck( );
		// �ʼ��� �Է��� �ȵǾ��� ���
		if ( m_KorChar[ 0 ]	==	-1 )
		{
			// �׷��� ������ �Է� �Ǿ� ���� ���
			if ( m_KorChar[ 1 ]	!=	-1 )
			{
				//	���� ��������?
				if ( MixMother( Mother ) )
				{
					//	���� ���ڿ� ������ �ΰ��� ���յ� ������ ��� 
					if ( m_KorReslutMo	!=	m_KorChar[ 1 ] )
					{
						m_StoregeCh		=	Mother		+	4449;
						return 2;
					}
					// ������ �����Ѱ�� 
					else
					{
						m_KorChar[ 2 ]	=	Mother;
						// ����
						Mix_Mother( );
						m_ResultChar	=	m_KorReslutMo	+	4449;
						return 0;
					}
				}
				// ���յ� �Ұ��� �ϴ� ���� ���ڷ� �Է����ش�.
				else
				{
					//m_ResultChar		=	Mother	+	4449;
					m_StoregeCh			=	Mother	+	4449;
					m_KorChar[ 1 ]		=	Mother;
					m_KorReslutMo		=	Mother;
					return	4 ;
				}
			}
			// ó�� ���� �Ҷ� �̰ų� �����̽�Ű�� ���� 
			else
			{
				m_ResultChar			=	Mother + 4449;
				m_StoregeCh				=	m_ResultChar;
				m_KorChar[ 1 ]			=	Mother;
				m_KorReslutMo			=	Mother;
				return	0;
			}
		}

		// �ʼ��� �Է� �Ǿ��� ���
		if ( m_KorChar[ 1 ]	==	-1 )
		{
			m_KorChar[ 1 ]				=	Mother;
			m_KorReslutMo				=	Mother;
			m_ResultChar				=	( m_KorChar[0] * 588 )	+	( m_KorReslutMo * 28 )	+	44032;
			return 0; 
		}
		//  ������ �ԷµǾ� ���� ���
		if ( m_KorChar[ 3 ]	!=	-1)
		{
			m_StoregeCh					=	Mother	+	4449;
			return 2;
		}

		// �߼��� �ϼ��Ǿ� �Է� �Ǿ� ������� 
		if ( m_KorChar[ 2 ]	!=	-1 )
		{
			m_StoregeCh					=	Mother	+	4449;
			return 2;
		}
		// �ʼ��Է� �Ǿ� �ְ� ������ ������ �����Ѱ��
		if ( MixMother( Mother )	)
		{
			// ������ �Ѵ�. 
			m_KorChar[ 2 ]				=	Mother;

			// ����
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
	// Desc :	�������� ����Ҽ� ���� ���ڸ� Ȯ���Ѵ�. 
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
	// Desc :	������ ������ ���߿� �Էµ� ������ ������ �Ǵ��� Ȯ���� �Ѵ�.
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
	// Desc :	�ΰ��� ������ ���� ������ �������� Ȯ���� �Ѵ�. 
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
	// Desc :	�ΰ��� ������ ���� �����Ѵ�. 
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
	// Desc :	�ΰ��� ������ ���� �����Ѵ�. 
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
	// Desc :	�⺻������ ������ �ʼ��� �������� �����ڵ带 ����ϱ⿡ 
	//			������ �´� �ڵ�� �ٲٴ� �κ�
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
	// Desc :	�������� ���� ������ �ʼ����� ����� ��  �ֵ���
	//			������ش�.
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
	// Desc :	���յǴ� ���ڰ� ��� �ִ��� Ȯ���Ѵ�. 
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
	// Desc :	���յǴ� ���ڿ� �߸��� ���� �Է��� ��� �� ���� �ʱ�ȭ ���ش�
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
	// Desc :	���� �����ϰ� �ִ� ���ڰ� ���� �� ��� �ϳ��� �ڸ������ �����ش�.
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

