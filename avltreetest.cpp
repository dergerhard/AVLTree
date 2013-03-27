#include "avltreetest.h"


AVLTreeTest::AVLTreeTest()
{
}

/*!
      \brief Tests different rotations, by inserting 3 elements in a given order and then comparing
        the output to the expected result.
      \param name name of the rotation
      \param v1 value 1 to be inserted
      \param v2 value 2 to be inserted
      \param v3 value 3 to be inserted
      \param rootSouldBe value to compare with root node
      \param leftSouldBe value to compare with left node
      \param rightSouldBe value to compare with right node
      \param printTree if true, the tree will be printed after the check.
      \return bool true if the tree matches the control values after insertion, false if not
*/
bool AVLTreeTest::testRotation(string name, int v1, int v2, int v3, int rootShouldBe, int leftShouldBe, int rightShouldBe, bool printTree)
{
    cout << "TESTING " << name <<"-ROTATION" << endl;
    cout << line80chars << endl;

    AVLTree<int> *t = new AVLTree<int>();

    t->insert(v1);
    cout << v1 << " inserted" << endl;
    if (printTree)
        t->print();

    t->insert(v2);
    cout << v2 << " inserted" << endl;
    if (printTree)
        t->print();

    t->insert(v3);
    cout << v3 << " inserted" << endl;
    if (printTree)
        t->print();

    if (t->root->val==rootShouldBe &&
        t->root->left->val==leftShouldBe &&
        t->root->right->val==rightShouldBe)
    {
        cout << name <<" ROTATION PASSED SUCCESSFULLY! :)" << endl;
    }
    else
    {
        cout << name << " ROTATION FAILED! :(" << endl;
    }
    cout << line80chars << endl << endl;

}

/*!
      \brief Tests the left-left rotation
      \param printTree if true, the tree will be printed after the check.
      \return bool if the rotation is done correctly, false if not
*/
bool AVLTreeTest::testLLRotation(bool printTree)
{
    return testRotation("LEFT-LEFT", 5,4,3, 4,3,5, printTree);
}

/*!
      \brief Tests the left-right rotation
      \param printTree if true, the tree will be printed after the check.
      \return bool if the rotation is done correctly, false if not
*/
bool AVLTreeTest::testLRRotation(bool printTree)
{
    return testRotation("LEFT-RIGHT", 5,3,4, 4,3,5, printTree);

}

/*!
      \brief Tests the right-right rotation
      \param printTree if true, the tree will be printed after the check.
      \return bool if the rotation is done correctly, false if not
*/
bool AVLTreeTest::testRRRotation(bool printTree)
{
    return testRotation("RIGHT-RIGHT", 3,4,5, 4,3,5, printTree);
}

/*!
      \brief Tests the right-left rotation
      \param printTree if true, the tree will be printed after the check.
      \return bool if the rotation is done correctly, false if not
*/
bool AVLTreeTest::testRLRotation(bool printTree)
{
    return testRotation("RIGHT-LEFT", 3,5,4, 4,3,5, printTree);
}


/*!
      \brief Recursively calculates the nodes height.
      \param node node to calculate height
      \return int height of the node
*/
int AVLTreeTest::height(Node<int> *node)
{
    if (node==0)
        return 0;

    if (node->left==0 && node->right==0)
        return 1;

    int lHeight = 0;
    int rHeight = 0;

    if (node->left!=0)
        lHeight = height(node->left);

    if (node->right!=0)
        rHeight = height(node->right);

    return (lHeight>rHeight ? lHeight+1 : rHeight+1);
}


/*!
      \brief Checks if a node is balanced. To check the whole tree - use the root node.
      \param node node to be checked.
      \return bool true if the tree is balanced, false if it is not
*/
bool AVLTreeTest::checkIfIntTreeBalanced(Node<int> *node)
{/*
    IsHeightBalanced(tree)
        return (tree is empty) or
               (IsHeightBalanced(tree.left) and
                IsHeightBalanced(tree.right) and
                abs(Height(tree.left) - Height(tree.right)) <= 1)*/
    if (node==0)
        return true;

    int lHeight = height(node->left);
    int rHeight = height(node->right);
    //cout << "lh/rh: " << lHeight << "/" << rHeight << endl;
    if (((checkIfIntTreeBalanced(node->left) && checkIfIntTreeBalanced(node->right)) &&
            (abs(lHeight - rHeight)<=1)))
        return true;

    return false;
}


/*!
      \brief Recursively calculates the tree/subtree heights and calculates the balance factor.
      \param tree AVLTree to be checked
      \return bool true if the tree is balanced, false if it is not
*/
bool AVLTreeTest::checkIfIntTreeBalanced(AVLTree<int> *tree)
{
    return checkIfIntTreeBalanced(tree->root);
}


/*!
      \brief Recursive implementation of the compareOrder method.
      \param n the starting node to compare. If you want to compare the whole tree, start
        with the root node.
      \param vec the STL vector to be compared
      \param index represents the index of the vector to start to compare with. Keep in mind, that
        this parameter is mutated during execution!
      \return bool true if order matches, false if not
*/
bool AVLTreeTest::compareOrder(Node<int> *n, vector<int> *vec, int &index)
{
    if (n->left!=0)
        if (!compareOrder(n->left, vec, index))
            return false;

    //cout << index << ": " << n->val << "/" << vec->at(index) << endl;

    if (n->val!=vec->at(index++))
        return false;

    if (n->right!=0)
        if (!compareOrder(n->right, vec, index))
            return false;

    return true;
}

/*!
      \brief Sequencially compares every element of the vector with every element of the tree
        starting with the leftmost leaf, finishing with the rightmost leaf.
      \param tr AVLTree to be compared
      \param vec STL vector to be compared
      \return bool true if order matches, false if not
*/
bool AVLTreeTest::compareOrder(AVLTree<int> *tr, vector<int> *vec)
{
    int index =0;
    return compareOrder(tr->root, vec, index);

}

/*!
      \brief Starts a test of the AVLTree by generating random numbers and storing them
        in an STL vector first. Then it is sorted and duplicates are removed, as they are
        not allowed in the AVLTree class. After inserting them into the AVLTree class,
        various tests are performed to ensure, that the tree is balanced and all values
        in the previously created vector are present in the tree, as well as in the correct
        order. The method prints out debug output on cout.

      \param count set the number of random numbers to be created. Keep in mind, that
        random numbers are created between 1 and 1,000,000,000. So this is the maximum
        numbers to test with.
      \return true if test is passed, false if not
*/
bool AVLTreeTest::randomNumbersTest(int count, int startRange, int endRange)
{
    vector<int> *stlVec = new vector<int>();
    srand (time(NULL));

    cout << line80chars << endl;
    cout << "Preparing test..." << endl;
    cout << "    Generating " << count << " random numbers between " <<  startRange << " and " << endRange << "...... ";
    cout.flush();
    for (int i=0; i<count; i++)
        stlVec->push_back(rand()%endRange+startRange);
    cout << "done" << endl;


    cout << "    Sorting values...... " ;
    cout.flush();
    std::sort (stlVec->begin(), stlVec->end());
    cout << "done" << endl;


    cout << "    Eliminating duplicates...... " ;
    cout.flush();
    stlVec->erase(unique(stlVec->begin(), stlVec->end()), stlVec->end());
    cout << "done" << endl;
    cout << "    " << (count-stlVec->size()) << " duplicates removed" << endl;




    cout << "Running insert test...... " << endl;
    cout << "    Inserting elements into the AVLTree...... " ;
    cout.flush();
    AVLTree<int> *tr = new AVLTree<int>();
    for (int i=0; i<stlVec->size(); i++)
        tr->insert(stlVec->at(i));
    cout << "done" << endl;

    cout << "    Checking balance...... ";
    cout.flush();
    bool balanced = AVLTreeTest::checkIfIntTreeBalanced(tr);
    if (balanced)
        cout << "done and succeeded" << endl;
    else cout << "done and failed" << endl;

    cout << "    Comparing order...... ";
    cout.flush();
    cout << (compareOrder(tr, stlVec) ? "order correct" : "order INCORRECT") << endl;

    cout << "    Checking size for match...... ";
    cout.flush();
    if (stlVec->size()==tr->size())
        cout << "succeeded" << endl;
    else cout << "failed. Size difference is" << (stlVec->size()-tr->size()) << endl;


    cout << "Running delete test...... " << endl;
    cout << "    Deleting half the elements from the AVLTree...... " ;
    cout.flush();
    for (int i=0; i<(stlVec->size()/10); i++)
    {
        int removeAt =rand() % stlVec->size();
        int removeValue = stlVec->at(removeAt);
        tr->remove(removeValue);
        stlVec->erase(stlVec->begin()+removeAt);
    }
    cout << "done" << endl;


    cout << "    Checking balance...... ";
    cout.flush();
    balanced = AVLTreeTest::checkIfIntTreeBalanced(tr);
    if (balanced)
        cout << "done and succeeded" << endl;
    else cout << "done and failed" << endl;

    cout << "    Comparing order...... ";
    cout.flush();
    cout << (compareOrder(tr, stlVec) ? "order correct" : "order INCORRECT") << endl;

    cout << "    Checking size for match...... ";
    cout.flush();
    int vs = stlVec->size();
    int ts = tr->size();
    cout << vs << "/" << ts << endl;
    if (stlVec->size()==tr->size())
        cout << "succeeded" << endl;
    else cout << "failed. Size difference is" << (stlVec->size()-tr->size()) << endl;



}
