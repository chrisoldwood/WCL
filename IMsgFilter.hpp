/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		IMSGFILTER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The IMsgFilter interface declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef IMSGFILTER_HPP
#define IMSGFILTER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** The interface used for pre-processing Windows messages.
**
*******************************************************************************
*/

class IMsgFilter
{
public:
	//
	// Methods.
	//
	virtual bool ProcessMsg(MSG& rMsg) = 0;

protected:
	// Make abstract.
	virtual ~IMsgFilter() {};
};

#endif //IMSGFILTER_HPP
