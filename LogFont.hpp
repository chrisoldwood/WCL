/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LOGFONT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CLogFont class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LOGFONT_HPP
#define LOGFONT_HPP

/******************************************************************************
** 
** A thin wrapper around the LOGFONT structure.
**
*******************************************************************************
*/

class CLogFont : public tagLOGFONTA
{
public:
	//
	// Constructors/Destructor.
	//
	CLogFont();
	CLogFont(HFONT hFont);
	~CLogFont();
	
	//
	// Methods.
	//

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //LOGFONT_HPP
