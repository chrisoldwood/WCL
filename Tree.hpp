/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TREE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CTree class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TREE_HPP
#define TREE_HPP

/******************************************************************************
** 
** This class is used to store a node in the tree collection.
**
*******************************************************************************
*/

class CTreeNode
{
public:
	//
	// Constructors/Destructor.
	//
	CTreeNode();
	virtual ~CTreeNode();

	//
	// Methods.
	//
	virtual bool operator< (const CTreeNode& rRHS) const = 0;
	virtual bool operator==(const CTreeNode& rRHS) const;
	virtual bool operator!=(const CTreeNode& rRHS) const;

	//
	// Members.
	//
	CTreeNode*	m_pLeft;
	CTreeNode*	m_pParent;
	CTreeNode*	m_pRight;
};

/******************************************************************************
** 
** This is the base class for all tree collections.
**
*******************************************************************************
*/

class CTree
{
public:
	//
	// Methods.
	//
	int  Count() const;

protected:
	//
	// Constructors/Destructor.
	//
	CTree();
	~CTree();
	
	//
	// Methods.
	//
	void Add(CTreeNode& rItem);
	void Remove(const CTreeNode& rItem);
	void RemoveAll();
	CTreeNode* Find(const CTreeNode& rItem) const;

	//
	// Members.
	//
	CTreeNode*	m_pRoot;		// The root node.
	int			m_nCount;		// The number of items in the tree.


	// Friends.
	friend class CTreeIter;
};

/******************************************************************************
** 
** The base class used to iterate a tree collection.
**
*******************************************************************************
*/

class CTreeIter
{
public:
	// Traversal types.
	enum Method
	{
		PREORDER,
		INORDER,
		POSTORDER,
	};

protected:
	//
	// Constructors/Destructor.
	//
	CTreeIter(const CTree& rTree, Method eMethod);
	virtual ~CTreeIter();

	//
	// Methods.
	//
	CTreeNode* Next();

	//
	// Members.
	//
	Method		m_eMethod;	// The traversal method.
	CTreeNode*	m_pNext;	// The next node.

	// Friends.
	friend class CTree;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CTree::Count() const
{
	return m_nCount;
}

inline bool CTreeNode::operator==(const CTreeNode& rRHS) const
{
	return !((*this < rRHS) || (rRHS < *this));
}

inline bool CTreeNode::operator!=(const CTreeNode& rRHS) const
{
	return !(*this == rRHS);
}

#endif //TREE_HPP
