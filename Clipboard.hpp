/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLIPBOARD.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CClipboard class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CLIPBOARD_HPP
#define CLIPBOARD_HPP

/******************************************************************************
** 
** This is a CStream derived class used to access the clipboard.
**
*******************************************************************************
*/

class CClipboard : public CStream
{
public:
	//
	// Constructors/Destructor.
	//
	CClipboard();
	~CClipboard();
	
	//
	// Open/Close operations.
	//
	void Open(Mode eMode, uint iFormat);
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, uint iNumBytes);
	virtual void  Write(const void* pBuffer, uint iNumBytes);
	virtual ulong Seek(ulong lPos, Origin eOrigin);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode);

protected:
	//
	// Members.
	//
	CMemStream	m_MemStream;	// Used to implement stream methods.
	uint		m_iFormat;		// The format of the clipboard data.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CClipboard::Read(void* pBuffer, uint iNumBytes)
{
	m_MemStream.Read(pBuffer, iNumBytes);
}

inline void CClipboard::Write(const void* pBuffer, uint iNumBytes)
{
	m_MemStream.Write(pBuffer, iNumBytes);
}

inline ulong CClipboard::Seek(ulong lPos, Origin eOrigin)
{
	return m_MemStream.Seek(lPos, eOrigin);
}

inline bool CClipboard::IsEOF()
{
	return m_MemStream.IsEOF();
}

inline void CClipboard::Throw(int eErrCode)
{
	m_MemStream.Throw(eErrCode);
}

#endif //CLIPBOARD_HPP
