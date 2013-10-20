#pragma once

#include "MixStringClass/TString.h"


namespace Virtual_Keyboard
{
	//=======================================================================
	// Name :	MixEnglish
	//
	// Desc :	���� �� �ƽ�Ű�ڵ带 �Է��ϴ� Ŭ���� 
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


