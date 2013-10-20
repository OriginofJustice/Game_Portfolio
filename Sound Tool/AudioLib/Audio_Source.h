#pragma once

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
 * \date 2007-07-19
 *
 * \author 정의원
 *
 * \par 
 * 
 * \brief 
 소스들을 관리하는 클래스 
 *
 */
class Audio_Source
{
public:
	list<ALuint>	m_nSource;
	list<ALuint>	m_nBGMSource;
	list<ALuint>	m_nVoiceSource;
	ALuint			m_nBGMSource1;
public:
	ALboolean AddSource(ALuint* buffer,ALuint BufferNum);
	ALuint AddSource(ALuint buffer,Source_Info* Info);
	ALuint AddVoice(ALuint buffer, Source_Info* Info);

	ALboolean AllSourceDelete();



	ALuint	AddBGM(ALuint* buffer, Source_Info* info);


	bool DeleteWave();
	bool DeleteBGM();
	bool DeleteVoice();
public:
	Audio_Source(void);
	~Audio_Source(void);
};
