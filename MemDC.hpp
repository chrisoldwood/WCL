/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMDC.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMemDC class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMDC_HPP
#define MEMDC_HPP

/******************************************************************************
** 
** This is a Device derived class that is used when creating a dc compatible
** with another dc.
**
*******************************************************************************
*/

class CMemDC : public CDC
{
public:
	//
	// Constructors/Destructor.
	//
	CMemDC(const CDC& rDC);
	~CMemDC();
	
	// RTTI
	virtual	Device Type() const;
	
protected:
	//
	// Members.
	//
	Device	m_devType;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMDC_HPP
