#pragma once

#include <string>
#include <windows.h>


class VSString
{
private:
	std::string			m_strText;
	std::string			m_strCompText;
	unsigned int		m_uiMaxByteSize;
	unsigned int		m_uiMaxLength;
	unsigned int		m_uiCursorPos;

	bool				m_bCursorMemory;
	unsigned int		m_uiMemoryCursorPos;

public:
	VSString(void);
	virtual	~VSString(void);

	void			Clear();
	void			AddChar					( char );
	void			AddString				( char * str, unsigned int niLength );
	void			Backspace				();
	void			DelMemoryText			();

	std::string		GetString				()				{ return m_strText; }
};
