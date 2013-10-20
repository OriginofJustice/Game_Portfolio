#pragma once

#include "MixStringClass/TString.h"


namespace Virtual_Keyboard
{
	//=======================================================================
	// Name :	MixEnglish
	//
	// Desc :	영어 및 아스키코드를 입력하는 클래스 
	//			
	//=======================================================================
	class MixEnglish
	{
	public:
		MixEnglish(void);
		virtual ~MixEnglish(void);

		tchar							ReturnAlphabet	( bool		bLarge , int		Index);
		tchar							ReturnNumber	( int Index );
		tchar							ReturnAscii		( int Index );
	};
}


