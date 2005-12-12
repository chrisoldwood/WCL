/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STLUTILS.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	Various STL helper functions.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STLUTILS_HPP
#define STLUTILS_HPP

/******************************************************************************
** Helper function for std::for_each() etc to invoke delete on each element.
*/

template <typename T>
inline void DeleteElement(T pElement)
{
	delete pElement;
}

/******************************************************************************
** Delete the object at the given vector index.
** NB: Used as a replacement for TPtrArray::Delete().
*/

template <typename T>
inline void Delete(std::vector<T>& vVector, int nIndex)
{
	delete vVector[nIndex];
	vVector.erase(vVector.begin()+nIndex);
}

/******************************************************************************
** Deletes all objects in the given vector.
** NB: Used as a replacement for TPtrArray::DeleteAll().
*/

template <typename T>
inline void DeleteAll(std::vector<T>& vVector)
{
	std::for_each(vVector.begin(), vVector.end(), DeleteElement<T>);
	vVector.clear();
}

/******************************************************************************
** Find the index of the element within the vector. Returns -1 if not found.
** NB: Used as a replacement for TPtrArray::Find().
*/

template <typename T>
inline int FindIndexOf(std::vector<T>& vVector, T Value)
{
	std::vector<T>::const_iterator oIter = std::find(vVector.begin(), vVector.end(), Value);

	if (oIter == vVector.end())
		return -1;

	return oIter-vVector.begin();
}

/******************************************************************************
** Deep-copy elements from one vector to another.
** NB: Used as a replacement for TPtrArray::DeepCopy().
*/

template <typename T>
inline void DeepCopy(const std::vector<T*>& vInput, std::vector<T*>& vOutput)
{
	typedef std::vector<T*>::const_iterator CIter;

	vOutput.reserve(vInput.size());

	for (CIter oIter = vInput.begin(); oIter != vInput.end(); ++oIter)
		vOutput.push_back(new T(*(*oIter)));
}

#endif // STLUTILS_HPP
