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
 * \par �޼ҵ� ����
 ������ �����͸� ���ڷ� �޾Ƽ� �� ���ۿ� �⺻������ ���õ� ������ �ҽ��� ����� �޼ҵ� 
 * \param buffer ���۰� ���� �Ǿ� �ִ� �迭
 * \param BufferNum ����� ������ ��ġ
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
 * \par �޼ҵ� ����
 �ҽ����� ����� ���ۿ� �ҽ��� �� ���� ����(����, ������,...) ���� �Է¹޾� �ҽ��� ����
 * \param buffer �ҽ����� ����� ����(���� �޸� �迭�� �ƴ�)
 * \param Info �ҽ����� ����ϰԵ� ������
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
 * \par �޼ҵ� ����
 �����߿��� ���� �����ͷ� üũ�� �� ���۸� �̿��ؼ� �ҽ��� ������� �� �� �� �޼ҵ带 ����Ѵ�
 AddSource�� �޼ҵ�� ������ ���� ��������� ���� �����ʹ� �ٸ� ��������� �����Ѵ�
 �̷��� ���� �����ӿ��� �ұ��ϰ� ���� �����Ϳ� �Ϲ� ������ ���� ������ 
 �ϵ��������� �ҽ��� ������ ���ù������� ������ �ֱ� �����̴�.
 OpelAL�� ��� ���� �������� 14���ε� 14���̻� �ѹ��� ����� �Ǿ� ������ BGM�ʿ� ������ ����ų�
 �߿��� ������ �ִ� �����޼����� �� �����ų� �����ٰ� ���� ������ ��Ȳ�� �߻��ϱ� �����̴�.
 �Դٰ� �ҽ��� ���������� �ϵ����������(���� ��󽺵� DE 5.1 ����) 28�� ����Ʈ���������� 256�� �ۿ� ������ 
 �Ұ����ϱ⿡ �ҽ� ������ �ϴ� �κ��� ������ ���� ���̴�. 
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
 * \par �޼ҵ� ����
 ��� ������ �ҽ����� �����Ѵ�.
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
 * \par �޼ҵ� ����
 Wave �����ͷ� ������ �ҽ��� ������ �̻� �Ѿ� ���ԵǸ� ���� ��� �Ǵ� �����Ͱ� �� ��� �ɼ� �ֵ���
 ������ ����Ǿ��� �����͵��� ������� �������ش�. 
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
 * \par �޼ҵ� ����
 ���� �����ͷ� ������ �ҽ��� ������ �̻� �Ѿ�� �Ǹ� ��������� �����ҽ��� �������ش�
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

