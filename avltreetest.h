#ifndef AVLTREETEST_H
#define AVLTREETEST_H

#include "avltree.h"
#include <string.h>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

const string line80chars = "################################################################################";

/*
 * This class tests the 4 kinds of rotations. If you call the test methods with (true), after every insertion the tree will be printed.
 */
class AVLTreeTest
{

private:
    static bool testRotation(string name, int v1, int v2, int v3, int rootShouldBe, int leftShouldBe, int rightShouldBe, bool printTree=false);
    static bool  checkIfIntTreeBalanced(Node<int> *node);
    static bool compareOrder(Node<int> *n, vector<int> *vec, int &index);
    AVLTreeTest();

public:
    static int height(Node<int> *node);
    static bool testLLRotation(bool printTree=false);
    static bool testLRRotation(bool printTree=false);
    static bool testRRRotation(bool printTree=false);
    static bool testRLRotation(bool printTree=false);
    static bool compareOrder(AVLTree<int> *tr, vector<int> *vec);
    static bool checkIfIntTreeBalanced(AVLTree<int> *tree);
    static bool randomNumbersTest(int count, int startRange=1, int endRange=1000000000);
};

#endif // AVLTREETEST_H
