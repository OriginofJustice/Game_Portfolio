#include "stdafx.h"
#include "MixStringClass/English/English_OutPut.h"


namespace Virtual_Keyboard
{
	MixEnglish::MixEnglish()
	{

	}

	MixEnglish::~MixEnglish()
	{

	}

	tchar				MixEnglish::ReturnAlphabet(bool bLarge, int Index)
	{
		tchar				TempChar;
		if ( bLarge )		TempChar = 65;
		else				TempChar = 97;

		TempChar = TempChar + Index;
		
		return TempChar;
	}

	tchar				MixEnglish::ReturnNumber( int Index )
	{
		tchar			TempNumber;
		if	(Index == 11)
		{
			TempNumber	= 63;
			return		TempNumber; 
		}
		else if ( Index == 10 )
		{
			TempNumber	= 46;
			return		TempNumber; 
		}
		else
		{
			TempNumber	= 48 + Index;
			return		TempNumber; 
		}
	}

	tchar				MixEnglish::ReturnAscii( int Index )
	{
		tchar			TempAscii;

		if ( 127 < Index )
		{
			return 0;
		}
		TempAscii = Index;
		return	TempAscii;
	}
}
