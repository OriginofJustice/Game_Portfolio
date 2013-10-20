#include "StdAfx.h"
#include ".\audioparser.h"

bool AudioParser::BgmDataInput(char *path, char *szName)
{
	OggData		oggtemp;
	char Drive[MAX_PATH];
	char Dir[MAX_PATH];
	char FName[MAX_PATH];
	char Ext[MAX_PATH];									
	_splitpath( path, Drive, Dir, FName, Ext );						

	strcpy(path,Drive);
	lstrcat(path,Dir);

	strcpy(oggtemp.BufferPath, path);
	strcpy(oggtemp.BufferName, szName);
	oggtemp.id = m_OggData.size();
	m_OggData.push_back(oggtemp);
	return true;
}

/**
 * \par 메소드 설명
 OGG 데이터를 로드할 정보가 들어 있는 스크립트를 로드한다. 
 * \param szName 
 * \return 
 */
BOOL AudioParser::BgmScriptLoad(char* szName)
{
	if( OpenStream(szName) )
	{
		if( !GetDataFromFile( "#Luade_BGM_Script_0.01" ) )
		{
			return ErrorCloseStream( "BGM 라이브러리에 맞는 형식이 아닙니다.");		
		}		
	}
	while( !feof(m_pStream) )
	{
		// 파일 헤더
		if(GetDataFromFile("#Ogg_Data_List_Header"))
		{
			if (!BGM_List_Header())
			{
				return ErrorCloseStream("BGM List Header 에 문제가 있습니다.");
			}
		}
		if(GetDataFromFile("#Ogg_Data_List"))
		{
			if (!BGM_List())
			{
				return ErrorCloseStream("BGM List 에 문제가 있습니다.");
			}
		}

		if(GetDataFromFile("#End"))
		{
			 CloseStream();	
		}

	}
	return TRUE;
}

/**
 * \par 메소드 설명
 OGG 파일 정보가 들어 있는 스크립트의  헤더 부분을 읽는다.
 * \return 
 */
BOOL AudioParser::BGM_List_Header()
{
	fgets( m_pBuffer , 256 , m_pStream );		
	sscanf( m_pBuffer, "%d", &m_nOggDataSize);
	return true;
}

/**
 * \par 메소드 설명
 OGG 데이터를 언제나 로드 할수 있게 파일 명을 저장해둔다.
 * \return 
 */
BOOL AudioParser::BGM_List()
{
	UINT size = m_OggData.size();
	for (UINT i = 0 ; i < m_nOggDataSize; i++)
	{
		OggData  temp;
		fgets( m_pBuffer , 256 , m_pStream );		
		sscanf( m_pBuffer, "%d%s", &temp.id, temp.BufferName);
		temp.id = temp.id+size;		
		m_OggData.push_back(temp);		
	}
	return true;
}