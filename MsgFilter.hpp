/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGFILTER.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMsgFilter & CMsgFilters class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MSGFILTER_HPP
#define MSGFILTER_HPP

/******************************************************************************
** 
** An interface used by objects which can process raw messages.
**
*******************************************************************************
*/

class CMsgFilter
{
public:
	//
	// Methods.
	//
	virtual bool ProcessMsg(MSG& rMsg) = 0;

protected:
	//
	// Constructors/Destructor.
	//
	CMsgFilter();
	~CMsgFilter();
	
	//
	// Members.
	//
};

/******************************************************************************
** 
** A collection class used to hold a list of message filters.
**
*******************************************************************************
*/

class CMsgFilters : public CPtrList
{
public:
	//
	// Constructors/Destructor.
	//
	CMsgFilters();
	~CMsgFilters();
	
	//
	// Methods.
	//
	void Add(CMsgFilter& rFilter);
	void Remove(CMsgFilter& rFilter);

	/////////////////////////////////////////////////////////////////
	// Class used to iterate the list.
	/////////////////////////////////////////////////////////////////

	class CIter : public CPtrListIter
	{
	public:
		//
		// Constructors/Destructor.
		//
		CIter(const CMsgFilters& rList);
		~CIter();

		//
		// Methods.
		//
		CMsgFilter* Next();
	};

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

inline void CMsgFilters::Add(CMsgFilter& rFilter)
{
	CPtrList::AddToHead(&rFilter);
}

inline void CMsgFilters::Remove(CMsgFilter& rFilter)
{
	CPtrList::Remove(&rFilter);
}

inline CMsgFilter* CMsgFilters::CIter::Next()
{
	return (CMsgFilter*) CPtrListIter::Next();
}

#endif //MSGFILTER_HPP
