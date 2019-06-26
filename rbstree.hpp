#ifndef _RBSTREE_HPP_
#define _RBSTREE_HPP_

#include <iostream>
#include <ctime>
#include <cassert>

struct RBSTree
{
	struct Node
	{
		int m_key;
		int size_of_subtree;

		Node * m_pParent;
		Node * m_pLeft;
		Node * m_pRight;
	};

	Node * m_pRoot;
};

RBSTree * RBSTreeCreate();


void RBSTreeDestroy(RBSTree * _pTree);


RBSTree::Node * RBSTreeMinimumNode(RBSTree::Node * _pNode);


int RBSTreeMinimum(const RBSTree & _tree);


int RBSTreeMaximum(const RBSTree & _tree);


RBSTree::Node * RBSTreeCreateNode(int _key);


void RBSTreeInsert(RBSTree & _tree, int _key);


void RBSTreeLeftRotate(RBSTree & _tree, RBSTree::Node * _l);


void RBSTreeRightRotate(RBSTree & _tree, RBSTree::Node * _r);


void RBSTreeInsertRoot(RBSTree & _tree, RBSTree::Node * pCurrent, int _key);


void RBSTreeInsert(RBSTree & _tree, RBSTree::Node * _pNode, int _key);


RBSTree::Node * RBSTreeMerger(RBSTree::Node * _l, RBSTree::Node * _r);


void RBSTreeRemove(RBSTree & _tree, RBSTree::Node * _pNode, int _key);


void RBSTreeTransplant(RBSTree & _tree, RBSTree::Node * _pNode, RBSTree::Node * _pOtherNode);


typedef void(*RBSTreeWalkFunction) (const RBSTree::Node & _node);
void RBSTreeSymmetricWalk(const RBSTree & _tree, RBSTreeWalkFunction _f);


int getSize(RBSTree::Node * _pNode);


void fixSize(RBSTree::Node * _pNode);


bool RBSTreeHasKey(const RBSTree & _tree, int _key);


RBSTree::Node * RBSTreeFindKeyNode(const RBSTree & _tree, int _key);


int RBSTreeDepth(const RBSTree::Node * _pNode, int _currentDepth);


int RBSTreeDepth(const RBSTree * _pTree);


void growth_subtree(RBSTree::Node * pCurrent);


void reduction_subtree(RBSTree::Node * pCurrent);


#endif
