#include "StdAfx.h"
#include ".\audiomanager.h"

AudioManager	g_AudioEngine;
UINT			g_nState;
int				g_OggID;


/**
 * \par 메소드 설명
 스레드를 만들어서 OGG 파일을 재생하기 위해서 클래스 내부의 데이터가 필요하기에 
 클레스 내부의 함수를 호출하기 위해 사용하는 함수 
 * \param lpPara AudioManager클래스의 void* 형
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
 * \par 메소드 설명
 장치의 초기화를 담당하는 메소드를 호출하고 OGG파일을 재생할 스레드를 생성한다.
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
//	 릴리즈  함수 
//	 사용했던 장치를 모두 해제 시켜준다. 
//--------------------------------------------------
/**
 * \par 메소드 설명
 사용했던 장치를 모두 해제 시켜주고 쓰레드를 닫아준다. 
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
 * \par 메소드 설명
 로드된 OGG 파일을 스트리밍 방식으로 재생하는 메소드 
 여기서는 버퍼를 2개를 사용해 로드 하고 있다.
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
 * \par 메소드 설명
 스트리밍 방식의 재생을 위해서 일정한 만큼의 데이터를 읽어와서 버퍼에 저장 시켜둔다.
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
 * \par 메소드 설명
 지금 현재 OGG 파일이 플레이 되고 있는지 아닌지를 판명 하는 함수 
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
 * \par 메소드 설명
 스트리밍 방식으로 읽어온 버퍼를 소스로 업데이트 해준다. 
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
 * \par 메소드 설명
 플레이하고자하는 OGG 데이터의 아이디를 입력받아서 
 그 OGG 파일을 로드해서 재생수 있게 상태를 바꾸어준다.
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
 * \par 메소드 설명
 OGG 데이터를 재생하는 메소드
 각 상태에 맞게 재생할 데이터가 없을 때에는 재생되지 않고
 재생 되어야 하는 데이터가 생겼을시에는 데이터를 로드한뒤에 재생을 하도록 한다. 
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
 * \par 메소드 설명
 현재 재생되고 있는 OGG 데이터를 멈추고자 할때 사용하는 함수 이다.
 * \return 
 */
bool AudioManager::Stop_BGM()
{
	g_nState = 2;
	return true;
}