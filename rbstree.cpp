#include "rbstree.hpp"

RBSTree * RBSTreeCreate()
{
	RBSTree * pTree = new RBSTree;
	pTree->m_pRoot = nullptr;
	return pTree;
}


RBSTree::Node * RBSTreeCreateNode(int _key)
{
	RBSTree::Node * pNewNode = new RBSTree::Node;
	pNewNode->m_key = _key;
	pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
	pNewNode->size_of_subtree = 1;
	return pNewNode;
}


void RBSTreeDestroy(RBSTree::Node * _pNode)
{
	if (!_pNode)
		return;

	RBSTreeDestroy(_pNode->m_pLeft);
	RBSTreeDestroy(_pNode->m_pRight);
	delete _pNode;
}


void RBSTreeDestroy(RBSTree * _pTree)
{
	RBSTreeDestroy(_pTree->m_pRoot);
	delete _pTree;
}


int RBSTreeDepth ( const RBSTree::Node * _pNode, int _currentDepth )
{
	int leftSubtreeDepth = 0;
	int rightSubtreeDepth = 0;

	if (_pNode->m_pLeft)
	{
		leftSubtreeDepth = RBSTreeDepth(_pNode->m_pLeft, _currentDepth + 1);
	}
	if (_pNode->m_pRight)
	{
		rightSubtreeDepth = RBSTreeDepth(_pNode->m_pRight, _currentDepth + 1);
	}

	if (leftSubtreeDepth >= rightSubtreeDepth
		&& leftSubtreeDepth >= (_currentDepth + 1))
	{
		return leftSubtreeDepth;
	}

	else if(rightSubtreeDepth >= leftSubtreeDepth
		&& rightSubtreeDepth >= (_currentDepth + 1))
	{
		return rightSubtreeDepth;
	}

	else
	{
		return _currentDepth + 1;
	}
	return _currentDepth;
}


int RBSTreeDepth(const RBSTree * _pTree)
{
	return RBSTreeDepth(_pTree->m_pRoot, 0);
}


void RBSTreeSymmetricWalk(const RBSTree::Node * _pNode, RBSTreeWalkFunction _f)
{
	if (!_pNode)
		return;

	RBSTreeSymmetricWalk(_pNode->m_pLeft, _f);
	(*_f)(*_pNode);
	RBSTreeSymmetricWalk(_pNode->m_pRight, _f);
}


void RBSTreeSymmetricWalk(const RBSTree & _tree, RBSTreeWalkFunction _f)
{
	RBSTreeSymmetricWalk(_tree.m_pRoot, _f);
}


void RBSTreeInsert(RBSTree & _tree, int _key)
{
	RBSTree::Node * pCurrent = _tree.m_pRoot;
	if (!pCurrent)
	{
		_tree.m_pRoot = RBSTreeCreateNode(_key);
		fixSize(_tree.m_pRoot);
		return;
	}
	else
	{
		RBSTreeInsert(_tree, pCurrent, _key);
		return;
	}
		

	assert(0);
	return ;
}


void RBSTreeLeftRotate(RBSTree & _tree, RBSTree::Node * _l)
{
	RBSTree::Node* r = _l->m_pRight;
	if (!r)
		return;

	r->size_of_subtree = _l->size_of_subtree;
	_l->size_of_subtree--;

	if (r->m_pRight)
		_l->size_of_subtree -= r->m_pRight->size_of_subtree;

	_l->m_pRight = r->m_pLeft;
	if (_l->m_pRight)
		_l->m_pRight->m_pParent = _l;

	r->m_pParent = _l->m_pParent;
	if (!r->m_pParent)
		_tree.m_pRoot = r;
	else if (_l == _l->m_pParent->m_pLeft)
		_l->m_pParent->m_pLeft = r;
	else if (_l == _l->m_pParent->m_pRight)
		_l->m_pParent->m_pRight = r;
	else
		assert(0);

	r->m_pLeft = _l;
	_l->m_pParent = r;

	return;
}


void RBSTreeRightRotate(RBSTree & _tree, RBSTree::Node * _r)
{
	RBSTree::Node* l = _r->m_pLeft;
	if (!l)
		return;


	l->size_of_subtree = _r->size_of_subtree;
	_r->size_of_subtree--;
	
	if (l->m_pLeft)
		_r->size_of_subtree -= l->m_pLeft->size_of_subtree;

	_r->m_pLeft = l->m_pRight;
	if (_r->m_pLeft)
		_r->m_pLeft->m_pParent = _r;

	l->m_pParent = _r->m_pParent;
	if (!l->m_pParent)
		_tree.m_pRoot = l;
	else if (_r == _r->m_pParent->m_pLeft)
		_r->m_pParent->m_pLeft = l;
	else if (_r == _r->m_pParent->m_pRight)
		_r->m_pParent->m_pRight = l;
	else
		assert(0);

	l->m_pRight = _r;
	_r->m_pParent = l;

	return;
}


RBSTree::Node * RBSTreeMinimumNode(RBSTree::Node * _pNode)
{
	assert(_pNode);

	RBSTree::Node * pCurrent = _pNode;
	while (pCurrent && pCurrent->m_pLeft)
		pCurrent = pCurrent->m_pLeft;

	return pCurrent;
}


int RBSTreeMinimum(const RBSTree & _tree)
{
	RBSTree::Node * pMinimumNode = RBSTreeMinimumNode(_tree.m_pRoot);
	return pMinimumNode->m_key;
}


int RBSTreeMaximum(const RBSTree & _tree)
{
	assert(_tree.m_pRoot);

	const RBSTree::Node * pCurrent = _tree.m_pRoot;
	while (pCurrent && pCurrent->m_pRight)
		pCurrent = pCurrent->m_pRight;

	return pCurrent->m_key;
}


void RBSTreeInsertRoot(RBSTree & _tree, RBSTree::Node * pCurrent, int _key)
{
	if (pCurrent->m_key == _key)
		return;

		else if (_key < pCurrent->m_key)
		{
			if (pCurrent->m_pLeft)
			{
				RBSTreeInsertRoot(_tree, pCurrent->m_pLeft, _key);
				RBSTreeRightRotate(_tree, pCurrent);
				return;
			}
			else
			{
				RBSTree::Node * pNewNode = RBSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pLeft = pNewNode;
				growth_subtree(pCurrent);
				return;
			}
		}

		else
		{
			if (pCurrent->m_pRight)
			{
				RBSTreeInsertRoot(_tree, pCurrent->m_pRight, _key);
				RBSTreeLeftRotate(_tree, pCurrent);
				return;
			}
			else
			{
				RBSTree::Node * pNewNode = RBSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pRight = pNewNode;
				growth_subtree(pCurrent);
				return;
			}
		}
}


void RBSTreeInsert(RBSTree & _tree, RBSTree::Node * pCurrent, int _key)
{
		if (pCurrent->m_key == _key)
			return;

		else if (rand() % (pCurrent->size_of_subtree + 1) == 0)
			return RBSTreeInsertRoot(_tree, pCurrent, _key);

		else if (_key < pCurrent->m_key)
		{
			if (pCurrent->m_pLeft)
			{
				RBSTreeInsert(_tree, pCurrent->m_pLeft, _key);
				return;
			}
			else
			{
				RBSTree::Node * pNewNode = RBSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pLeft = pNewNode;
				growth_subtree(pCurrent);
				return;
			}
		}

		else
		{
			if (pCurrent->m_pRight)
			{
				RBSTreeInsert(_tree, pCurrent->m_pRight, _key);
				return;
			}
			else
			{
				RBSTree::Node * pNewNode = RBSTreeCreateNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pRight = pNewNode;
				growth_subtree(pCurrent);
				return;
			}
		}
}


int getSize(RBSTree::Node * _pNode) 
{
	if (!_pNode) return 0;
	return _pNode->size_of_subtree;
}


void fixSize(RBSTree::Node * _pNode) 
{
	_pNode->size_of_subtree = getSize(_pNode->m_pLeft) + getSize(_pNode->m_pRight) + 1;
}


void growth_subtree(RBSTree::Node * pCurrent)
{
	while (pCurrent)
	{
		pCurrent->size_of_subtree++;
		pCurrent = pCurrent->m_pParent;
	}
}


void reduction_subtree(RBSTree::Node * pCurrent)
{
	while (pCurrent)
	{
		pCurrent->size_of_subtree--;
		pCurrent = pCurrent->m_pParent;
	}
}


RBSTree::Node * RBSTreeMerger(RBSTree::Node * _l, RBSTree::Node * _r)
{
	if (!_l) return _r;
	if (!_r) return _l;
	
	if ((rand() % (_l->size_of_subtree + _r->size_of_subtree)) < _l->size_of_subtree)
	{
		 _l->m_pRight = RBSTreeMerger(_l->m_pRight, _r);
		 _l->m_pRight->m_pParent = _l;
		 
		fixSize(_l);
		return _l;
	}
	
	else
	{
		_r->m_pLeft  = RBSTreeMerger(_l, _r->m_pLeft);
		_r->m_pLeft->m_pParent = _r;

		fixSize(_r);
		return _r;
	}
}


void RBSTreeRemove(RBSTree & _tree, RBSTree::Node * _pNode, int _key)
{
	if (!_pNode) return;

	if (_pNode->m_key == _key)
	{
		RBSTree::Node * q = RBSTreeMerger(_pNode->m_pLeft, _pNode->m_pRight);
		
		RBSTreeTransplant(_tree, _pNode, q);			

		if(_pNode->m_pParent)
			reduction_subtree(_pNode->m_pParent);
		
		delete _pNode;
		return;
	}

	else if (_key < _pNode->m_key)
		RBSTreeRemove(_tree, _pNode->m_pLeft, _key);

	else
		RBSTreeRemove(_tree, _pNode->m_pRight, _key);

	return;
}


void RBSTreeTransplant(RBSTree & _tree, RBSTree::Node * _pNode, RBSTree::Node * _pOtherNode)
{
	if (!_pNode->m_pParent)
	{
		assert(_pNode == _tree.m_pRoot);
		_tree.m_pRoot = _pOtherNode;
	}

	else if (_pNode->m_pParent->m_pLeft == _pNode)
		_pNode->m_pParent->m_pLeft = _pOtherNode;

	else if (_pNode->m_pParent->m_pRight == _pNode)
		_pNode->m_pParent->m_pRight = _pOtherNode;

	else
		assert(0);

	if (_pOtherNode)
	{
		_pOtherNode->m_pParent = _pNode->m_pParent;
		 _pOtherNode->size_of_subtree = _pNode->size_of_subtree - 1;
	}
}


RBSTree::Node * RBSTreeFindKeyNode(const RBSTree & _tree, int _key)
{
	RBSTree::Node * pCurrent = _tree.m_pRoot;
	while (pCurrent && pCurrent != nullptr)
	{
		if (_key == pCurrent->m_key)
			return pCurrent;

		else if (_key < pCurrent->m_key)
			pCurrent = pCurrent->m_pLeft;

		else
			pCurrent = pCurrent->m_pRight;
	}

	return nullptr;
}


bool RBSTreeHasKey(const RBSTree & _tree, int _key)
{
	return RBSTreeFindKeyNode(_tree, _key) != nullptr;
}
