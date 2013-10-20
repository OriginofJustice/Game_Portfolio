#include "StdAfx.h"
#include "Audio_Save.h"

Audio_Save::Audio_Save(void)
{
	m_pStream = NULL;
}

Audio_Save::~Audio_Save(void)
{
}

/**
 * \par 메소드 설명
 Wave 파일을 스크립트로 저장하기 위한 메소드 
 * \param *szName 
 * \param Buffer 
 * \param Source 
 */
void Audio_Save::FileSave(char *szName, std::vector<Audio_BufferHouse*> Buffer, std::vector<Source_Info*> Source)
{
	FileOpen(szName);
	// 파일 익스포트 종료
	FileHeader( Buffer.size() , Source.size() );
	FileBufferExport( Buffer );
	FileSourceExport(Source);
	FileEnd();

	// 파일 익스포트 종료
	FileClose();
}

/**
 * \par 메소드 설명
 스크립트로 저장하기 위해서 열었던 파일을 닫아준다.
 * \return 
 */
bool Audio_Save::FileClose()
{
	if (m_pStream != NULL)
	{
		fclose( m_pStream );
		m_pStream = NULL;
	}
	return true;
}

/**
 * \par 메소드 설명
 스크립트로 출력하기 위해 파일을 열어준다.
 * \param *szName 
 * \return 
 */
bool Audio_Save::FileOpen(char *szName)
{
	m_pStream = fopen( szName, "wt" );
	if( !m_pStream )
	{
		MessageBox(NULL, "파일을 생성하지 못했습니다.", "파일생성에러", MB_ICONERROR);
		return FALSE;
	}
	return true;
}

/**
 * \par 메소드 설명
 Wave 파일들을 스크립트로 출력하기 위해 버퍼의 갯수와 소스의 갯수를 출력한다. 
 * \param buffer 
 * \param source 
 * \return 
 */
bool Audio_Save::FileHeader(UINT buffer, UINT source)
{
	fprintf( m_pStream, "%s\n","#Luade_Audio_Script_0.01");
	fprintf( m_pStream, "%s\n","#BufferNSouce");
	fprintf( m_pStream, "\t%d\t%d\n",buffer,source);

	return true;
}

/**
 * \par 메소드 설명
 버퍼에 관련된 정보를 스크립트로 출력한다.
 * \param Buffer 
 * \return 
 */
bool Audio_Save::FileBufferExport(std::vector<Audio_BufferHouse*> Buffer)
{
	int count = 0;
	fprintf( m_pStream, "%s\n","#Buffer_Path");
	vector<Audio_BufferHouse*>::iterator it;
	for (it = Buffer.begin(); it != Buffer.end(); it++,count++)
	{
		fprintf( m_pStream, "\t%d\t%s\n",Buffer[count]->BufferID,Buffer[count]->BufferName);
	}
	return true;
}
/**
 * \par 메소드 설명
 스크립트로 출력할 소스 정보를 출력한다. 
 * \param Source 
 * \return 
 */
bool Audio_Save::FileSourceExport(std::vector<Source_Info*> Source)
{
	int count = 0;
	fprintf( m_pStream, "%s\n","#SourceInfo");
	vector<Source_Info*>::iterator it;
	for (it = Source.begin(); it != Source.end(); it++, count++)
	{
		fprintf( m_pStream, "\t%d\t%d\t%f\t%f\t%d\t%d\n",Source[count]->SourceID, 
			Source[count]->SourceRef, Source[count]->Picth, 
			Source[count]->Gain, Source[count]->Loop, Source[count]->attribute);
	}
	return true;
}

/**
 * \par
 * \return 
 */
bool Audio_Save::FileEnd()
{
	fprintf( m_pStream, "%s\n","#End");
	return true;
}