/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TREE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CTree class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTree::CTree()
	: m_pRoot(NULL)
	, m_nCount(0)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTree::~CTree()
{
	RemoveAll();
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds an item to the tree.
**
** Parameters:	rItem	The item to add.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTree::Add(CTreeNode& rItem)
{
}

/******************************************************************************
** Method:		Remove()
**
** Description:	Removes an item from the tree.
**
** Parameters:	rItem	The item to remove.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTree::Remove(const CTreeNode& rItem)
{
}

/******************************************************************************
** Method:		RemoveAll()
**
** Description:	Removes all items from the list.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTree::RemoveAll()
{
	// Perform a post-order traversal.
	CTreeIter	oIter(*this, CTreeIter::POSTORDER);
	CTreeNode*	pNext = NULL;

	// Remove all nodes.
	while ((pNext = oIter.Next()) != NULL)
		delete pNext;

	// Reset members.
	m_pRoot  = NULL;
	m_nCount = 0;
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds an item in the tree.
**
** Parameters:	rItem	The tree to find.
**
** Returns:		The item or NULL.
**
*******************************************************************************
*/

CTreeNode* CTree::Find(const CTreeNode& rItem) const
{
	return NULL;
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTreeNode::CTreeNode()
	: m_pLeft(NULL)
	, m_pParent(NULL)
	, m_pRight(NULL)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTreeNode::~CTreeNode()
{
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	rTree	The tree to iterate.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTreeIter::CTreeIter(const CTree& rTree, Method eMethod)
	: m_eMethod(eMethod)
	, m_pNext(rTree.m_pRoot)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTreeIter::~CTreeIter()
{
}

/******************************************************************************
** Method:		Next()
**
** Description:	Returns the next node based on the traversal method.
**
** Parameters:	None.
**
** Returns:		The next node or NULL.
**
*******************************************************************************
*/

CTreeNode* CTreeIter::Next()
{
	return NULL;
}
