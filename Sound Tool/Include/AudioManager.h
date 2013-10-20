#pragma once

#include "Audio_Engine.h"
#include "Listener.h"
#include "AudioParser.h"
#include "Audio_Source.h"
#include "Audio_Buffer.h"
#include "Audio_Save.h"


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
 * \date 2007-07-20
 *
 * \author ���ǿ�
 *
 * \par 
 * 
 * \brief 
 OpenAL�� ����� �� ����� ���̺귯���� ���ؼ� �����ϴ� Ŭ���� 
 �� OGG ������ ��쿡 ����� �����带 ����� ��Ʈ���ֹ������ ����� �ϴ� �ϵ� �ð� �ִ�. 
 *
 */
class AudioManager : public Audio_Engine
{
public:
	AudioParser			m_Parser;
	Listener			m_Listener;
	Audio_Source		m_Source;
	Audio_Buffer		m_Buffer;
	Audio_Save			m_Save;
	UINT				m_nState;


	CRITICAL_SECTION	m_cs;
	HANDLE				m_hThread;

	ALuint				m_BGMsource;


public:

	bool	Init();
	bool	Play_Music(ALuint* buffers, ALuint source);
	bool	Play_Sound();
	bool	Release();

	bool	Play_BGM(int id);
	bool	Play_BGM_Thread(/*LPVOID	arg*/);
	bool	Stop_BGM();


	bool	SourceInput(int ref);

	bool	BGMStream(ALuint buffer);
	bool	IsPlay(ALuint source);
	bool	StreamUpdate(ALuint* buffers, ALuint source);



	

public:
	AudioManager(void);
	virtual ~AudioManager(void);
};
extern AudioManager g_AudioEngine;