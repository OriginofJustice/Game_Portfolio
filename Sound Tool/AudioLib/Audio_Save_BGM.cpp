#include "StdAfx.h"
#include "Audio_Save.h"


/**
 * \par 메소드 데이터
 로드할 OGG 데이터들에 관한 정보를 출력하는 함수
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
	// 파일 익스포트 종료
	FileClose();
	return true;
}
