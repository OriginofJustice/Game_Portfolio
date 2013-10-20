#pragma once

//#include <string>
//#include <tchar.h>

#include "MixStringClass/tstring.h"


//////////////////////////////////////////////////////////////////////////



namespace Virtual_Keyboard
{
	enum 
	{
		MIXRESULT_OK = 0,
		MIXRESLUT_ADDJAUM,
		MIXRESLUT_ADDMOUM,
		MIXRESLUT_TEMP,
		MIXRESLUT_NOTMIX,

		MIXRESLUT_MAX
	};

	//=======================================================================
	// Name :	CMix_Korean
	//
	// Desc :	한글 자음 모음로 조합을 행하는 클래스
	//=======================================================================
	class MixKorean
	{
		int				m_KorChar[ 5 ];
		tchar			m_KorReslutMo;
		tchar			m_KorReslutFi;
		tchar			m_ResultChar;

		int				m_TempCharacter;

		tchar			m_StoregeCh;


	public:
		MixKorean(void);
		virtual ~MixKorean(void);

		tchar			ResultCharacter( )								{ return m_ResultChar; }
		int				InputChild	(	int		Child	);
		int				InputMother	(	int		Mother	);

		bool			MakeLastChild(	int		Kchar	);
		bool			MixChild	(	int		Kchar	);
		bool			MixMother	(	int		Kchar	);

		void			Mix_Last_Child( );
		void			Mix_Mother( );

		tchar			MakeJaum	(	int		Kchar	);

		void			UnMakeJaum( int		Jaum);

		void			JaUmInput( );
		void			MoUmInput( );

		void			ResultAfter( );

		void			AfterJaum( );

		void			Reset( );

		bool			ResetCheck( );
		void			CharacterCheck( );

		bool			OnlyMoumMix();
		bool			BackSpace();

	};

}

