#include "StdAfx.h"
#include "Default_Paser.h"

Default_Parser::Default_Parser(void)
{
	m_pStream =NULL;
}

Default_Parser::~Default_Parser(void)
{
}
//------------------------------------------------------------------------------------------------
//클래스명  : DSAseParser
//함수명  : ComparisonData
//하는일  : 입력받은 두개의 문자열을 비교한다. 
//리턴 값 : BOOL 
//생성일자 : 2007.3.13
//마지막 수정 일자 : 2007.3.13
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::ComparisonData( char* pDestString, char* pSrcString /* = NULL  */)
{
	if( pSrcString == NULL )
	{
		pSrcString = m_pString;
	}
	if( !lstrcmpA( pSrcString, pDestString ) )
	{
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : ErrorCloseStream
//하는일  : 파일포인터를 찾을수가 없거나 에러가 발생했을 경우 파일 포인터를 닫아주고 종료
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::ErrorCloseStream( char* pMsg )
{
	// 파일 포인터를 닫아줌
	fclose(m_pStream);		
	if( pMsg != NULL )
	{
	//	DEBUGMSG( pMsg );
	}
	return FALSE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : OpenStream
//하는일  : 파일명인 문자열을 입력받아서 파일을 연다 
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::OpenStream( char* pFileName )
{
	// 인자로 받은 파일 열어 파일 포인터로 넘긴다. 
	m_pStream = fopen( pFileName, "rt");
	// 파일을 찾지 못했을 경우
	if ( m_pStream == NULL)
	{
		return ErrorCloseStream( "파일을 찾지 못했습니다.");				
	}	
	return TRUE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetDataFromString
//하는일  : 문자열로 부터 데이터를 읽어들어 그 데이터가 어느 형인지 판단하고 
//			  그 데이터를 입력한다. 
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromString( VOID* pData, INT DataType)
{	
	if( pData != NULL )
	{
		switch( DataType )
		{
			// int 타입일 경우
		case INT_DATA:
			sscanf(m_pBuffer, "%s%d", m_pString, pData );
			break;
			// float 타입일 경우
		case FLOAT_DATA:
			sscanf(m_pBuffer, "%s%f", m_pString, pData );
			break;
			// 문자열 타입일경우
		case STRING_DATA:	
			{
				char szTexPath[MAX_PATH] = TEXT("");
				sscanf(m_pBuffer, "%s%s", m_pString, szTexPath );								
				if( szTexPath[0] == '"')
				{
					// 문자열의 시작과 끝에 있는 (")문자를 삭제한다.
					// 또한 문자열중간에 공백까지도 반환문자열에 포함한다.
					strcpy( szTexPath, strstr( m_pBuffer, "\""));
					size_t filelen = strlen( szTexPath );						
					szTexPath[filelen-2] = 0;
					strcpy( (char*)pData, &szTexPath[1] );						
				}
				else
				{
					strcpy( (char*)pData, &szTexPath[0] );						
				}												
			}
			break;
			// 정점 데이터일 경우
		case VERTEX_DATA:			

			sscanf(m_pBuffer, "%s%f%f%f", m_pString, 
				&((D3DXVECTOR3*)pData)->x, 
				&((D3DXVECTOR3*)pData)->z, 
				&((D3DXVECTOR3*)pData)->y  );												
			break;
		case FACE_DATA:
		case MATRIX_DATA:
		case NULL_DATA: 
			break;				
		}		
	}				
	return TRUE;	
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetDataFromFileLoop
//하는일  : 전체 파일 중에서 입력받은 문자열을 찾은 다음 파일 포인터를 다음줄로 보냄
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFileLoop( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	while( !feof( m_pStream ) )
	{
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			return GetDataFromString( pData, DataType);
		}
	}
	return FALSE;//ErrorCloseStream( "전체파일에서 검색할수 없습니다.");	
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetDataFromFileNext
//하는일  : 다음라인을 대상으로 문자열을 찾고 다음라인으로 파일포인터를 옮긴다. 
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFileNext( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	if( !feof( m_pStream ) )
	{
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			return GetDataFromString( pData, DataType);
		}		
	}
	return FALSE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetDataFromFileString
//하는일  : 원하는 문자열을 찾고 찾은 문자열 시작위치로 옮긴다
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFileString( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA  */)
{
	fpos_t  FilePos; 

	while( !feof( m_pStream ) )
	{
		if( fgetpos( m_pStream, &FilePos ) )
		{
			ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
		}
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			if( GetDataFromString( pData, DataType) )
			{
				if( fsetpos( m_pStream, &FilePos ) )
				{
					ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
				}		
			}
			return TRUE;
		}		
	}

	return FALSE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetDataFromFile
//하는일  : 파일로 부터 데이터를 읽어 들인다. 
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFile( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	fpos_t  FilePos; 
	if( fgetpos( m_pStream, &FilePos ) )
	{
		ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
	}
	if( !feof( m_pStream ) )
	{
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			return GetDataFromString( pData, DataType);
		}
		else
		{
			if( fsetpos( m_pStream, &FilePos ) )
			{
				ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
			}
		}
	}

	return FALSE;
}
//------------------------------------------------------------------------------------------------
//클래스명  : Default_Parser
//함수명  : GetNodeName
//하는일  : 애니메이션 관련 노드 네임 처리...(아직 기능 파악 덜 되었음)
//리턴 값 : BOOL 
//생성일자 : 2007.2.6
//마지막 수정 일자 : 2007.2.6
//수정사항
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetNodeName( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	fpos_t  FilePos; 
	if( fgetpos( m_pStream, &FilePos ) )
	{
		ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
	}
	// 파일의 끝이 아닐경우 
	if( !feof( m_pStream ) )
	{
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			if( pData != NULL )
			{
				switch( DataType )
				{					
				case STRING_DATA:	
					{
						char *pStr = NULL;
						char String1[20];
						char String2[20];							
						char ResultString[40];
						memset( String1, 0 , sizeof(char) * 20 );
						memset( String2, 0 , sizeof(char) * 20 );
						memset( ResultString, 0 , sizeof(char) * 40 );
						bool check = false;
						int j = 0;
						if( strstr( m_pBuffer, "Bip01 R UpperArm" ) )
						{
							int k;
							k = 0;
						}
						for(int i=0; i<256; i++)
						{
							if(check)
							{
								if(m_pBuffer[i]=='"')
								{ 
									check=false; 
									String2[j++] = 0;
									break;
								}
								String2[j++] = m_pBuffer[i];									
							}
							else
							{
								if(m_pBuffer[i]=='"')
									check = true;
							}

						}
						//String2[filelen-1] = 0;					
						strcpy( (char*)pData, &String2[0] );						
					}
					break;								
				}
			}				
			return TRUE;
		}
		else
		{
			if( fsetpos( m_pStream, &FilePos ) )
			{
				ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
			}
		}
	}
	return -1;
}