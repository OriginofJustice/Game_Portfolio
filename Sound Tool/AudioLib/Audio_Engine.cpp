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
 * \par �޼ҵ� ����
 DirectX �� 3D ��ǥ�踦 �̿��� ����� ����̽��� ����� ���ؽ�Ʈ�� �����Ѵ�. 
 �� ���� ī�忡�� OpenAL�� �������� ������ ����̽� ������ �����ϰ� �ȴ�.
 * \return ������ AL_TRUE  ���н� AL_FALSE
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
 * \par �޼ҵ� ����
 ����� ����̽��� ���ؽ�Ʈ�� ���� �����ִ� �����̴�. 
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