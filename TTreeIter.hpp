/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TTREEITER.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The TTreeFwdIter class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TTREEITER_HPP
#define TTREEITER_HPP

/******************************************************************************
** 
** The template version of the tree forward iterator.
**
*******************************************************************************
*/

template<class T> class TTreeFwdIter
{
public:
	//
	// Constructors/Destructor.
	//
	TTreeFwdIter(TTree<T>& oTree);
	TTreeFwdIter(TTreeNode<T>* pNode);
	~TTreeFwdIter();
	
	//
	// Methods.
	//
	TTreeNode<T>* Next();

private:
	// Template shorthands.
	typedef TTreeFwdIter<T>	 CIter;
	typedef TPtrArray<CIter> CIterStack;

	//
	// Members.
	//
	TTreeNode<T>*	m_pNode;
	CIterStack		m_vIterStack;

	//
	// Disallow copying for now.
	//
	TTreeFwdIter(const TTreeFwdIter<T>&);
	void operator=(const TTreeFwdIter<T>&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

template<class T> inline TTreeFwdIter<T>::TTreeFwdIter(TTree<T>& oTree)
	: m_pNode(oTree.Root())
{
}

template<class T> inline TTreeFwdIter<T>::TTreeFwdIter(TTreeNode<T>* pNode)
	: m_pNode(pNode)
{
}

template<class T> inline TTreeFwdIter<T>::~TTreeFwdIter()
{
}

template<class T> inline TTreeNode<T>* TTreeFwdIter<T>::Next()
{
	TTreeNode<T>* pNode = NULL;

	// Start iteration?
	if (m_pNode != NULL)
	{
		pNode = m_pNode;

		// Populate iterator stack...
		for (int i = 0; i < m_pNode->NumNodes(); ++i)
			m_vIterStack.Add(new CIter(m_pNode->Node(i)));

		m_pNode = NULL;
	}

	// Iterator stack not empty?
	while ( (pNode == NULL) && (m_vIterStack.Size() > 0) )
	{
		// Query top iterator.
		if ((pNode = m_vIterStack[0]->Next()) == NULL)
			m_vIterStack.Delete(0);
	}

	return pNode;
}

#endif // TTREEITER_HPP
