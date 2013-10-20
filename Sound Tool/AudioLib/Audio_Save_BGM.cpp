#include "StdAfx.h"
#include "Audio_Save.h"


/**
 * \par �޼ҵ� ������
 �ε��� OGG �����͵鿡 ���� ������ ����ϴ� �Լ�
 * \param szName 
 * \param OggData 
 * \return 
 */
bool Audio_Save::FileBgmExport(char* szName, vector<OggData> OggData)
{
	FileOpen(szName);

	fprintf( m_pStream, "#Luade_BGM_Script_0.01\n");
	fprintf( m_pStream, "%s\n","#Ogg_Data_List_Header");
	fprintf( m_pStream, "\t%d\n",OggData.size());

	fprintf( m_pStream, "%s\n","#Ogg_Data_List");
	for (UINT i = 0 ; i < OggData.size(); i++)
	{
		fprintf( m_pStream, "\t%d\t%s\n",i, OggData[i].BufferName);
	}

	FileEnd();
	// ���� �ͽ���Ʈ ����
	FileClose();
	return true;
}
