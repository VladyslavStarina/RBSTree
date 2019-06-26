#include "test.hpp"

void TestRBSTreeCreate()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTreeInsertOneKey()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	RBSTreeInsert(*pTree, 10);
	assert(RBSTreeHasKey(*pTree, 10));

	RBSTreeDestroy(pTree);
}

void TestRBSTreeInsertManyKeys()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	int keys[] = { 5, 2, 7, 3, 9, 0, 1, 4, 6, 8 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, keys[i]);

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, keys[i]));

	assert(RBSTreeMinimum(*pTree) == 0);
	assert(RBSTreeMaximum(*pTree) == 9);

	RBSTreeDestroy(pTree);
}

void TestRBSTreeDeleteKey()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	RBSTreeInsert(*pTree, 10);
	assert(RBSTreeHasKey(*pTree, 10));

	RBSTreeRemove(*pTree, pTree->m_pRoot, 10);
	assert(!RBSTreeHasKey(*pTree, 10));

	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTreeDeleteManyKeys()
{
	RBSTree * pTree = RBSTreeCreate();

	int keys[] = { 5, 2, 7, 3, 9, 0, 1, 4, 6, 8 };
	int nKeys = sizeof(keys) / sizeof(int);

	double time = clock();

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, keys[i]);

	std::cout << "Time of 10 elements : " << (clock() - time) / CLOCKS_PER_SEC << "\n";

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, keys[i]));
	
	int depth = RBSTreeDepth(pTree);
	std::cout << "Depth of 10 elements : " << depth << "\n\n";

	for (int i = 0; i < nKeys; i++)
	{
		RBSTreeRemove(*pTree, pTree->m_pRoot, keys[i]);

		assert(!RBSTreeHasKey(*pTree, keys[i]));

		for (int k = i + 1; k < nKeys; k++)
			assert(RBSTreeHasKey(*pTree, keys[k]));
	}

	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTreeInsertRandomManyKeys()
{
	RBSTree * pTree = RBSTreeCreate();

	int nKeys = 1000000;
	int * keys = new int[nKeys];

	for (int i = 0; i < nKeys; i++)
		keys[i] = ( rand() << 16 ) + rand() ;

	double time = clock();

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, keys[i]);

	std::cout << "Time of 1000000 elements : " << (clock() - time) / CLOCKS_PER_SEC << "\n";
	
	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, keys[i]));

	int depth = RBSTreeDepth(pTree);
	std::cout << "Depth of 1000000 elements : " << depth << "\n\n";

	for (int i = 0; i < nKeys; i++)
	{
		RBSTreeRemove(*pTree, pTree->m_pRoot, keys[i]);
		assert(!RBSTreeHasKey(*pTree, keys[i]));
	}
	
	delete [] keys;
	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTreeInsertSortAscendingMillionKeys()
{
	RBSTree * pTree = RBSTreeCreate();

	int nKeys = 1000000;
	double time = clock();

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, i);

	std::cout << "Time of 1000000 sort ascending elements : " << (clock() - time)/ CLOCKS_PER_SEC << "\n";
	
	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, i));

	assert(pTree->m_pRoot->size_of_subtree == nKeys);

	int depth = RBSTreeDepth(pTree);
	std::cout << "Depth of 1000000 sort ascending elements : " << depth << "\n\n";

	for (int i = 0; i < nKeys; i++)
	{
		RBSTreeRemove(*pTree, pTree->m_pRoot, i);
		assert(!RBSTreeHasKey(*pTree, i));
	}

	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTreeInsertSortDescendingMillionKeys()
{
	RBSTree * pTree = RBSTreeCreate();

	int nKeys = 1000000;
	double time = clock();

	for (int i = nKeys - 1; i >= 0; i--)
		RBSTreeInsert(*pTree, i);
	
	std::cout << "Time of 1000000 sort descending elements : " << (clock() - time) / CLOCKS_PER_SEC << "\n";
	
	for (int i = nKeys - 1; i > 0; i--)
		assert(RBSTreeHasKey(*pTree, i));

	assert(pTree->m_pRoot->size_of_subtree == nKeys);

	int depth = RBSTreeDepth(pTree);
	std::cout << "Depth of 1000000 sort descending elements : " << depth << "\n\n";

	for (int i = 0; i < nKeys; i++)
	{
		RBSTreeRemove(*pTree, pTree->m_pRoot, i);
		assert(!RBSTreeHasKey(*pTree, i));
	}

	assert(pTree->m_pRoot == nullptr);
	RBSTreeDestroy(pTree);
}

void TestRBSTree_growth_subtree()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	int nKeys = 10;

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, i);

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, i));

	assert(pTree->m_pRoot->size_of_subtree == nKeys);

	RBSTreeDestroy(pTree);
}

void TestRBSTree_reduction_subtree()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	int nKeys = 10;

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, i);

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, i));
	
	for (int i = nKeys/2; i < nKeys; i++)
	{
		RBSTreeRemove(*pTree, pTree->m_pRoot, i);
		assert(!RBSTreeHasKey(*pTree, i));
	}

	assert(pTree->m_pRoot->size_of_subtree == nKeys/2);

	RBSTreeDestroy(pTree);
}

void TestRBSTreeLeftRotate()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	int keys[] = { 1, 2 , 3};
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, keys[i]);

	if (pTree->m_pRoot->m_key == 2)
	{
		RBSTreeLeftRotate(*pTree, pTree->m_pRoot);
		assert(!pTree->m_pRoot->m_pRight);
	}

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, keys[i]));

	RBSTreeDestroy(pTree);
}

void TestRBSTreeRightRotate()
{
	RBSTree * pTree = RBSTreeCreate();
	assert(pTree);

	int keys[] = { 1, 2 , 3 };
	int nKeys = sizeof(keys) / sizeof(int);

	for (int i = 0; i < nKeys; i++)
		RBSTreeInsert(*pTree, keys[i]);

	if (pTree->m_pRoot->m_key == 2)
	{
		RBSTreeRightRotate(*pTree, pTree->m_pRoot);
		assert(!pTree->m_pRoot->m_pLeft);
	}

	for (int i = 0; i < nKeys; i++)
		assert(RBSTreeHasKey(*pTree, keys[i]));

	RBSTreeDestroy(pTree);
}
