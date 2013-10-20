#include "StdAfx.h"
#include ".\audiomanager.h"

AudioManager	g_AudioEngine;
UINT			g_nState;
int				g_OggID;


/**
 * \par �޼ҵ� ����
 �����带 ���� OGG ������ ����ϱ� ���ؼ� Ŭ���� ������ �����Ͱ� �ʿ��ϱ⿡ 
 Ŭ���� ������ �Լ��� ȣ���ϱ� ���� ����ϴ� �Լ� 
 * \param lpPara AudioManagerŬ������ void* ��
 * \return 
 */
DWORD WINAPI Play_BGM_Thread(LPVOID lpPara)
{
	AudioManager*  pEngine = (AudioManager*) lpPara;
	pEngine->Play_BGM_Thread();

	return 0;
}


AudioManager::AudioManager(void)
{
	g_OggID = -1;
	g_nState = 0;
	m_BGMsource = NULL;
}

AudioManager::~AudioManager(void)
{
}

/**
 * \par �޼ҵ� ����
 ��ġ�� �ʱ�ȭ�� ����ϴ� �޼ҵ带 ȣ���ϰ� OGG������ ����� �����带 �����Ѵ�.
 * \return 
 */
bool AudioManager::Init()
{
	Audio_Engine::CreateAudioDevice();
	InitializeCriticalSection(&m_cs);
	m_hThread = CreateThread(NULL,0,::Play_BGM_Thread,(void *)this,0,0);
	return true;
}
//--------------------------------------------------
//	 ������  �Լ� 
//	 ����ߴ� ��ġ�� ��� ���� �����ش�. 
//--------------------------------------------------
/**
 * \par �޼ҵ� ����
 ����ߴ� ��ġ�� ��� ���� �����ְ� �����带 �ݾ��ش�. 
 * \return 
 */
bool AudioManager::Release()
{
	m_Parser.Release();
	if (m_BGMsource != NULL)
	{
		alSourceStop(m_BGMsource);
	}
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_cs);
	AudioManager::ReleaseDevice();
	return true;
}

bool AudioManager::Play_Sound()
{
	return true;
}

bool AudioManager::SourceInput(int ref)
{
	m_Parser.SourceInput(ref);
	return true;
}


/**
 * \par �޼ҵ� ����
 �ε�� OGG ������ ��Ʈ���� ������� ����ϴ� �޼ҵ� 
 ���⼭�� ���۸� 2���� ����� �ε� �ϰ� �ִ�.
 * \param buffers 
 * \param source 
 * \return 
 */
bool AudioManager::Play_Music(ALuint* buffers, ALuint source)
{
	if(IsPlay(source))
		return true;

	if(!BGMStream(buffers[0]))
		return false;

	if(!BGMStream(buffers[1]))
		return false;

	alSourceQueueBuffers(source, 2, buffers);
	alSourcePlay(source);
	return true;
}

/**
 * \par �޼ҵ� ����
 ��Ʈ���� ����� ����� ���ؼ� ������ ��ŭ�� �����͸� �о�ͼ� ���ۿ� ���� ���ѵд�.
 * \param buffer 
 * \return 
 */
bool AudioManager::BGMStream(ALuint buffer)
{
	char pcm[BUFFER_SIZE];
	int  size = 0;
	int  section;
	int  result;

	while(size < BUFFER_SIZE)
	{
		result = ov_read(&(m_Buffer.m_OggStream),
			pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);

		if(result > 0)
			size += result;
		else
			if(result < 0)
				m_Buffer.errorString(result);
			else
				break;
	}

	if(size == 0)
		return false;

	alBufferData(buffer, m_Buffer.m_Format, pcm, size,m_Buffer.m_pVorbis_Info->rate);
	m_Buffer.OggCheak();

	return true;
}

/**
 * \par �޼ҵ� ����
 ���� ���� OGG ������ �÷��� �ǰ� �ִ��� �ƴ����� �Ǹ� �ϴ� �Լ� 
 * \param source 
 * \return 
 */
bool AudioManager::IsPlay(ALuint source)
{
	ALenum state;

	alGetSourcei(source, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}

/**
 * \par �޼ҵ� ����
 ��Ʈ���� ������� �о�� ���۸� �ҽ��� ������Ʈ ���ش�. 
 * \param buffers 
 * \param source 
 * \return 
 */
bool AudioManager::StreamUpdate(ALuint* buffers, ALuint source)
{
	int processed;
	bool active = true;

	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

	while(processed--)
	{
		ALuint buffer;

		alSourceUnqueueBuffers(source, 1, &buffer);
		m_Buffer.OggCheak();

		active = BGMStream(buffer);

		alSourceQueueBuffers(source, 1, &buffer);
		m_Buffer.OggCheak();
	}
	return active;
}

/**
 * \par �޼ҵ� ����
 �÷����ϰ����ϴ� OGG �������� ���̵� �Է¹޾Ƽ� 
 �� OGG ������ �ε��ؼ� ����� �ְ� ���¸� �ٲپ��ش�.
 * \param id 
 * \return 
 */
bool AudioManager::Play_BGM(int id)
{
	g_OggID = id;
	g_nState = 1;
	if (g_OggID < 0)
	{
	}
	else
	{
	}
	return true;
}

/**
 * \par �޼ҵ� ����
 OGG �����͸� ����ϴ� �޼ҵ�
 �� ���¿� �°� ����� �����Ͱ� ���� ������ ������� �ʰ�
 ��� �Ǿ�� �ϴ� �����Ͱ� �������ÿ��� �����͸� �ε��ѵڿ� ����� �ϵ��� �Ѵ�. 
 * \return 
 */
bool AudioManager::Play_BGM_Thread()
{
	while(TRUE)
	{
		WaitForSingleObject(m_hThread,10);
		if (g_OggID >= 0)
		{
			if (g_nState == 1)
			{
				m_Buffer.OggFileLoad(m_Parser.m_OggData[g_OggID].BufferName);
				alGenSources(1, &m_BGMsource);
				if (!Play_Music( m_Buffer.m_buffer,  m_BGMsource))
					throw string("Ogg refused to play.");
				g_nState = 3;
			}
			if (g_nState != 0)
			{
				while(StreamUpdate(m_Buffer.m_buffer, m_BGMsource))
				{
					WaitForSingleObject(m_hThread,10);
					if (g_nState == 2)
					{
						alSourceStop(m_BGMsource);
						alDeleteSources(1, &m_BGMsource);
						m_Buffer.OggBufferClose();
						g_nState = 0;
						break;
					}
					else if (g_nState == 1)
					{
						m_Buffer.OggFileLoad(m_Parser.m_OggData[g_OggID].BufferName);
						alGenSources(1, &m_BGMsource);
						if (!Play_Music( m_Buffer.m_buffer,  m_BGMsource))
							throw string("Ogg refused to play.");
						g_nState = 3;
					}
					else if (g_nState == 3)
					{
						if (!IsPlay(m_BGMsource))
						{
							if(!Play_Music(m_Buffer.m_buffer, m_BGMsource))
							{
							}
							else
							{
							}
						}
					}
					else
					{
						int a =0;
					}
				}
			}
		}
	}
	//alDeleteSources(1, &m_BGMsource);
	//m_Buffer.OggBufferClose();
	return true;
}
/**
 * \par �޼ҵ� ����
 ���� ����ǰ� �ִ� OGG �����͸� ���߰��� �Ҷ� ����ϴ� �Լ� �̴�.
 * \return 
 */
bool AudioManager::Stop_BGM()
{
	g_nState = 2;
	return true;
}