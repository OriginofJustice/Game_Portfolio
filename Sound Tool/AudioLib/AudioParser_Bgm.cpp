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
 * \par �޼ҵ� ����
 OGG �����͸� �ε��� ������ ��� �ִ� ��ũ��Ʈ�� �ε��Ѵ�. 
 * \param szName 
 * \return 
 */
BOOL AudioParser::BgmScriptLoad(char* szName)
{
	if( OpenStream(szName) )
	{
		if( !GetDataFromFile( "#Luade_BGM_Script_0.01" ) )
		{
			return ErrorCloseStream( "BGM ���̺귯���� �´� ������ �ƴմϴ�.");		
		}		
	}
	while( !feof(m_pStream) )
	{
		// ���� ���
		if(GetDataFromFile("#Ogg_Data_List_Header"))
		{
			if (!BGM_List_Header())
			{
				return ErrorCloseStream("BGM List Header �� ������ �ֽ��ϴ�.");
			}
		}
		if(GetDataFromFile("#Ogg_Data_List"))
		{
			if (!BGM_List())
			{
				return ErrorCloseStream("BGM List �� ������ �ֽ��ϴ�.");
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
 * \par �޼ҵ� ����
 OGG ���� ������ ��� �ִ� ��ũ��Ʈ��  ��� �κ��� �д´�.
 * \return 
 */
BOOL AudioParser::BGM_List_Header()
{
	fgets( m_pBuffer , 256 , m_pStream );		
	sscanf( m_pBuffer, "%d", &m_nOggDataSize);
	return true;
}

/**
 * \par �޼ҵ� ����
 OGG �����͸� ������ �ε� �Ҽ� �ְ� ���� ���� �����صд�.
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