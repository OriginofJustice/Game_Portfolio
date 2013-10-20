#include "StdAfx.h"
#include "Audio_Engine.h"


ALCdevice*	g_pAudioDevice;
ALCcontext*	g_pAudioContext;

Audio_Engine::Audio_Engine(void)
{
	g_pAudioDevice	= NULL;
	g_pAudioContext = NULL;
	memset(m_szDeviceName ,NULL, sizeof(ALCubyte));
	strcpy(m_szDeviceName, "DirectSound3D");
}

Audio_Engine::~Audio_Engine(void)
{
}

/**
 * \par 메소드 설명
 DirectX 의 3D 좌표계를 이용해 오디오 디바이스와 오디오 컨텍스트를 생성한다. 
 단 사운드 카드에서 OpenAL이 지원되지 않으면 디바이스 생성은 실패하게 된다.
 * \return 성공시 AL_TRUE  실패시 AL_FALSE
 */
ALboolean Audio_Engine::CreateAudioDevice()
{
	g_pAudioDevice = alcOpenDevice(m_szDeviceName);
	g_pAudioContext = alcCreateContext(g_pAudioDevice, NULL);
	alcMakeContextCurrent(g_pAudioContext);

	if(alcGetError(g_pAudioDevice) != ALC_NO_ERROR)
		return AL_FALSE;

	alGetError(); // Clear the bit.

	return AL_TRUE;

}

/**
 * \par 메소드 설명
 오디오 디바이스와 컨텍스트를 해제 시켜주는 구문이다. 
 * \return 
 */
bool Audio_Engine::ReleaseDevice()
{

	if (g_pAudioContext !=NULL)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(g_pAudioContext);
		g_pAudioContext	= NULL;
	}
	if (g_pAudioDevice != NULL)
	{
		alcCloseDevice(g_pAudioDevice);
		g_pAudioDevice	= NULL;
	}
	return true;
}