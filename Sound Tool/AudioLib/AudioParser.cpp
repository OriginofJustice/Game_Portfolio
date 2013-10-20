#include "StdAfx.h"
#include ".\audioparser.h"

AudioParser::AudioParser(void)
{
	m_pHeader = NULL;
	m_ptempAudioBuffer =NULL;
	m_ptempSourceInfo=NULL;
	m_pAudioBuffer.erase(m_pAudioBuffer.begin(), m_pAudioBuffer.end());
	m_pSourceInfo.erase(m_pSourceInfo.begin(), m_pSourceInfo.end());
	m_nBufferSize = 0;
	m_nOggDataSize = 0;
	m_OggData.clear();
}

AudioParser::~AudioParser(void)
{
}

BOOL AudioParser::AudioLoader(char *szName)
{
	if( OpenStream(szName) )
	{
		if( !GetDataFromFile( "#Luade_Audio_Script_0.01" ) )
		{
			return ErrorCloseStream( "사운드 라이브러리에 맞는 형식이 아닙니다.");		
		}		
	}
	while( !feof(m_pStream) )
	{
		// 파일 헤더
		if(GetDataFromFile("#BufferNSouce"))
		{
			if (!BufferNSourceNum())
			{
				return ErrorCloseStream("버퍼와 소스의 갯수를 받아오는데 실패 했습니다.");
			}
		}
		if (GetDataFromFile("#Buffer_Path"))
		{
			if (!BufferLoad())
			{
				return ErrorCloseStream("버퍼를 로드하는데 실패 했습니다.");
			}
		}
		if(GetDataFromFile("#SourceInfo"))
		{
			if (!SourceInfo())
			{
				return ErrorCloseStream("소스에 정보를 입력하는데 실패 하였습니다.");
			}
		}
		if(GetDataFromFile("#End"))
		{

		}

	}
	return TRUE;
}

/**
 * \par 메소드 설명
 버퍼의 갯수와 소스의 갯수를 입력 받는다. 
 * \return 
 */
BOOL AudioParser::BufferNSourceNum()
{
	SAFE_NEW(m_pHeader,Audio_Header);
	fgets( m_pBuffer , 256 , m_pStream );		
	sscanf( m_pBuffer, "%d%d", &m_pHeader->BufferNum, &m_pHeader->SourceNum);
	return TRUE;
}

/**
 * \par 메소드 설명
 스크립트로 부터 버퍼를 로드한다. 
 * \return 
 */
BOOL AudioParser::BufferLoad()
{
	m_nBufferSize = m_pAudioBuffer.size();
	for (int i = 0;  i < m_pHeader->BufferNum; i++)
	{
		m_ptempAudioBuffer = NULL;
		SAFE_NEW(m_ptempAudioBuffer,Audio_BufferHouse);
		fgets( m_pBuffer , 256 , m_pStream );		
		sscanf( m_pBuffer, "%d%s", &m_ptempAudioBuffer->BufferID, m_ptempAudioBuffer->BufferName);
		m_ptempAudioBuffer->BufferID = m_ptempAudioBuffer->BufferID + m_nBufferSize;
		m_ptempAudioBuffer->Buffer = m_BufferManager.ScriptLoadWave(m_ptempAudioBuffer->BufferName);
		m_pAudioBuffer.push_back(m_ptempAudioBuffer);
	}
	
	return TRUE;
}
/**
 * \par 메소드 설명
 로드된 버퍼를 이용해 소스로 만들기 위해서 소스의 각종 데이터를 읽어들인다. 
 * \return 
 */
BOOL AudioParser::SourceInfo()
{
	m_nSourceSize = m_pSourceInfo.size();
	for (int i = 0;  i < m_pHeader->SourceNum; i++)
	{
		m_ptempSourceInfo = NULL;
		SAFE_NEW(m_ptempSourceInfo,Source_Info);
		fgets( m_pBuffer , 256 , m_pStream );		
		sscanf( m_pBuffer, "%d%d%f%f%d%d,", &m_ptempSourceInfo->SourceID,&m_ptempSourceInfo->SourceRef,
			&m_ptempSourceInfo->Picth, &m_ptempSourceInfo->Gain,&m_ptempSourceInfo->Loop,
			&m_ptempSourceInfo->attribute);
		m_ptempSourceInfo->SourceID = m_nSourceSize+m_ptempSourceInfo->SourceID;
		m_ptempSourceInfo->SourceRef = m_ptempSourceInfo->SourceRef+m_nBufferSize;
		m_pSourceInfo.push_back(m_ptempSourceInfo);
	}
	 
	return TRUE;
}


/**
 * \par 메소드 설명
 로드된 모든 버퍼와 소스들을 해제 시켜준다. 
 * \return 
 */
BOOL AudioParser::Release()
{
	if (!m_pSourceInfo.empty()||!m_pAudioBuffer.empty())
	{
		for (unsigned int i = 0; i < m_pAudioBuffer.size();i++)
		{
			// 이전에 버퍼들을 해제 시켜준다. 
			SAFE_DEL(m_pAudioBuffer[i]);
		}
		for (unsigned int i = 0; i < m_pSourceInfo.size();i++)
		{
			SAFE_DEL(m_pSourceInfo[i]);
		}
		SAFE_DEL(m_pHeader);
	}

	m_pAudioBuffer.erase(m_pAudioBuffer.begin(), m_pAudioBuffer.end());
	m_pSourceInfo.erase(m_pSourceInfo.begin(), m_pSourceInfo.end());
	return TRUE;
}

BOOL AudioParser::BufferImport(char *path, char* Name)
{
	m_ptempAudioBuffer = NULL;
	SAFE_NEW(m_ptempAudioBuffer,Audio_BufferHouse);
	m_ptempAudioBuffer->Buffer = m_BufferManager.ImportWave(path);
	strcpy(m_ptempAudioBuffer->BufferName,Name);
	m_ptempAudioBuffer->BufferID = m_pAudioBuffer.size();
	m_pAudioBuffer.push_back(m_ptempAudioBuffer);
	return TRUE;
}

BOOL AudioParser::SourceInput(int ref)
{
	m_ptempSourceInfo = NULL;
	SAFE_NEW(m_ptempSourceInfo,Source_Info);
	m_ptempSourceInfo->SourceID = m_pSourceInfo.size();
	m_ptempSourceInfo->SourceRef = ref;
	m_ptempSourceInfo->Picth = 1.0f;
	m_ptempSourceInfo->Gain = 1.0f;
	m_ptempSourceInfo->Loop = FALSE;
	m_ptempSourceInfo->attribute = WAVEFILE;
	m_pSourceInfo.push_back(m_ptempSourceInfo);
	return TRUE;
}