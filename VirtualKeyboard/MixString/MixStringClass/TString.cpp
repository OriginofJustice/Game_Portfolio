#include "stdafx.h"
#include "TString.h"

char	*	toMultiByte( char * szBuffer_out, int size, const wchar_t * wBuffer_in )
{
	WideCharToMultiByte( 949, WC_COMPOSITECHECK, wBuffer_in, static_cast< int >( wcslen( wBuffer_in ) + 1 ), szBuffer_out, size, NULL, NULL );

	return szBuffer_out;
}


char	*	toMultiByte( const wchar_t * wBuffer )
{
	static char s_szBuffer[ 2048 ];

	ZeroMemory( s_szBuffer, sizeof( char ) * 2048 );

	return toMultiByte( s_szBuffer, 2048, wBuffer );
}