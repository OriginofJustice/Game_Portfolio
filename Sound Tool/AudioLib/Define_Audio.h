#pragma once
#ifndef _DIFINE_AUDIO_H
#define _DIFINE_AUDIO_H

#include "..\OpenAL\include\al.h"
#include "..\OpenAL\include\alc.h"
#include "..\OpenAL\include\Ogg\os_types.h"
#include "..\OpenAL\include\Ogg\ogg.h"
//#include "..\OpenAL\include\Vorbis\vorbisenc.h"
#include "..\OpenAL\include\Vorbis\vorbisfile.h"
#include "..\OpenAL\include\alut.h"

//  STL 사용하기 위한 헤더 호출
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#include <Windows.h>
#include <TCHAR.H>
#include <cstdlib>
#include <time.h>
#include <conio.h>

#include <mmsystem.h>
//#include <sys/types.h>
//#include <sys/timeb.h>
// IME  
#include <imm.h>
#include <objbase.h>
#include <dimm.h>
#include <D3D9.H>
#include <D3DX9.H>
#include <D3dx9math.h>
#include <DXErr9.h>
#include <d3d9types.h>
#include <tchar.h>
#include <crtdbg.h>
#include <cassert>


// 라이브러리 호출


#pragma comment		(lib, "..\\OpenAL\\lib\\OpenAL32.lib")
#pragma comment		(lib, "..\\OpenAL\\lib\\alut.lib")
#pragma comment		(lib, "..\\OpenAL\\lib\\ogg.lib")
#pragma comment		(lib, "..\\OpenAL\\lib\\vorbis.lib")
#pragma comment		(lib, "..\\OpenAL\\lib\\vorbisenc.lib")
#pragma comment		(lib, "..\\OpenAL\\lib\\vorbisfile.lib")

#pragma comment		(lib, "ws2_32.lib")

#pragma comment		(lib, "dxguid.lib")
#pragma comment		(lib, "d3d9.lib")
#pragma comment		(lib, "d3dx9.lib")

#pragma warning(disable : 4786)
#pragma warning(disable : 4267)
#pragma warning(disable : 4101)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)

extern ALCdevice*	g_pAudioDevice;
extern ALCcontext*	g_pAudioContext;

#define BACKGROUNDMUSIC					0
#define	WAVEFILE						1
#define VOICEFILE						2

#define	BUFFER_SIZE		(4096*16)


#define ALMOST_ZERO 1.0e-3f
#define SAFE_ZERO(A)				{ A = 0; }
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }

#define SAFE_ARRAY_NEW(A, B, C)		{ if (!A && C) A = new B[C]; }
#define SAFE_ARRAY_DEL(A)			{ if (A) delete [] A; (A)=NULL; }
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#define NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
// Error codes


enum SET_DATA_TYPES
{
	// Gameplay semantics
	NULL_DATA	= 0,
	BOOL_DATA,
	INT_DATA,
	FLOAT_DATA,
	STRING_DATA,
	VERTEX_DATA,
	FACE_DATA,
	MATRIX_DATA,
	TGI_DATA,
	GIS_DATA,
	FXI_DATA,
};


#ifdef _DEBUG
static VOID TraceString( TCHAR* strMsg, ... )
{
#if defined(DEBUG) | defined(_DEBUG)
	TCHAR strBuffer[512];

	va_list args;
	va_start(args, strMsg);
	_vsntprintf( strBuffer, 512, strMsg, args );
	va_end(args);

	OutputDebugString( strBuffer );
#else
	UNREFERENCED_PARAMETER(strMsg);
#endif
}
#ifdef _DEBUG
#define DXTRACE           TraceString
#else
#define DXTRACE           sizeof
#endif
#define	DEBUGMSG(lpText)															\
{																						\
	static char szBuffer[256];															\
	sprintf(szBuffer, "[File: %s][Line: %d]\n[Note : %s]", __FILE__, __LINE__, lpText);	\
	MessageBox(NULL, szBuffer, "ERROR", MB_ICONERROR);									\
	_ASSERT(1);																			\
	_asm {																				\
	int 3																			\
}																					\
}
#else
#define DEBUGMSG(lpText)
#endif

struct  Source_Info
{
	UINT		attribute;
	int			SourceID;
	int			SourceRef;
	float		Picth;
	float		Gain;
	D3DXVECTOR3	Position;
	D3DXVECTOR3	Velocity;
	BOOL		Loop;
	ALuint		Source;
};

struct Audio_Header
{
	int BufferNum;
	int SourceNum;
};

struct Audio_BufferHouse
{
	int		BufferID;
	char	BufferName[260];
	ALuint	Buffer;
	int		BufferType;
};


struct OggData
{
	int		id;
	char	BufferName[260];
	char	BufferPath[260];
};

struct SOggFile
{
	char* dataPtr;    // Pointer to the data in memory
	int   dataSize;   // Size of the data
	int   dataRead;   // How much data we have read so far
};
extern SOggFile oggMemoryFile;

#endif