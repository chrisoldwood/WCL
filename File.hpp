/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CFile class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FILE_HPP
#define FILE_HPP

/******************************************************************************
** 
** This class encapsulates I/O to a binary/ASCII file.
**
*******************************************************************************
*/

class CFile : public CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CFile();
	~CFile();
	
	//
	// Member access.
	//
	HFILE Handle() const;
	CPath Path() const;

	//
	// Open/Close operations.
	//
	void Create(const char* pszPath);
	void Open(const char* pszPath, Mode eMode);
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, uint iNumBytes);
	virtual void  Write(const void* pBuffer, uint iNumBytes);
	virtual ulong Seek(ulong lPos, Origin eOrigin = Start);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode);

	//
	// Members.
	//

protected:
	//
	// Internal members.
	//
	HFILE	m_hFile;	// The files' handle.
	CPath	m_Path;		// The files' path.
	ulong	m_lEOF;		// Used to determine EOF.
};


/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HFILE CFile::Handle() const
{
	return m_hFile;
}

inline CPath CFile::Path() const
{
	return m_Path;
}

#endif //FILE_HPP
