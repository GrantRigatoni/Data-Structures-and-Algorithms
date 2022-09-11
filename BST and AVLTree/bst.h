#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    Node<Key, Value>* deleteAndReturnParent(Node<Key, Value>* current); //helper TODO
    Node<Key, Value>* createNewNode(Key k, Value v, Node<Key, Value>* parent);
    Node<Key, Value>* downLeftToGreatest(Node<Key, Value>* current);
    void deleteFunction(Node<Key, Value> *root);//post order delete
    bool isLeftChild(Node<Key, Value>* current);
    int height(Node<Key, Value>* current, bool &help) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO    something == something else
    if(rhs.current_ == NULL && this->current_ == NULL)
    {
        return true;//nulls have no value so we know they are not equal
    }else if(rhs.current_ == NULL || this->current_ == NULL)
    {
        return false;
    }
    if (this->current_->getValue() == rhs.current_->getValue())
    {
        return true;
    }else return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if(rhs.current_ == NULL && this->current_ == NULL)
    {
        return false;//nulls have no value so we know they are not equal
    }else if(rhs.current_ == NULL || this->current_ == NULL)
    {
        return true;
    }
    if (this->current_->getValue() == rhs.current_->getValue())
    {
        return false;
    }else return true;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if(this->current_->getRight() == NULL)
    {
        while(true)
        {
            bool isLeftChild = false;
            //std::cout << "in while: operator++" << std::endl;
            if (this->current_->getParent() == NULL)//if parent is null, we are done
            {
                this->current_ = NULL;
                return *this;
            }
            //BinarySearchTree<Key, Value>::iterator temp(this->current_);
            if (this->current_->getParent()->getLeft() != NULL)
            {
                if(this->current_->getParent()->getLeft() == this->current_)
                {
                   isLeftChild = true;
                }    
            }
            else//is right child
            {
                isLeftChild = false;
            }
    
            if(isLeftChild)
            {
                this->current_ = this->current_->getParent();
                //std::cout << this->current_->getKey() << std::endl;
                return *this;
            }else
            {
                this->current_ = this->current_->getParent();
            }
            //we have iterated through the list
        }
    }else//right exists go right once and all the way left
    {
        //std::cout << "in operator++ else" << std::endl;
        this->current_ = this->current_->getRight();
        if(this->current_->getLeft() == NULL)
        {
            //std::cout << this->current_->getKey()<< std::endl;
            return *this;
        }
        while (this->current_->getLeft() != NULL)
        {
            this->current_ = this->current_->getLeft();
        }
        //std::cout << this->current_->getKey()<< std::endl;
        return *this;
    }
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //check if key is less than, greater than, or equal to node and move left, right, or replace 
    
    if (root_ == NULL)//insert as root if empty
    {
        root_ = createNewNode(keyValuePair.first, keyValuePair.second, NULL);
    }
    else
    {
        Node<Key, Value>* temp = root_;
        while (true)//find the spot to put this hoe
        {
        //std::cout << "in insert" << std::endl;
        if(keyValuePair.first > temp->getKey())
        {
            if(temp->getRight() == NULL)//we found our insert location
            {
                temp->setRight(createNewNode(keyValuePair.first, keyValuePair.second, temp));
                //std::cout << "inserted" << std::endl;
                break;
            }
            temp = temp->getRight();

        }else if (keyValuePair.first < temp->getKey())
        {
            if(temp->getLeft() == NULL)
            {
                temp->setLeft(createNewNode(keyValuePair.first, keyValuePair.second, temp));
                //std::cout << "inserted" << std::endl;
                break;

            }
            temp = temp->getLeft();

        }else
        {
            //std::cout << "Node updated b/c Key already exists in tree" << std::endl;
            temp->setValue(keyValuePair.second);
            break;
        }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::createNewNode(Key k, Value v, Node<Key, Value>* parent)
{
    //creates new node with appropriate parts
    //std::cout << "creating new node... " << std::endl;
    Node<Key, Value>* newNode = new Node<Key, Value>(k, v, parent);
    return newNode;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* temp = internalFind(key);//find key
    if (temp != NULL)
    {
    if (temp->getLeft() == NULL && temp->getRight() == NULL)
    {
        if(temp->getParent() == NULL)
        {
            root_ = NULL;
        }
        else if(isLeftChild(temp))
        {//temp 
            (temp->getParent())->setLeft(NULL);
        }else
        {
            (temp->getParent())->setRight(NULL);
        }
        delete temp;//deletes if leaf node
    }else if (temp->getLeft() == NULL)//only right so we promote
    {
        Node<Key, Value>* tempRight = temp->getRight();//4
        if(isLeftChild(temp))
        {
            //std::cout<< "is Left CHILD:remove" << std::endl;
            Node<Key, Value>* tempParent = deleteAndReturnParent(temp);
            if (tempParent != NULL)
            {
                tempParent->setLeft(tempRight);
            }else
            {
                root_ = tempRight;
            }
            tempRight->setParent(tempParent);

            
        }else
        {
            //std::cout<< "is Right CHILD:remove" << std::endl;
            Node<Key, Value>* tempParent = deleteAndReturnParent(temp);
            if (tempParent != NULL)
            {
                tempParent->setRight(tempRight);
            }else
            {
                root_ = tempRight;
            }
            tempRight->setParent(tempParent);
        }
    }else if(temp->getRight() == NULL)//only left so we promote left
    {
        Node<Key, Value>* tempLeft = temp->getLeft();
        if(isLeftChild(temp))
        {
            //std::cout<< "is Left CHILD:remove" << std::endl;
            
            Node<Key, Value>* tempParent = deleteAndReturnParent(temp);
            if (tempParent != NULL)
            {
                tempParent->setLeft(tempLeft);
            }else
            {
                root_ = tempLeft;
            }
            tempLeft->setParent(tempParent);

            
        }else
        {
            //std::cout<< "is Right CHILD:remove" << std::endl;
            Node<Key, Value>* tempParent = deleteAndReturnParent(temp);
            if (tempParent != NULL)
            {
                tempParent->setRight(tempLeft);
            }else
            {
                root_ = tempLeft;
            }
            tempLeft->setParent(tempParent);
        }
    }else//node has two children - promote predecessor and leave the other to the right
    {
        Node<Key, Value>* toSwap = downLeftToGreatest(temp);
        nodeSwap(toSwap, temp);//also make toSwap point down well and that node point up
        if(isLeftChild(temp))//else do this
        {//temp 
            if(temp->getLeft() != NULL)//do this if down to greatest doesn't go right at all
            {
                toSwap->setLeft(temp->getLeft());
                temp->getLeft()->setParent(toSwap);
            }else
            {
                toSwap->setLeft(NULL);
            }

        }else
        {
            (temp->getParent())->setRight(NULL);//wouldn't we get same issue
        }
        if (toSwap->getParent() == NULL)
        {
            root_ = toSwap;
        }
        delete temp;
    }
    }//else
}




template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //called only if node has two children
    //node has left child
    if(current->getLeft() != NULL)
    {
        //std::cout << "pred found" << std::endl;
        return current->getLeft();
    }
    //node does not have left child
    if (current->getParent() == NULL && current->getLeft() == NULL)
    {
            //std::cout << "no pred" << std::endl;
            return current->getParent();
    }else
    {//node has parent so we check if we're are right child, if so that is our predecessor
        while(true)
        {
            Key temp = current->getKey();
            if (((current->getParent())->getRight())->getKey() == temp)
            {
                //we found it! - the first parent where we are the right child
                //std::cout << "pred found" << std::endl;
                return current->getParent();
                break;
            }
            current = current->getParent();
            if(current == NULL)
            {
                //std::cout << "no pred" << std::endl;
                return current;
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::deleteAndReturnParent(Node<Key, Value>* current)
{
    Node<Key, Value>* parent = current->getParent();
    delete current;
    return parent;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::downLeftToGreatest(Node<Key, Value>* current)
{
    current = current->getLeft();
    //current = current->getLeft();
    while(current->getRight() != NULL)
    {
        current = current->getRight();
    }
    return current;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isLeftChild(Node<Key, Value>* current)
{
    Node<Key, Value>* temp = current->getParent();
    if(temp != NULL)
    {
        if(current == temp->getLeft())
        {
            return true;
        }else if (current == temp->getRight())
        {
            return false;
        }
    }
        //std::cout << "node not a child:isLeftChild" << std::endl;
        return false;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    deleteFunction(root_);
    root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteFunction(Node<Key, Value> *root) {
    if (root == NULL) {
        return;
    }
    deleteFunction(root->getLeft());
    deleteFunction(root->getRight());
    delete root;
}   


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

    Node<Key, Value>* findSmallest = root_;
    if(findSmallest != NULL)
    {
    while (findSmallest->getLeft() != NULL)
    {
        //std::cout << "in while: getSmallestNode" << std::endl;
        findSmallest = findSmallest->getLeft();

    }
    //std::cout << "smallest node's key = " << findSmallest->getKey() << std::endl;
    return findSmallest;
    }
    return NULL;
    //start at root and go left
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_;//when the node is swapped this don't work b/c shit be out of order
    while (true)
    {
        if(temp == NULL)
        {
            //std::cout << "key does not exitst: internalFind" << std::endl;
            return NULL;
        }
        else if(temp->getKey() == key)
        {
            return temp;
        }else if (key > temp->getKey())
        {
            temp = temp->getRight();
        }else if (key < temp->getKey())
        {
            temp = temp->getLeft();
        }
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == NULL) return true;
    bool help = true;
    height(root_, help);
    return help;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* current, bool &help) const
{
    if(current == NULL || !help) return 0;
    int left = height(current->getLeft(), help);
    int right = height(current->getRight(), help);
    if (abs(left-right) > 1)
    {
        help = false;
    }
    if(left > right) return 1 + left;
    else return right + 1;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
