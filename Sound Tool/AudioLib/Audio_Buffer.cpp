#include "StdAfx.h"
#include "Audio_Buffer.h"


/**
 * \par 메소드 설명
 데이터 소스로부터 보비스 라이브러리 내부의 압축 해제용 버퍼로
 데이터를 전송하고 검색하는 실제의 작업을 수행하는 콜백함수
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
 * \par 메소드 설명
 스크립트로부터 사용하게 될 파일명들을 불러와서 그 파일들을 로드한뒤 버퍼에 담는다.
 * \param *szName 스크립트 파일명
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
 * \par 메소드 설명
 PCM방식의 Wave 파일을 하나 로드하고자 할때 사용하는 함수이다
 로드하고 난 뒤에는 데이터를 버퍼에 담는다. 
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
 * \par 메소드 설명 
 예외 상황을 위한 함수 
 * \param err 예외 상황의 번호
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
 * \par 메소드 설명
 모든 버퍼에 담긴 데이터를 모두 삭제 할때 사용한다. 
 프로그램을 종료 하거나 모든 음을 상제 할때 유용하다.
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
 * \par 메소드 설명
 PCM 방식의 Wave 파일을 로드하는 함수이다
 * \param szName 
 * \return 로드한 데이터가 들어있는 버퍼의 주소값
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
 * \par 메소드 설명
 OGG 파일을 로드하기 위한 메소드이다. 
 로드가 끝난뒤 버퍼에 담는다. 
 * \param szName 로드할 파일명
 * \return 
 */
ALuint* Audio_Buffer::OggFileLoad(char* szName)
{
	//파일열기

	m_pOggFile = NULL;
	m_pVorbis_Info = NULL;
	m_pVorbis_Comment = NULL;
	m_bOggLoad = true;
	if(FAILED(m_StreamSrc.Open(szName)))
	{
		return false;
	}

	//적절한 콜백함수를 설정
	ov_callbacks cb;
	cb.read_func = &read_func_stream;
	cb.seek_func = &seek_func_stream;
	cb.close_func = &close_func_stream;
	cb.tell_func = &tell_func_stream;

	//Ogg 비트 스트림을 연다.
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
 * \par 메소드 설명
 Ogg 파일을 로드 할 경우에 예상치 못한 예외가 발생하였을 경우에 예외처리
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
 * \par 메소드 설명
 로드한 OGG 데이터의 버퍼를 닫아준다. 
 * \return 
 */
bool Audio_Buffer::OggBufferClose()
{
	alDeleteBuffers(2, m_buffer);
	if (m_bOggLoad == true)
		ov_clear(&m_OggStream);
	return true;
}