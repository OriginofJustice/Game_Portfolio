#pragma once
#include "AudioParser.h"

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
 * \date 2007-07-15
 *
 * \author 정의원
 *
 * \par 
 * 
 * \brief 
 오디오 디바이스의 생성과 소멸을 관리하는 클래스이다. 
 *
 */
class Audio_Engine
{
public:
	ALCchar m_szDeviceName[260];
public:
	Audio_Engine(void);
	virtual ~Audio_Engine(void);
public:
	ALboolean CreateAudioDevice();
	bool ReleaseDevice();


};
