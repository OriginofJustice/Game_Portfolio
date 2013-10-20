#include "StdAfx.h"
#include "VSString.h"

VSString::VSString(void)
{
}

VSString::~VSString(void)
{
}

void
VSString::Clear()
{
	m_strText.clear();
	m_strCompText.clear();
	m_uiCursorPos = 0;
	m_bCursorMemory = false;
	m_uiMemoryCursorPos = 0;
	m_uiMaxByteSize = 64;
}

void
VSString::AddChar( char ch )
{
	if( m_uiMemoryCursorPos != m_uiCursorPos )
	{
		DelMemoryText();
	}

	if( m_uiMaxByteSize > ( unsigned int )m_strText.length() )
	{
		std::string strTmp = m_strText;
		strTmp.insert( m_uiCursorPos, 1, ch );

	/*	unsigned int x, y;
		pFont->GetTextExtent( strTmp.c_str(), x, y );

		if( x <= m_uiMaxLength )*/
		{
			m_strText.insert( m_uiCursorPos, 1, ch );
			m_uiCursorPos++;
		}
	}

	m_uiMemoryCursorPos = m_uiCursorPos;
}


void
VSString::AddString( char * str, unsigned int uiLength )
{
	if( m_uiMemoryCursorPos != m_uiCursorPos )
	{
		DelMemoryText();
	}

	if( 0 == uiLength )
	{
		return;
	}

	if( m_uiMaxByteSize > ( unsigned int )m_strText.length() )
	{
		if( m_uiMaxByteSize < ( unsigned int )m_strText.length() + uiLength )
		{
			uiLength = m_uiMaxByteSize - ( unsigned int )m_strText.length();
		}

		std::string strTmp = m_strText;
		strTmp.insert( m_uiCursorPos, str, uiLength );

		/*unsigned int x, y;
		pFont->GetTextExtent( strTmp.c_str(), x, y );

		if( x <= m_uiMaxLength )*/
		{
			m_strText.insert( m_uiCursorPos, str, uiLength );
			m_uiCursorPos += uiLength;
		}
	}

	m_uiMemoryCursorPos = m_uiCursorPos;
}

void VSString::Backspace()
{
	if( m_uiMemoryCursorPos != m_uiCursorPos )
	{
		DelMemoryText();
		return;
	}

	if( m_uiCursorPos > 0 )
	{
		if( m_uiCursorPos >= 2 )
		{
			unsigned int uiCurPos = 0;
			unsigned int uistrLength = ( unsigned int )m_strText.length();

			while( uistrLength > uiCurPos )
			{
				bool bIs2Byte = false;

				if( IsDBCSLeadByte( ( unsigned char )m_strText[ uiCurPos++ ] ) )
				{
					bIs2Byte = true;
					uiCurPos++;
				}
				else
				{
					bIs2Byte = false;
				}

				if( uiCurPos == m_uiCursorPos )
				{
					if( bIs2Byte )
					{
						m_strText.erase( m_uiCursorPos - 2, 2 );
						m_uiCursorPos -= 2;
					}
					else
					{
						m_strText.erase( m_uiCursorPos - 1, 1 );
						m_uiCursorPos--;
					}

					break;
				}
			}
		}
		else
		{
			m_strText.erase( m_uiCursorPos - 1, 1 );
			m_uiCursorPos--;
		}
	}

	m_uiMemoryCursorPos = m_uiCursorPos;
}

void VSString::DelMemoryText()
{
	if( m_uiMemoryCursorPos != m_uiCursorPos )
	{
		if( m_uiCursorPos <= m_strText.size() && m_uiMemoryCursorPos <= m_strText.size() )
		{
			unsigned int uiBegin	= m_uiMemoryCursorPos < m_uiCursorPos ? m_uiMemoryCursorPos : m_uiCursorPos;
			unsigned int uiEnd	= m_uiMemoryCursorPos > m_uiCursorPos ? m_uiMemoryCursorPos : m_uiCursorPos;

			m_strText.erase( uiBegin, uiEnd - uiBegin );

			m_uiMemoryCursorPos = m_uiCursorPos = uiBegin;
		}
		else
		{
			m_uiMemoryCursorPos = m_uiCursorPos;
		}
	}
}