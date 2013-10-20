#include "StdAfx.h"
#include "Audio_Source.h"

Audio_Source::Audio_Source(void)
{
	m_nSource.clear();
	m_nBGMSource.clear();
	m_nVoiceSource.clear();
}

Audio_Source::~Audio_Source(void)
{
}

/**
 * \par 메소드 설명
 버퍼의 데이터를 인자로 받아서 그 버퍼와 기본적으로 셋팅된 정보로 소스를 만드는 메소드 
 * \param buffer 버퍼가 저장 되어 있는 배열
 * \param BufferNum 사용할 버퍼의 위치
 * \return 
 */
ALboolean Audio_Source::AddSource(ALuint* buffer,ALuint BufferNum)
{
	ALuint Source;

	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
	{
		MessageBox(NULL,"Error generating audio source.", "Error",MB_OK);
		exit(-1);
	}
	// Position of the source sounds.
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the source sounds.
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };


	alSourcei (Source, AL_BUFFER,   buffer[BufferNum]);
	alSourcef (Source, AL_PITCH,    1.0f         );
	alSourcef (Source, AL_GAIN,     1.0f         );
	alSourcefv(Source, AL_POSITION, SourcePos    );
	alSourcefv(Source, AL_VELOCITY, SourceVel    );
	alSourcei (Source, AL_LOOPING,  AL_TRUE      );

	//alSourcePlay(Source);

	m_nSource.push_back(Source);
	return AL_TRUE;
}

/**
 * \par 메소드 설명
 소스에서 사용할 버퍼와 소스에 들어갈 각종 정보(루프, 포지션,...) 등을 입력받아 소스를 생성
 * \param buffer 소스에서 사용할 버퍼(위와 달리 배열이 아님)
 * \param Info 소스에서 사용하게될 데이터
 * \return 
 */
ALuint Audio_Source::AddSource(ALuint buffer,Source_Info* Info)
{
	ALuint Source;

	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
	{
		MessageBox(NULL,"Error generating audio source.", "Error",MB_OK);
		exit(-1);
	}
	ALfloat postemp[3];
	ALfloat velotemp[3];
	for (int i = 0; i < 3;i++)
	{
		postemp[i] = (ALfloat)Info->Position[i];
		velotemp[i] = (ALfloat)Info->Velocity[i];
	}
	alSourcei (Source, AL_BUFFER,   buffer);
	alSourcef (Source, AL_PITCH,    (ALfloat)Info->Picth);
	alSourcef (Source, AL_GAIN,     (ALfloat)Info->Gain );
	alSourcefv(Source, AL_POSITION, postemp);
	alSourcefv(Source, AL_VELOCITY, velotemp);
	if (Info->Loop == TRUE)
		alSourcei (Source, AL_LOOPING,  AL_TRUE    );
	else
		alSourcei (Source, AL_LOOPING,  AL_FALSE    );

//	alSourcePlay(Source);

	m_nSource.push_back(Source);

	return Source;
}

/**
 * \par 메소드 설명
 버퍼중에서 음성 데이터로 체크가 된 버퍼를 이용해서 소스를 만들고자 할 때 이 메소드를 사용한다
 AddSource의 메소드와 내용은 거의 비슷하지만 음성 데이터는 다른 저장공간에 저장한다
 이렇게 같은 내용임에도 불구하고 음성 데이터와 일반 음원을 나눈 이유는 
 하드웨어상으로 소스의 생성과 동시발음수의 제한이 있기 때문이다.
 OpelAL의 경우 동시 발음수가 14개인데 14개이상 한번에 재생이 되어 버리면 BGM쪽에 문제가 생기거나
 중요한 정보를 주는 음성메서지가 안 나오거나 나오다가 끊겨 버리는 상황이 발생하기 때문이다.
 게다가 소스의 생성갯수는 하드웨어적으로(사운드 블라스드 DE 5.1 기준) 28개 소프트웨어적으로 256개 밖에 생성이 
 불가능하기에 소스 생성을 하는 부분을 나누어 놓은 것이다. 
 * \param buffer 
 * \param Info 
 * \return 
 */
ALuint Audio_Source::AddVoice(ALuint buffer, Source_Info* Info)
{
	ALuint Source;

	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
	{
		MessageBox(NULL,"Error generating audio source.", "Error",MB_OK);
		exit(-1);
	}
	ALfloat postemp[3];
	ALfloat velotemp[3];
	for (int i = 0; i < 3;i++)
	{
		postemp[i] = (ALfloat)Info->Position[i];
		velotemp[i] = (ALfloat)Info->Velocity[i];
	}
	alSourcei (Source, AL_BUFFER,   buffer);
	alSourcef (Source, AL_PITCH,    (ALfloat)Info->Picth);
	alSourcef (Source, AL_GAIN,     (ALfloat)Info->Gain );
	alSourcefv(Source, AL_POSITION, postemp);
	alSourcefv(Source, AL_VELOCITY, velotemp);
	if (Info->Loop == TRUE)
		alSourcei (Source, AL_LOOPING,  AL_TRUE    );
	else
		alSourcei (Source, AL_LOOPING,  AL_FALSE    );

	//	alSourcePlay(Source);

	m_nVoiceSource.push_back(Source);

	return Source;
}

/**
 * \par 메소드 설명
 모든 생성된 소스들을 삭제한다.
 * \return 
 */
ALboolean Audio_Source::AllSourceDelete()
{
	for(list<ALuint>::iterator iter = m_nSource.begin(); iter != m_nSource.end(); iter++)
		alDeleteSources(1, &(*iter));
	for(list<ALuint>::iterator iter = m_nBGMSource.begin(); iter != m_nBGMSource.end(); iter++)
		alDeleteSources(1, &(*iter));
	for(list<ALuint>::iterator iter = m_nVoiceSource.begin(); iter != m_nVoiceSource.end(); iter++)
		alDeleteSources(1, &(*iter));
	alDeleteSources(1, &m_nBGMSource1);
	m_nSource.clear();
	m_nBGMSource.clear();
	m_nVoiceSource.clear();
	return AL_TRUE;
}



/**
 * \par 메소드 설명
 Wave 데이터로 생성한 소스가 일정수 이상 넘어 가게되면 다음 재생 되는 데이터가 잘 재생 될수 있도록
 이전에 재생되었던 데이터들을 어느정도 삭제해준다. 
 * \return 
 */
bool Audio_Source::DeleteWave()
{
	int count  = 0;
	int WaveCount = 0;
	for(list<ALuint>::iterator iter = m_nSource.begin(); iter != m_nSource.end(); iter++)
		count++;
	if (count > 150)
	{
		for(list<ALuint>::iterator iter = m_nSource.begin(); WaveCount < 100; WaveCount++)
		{
			iter = m_nSource.begin();
			alDeleteSources(1, &(*iter));	
			m_nSource.erase(iter);
		}
		

	}

	return true;
}


bool Audio_Source::DeleteBGM()
{
	int count  = 0;
	int BGMCount = 0;
	for(list<ALuint>::iterator iter = m_nBGMSource.begin(); iter != m_nBGMSource.end(); iter++)
		count++;
	if (count > 10)
	{
		for(list<ALuint>::iterator iter = m_nBGMSource.begin(); BGMCount < 6; iter++,BGMCount++)
		{
			iter = m_nBGMSource.begin();
			alDeleteSources(1, &(*iter));
			m_nBGMSource.erase(iter);
		}
	}
	return true;
}

/**
 * \par 메소드 설명
 음성 데이터로 생성된 소스가 일정수 이상 넘어가게 되면 어느정도의 음성소스를 삭제해준다
 * \return 
 */
bool Audio_Source::DeleteVoice()
{
	int count  = 0;
	int VoiceCount = 0;
	for(list<ALuint>::iterator iter = m_nVoiceSource.begin(); iter != m_nVoiceSource.end(); iter++)
		count++;
	if (count > 50)
	{
		for(list<ALuint>::iterator iter = m_nVoiceSource.begin(); VoiceCount < 25; iter++,VoiceCount++)
		{
			iter = m_nVoiceSource.begin();
			alDeleteSources(1, &(*iter));
			m_nVoiceSource.erase(iter);
		}
	}
	return true;
}

ALuint Audio_Source::AddBGM(ALuint* buffer, Source_Info* info)
{
	alGenSources(1, &m_nBGMSource1);

	alSource3f(m_nBGMSource1, AL_POSITION,        0.0, 0.0, 0.0);
	alSource3f(m_nBGMSource1, AL_VELOCITY,        0.0, 0.0, 0.0);
	alSource3f(m_nBGMSource1, AL_DIRECTION,       0.0, 0.0, 0.0);
	alSourcef (m_nBGMSource1, AL_ROLLOFF_FACTOR,  0.0          );
	alSourcei (m_nBGMSource1, AL_SOURCE_RELATIVE, AL_TRUE      );
	return true;	
}

