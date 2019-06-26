#include "test.hpp"

int main()
{
	TestRBSTreeCreate();
	TestRBSTreeInsertOneKey();
	TestRBSTreeInsertManyKeys();
	TestRBSTreeDeleteKey();
	TestRBSTreeDeleteManyKeys();
	TestRBSTreeInsertRandomManyKeys();
	TestRBSTreeInsertSortAscendingMillionKeys();
	TestRBSTreeInsertSortDescendingMillionKeys();
	TestRBSTree_reduction_subtree();
	TestRBSTree_growth_subtree();
	TestRBSTreeLeftRotate();
	TestRBSTreeRightRotate();

	return 0;
}
