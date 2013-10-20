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
 * \par �޼ҵ� ����
 Wave ������ ��ũ��Ʈ�� �����ϱ� ���� �޼ҵ� 
 * \param *szName 
 * \param Buffer 
 * \param Source 
 */
void Audio_Save::FileSave(char *szName, std::vector<Audio_BufferHouse*> Buffer, std::vector<Source_Info*> Source)
{
	FileOpen(szName);
	// ���� �ͽ���Ʈ ����
	FileHeader( Buffer.size() , Source.size() );
	FileBufferExport( Buffer );
	FileSourceExport(Source);
	FileEnd();

	// ���� �ͽ���Ʈ ����
	FileClose();
}

/**
 * \par �޼ҵ� ����
 ��ũ��Ʈ�� �����ϱ� ���ؼ� ������ ������ �ݾ��ش�.
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
 * \par �޼ҵ� ����
 ��ũ��Ʈ�� ����ϱ� ���� ������ �����ش�.
 * \param *szName 
 * \return 
 */
bool Audio_Save::FileOpen(char *szName)
{
	m_pStream = fopen( szName, "wt" );
	if( !m_pStream )
	{
		MessageBox(NULL, "������ �������� ���߽��ϴ�.", "���ϻ�������", MB_ICONERROR);
		return FALSE;
	}
	return true;
}

/**
 * \par �޼ҵ� ����
 Wave ���ϵ��� ��ũ��Ʈ�� ����ϱ� ���� ������ ������ �ҽ��� ������ ����Ѵ�. 
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
 * \par �޼ҵ� ����
 ���ۿ� ���õ� ������ ��ũ��Ʈ�� ����Ѵ�.
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
 * \par �޼ҵ� ����
 ��ũ��Ʈ�� ����� �ҽ� ������ ����Ѵ�. 
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