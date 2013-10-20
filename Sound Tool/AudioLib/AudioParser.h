#pragma once
#include "Default_Paser.h"
#include "Audio_Buffer.h"
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
 * \date 2007-07-21
 *
 * \author Administrator
 *
 * \par 
 * 
 * \brief 
 스크립트로 부터 각종 음원들을 로드하는 함수 
 *
 */
class AudioParser : public Default_Parser
{

public:
	Audio_Buffer				m_BufferManager;
	Audio_Header*				m_pHeader;
	Audio_BufferHouse*			m_ptempAudioBuffer;
	Source_Info*				m_ptempSourceInfo;
	vector<Audio_BufferHouse*>	m_pAudioBuffer;
	vector<Source_Info*>		m_pSourceInfo;
	UINT						m_nBufferSize;
	UINT						m_nSourceSize;
	vector<OggData>				m_OggData;

	UINT						m_nOggDataSize;



	
public:
	BOOL	AudioLoader(char*	szName);
	BOOL	BufferNSourceNum();
	BOOL	BufferLoad();
	BOOL	SourceInfo();

	BOOL	BufferImport(char*  path, char* Name);

	BOOL	SourceInput(int ref);

	bool	BgmDataInput(char*  path, char*  szName);
	BOOL	BgmScriptLoad(char* szName);
	BOOL	BGM_List();
	BOOL	BGM_List_Header();

	BOOL	Release();
public:
	AudioParser(void);
	virtual ~AudioParser(void);
};
