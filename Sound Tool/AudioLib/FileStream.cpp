#include "stdafx.h"
#include "FileStream.h"

using namespace std;

//------------------------------------------------------------------------//
FileStream::FileStream()
{
	Clear();
}

//------------------------------------------------------------------------//
FileStream::~FileStream()
{

}

//------------------------------------------------------------------------//
void FileStream::Clear()
{
	m_iRefCount = 0;
	m_pFile = 0;
	m_nSize = 0;
	m_sFileName.erase();

	m_pBuffer = 0;
	m_nReadPtr = 0;
	m_bBuffered = false;
}


//------------------------------------------------------------------------//
HRESULT FileStream::Open(std::string sFileName)
{
	m_pFile = NULL;
	if(m_pFile)
		return E_FAIL;
	char temppath[260];
	

	m_sFileName = sFileName;
	m_pFile = fopen(sFileName.c_str(), "rb");
	if (m_pFile == NULL)
	{
		strcpy(temppath, "..\\OggData\\");
		lstrcat(temppath,sFileName.c_str());
		m_pFile = fopen(temppath, "rb");
	}


	fseek(m_pFile, 0, SEEK_END);
	m_nSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	return S_OK;
}


//------------------------------------------------------------------------//
void FileStream::Close()
{
	Clear();
}

// IStream Interface
//------------------------------------------------------------------------//
HRESULT FileStream::Seek( 
						 LARGE_INTEGER dlibMove,
						 DWORD dwOrigin,
						 ULARGE_INTEGER *plibNewPosition)
{

	if(!m_pFile)
		return E_FAIL;

	UINT32 nSeek = (UINT32)dlibMove.QuadPart;
	if(fseek(m_pFile, nSeek, dwOrigin))
	{
		return E_FAIL;
	}

	if(plibNewPosition)
	{
		plibNewPosition->QuadPart = ftell(m_pFile);
	}

	return S_OK;
}

// ISequentialStream Interface
//------------------------------------------------------------------------//
HRESULT FileStream::Read( 
						 void *pv,
						 ULONG cb,
						 ULONG *pcbRead)
{
	if(!m_pFile)
		return E_FAIL;

	UINT32 nRead = fread((UINT8*)pv, 1, cb, m_pFile);
	if(pcbRead)
	{
		*pcbRead = nRead;
	}

	return S_OK;
}