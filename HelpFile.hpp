/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HELPFILE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CHelpFile class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef HELPFILE_HPP
#define HELPFILE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This class provides a simple wrapper around a Windows Help File.
**
*******************************************************************************
*/

class CHelpFile
{
public:
	//
	// Constructors/Destructor.
	//
	CHelpFile(CWnd& rParent);
	
	//
	// Commands.
	//
	void Contents();
	void Topic(DWORD dwTopic);
	void Close();
	
	//
	// Members.
	//
	CPath	m_HelpFile;
	CWnd&	m_rParent;
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CHelpFile::CHelpFile(CWnd& rParent)
	: m_rParent(rParent)
{
}

inline void CHelpFile::Contents()
{
	WinHelp(m_rParent.Handle(), m_HelpFile, HELP_CONTENTS, 0L);
}

inline void CHelpFile::Topic(DWORD dwTopic)
{
	WinHelp(m_rParent.Handle(), m_HelpFile, HELP_CONTEXT, dwTopic);
}

inline void CHelpFile::Close()
{
	WinHelp(m_rParent.Handle(), m_HelpFile, HELP_QUIT, 0L);
}

#endif //HELPFILE_HPP
