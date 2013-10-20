#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__
//-----------------------------------------------------------------------------

#include <d3d9.h>
#include <string>

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
 * \date 2002
 *
 * \author James Boer
 *
 * \par 
 * 
 * \brief 
 This software is provided "as is" without express or implied
 warranties. You may freely copy and compile this source into
 applications you distribute provided that the copyright text
 below is included in the resulting source code, for example:
 "Portions Copyright (C) James Boer, 2002"
 *
 */
class FileStream
{
public:
	FileStream();
	virtual ~FileStream();
	void Clear();

	HRESULT __stdcall Open(std::string sFileName);
	void Close();

	// IStream Interface
	HRESULT __stdcall Seek( 
		LARGE_INTEGER dlibMove,
		DWORD dwOrigin,
		ULARGE_INTEGER *plibNewPosition);

	// ISequentialStream Interface
	HRESULT __stdcall Read( 
		void *pv,
		ULONG cb,
		ULONG *pcbRead);        
private:

	INT32			m_iRefCount;
	FILE*			m_pFile;
	UINT32			m_nSize;
	std::string		m_sFileName;

	UINT8*			m_pBuffer;
	UINT32			m_nReadPtr;
	bool			m_bBuffered;
};

#endif __FILESTREAM_H__


