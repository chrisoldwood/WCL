/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MRULIST.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMRUList class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MRULIST_HPP
#define MRULIST_HPP

/******************************************************************************
** 
** This class manages the list of Most Recently Used files for an App.
**
*******************************************************************************
*/

class CMRUList
{
public:
	//
	// Constructors/Destructor.
	//
	CMRUList(int nMaxSize = 4);
	~CMRUList();
	
	//
	// Accessors & mutators.
	//
	void Add(const char* pszPath);

	const CString& operator[](int nIndex) const;

	//
	// GUI methods.
	//
	void UpdateMenu(CMenu& rMenu, uint iCmdBase);

	//
	// Persistance methods.
	//
	void Load(CIniFile& rCfgFile);
	void Save(CIniFile& rCfgFile);

protected:
	//
	// Members.
	//
	int			m_nMaxSize;		// Max size of list.
	CStrArray	m_Paths;		// The list of MRU files.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline const CString& CMRUList::operator[](int nIndex) const
{
	return m_Paths[nIndex];
}

#endif //MRULIST_HPP
