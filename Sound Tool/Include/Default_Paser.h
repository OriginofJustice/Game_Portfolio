#pragma once

class Default_Parser
{
public:
	FILE*	m_pStream;			

public:
	CHAR	m_pBuffer[256];		
	CHAR	m_pString[256];	
public:
	BOOL	ComparisonData		(	char* pDestString, char* pSrcString = NULL );	
	BOOL	ErrorCloseStream	(	char* pMsg		);		
	BOOL	OpenStream			(	char* pFileName );
	BOOL    CloseStream()		{	fclose( m_pStream); return TRUE; };

	BOOL	GetDataFromString	( VOID* pData, INT DataType);
	BOOL	GetDataFromFileLoop	(	char* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	BOOL	GetDataFromFileNext	(	char* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	BOOL	GetDataFromFileString	(	char* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA  );

	BOOL	GetDataFromFile		(	char* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
	BOOL	GetNodeName			(   char* pString = NULL, VOID* pData = NULL,INT DataType = NULL_DATA);
public:
	Default_Parser(void);
	virtual ~Default_Parser(void);
};
