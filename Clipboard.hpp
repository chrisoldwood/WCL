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
#ifndef WCL_CLIPBOARD_HPP
#define WCL_CLIPBOARD_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "MemStream.hpp"

/* WINVER >= 0x0500 */
#ifndef CF_DIBV5
#define CF_DIBV5	17
#endif 

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
	// Properties.
	//
	size_t Size() const;

	//
	// Open/Close operations.
	//
	void Open(uint nMode, uint iFormat);
	void Close();

	//
	// Overriden generic operations.
	//
	virtual void  Read(void* pBuffer, size_t nNumBytes);
	virtual void  Write(const void* pBuffer, size_t nNumBytes);
	virtual WCL::StreamPos Seek(WCL::StreamPos lPos, SeekPos eFrom = BEGIN);
	virtual bool  IsEOF();
	virtual void  Throw(int eErrCode, DWORD dwLastError);

	//
	// Helper methods.
	//
	static bool CopyText(HWND hOwner, const tchar* pszText);

	static bool IsEmpty();
	static bool IsFormatAvail(uint nFormat);
	static bool PasteText(CString& strString);

	//
	// Format methods.
	//
	static bool    IsStdFormat(uint nFormat);
	static uint    RegisterFormat(const tchar* pszFormat);
	static CString FormatName(uint nFormat);
	static uint    FormatHandle(const tchar* pszFormat);

protected:
	//! The memory buffer smart-pointer type.
	typedef Core::SharedPtr<CBuffer> BufferPtr;
	//! The stream adaptor smart-pointer type.
	typedef Core::SharedPtr<CMemStream> MemStreamPtr;

	//
	// Members.
	//
	BufferPtr		m_pBuffer;		// Buffer for stream.
	MemStreamPtr	m_pStream;		// Used to implement stream methods.
	uint			m_iFormat;		// The format of the clipboard data.

private:
	/**************************************************************************
	** Structure used for standard formats table
	*/

	struct FmtEntry
	{
		uint			m_nFormat;		// Handle.
		const tchar*	m_pszFormat;	// Name.
	};

	static FmtEntry s_oStdFormats[];
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline size_t CClipboard::Size() const
{
	return m_pStream->Size();
}

inline void CClipboard::Read(void* pBuffer, size_t nNumBytes)
{
	m_pStream->Read(pBuffer, nNumBytes);
}

inline void CClipboard::Write(const void* pBuffer, size_t nNumBytes)
{
	m_pStream->Write(pBuffer, nNumBytes);
}

inline WCL::StreamPos CClipboard::Seek(WCL::StreamPos lPos, SeekPos eFrom)
{
	return m_pStream->Seek(lPos, eFrom);
}

inline bool CClipboard::IsEOF()
{
	return m_pStream->IsEOF();
}

inline void CClipboard::Throw(int eErrCode, DWORD dwLastError)
{
	m_pStream->Throw(eErrCode, dwLastError);
}

#endif // WCL_CLIPBOARD_HPP
