#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>


using namespace std;



/*!
    /brief This struct represents one node of the tree with left and right node.
        Left, right and height are initialized with 0, val with the default constructor of
        the node type.
*/
template<class T>
struct Node {
        T val;
        Node<T>* left;
        Node<T>* right;
        int height;
        Node()
        {
            left=0;
            right=0;
            val=T();
            height=0;
        }

        /*!
         * \brief corrects the height after an insert/rotation/delete
         */
        void correctHeight()
        {
            if (left==0 && right==0)
                height = 0;
            else if (lHeight()>rHeight())
                height = lHeight()+1;
            else height = rHeight()+1;
        }

        /*!
         * \brief returns the height of the left tree
         * \return
         */
        int lHeight()
        {
            if (left!=0)
                return left->height;
            return 0;
        }

        /*!
         * \brief returns the height of the right tree
         * \return
         */
        int rHeight()
        {
            if (right!=0)
                return right->height;
            return 0;
        }

        /*!
         * \brief calculates the balanceFactor and returns it
         * \return
         */
        int balanceFactor()
        {
            int lh = left!=0 ? left->height+1 : 0;
            int rh = right!=0 ? right->height+1 : 0;
            return lh-rh;
        }

        friend class AVLTreeTest;
    };


/*!
 * This class is a binary tree storage structure, implemented as AVL tree. It can store
 * any primitive type or class which is comparable with <, >, ==. Duplicates are not allowed
 * will be ignored on insertion.
 */
template<class T>
class AVLTree {

    friend class AVLTreeTest;

private:
    Node<T>* root;
    bool initialized;
    int count;

    /*!
     * \brief checks if a rotation has to be made and calls the regarding method. This method is
     *  invoced by the insert method.
     * \param n node to be checked
     * \return returns the node n
     */
    Node<T>* rebalance(Node<T> *n)
    {
        n->correctHeight();
        int bf = n->balanceFactor();

        if(bf==2)
        {
            if (n->left->balanceFactor()==1)
                return rotateLL(n);
            else if (n->left->balanceFactor()==-1)
                return rotateLR(n);
            else if (n->left->balanceFactor()==0)
                return rotateLL(n);
        }

        if(bf==-2)
        {
            if (n->right->balanceFactor()==1)
                return rotateRL(n);
            else if (n->right->balanceFactor()==-1)
                return rotateRR(n);
            else if (n->right->balanceFactor()==0)
                return rotateRR(n);
        }

        return n;
    }


    /*!
     * \brief insert Inserts a node into the tree by parsing it recursively to find the right place.
     *      Rebalancing is done in the process. Duplicates will be ignored.
     * \param n is the current node. If val<n.val, the search for the right place to insert proceeds
     *      on the left subtree, if val>n.val the right subtree will be searched.
     * \param parent is the parent element of n.
     * \param val is the value thant will be inserted.
     */
    void insert(Node<T> *n, Node<T> *parent, T val)
    {
        // duplicates not allowed
        if (val==n->val)
            ;

        //go left
        if (val < n->val)
        {
            if (n->left==0)
            {
                n->left = new Node<T>();
                n->left->val = val;
                n->correctHeight();
                count++;
            }
            else
            {
                insert(n->left, n, val);
                Node<T> *tmp = rebalance(n);
                if (parent!=n)
                {
                    if (tmp->val > parent->val)
                        parent->right = tmp;
                    else parent->left = tmp;
                }
                if (parent==n)
                    root = tmp;
            }
        }

        //go right
        if (val > n->val)
        {
            if (n->right==0)
            {
                n->right = new Node<T>();
                n->right->val = val;
                n->correctHeight();
                count++;
            }
            else
            {
                insert(n->right, n, val);
                Node<T> *tmp = rebalance(n);
                if (parent!=n)
                {
                    if (tmp->val > parent->val)
                        parent->right = tmp;
                    else parent->left = tmp;
                }
                if (parent==n)
                    root = tmp;
            }
        }
    }

    /*!
     * \brief prints the subtree of node to the console or to any ostream. The first element
     *      to be printed is the leftmost - so the tree will be printed with the root node
     *      left and the leaf nodes right. Mind that, only small trees will be visually accurate
     *      on the console because of the 80 char limitation.
     * \param node is the node to print
     * \param output is the stream to print to
     * \param level represents the tree depth - is used to print the tree correctly
     */
    void print(Node<T> *node, ostream &output, int level=0)
    {
        /* Algorithm:
            call print(node->right, level+1)
            print out middle
            call print(node->left, level+1)
        */

        if (node->right!=0)
            print(node->right, output, level+1);

        for (int i=0; i<level; i++)
            output << "       ";

        output << node->val << "(" << node->height << ")";
        output << endl;

        if (node->left!=0)
        {
            print(node->left, output, level+1);
            output << endl;
        }
    }

    /*!
     * \brief clear delete all subnodes of node and node itself.
     * \param node is the node which will be deleted
     * \param debugOutput if true, every call of "delete" will be printed to the console.
     */
    void clear(Node<T> *node, bool debugOutput=false)
    {
        //remove left
        //remove right
        //remove middle

        if (node->left!=0)
            clear(node->left, debugOutput);
        if (node->right!=0)
            clear(node->right, debugOutput);

        if (debugOutput)
            cout << "delete node " << node->val << endl;
        delete node;
    }

    /*!
     * \brief remove removes a node from the tree.
     * \param t value to be removed.
     * \param node current node to be searched
     * \param parent parent node of node.
     * \return returns true, if the node has been found and deleted. False, if it was not found.
     */
    bool remove(T t, Node<T> *node, Node<T> *parent)
    {
        if (node->val==t)
        {
            //node is leaf
            if (node->left==0 && node->right==0)
            {
                parent->left = parent->left==node ? 0 : parent->left;
                parent->right = parent->right==node ? 0 : parent->right;

                delete node;
                parent->correctHeight();
                count--;
                return true;
            }
            else if (node->left==0 && node->right!=0)
            {
                T tmp = retreiveSmallestPredecessorAndRemoveNode(node->right, node);
                node->val = tmp;
            }
            else if (node->left!=0 && node->right==0)
            {
                T tmp = retreiveBiggestSuccessorAndRemoveNode(node->left, node);
                node->val = tmp;
                //node->left = node->left->left;
            }
            else if (node->left!=0 && node->right!=0)
            {
                T tmp = retreiveBiggestSuccessorAndRemoveNode(node->left, node);
                node->val = tmp;
            }

            node->correctHeight();
            parent->correctHeight();

            if (node==parent)
                root = rebalance(node);
            else
            {
                if (node==parent->right)
                    parent->right = rebalance(node);
                else parent->left = rebalance(node);
            }

            count--;
            return true;

        }
        else
        {
            bool res = false;
            if (t > node->val)
                res = remove(t, node->right, node);

            if (t < node->val)
                res = remove(t, node->left, node);

            if (node==parent)
                root = rebalance(node);
            else
            {
                if (node==parent->right)
                    parent->right = rebalance(node);
                else parent->left = rebalance(node);
            }
            return res;
        }

    }

    /*!
     * \brief goes right from node, until a leaf is found. The leaf is deletet and its value retreived.
     * \param node start node
     * \param parent parent of node
     * \return returns the value of the biggest successor
     */
    T retreiveBiggestSuccessorAndRemoveNode(Node<T> *node, Node<T> *parent)
    {
        if (node->right!=0)
        {
            if (node->right->val > node->val)
            {
                T tmp = retreiveBiggestSuccessorAndRemoveNode(node->right, node);
                parent->left = parent->left!=0 ? rebalance(parent->left) : 0;
                parent->right = parent->right!=0 ? rebalance(parent->right) : 0;
                return tmp;
            }
        }
        else
        {
            if (parent->left==node)
                parent->left= parent->left!=0 ? parent->left->left : 0;
            else parent->right= parent->right!=0 ? parent->right->left : 0;
            T tmp = node->val;
            delete node;
            return tmp;
        }
    }


    /*!
     * \brief goes left from node, until a leaf is found. The leaf is deletet and its value retreived.
     * \param node start node
     * \param parent parent of node
     * \return returns the value of the smallest successor
     */
    T retreiveSmallestPredecessorAndRemoveNode(Node<T> *node, Node<T> *parent)
    {
        if (node->left!=0)
        {
            if (node->left->val < node->val)
            {
                T tmp = retreiveSmallestPredecessorAndRemoveNode(node->left, node);
                parent->left = parent->left!=0 ? rebalance(parent->left) : 0;
                parent->right = parent->right!=0 ? rebalance(parent->right) : 0;
                return tmp;
            }
        }
        else
        {
            if (parent->left==node)
                parent->left= parent->left!=0 ? parent->left->left : 0;
            else parent->right= parent->right!=0 ? parent->right->left : 0;
            T tmp = node->val;
            delete node;
            return tmp;
        }
    }

public:

    /*!
     * \brief the tree is initialized and empty
     */
    AVLTree()
    {
        initialized=false;
        count=0;
    }


    ~AVLTree()
    {
        if (initialized)
            clear();
    }

    /*!
     * \brief returns the number of elements in the tree
     * \return
     */
    int size()
    {
        return count;
    }

    /*!
     * \brief rotateLL performs a left-left rotation
     * \param node node with balance factor 2
     * \return returns the root node of the rotation
     */
    Node<T>* rotateLL(Node<T> *node)
    {
        Node<T> *tmp = node->left;
        node->left = node->left->right;
        tmp->right = node;

        tmp->left->correctHeight();
        tmp->right->correctHeight();
        tmp->correctHeight();

        return tmp;
    }

    /*!
     * \brief rotateLR performs a left-right rotation
     * \param node node with balance factor 2
     * \return returns the root node of the rotation
     */
    Node<T>* rotateLR(Node<T> *node)
    {
        Node<T> *lrr = node->left->right->right;
        Node<T> *lrl = node->left->right->left;

        node->left->right->right = node;
        node->left->right->left = node->left;
        node = node->left->right;
        node->left->right = lrl;
        node->right->left = lrr;

        node->left->correctHeight();
        node->right->correctHeight();
        node->correctHeight();

        return node;
    }

    /*!
     * \brief rotateRL performs a right-left rotation
     * \param node node with balance factor 2
     * \return returns the root node of the rotation
     */
    Node<T>* rotateRL(Node<T> *node)
    {
        Node<T> *rll = node->right->left->left;
        Node<T> *rlr = node->right->left->right;

        node->right->left->left = node;
        node->right->left->right = node->right;
        node = node->right->left;
        node->right->left=rll; //???
        node->left->right=rlr;

        node->left->correctHeight();
        node->right->correctHeight();
        node->correctHeight();

        return node;
    }

    /*!
     * \brief rotateRR performs a rihgt-right rotation
     * \param node node with balance factor 2
     * \return returns the root node of the rotation
     */
    Node<T>* rotateRR(Node<T> *node)
    {
        Node<T> *tmp = node->right;
        node->right = node->right->left;
        tmp->left = node;

        tmp->left->correctHeight();
        tmp->right->correctHeight();
        tmp->correctHeight();

        return tmp;
    }

    /*!
     * \brief clear removes all elements of the tree
     * \param debugOutput if true, the deleted elements are printed to the console
     */
    void clear(bool debugOutput=false)
    {
        clear(root, debugOutput);
        count = 0;
        initialized=false;
    }

    /*!
     * \brief insert inserts a value into the tree
     * \param t value
     */
    void insert(T t)
    {
        if (!initialized)
        {
            root = new Node<T>();
            root->val = t;
            initialized = true;
            count++;
        }
        else
        {
            insert(root, root, t);
            root->correctHeight();
        }
    }


    /*!
     * \brief print prints the tree to the console. If a filename is specified, the tree will be printed to that file.
     * \param filename
     */
    void print(string filename="")
    {
        if (initialized)
        {
            if (filename == "")
            {
                ostream &output = cout;
                output << "===PRINT-TREE===================================================================" << endl;
                print(root, output, 0);
                output << "--------------------------------------------------------------------------------" << endl;
            }
            else
            {
                ofstream output;
                output.open(filename.c_str(), ios::out | ios::app | ios::binary);
                print (root, output, 0);
                output.close();
            }
        }
    }

    /*!
     * \brief remove removes a value from the tree
     * \param t value
     * \return true if a value is removed, false if not
     */
    bool remove(T t)
    {
        bool res = false;
        if (initialized && count>0)
            res = remove(t,root, root);
        if (count==0)
            initialized=false;
        return res;
    }

};


#endif // AVLTREE_H
