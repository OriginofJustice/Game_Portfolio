#pragma once
#include "FileStream.h"

/**
 * \ingroup AudioLib
 *
 *
 * \par requirements
 * Windows XP\n
 * DirectX 9.0c\n
 * OpenAL Driver Install
 *
 * \version 1.0
 * first version
 *
 * \date 2007-07-16
 *
 * \author 정의원
 *
 * \par 
 * 
 * \brief 
 OpenAL에서 사용하는 버퍼를 관리하는 클래스 
 *
 */
class Audio_Buffer
{

public:
	char			m_szFilePath[260];
	vector<ALuint>	m_Buffer;
	vector<ALuint*>	m_OggBuffer;
	FILE*			m_pOggFile;
	OggVorbis_File	m_OggStream;
	vorbis_info*	m_pVorbis_Info;
	vorbis_comment*	m_pVorbis_Comment;

	bool	m_bOggLoad;



	FileStream	   m_StreamSrc;

	ALenum			m_Format;

	ALuint			m_buffer[2];

public:

	ALuint ScriptLoadWave(char* szName);
	string GetALErrorString(ALenum err);
	string GetALCErrorString(ALenum err);

	ALuint ImportWave(char* szName);

	ALuint	LoadSound(char* szName);

	void	AllBufferDelete();

	ALuint*  OggFileLoad(char* szName);

	string	errorString(int code);

	bool	OggBufferLoad();
	void	OggCheak();

	bool	OggBufferClose();



public:
	Audio_Buffer(void);
	~Audio_Buffer(void);
};
