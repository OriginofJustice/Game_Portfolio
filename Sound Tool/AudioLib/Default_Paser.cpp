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
//Ŭ������  : DSAseParser
//�Լ���  : ComparisonData
//�ϴ���  : �Է¹��� �ΰ��� ���ڿ��� ���Ѵ�. 
//���� �� : BOOL 
//�������� : 2007.3.13
//������ ���� ���� : 2007.3.13
//��������
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
//Ŭ������  : Default_Parser
//�Լ���  : ErrorCloseStream
//�ϴ���  : ���������͸� ã������ ���ų� ������ �߻����� ��� ���� �����͸� �ݾ��ְ� ����
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::ErrorCloseStream( char* pMsg )
{
	// ���� �����͸� �ݾ���
	fclose(m_pStream);		
	if( pMsg != NULL )
	{
	//	DEBUGMSG( pMsg );
	}
	return FALSE;
}
//------------------------------------------------------------------------------------------------
//Ŭ������  : Default_Parser
//�Լ���  : OpenStream
//�ϴ���  : ���ϸ��� ���ڿ��� �Է¹޾Ƽ� ������ ���� 
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::OpenStream( char* pFileName )
{
	// ���ڷ� ���� ���� ���� ���� �����ͷ� �ѱ��. 
	m_pStream = fopen( pFileName, "rt");
	// ������ ã�� ������ ���
	if ( m_pStream == NULL)
	{
		return ErrorCloseStream( "������ ã�� ���߽��ϴ�.");				
	}	
	return TRUE;
}
//------------------------------------------------------------------------------------------------
//Ŭ������  : Default_Parser
//�Լ���  : GetDataFromString
//�ϴ���  : ���ڿ��� ���� �����͸� �о��� �� �����Ͱ� ��� ������ �Ǵ��ϰ� 
//			  �� �����͸� �Է��Ѵ�. 
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromString( VOID* pData, INT DataType)
{	
	if( pData != NULL )
	{
		switch( DataType )
		{
			// int Ÿ���� ���
		case INT_DATA:
			sscanf(m_pBuffer, "%s%d", m_pString, pData );
			break;
			// float Ÿ���� ���
		case FLOAT_DATA:
			sscanf(m_pBuffer, "%s%f", m_pString, pData );
			break;
			// ���ڿ� Ÿ���ϰ��
		case STRING_DATA:	
			{
				char szTexPath[MAX_PATH] = TEXT("");
				sscanf(m_pBuffer, "%s%s", m_pString, szTexPath );								
				if( szTexPath[0] == '"')
				{
					// ���ڿ��� ���۰� ���� �ִ� (")���ڸ� �����Ѵ�.
					// ���� ���ڿ��߰��� ��������� ��ȯ���ڿ��� �����Ѵ�.
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
			// ���� �������� ���
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
//Ŭ������  : Default_Parser
//�Լ���  : GetDataFromFileLoop
//�ϴ���  : ��ü ���� �߿��� �Է¹��� ���ڿ��� ã�� ���� ���� �����͸� �����ٷ� ����
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
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
	return FALSE;//ErrorCloseStream( "��ü���Ͽ��� �˻��Ҽ� �����ϴ�.");	
}
//------------------------------------------------------------------------------------------------
//Ŭ������  : Default_Parser
//�Լ���  : GetDataFromFileNext
//�ϴ���  : ���������� ������� ���ڿ��� ã�� ������������ ���������͸� �ű��. 
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
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
//Ŭ������  : Default_Parser
//�Լ���  : GetDataFromFileString
//�ϴ���  : ���ϴ� ���ڿ��� ã�� ã�� ���ڿ� ������ġ�� �ű��
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFileString( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA  */)
{
	fpos_t  FilePos; 

	while( !feof( m_pStream ) )
	{
		if( fgetpos( m_pStream, &FilePos ) )
		{
			ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
		}
		fgets( m_pBuffer, 256, m_pStream );		
		sscanf(m_pBuffer, "%s", m_pString);
		if( !lstrcmpA(m_pString, pString ) )
		{
			if( GetDataFromString( pData, DataType) )
			{
				if( fsetpos( m_pStream, &FilePos ) )
				{
					ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
				}		
			}
			return TRUE;
		}		
	}

	return FALSE;
}
//------------------------------------------------------------------------------------------------
//Ŭ������  : Default_Parser
//�Լ���  : GetDataFromFile
//�ϴ���  : ���Ϸ� ���� �����͸� �о� ���δ�. 
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetDataFromFile( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	fpos_t  FilePos; 
	if( fgetpos( m_pStream, &FilePos ) )
	{
		ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
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
				ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
			}
		}
	}

	return FALSE;
}
//------------------------------------------------------------------------------------------------
//Ŭ������  : Default_Parser
//�Լ���  : GetNodeName
//�ϴ���  : �ִϸ��̼� ���� ��� ���� ó��...(���� ��� �ľ� �� �Ǿ���)
//���� �� : BOOL 
//�������� : 2007.2.6
//������ ���� ���� : 2007.2.6
//��������
//
//------------------------------------------------------------------------------------------------
BOOL Default_Parser::GetNodeName( char* pString /* = NULL */, VOID* pData /* = NULL */,INT DataType /* = NULL_DATA */)
{
	fpos_t  FilePos; 
	if( fgetpos( m_pStream, &FilePos ) )
	{
		ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
	}
	// ������ ���� �ƴҰ�� 
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
				ErrorCloseStream( "�۾����� ���������͸� �Ҿ� ���Ƚ��ϴ�.");
			}
		}
	}
	return -1;
}