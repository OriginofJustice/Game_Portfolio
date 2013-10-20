#pragma once

#include "Define_Audio.h"

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
 * \author ���ǿ�
 *
 * \par 
 * 
 * \brief 
 �ε�� �����͵��� ��ũ��Ʈ�� ����ϱ� ���� �Լ� 
 *
 */
class Audio_Save
{
	FILE*			m_pStream;
public:
	bool FileOpen(char* szName);
	void FileSave(char* szName, vector<Audio_BufferHouse*>, vector<Source_Info*>);
	bool FileClose();

	bool FileHeader(UINT buffer, UINT source);
	bool FileBufferExport(vector<Audio_BufferHouse*> Buffer );
	bool FileSourceExport(vector<Source_Info*> Source);
	bool FileEnd();

	bool FileBgmExport(char* szName, vector<OggData> OggData);


public:
	Audio_Save(void);
	~Audio_Save(void);

};
