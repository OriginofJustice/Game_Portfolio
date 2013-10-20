#include "StdAfx.h"
#include "Audio_Buffer.h"


/**
 * \par �޼ҵ� ����
 ������ �ҽ��κ��� ���� ���̺귯�� ������ ���� ������ ���۷�
 �����͸� �����ϰ� �˻��ϴ� ������ �۾��� �����ϴ� �ݹ��Լ�
 * \param ptr 
 * \param size 
 * \param nmemb 
 * \param datasoure 
 * \return 
 */
size_t read_func_stream(void * ptr, size_t size,
						size_t nmemb, void * datasoure)
{
	if(!size || !nmemb)
	{
		return 0;
	}

	FileStream * pSrc = (FileStream *)datasoure;
	UINT32 nBytesToRead = size * nmemb;

	ULONG nRead;
	if(FAILED(pSrc->Read(ptr, nBytesToRead, &nRead)))
	{
		return 0;
	}

	return (UINT32)nRead;
}

int seek_func_stream(void * datasource, ogg_int64_t offset, 
					 int whence)
{
	FileStream * pSrc = (FileStream *)datasource;
	LARGE_INTEGER	 liOffset;
	ULARGE_INTEGER	 lnNewPos;
	liOffset.QuadPart = offset;

	if(FAILED(pSrc->Seek(liOffset, whence, &lnNewPos)))
		return -1;

	return 0;
}

int close_func_stream(void * datasource)
{
	return 0;
}

long tell_func_stream(void * datasource)
{
	FileStream * pSrc = (FileStream *)datasource;	
	LARGE_INTEGER dlibMove;
	dlibMove.QuadPart = 0;
	ULARGE_INTEGER nNewPos;
	pSrc->Seek(dlibMove, SEEK_CUR, &nNewPos);	

	return nNewPos.QuadPart;
}



Audio_Buffer::Audio_Buffer(void)
{
	strcpy( m_szFilePath, "..\\WavData\\" );
	m_pOggFile = NULL;
	m_pVorbis_Info = NULL;
	m_pVorbis_Comment = NULL;
	m_bOggLoad = false;
	m_OggBuffer.clear();
}

Audio_Buffer::~Audio_Buffer(void)
{
}

/**
 * \par �޼ҵ� ����
 ��ũ��Ʈ�κ��� ����ϰ� �� ���ϸ���� �ҷ��ͼ� �� ���ϵ��� �ε��ѵ� ���ۿ� ��´�.
 * \param *szName ��ũ��Ʈ ���ϸ�
 * \return 
 */
ALuint Audio_Buffer::ScriptLoadWave(char *szName)
{

	// Read in the wav data from file. Check that it loaded correctly.
	strcpy( m_szFilePath, "..\\WavData\\" );
	strcat( m_szFilePath, szName );
	
	ALuint buffer = LoadSound(m_szFilePath);

	m_Buffer.push_back(buffer);

	// Return the buffer id.
	return buffer;
}

/**
 * \par �޼ҵ� ����
 PCM����� Wave ������ �ϳ� �ε��ϰ��� �Ҷ� ����ϴ� �Լ��̴�
 �ε��ϰ� �� �ڿ��� �����͸� ���ۿ� ��´�. 
 * \param *szName 
 * \return 
 */
ALuint Audio_Buffer::ImportWave(char *szName)
{
	ALuint buffer = LoadSound(szName);
	m_Buffer.push_back(buffer);

	// Return the buffer id.
	return buffer;
}
/**
 * \par �޼ҵ� ���� 
 ���� ��Ȳ�� ���� �Լ� 
 * \param err ���� ��Ȳ�� ��ȣ
 * \return 
 */
string Audio_Buffer::GetALErrorString(ALenum err)
{
	switch(err)
	{
	case AL_NO_ERROR:
		return string("AL_NO_ERROR");
		break;

	case AL_INVALID_NAME:
		return string("AL_INVALID_NAME");
		break;

	case AL_INVALID_ENUM:
		return string("AL_INVALID_ENUM");
		break;

	case AL_INVALID_VALUE:
		return string("AL_INVALID_VALUE");
		break;

	case AL_INVALID_OPERATION:
		return string("AL_INVALID_OPERATION");
		break;

	case AL_OUT_OF_MEMORY:
		return string("AL_OUT_OF_MEMORY");
		break;
	}
	return NULL;
}

string Audio_Buffer::GetALCErrorString(ALenum err)
{
	switch(err)
	{
	case ALC_NO_ERROR:
		return string("AL_NO_ERROR");
		break;

	case ALC_INVALID_DEVICE:
		return string("ALC_INVALID_DEVICE");
		break;

	case ALC_INVALID_CONTEXT:
		return string("ALC_INVALID_CONTEXT");
		break;

	case ALC_INVALID_ENUM:
		return string("ALC_INVALID_ENUM");
		break;

	case ALC_INVALID_VALUE:
		return string("ALC_INVALID_VALUE");
		break;

	case ALC_OUT_OF_MEMORY:
		return string("ALC_OUT_OF_MEMORY");
		break;
	}
	return NULL;
}

/**
 * \par �޼ҵ� ����
 ��� ���ۿ� ��� �����͸� ��� ���� �Ҷ� ����Ѵ�. 
 ���α׷��� ���� �ϰų� ��� ���� ���� �Ҷ� �����ϴ�.
 */
void Audio_Buffer::AllBufferDelete()
{
	for(vector<ALuint>::iterator iter = m_Buffer.begin(); iter != m_Buffer.end(); iter++)
		alDeleteBuffers(1, &(*iter));
	for (vector<ALuint*>::iterator it = m_OggBuffer.begin();
		it != m_OggBuffer.end(); it++)
		alDeleteBuffers(1, *it);
	m_Buffer.clear();
	if (m_bOggLoad == true)
		ov_clear(&m_OggStream);
}

/**
 * \par �޼ҵ� ����
 PCM ����� Wave ������ �ε��ϴ� �Լ��̴�
 * \param szName 
 * \return �ε��� �����Ͱ� ����ִ� ������ �ּҰ�
 */
ALuint Audio_Buffer::LoadSound(char* szName)
{
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean	loop;
	ALuint buffer;
	ALenum result;
	alGenBuffers(1, &buffer);
	alutLoadWAVFile(szName, &format, &data, &size, &freq, &loop);
	alBufferData(buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	return buffer;
}


/**
 * \par �޼ҵ� ����
 OGG ������ �ε��ϱ� ���� �޼ҵ��̴�. 
 �ε尡 ������ ���ۿ� ��´�. 
 * \param szName �ε��� ���ϸ�
 * \return 
 */
ALuint* Audio_Buffer::OggFileLoad(char* szName)
{
	//���Ͽ���

	m_pOggFile = NULL;
	m_pVorbis_Info = NULL;
	m_pVorbis_Comment = NULL;
	m_bOggLoad = true;
	if(FAILED(m_StreamSrc.Open(szName)))
	{
		return false;
	}

	//������ �ݹ��Լ��� ����
	ov_callbacks cb;
	cb.read_func = &read_func_stream;
	cb.seek_func = &seek_func_stream;
	cb.close_func = &close_func_stream;
	cb.tell_func = &tell_func_stream;

	//Ogg ��Ʈ ��Ʈ���� ����.
	int res = ov_open_callbacks((void*)&m_StreamSrc, &m_OggStream, NULL, 0, cb);		
	if ( res < 0 )
	{
		return false;
	}

	m_pVorbis_Info = ov_info(&m_OggStream, -1);
	m_pVorbis_Comment = ov_comment(&m_OggStream, -1);

	if(m_pVorbis_Info->channels == 1)
		m_Format = AL_FORMAT_MONO16;
	else
		m_Format = AL_FORMAT_STEREO16;


	alGenBuffers(2, m_buffer);
	OggCheak();

	OggBufferLoad();

	m_OggBuffer.push_back(m_buffer);

	return m_buffer;
}


bool Audio_Buffer::OggBufferLoad()
{
	return true;
}


/**
 * \par �޼ҵ� ����
 Ogg ������ �ε� �� ��쿡 ����ġ ���� ���ܰ� �߻��Ͽ��� ��쿡 ����ó��
 * \param code 
 * \return 
 */
string Audio_Buffer::errorString(int code)
{
	switch(code)
	{
	case OV_EREAD:
		return string("Read from media.");
	case OV_ENOTVORBIS:
		return string("Not Vorbis data.");
	case OV_EVERSION:
		return string("Vorbis version mismatch.");
	case OV_EBADHEADER:
		return string("Invalid Vorbis header.");
	case OV_EFAULT:
		return string("Internal logic fault (bug or heap/stack corruption.");
	default:
		return string("Unknown Ogg error.");
	}
}

void Audio_Buffer::OggCheak()
{
	int error = alGetError();

	if(error != AL_NO_ERROR)
		MessageBox(NULL,"OpenAL error was raised.","Error" ,MB_OK);

}

/**
 * \par �޼ҵ� ����
 �ε��� OGG �������� ���۸� �ݾ��ش�. 
 * \return 
 */
bool Audio_Buffer::OggBufferClose()
{
	alDeleteBuffers(2, m_buffer);
	if (m_bOggLoad == true)
		ov_clear(&m_OggStream);
	return true;
}