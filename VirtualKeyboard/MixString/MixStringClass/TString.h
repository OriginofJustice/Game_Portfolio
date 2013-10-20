#ifndef _TSTRING_H_
#define _TSTRING_H_
#include <tchar.h>
#include <string>
#include <Windows.h>

#define SAFE_DELETE( p )  if( p ) { delete p;  p = NULL; }


typedef TCHAR						tchar;
typedef std::basic_string< tchar >	tstring;

extern char		*	toMultiByte( const wchar_t * wBuffer );
extern char		*	toMultiByte( char * szBuffer_out, int size, const wchar_t * wBuffer_in );



#endif