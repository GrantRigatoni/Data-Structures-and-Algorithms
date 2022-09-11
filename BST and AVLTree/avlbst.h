#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void leftRotation(AVLNode<Key,Value>* x);//rotates left
    void rightRotation(AVLNode<Key,Value>* x);//rotates right
    void RightLeftRotation(AVLNode<Key,Value>* x);//right left rotate
    void LeftRightRotation(AVLNode<Key,Value>* x);//left right rotate
    bool isLeftChild(Node<Key, Value>* current);//sees if node is left child
    bool isChild(AVLNode<Key,Value>* current);//checks if node is child
    void updateHeight(AVLNode<Key,Value>* current);//updates height of node to correct value
    AVLNode<Key, Value>* createNewNode(Key k, Value v, AVLNode<Key, Value>* parent);//creates new node
    AVLNode<Key, Value>* insertLocation(const std::pair<const Key, Value> &new_item);//returns location of insert
    AVLNode<Key, Value>* removeLocation(const Key& key);//returns location of removed node
    //AVLNode<Key, Value>* removeLocation(const Key& key);
    
    //How to Cast:
    //static_cast<AVLNode<Key,Value>*>(bstHelperFunction(input))
    
};

template<typename Key, typename Value>
bool AVLTree<Key, Value>::isChild(AVLNode<Key, Value>* current)
{
    if(current->getParent() != NULL) return true;
    return false;
}


template<typename Key, typename Value>
bool AVLTree<Key, Value>::isLeftChild(Node<Key, Value>* current)
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

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::createNewNode(Key k, Value v, AVLNode<Key, Value>* parent)
{
    //creates new node with appropriate parts
    //std::cout << "creating new node... " << std::endl;
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(k, v, parent);
    return newNode;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* currentLocation = insertLocation(new_item);
    AVLNode<Key, Value>* previousLocation = currentLocation;
    currentLocation = currentLocation->getParent();
    if (currentLocation != NULL)
    {
    while(currentLocation != NULL)
    {
        updateHeight(currentLocation);
        if(isLeftChild(currentLocation))//we are a left child
        {
            if(currentLocation->getParent()->getRight() == NULL)//if parent doesn't have another child we compare height to 0
            {
                if (currentLocation->getHeight() > 1)//left children do right rotation if previous if a left child
                {
                    if (isLeftChild(previousLocation))
                    {rightRotation(currentLocation->getParent());}
                    else{LeftRightRotation(currentLocation->getParent());}
                    //std::cout << "current location = " << currentLocation->getKey() << std::endl;
                    //std::cout << "prev location = " << previousLocation->getKey() << std::endl;
                    break;
                }
                //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                previousLocation = currentLocation;
                currentLocation = currentLocation->getParent();
                
            }else
            {
                
                if (abs(currentLocation->getHeight() - currentLocation->getParent()->getRight()->getHeight()) > 1)//checks if children are unbalanced
                {
                    if (isLeftChild(previousLocation))
                    {rightRotation(currentLocation->getParent());}
                    else{LeftRightRotation(currentLocation->getParent());}
                    //std::cout << "current location = " << currentLocation->getKey() << std::endl;
                    //std::cout << "prev location = " << previousLocation->getKey() << std::endl;
                    break;
                }else//keep goin up the tree
                {
                    //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                    previousLocation = currentLocation;
                    currentLocation = currentLocation->getParent();
                }
            }
        }else if(isChild(currentLocation))//we are a right 
        {
            if(currentLocation->getParent()->getLeft() == NULL)//if parent doesn't have another child we compare height to 0
            {
                if (currentLocation->getHeight() > 1)//compares height with null
                {
                    if (!isLeftChild(previousLocation))
                        {leftRotation(currentLocation->getParent());}
                    else{RightLeftRotation(currentLocation->getParent());}
                    //std::cout << "current location = " << currentLocation->getKey() << std::endl;
                    //std::cout << "prev location = " << previousLocation->getKey() << std::endl;
                    break;
                        
                }
                //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                previousLocation = currentLocation;
                currentLocation = currentLocation->getParent();
            }else
            {
                if (abs(currentLocation->getHeight() - currentLocation->getParent()->getLeft()->getHeight()) > 1)//checks if children are unbalanced
                {
                    if (!isLeftChild(previousLocation))
                        {leftRotation(currentLocation->getParent());}
                    else{RightLeftRotation(currentLocation->getParent());}
                    //std::cout << "current location = " << currentLocation->getKey() << std::endl;
                    //std::cout << "prev location = " << previousLocation->getKey() << std::endl;
                    break;
                }else{
                    //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                    previousLocation = currentLocation;
                    currentLocation = currentLocation->getParent();
                }
            }
        }else break;//we are at the top of the tree
    }
    }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insertLocation(const std::pair<const Key, Value> &new_item)
{
    // TODO
    //check if key is less than, greater than, or equal to node and move left, right, or replace 
    
    if (this->root_ == NULL)//insert as root if empty
    {
        this->root_= createNewNode(new_item.first, new_item.second, NULL);
        return static_cast<AVLNode<Key,Value>*>(this->root_);
    }
    else
    {
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
        while (true)//find the spot to put this hoe
        {
        //std::cout << "in insert" << std::endl;
        if(new_item.first > temp->getKey())
        {
            if(temp->getRight() == NULL)//we found our insert location
            {
                temp->setRight(createNewNode(new_item.first, new_item.second, temp));
                //std::cout << "inserted" << std::endl;
                return temp->getRight();
            }
            temp = temp->getRight();

        }else if (new_item.first < temp->getKey())
        {
            if(temp->getLeft() == NULL)
            {
                temp->setLeft(createNewNode(new_item.first, new_item.second, temp));
                //std::cout << "inserted" << std::endl;
                return temp->getLeft();

            }
            temp = temp->getLeft();

        }else
        {
            //std::cout << "Node updated b/c Key already exists in tree" << std::endl;
            temp->setValue(new_item.second);
            return temp;
        }
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    std::cout << "deleting Node: " << key << std::endl;
    AVLNode<Key,Value>* temp = removeLocation(key);
    //Key help;
    if (temp != NULL)
    {
        //help = static_cast<AVLNode<Key,Value>*>(temp)->getKey();
         std::cout << "remove Location: " << temp->getKey() << std::endl;
    

    //if children are null,we have parent so make height 1 and update all parent heights (Note:when we update heights look at other children and take heigher baase height)
        // TODO
    int rightH = 0;//use these to see if the removal caused an imbalance - otherwise just go up the tree
    int leftH = 0;
    bool leafNodeRootException = false;
    if(temp->getLeft() == NULL && temp->getRight() == NULL)//removal spot has no children
    {
        temp->setHeight(1);
        if(temp->getParent() == NULL) 
        {   
            leafNodeRootException = true;//if our removal spot is the root back off
           
        }else if(temp->getParent()->getParent() == NULL) leafNodeRootException = true;
    }else if(temp->getLeft() != NULL && temp->getRight() == NULL)//left child
    {
        temp->setHeight(temp->getLeft()->getHeight() + 1);
        leftH = temp->getLeft()->getHeight();
    }else if(temp->getLeft() == NULL && temp->getRight() != NULL)//right child
    {
        temp->setHeight(temp->getRight()->getHeight() + 1);
        rightH = temp->getRight()->getHeight();
    }else//both children
    {
        temp->setHeight(std::max(temp->getRight()->getHeight(),temp->getLeft()->getHeight()) + 1);
        leftH = temp->getLeft()->getHeight();
        rightH = temp->getRight()->getHeight();
    }
    AVLNode<Key, Value>* currentLocation = temp;
    AVLNode<Key, Value>* previousLocation = currentLocation;
    if (abs(leftH - rightH) > 1)//we have an imbalance - set currentLocation and Previous Location back to greatest height child and child's greatest
    {
        if(leftH > rightH)
        {
            currentLocation = temp->getLeft();
            leftH =0;
            rightH = 0;
            if(currentLocation->getLeft() == NULL && currentLocation->getRight() == NULL)//removal spot has no children
            {
                
            }else if(currentLocation->getLeft() != NULL && currentLocation->getRight() == NULL)//left child
            {
                leftH = currentLocation->getLeft()->getHeight();
            }else if(currentLocation->getLeft() == NULL && currentLocation->getRight() != NULL)//right child
            {
                rightH = currentLocation->getRight()->getHeight();
            }else//both children
            {
                leftH = currentLocation->getLeft()->getHeight();
                rightH = currentLocation->getRight()->getHeight();
            }
            if(leftH > rightH)
            {
                previousLocation = currentLocation->getLeft();

            }else if (rightH > leftH)
            {
                previousLocation = currentLocation->getRight();
            }else if(isLeftChild(currentLocation))//heights are equal so we have it follow straight line
            {
                previousLocation = currentLocation->getLeft();
            }else
            {
                previousLocation = currentLocation->getRight();
            }
        }else 
        {
            currentLocation = temp->getRight();
            leftH = 0;
            rightH = 0;
            if(currentLocation->getLeft() == NULL && currentLocation->getRight() == NULL)//removal spot has no children
            {
                
            }else if(currentLocation->getLeft() != NULL && currentLocation->getRight() == NULL)//left child
            {
                leftH = currentLocation->getLeft()->getHeight();
            }else if(temp->getLeft() == NULL && temp->getRight() != NULL)//right child
            {
                rightH = currentLocation->getRight()->getHeight();
            }else//both children
            {
                leftH = currentLocation->getLeft()->getHeight();
                rightH = currentLocation->getRight()->getHeight();
            }
            if(leftH > rightH)
            {
                previousLocation = currentLocation->getLeft();

            }else if (rightH > leftH)
            {
                previousLocation = currentLocation->getRight();
            }else if(isLeftChild(currentLocation))//heights are equal so we have it follow straight line
            {
                previousLocation = currentLocation->getLeft();
            }else
            {
                previousLocation = currentLocation->getRight();
            }
        }

    }else//no imediate imbalance but we should place the previous location back just in case
    {
        //calculate leftH and right H first of 
        leftH = 0;
        rightH = 0;
        if(currentLocation->getLeft() == NULL && currentLocation->getRight() == NULL)//removal spot has no children
        {

        }else if(currentLocation->getLeft() != NULL && currentLocation->getRight() == NULL)//left child
        {

            leftH = currentLocation->getLeft()->getHeight();
        }else if(currentLocation->getLeft() == NULL && currentLocation->getRight() != NULL)//right child
        {
            rightH = currentLocation->getRight()->getHeight();
        }else//both children
        {
            leftH = currentLocation->getLeft()->getHeight();
            rightH = currentLocation->getRight()->getHeight();
        }
        if(leftH > rightH)
        {
            previousLocation = currentLocation->getLeft();
        }else if (rightH > leftH)
        {
            previousLocation = currentLocation->getRight();
        }else if (isLeftChild(currentLocation) && currentLocation->getLeft() != NULL)//equal heights so we follow line
        {
            previousLocation = currentLocation->getLeft();

        }else if (currentLocation->getRight() != NULL)
        {
            previousLocation = currentLocation->getRight();
        }else
        {
            previousLocation = currentLocation;
            if (!leafNodeRootException) currentLocation = currentLocation->getParent();
            
        }
    }
    if(currentLocation->getParent() == NULL)//can't have current be root
    {
        if(previousLocation != NULL)
        {
            currentLocation = previousLocation;
        }
    }
    
    if (currentLocation != NULL)
    {
    while(currentLocation != NULL)
    {
        updateHeight(currentLocation);
        if(isLeftChild(currentLocation))//we are a left child
        {
            if(currentLocation->getParent()->getRight() == NULL)//if parent doesn't have another child we compare height to 0
            {
                if (currentLocation->getHeight() > 1)//left children do right rotation if previous if a left child
                {
                    if (isLeftChild(previousLocation))
                    {
                        rightRotation(currentLocation->getParent());
                        previousLocation = currentLocation;
                        currentLocation = currentLocation->getParent();
                    }
                    else{
                            LeftRightRotation(currentLocation->getParent());
                            currentLocation = previousLocation->getParent();
                            //previousLocation stays same
                        }
                    
                }
                //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                previousLocation = currentLocation;
                currentLocation = currentLocation->getParent();
                
            }else
            {
                if ((abs(currentLocation->getHeight() - currentLocation->getParent()->getRight()->getHeight()) > 1) 
                && currentLocation->getHeight() > currentLocation->getParent()->getRight()->getHeight())//checks if children are unbalanced and that our child has greater height
                {
                    if (isLeftChild(previousLocation))
                    {
                        rightRotation(currentLocation->getParent());
                        previousLocation = currentLocation;
                        currentLocation = currentLocation->getParent();
                    }
                    else{
                        LeftRightRotation(currentLocation->getParent());
                        currentLocation = previousLocation->getParent();
                        }
                    }else if (abs(currentLocation->getHeight() - currentLocation->getParent()->getRight()->getHeight()) > 1)//we on the wrong side of the tree. move over, rotate and continue
                    {
                        currentLocation = currentLocation->getParent()->getRight();
                        int leftH = 0;
                        int rightH = 0;
                        if(currentLocation->getLeft() == NULL && currentLocation->getRight() == NULL)//removal spot has no children
                        {

                        }else if(currentLocation->getLeft() != NULL && currentLocation->getRight() == NULL)//left child
                        {

                            leftH = currentLocation->getLeft()->getHeight();
                        }else if(currentLocation->getLeft() == NULL && currentLocation->getRight() != NULL)//right child
                        {
                            rightH = currentLocation->getRight()->getHeight();
                        }else//both children
                        {
                            leftH = currentLocation->getLeft()->getHeight();
                            rightH = currentLocation->getRight()->getHeight();
                        }
                        if(leftH > rightH)//set the correct previous
                        {
                            previousLocation = currentLocation->getLeft();
                        }else if (rightH > leftH)
                        {
                            previousLocation = currentLocation->getRight();
                        }else if (isLeftChild(currentLocation) && currentLocation->getLeft() != NULL)//equal heights so we follow line
                        {
                            previousLocation = currentLocation->getLeft();

                        }else if (currentLocation->getRight() != NULL)
                        {
                            previousLocation = currentLocation->getRight();
                        }else
                        {
                            previousLocation = currentLocation;
                            currentLocation = currentLocation->getParent();
                        }
                        //we are now Right so follow remove right protocall
                        if (!isLeftChild(previousLocation))
                        {
                            leftRotation(currentLocation->getParent());
                            previousLocation = currentLocation;
                            currentLocation = currentLocation->getParent();
                        }
                        else{
                            RightLeftRotation(currentLocation->getParent());
                            currentLocation = previousLocation->getParent();
                            //previousLocation stays same
                        }
                }else//keep goin up the tree
                {
                    //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                    previousLocation = currentLocation;
                    currentLocation = currentLocation->getParent();
                }
            }
        }else if(isChild(currentLocation))//we are a right 
        {
            if(currentLocation->getParent()->getLeft() == NULL)//if the child is null pointer then the height is 0
            {
                if (currentLocation->getHeight() > 1)//compares height with null
                {
                    if (!isLeftChild(previousLocation))
                        {
                            leftRotation(currentLocation->getParent());
                            previousLocation = currentLocation;
                            currentLocation = currentLocation->getParent();
                        }
                    else{
                            RightLeftRotation(currentLocation->getParent());
                            currentLocation = previousLocation->getParent();
                            //previousLocation stays same
                        }
                        
                }else
                {
                    previousLocation = currentLocation;
                    currentLocation = currentLocation->getParent();
                }
                
                
            }else
            {
                if ((abs(currentLocation->getHeight() - currentLocation->getParent()->getLeft()->getHeight()) > 1) && (currentLocation->getHeight() > currentLocation->getParent()->getLeft()->getHeight()))//checks if children are unbalanced and that we only do normal inert IF we are the bigger ones!
                {
                    if (!isLeftChild(previousLocation))
                        {
                            leftRotation(currentLocation->getParent());
                            previousLocation = currentLocation;
                            currentLocation = currentLocation->getParent();
                        }
                    else{
                            RightLeftRotation(currentLocation->getParent());
                            currentLocation = previousLocation->getParent();
                            //previousLocation stays same
                        }
                    }
                    else if (abs(currentLocation->getHeight() - currentLocation->getParent()->getLeft()->getHeight()) > 1)//we on the wrong side of the tree. move over, rotate and continue
                    {
                        currentLocation = currentLocation->getParent()->getLeft();
                        int leftH = 0;
                        int rightH = 0;
                        if(currentLocation->getLeft() == NULL && currentLocation->getRight() == NULL)//removal spot has no children
                        {

                        }else if(currentLocation->getLeft() != NULL && currentLocation->getRight() == NULL)//left child
                        {

                            leftH = currentLocation->getLeft()->getHeight();
                        }else if(currentLocation->getLeft() == NULL && currentLocation->getRight() != NULL)//right child
                        {
                            rightH = currentLocation->getRight()->getHeight();
                        }else//both children
                        {
                            leftH = currentLocation->getLeft()->getHeight();
                            rightH = currentLocation->getRight()->getHeight();
                        }
                        if(leftH > rightH)//set the correct previous
                        {
                            previousLocation = currentLocation->getLeft();
                        }else if (rightH > leftH)
                        {
                            previousLocation = currentLocation->getRight();
                        }else if (isLeftChild(currentLocation) && currentLocation->getLeft() != NULL)//equal heights so we follow line
                        {
                            previousLocation = currentLocation->getLeft();

                        }else if (currentLocation->getRight() != NULL)
                        {
                            previousLocation = currentLocation->getRight();
                        }else
                        {
                            previousLocation = currentLocation;
                            currentLocation = currentLocation->getParent();
                        }
                        //we are now left so follow remove left protocall and 2 children
                        if (isLeftChild(previousLocation))
                        {
                        rightRotation(currentLocation->getParent());
                        previousLocation = currentLocation;
                        currentLocation = currentLocation->getParent();
                        }
                        else{
                        LeftRightRotation(currentLocation->getParent());
                        currentLocation = previousLocation->getParent();
                        }
                }
                else//keep goin up the tree
                {
                    //currentLocation->getParent()->setHeight(currentLocation->getHeight() + 1);
                    previousLocation = currentLocation;
                    currentLocation = currentLocation->getParent();
                }
            }
        }else //we are at the top of the tree so we will check the two children for balance and initiate protocal if needed
        {
            break;


        }
    }
    }

    }else  
    {
        //help = NULL;
        //std::cout << "temp is NULL and Tree should be empty: " << std::endl;
    }
}


template<typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key,Value>* current)//updates height of current node to correct value
{
    if(current != NULL)
    {
        if(current->getLeft() == NULL && current->getRight() == NULL)
        {
            current->setHeight(1);
        }else if (current->getLeft() == NULL && current->getRight() != NULL)
        {
            current->setHeight(current->getRight()->getHeight() + 1);
        }else if (current->getLeft() != NULL && current->getRight() == NULL)
        {
            current->setHeight(current->getLeft()->getHeight() + 1);
        }else
        {
            int newHeight = std::max(current->getLeft()->getHeight(), current->getRight()->getHeight());
            newHeight++;
            current->setHeight(newHeight);
        }
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotation(AVLNode<Key,Value>* x)
{
    //std::cout << "in Left" << std::endl;
    if(x == this->root_) this->root_ = x->getRight();//if parent is root, make right child root
    AVLNode<Key,Value>* temp = x->getRight()->getLeft();
    x->getRight()->setLeft(x);
    x->getRight()->setParent(x->getParent());
    x->setParent(x->getRight());
    x->setRight(temp);
    if(temp != NULL)
    {
        temp->setParent(x);
    }
    x->setHeight(x->getHeight() - 1);
    if(x->getParent()->getParent() != NULL)//new
    {
        if(x->getParent()->getParent()->getRight() == x)//is right child
        {
            x->getParent()->getParent()->setRight(x->getParent());
        }else
        {
            x->getParent()->getParent()->setLeft(x->getParent());
        }
    }
}

template<typename Key, typename Value>  
void AVLTree<Key, Value>::rightRotation(AVLNode<Key,Value>* x)
{
    //std::cout << "in Right" << std::endl;
    if(x == this->root_) this->root_ = x->getLeft();//if parent is root, make left child root
    AVLNode<Key,Value>* temp = x->getLeft()->getRight();
    x->getLeft()->setRight(x);
    x->getLeft()->setParent(x->getParent());
    x->setParent(x->getLeft());
    x->setLeft(temp);
    if(temp != NULL)
    {
        temp->setParent(x);
    }
    x->setHeight(x->getHeight() - 1);
    if(x->getParent()->getParent() != NULL)//new
    {
        if(x->getParent()->getParent()->getRight() == x)//is right child
        {
            x->getParent()->getParent()->setRight(x->getParent());
        }else
        {
            x->getParent()->getParent()->setLeft(x->getParent());
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::RightLeftRotation(AVLNode<Key,Value>* x)//x is the top node (old root)
{

    if(x == this->root_) this->root_ = x->getRight()->getLeft();
    AVLNode<Key,Value>* y = x->getRight();
    //std::cout << "in RightLeft" << std::endl;
    int biggestH = 0;
    y->setParent(y->getLeft());
    x->setRight(y->getParent()->getLeft());
    y->setLeft(y->getParent()->getRight());
    y->getParent()->setParent(x->getParent());
    x->setParent(y->getParent());
    y->getParent()->setLeft(x);
    y->getParent()->setRight(y);
    
    if(x->getRight() != NULL) x->getRight()->setParent(x);//new
    if(x->getParent()->getParent() != NULL)//new
    {
        if(x->getParent()->getParent()->getRight() == x)//is right child
        {
            x->getParent()->getParent()->setRight(x->getParent());
        }else
        {
            x->getParent()->getParent()->setLeft(x->getParent());
        }
    }
    if(y->getLeft() != NULL)
    {
        y->getLeft()->setParent(y);
    }
    int biggestHL = 0;
    int biggestHR = 0;
    int biggestHP = 0;
    if(x->getLeft() != NULL)
    {
        biggestHL = x->getLeft()->getHeight();
    }
    else if(x->getRight() != NULL)
    {
        biggestHL = std::max(x->getRight()->getHeight(), biggestH);
    }
    if(y->getRight() != NULL)
    {
        biggestHR = y->getRight()->getHeight();
    }else if(y->getLeft() != NULL)
    {
        biggestHR = std::max(y->getLeft()->getHeight(), biggestH);
    }
    biggestHP = std::max(biggestHR, biggestHL);
    x->setHeight(biggestHL + 1);
    y->setHeight(biggestHR + 1);
    y->getParent()->setHeight(biggestHP + 2);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::LeftRightRotation(AVLNode<Key,Value>* x)//x is the top node (old root)
{
    if(x == this->root_) this->root_ = x->getLeft()->getRight();
    AVLNode<Key,Value>* y = x->getLeft();
    //std::cout << "in LeftRight" << std::endl;
    y->setParent(y->getRight());
    x->setLeft(y->getParent()->getRight());
    y->setRight(y->getParent()->getLeft());
    y->getParent()->setParent(x->getParent());
    x->setParent(y->getParent());
    y->getParent()->setRight(x);
    y->getParent()->setLeft(y);
    if(x->getLeft() != NULL) x->getLeft()->setParent(x);//new
    if(x->getParent()->getParent() != NULL)//new
    {
        if(x->getParent()->getParent()->getRight() == x)//is right child
        {
            x->getParent()->getParent()->setRight(x->getParent());
        }else
        {
            x->getParent()->getParent()->setLeft(x->getParent());
        }
    }
    if(y->getRight() != NULL)
    {
        y->getRight()->setParent(y);
    }
    int biggestHL = 0;
    int biggestHR = 0;
    int biggestHP = 0;
    if(x->getLeft() != NULL)
    {
        biggestHL = x->getLeft()->getHeight();
    }
    else if(x->getRight() != NULL)
    {
        biggestHL = std::max(x->getRight()->getHeight(), biggestHL);
    }
    if(y->getRight() != NULL)
    {
        biggestHR = y->getRight()->getHeight();
    }else if(y->getLeft() != NULL)
    {
        biggestHR = std::max(y->getLeft()->getHeight(), biggestHR);
    }
    biggestHP = std::max(biggestHR, biggestHL);
    x->setHeight(biggestHL + 1);
    y->setHeight(biggestHR + 1);
    y->getParent()->setHeight(biggestHP + 2);
    

}


template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::removeLocation(const Key& key)//returns location of promotedNode(akaSpotwherenodewasdeleted) or parent of leaf node
{
        // TODO
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::internalFind(key));//find key
    if (temp != NULL)
    {
    if (temp->getLeft() == NULL && temp->getRight() == NULL)//we are leaf node
    {
        if(temp->getParent() == NULL)//empty tree
        {
            this->root_ = NULL;
            return NULL;
        }
        else if(isLeftChild(temp))
        {
            (temp->getParent())->setLeft(NULL);

        }else
        {
            (temp->getParent())->setRight(NULL);
            
        }
        AVLNode<Key, Value>* result = temp->getParent();
        delete temp;//deletes if leaf node
        return result;
    }else if (temp->getLeft() == NULL)//only right so we promote
    {
        AVLNode<Key, Value>* tempRight = temp->getRight();//4
        if(isLeftChild(temp))
        {
            //std::cout<< "is Left CHILD:remove" << std::endl;
            AVLNode<Key, Value>* tempParent = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::deleteAndReturnParent(temp));
            if (tempParent != NULL)
            {
                tempParent->setLeft(tempRight);
            }else
            {
                this->root_ = tempRight;
            }
            tempRight->setParent(tempParent);

        }else
        {
            //std::cout<< "is Right CHILD:remove" << std::endl;
            AVLNode<Key, Value>* tempParent = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::deleteAndReturnParent(temp));
            if (tempParent != NULL)
            {
                tempParent->setRight(tempRight);
            }else
            {
                this->root_ = tempRight;
            }
            tempRight->setParent(tempParent);
        }
        return tempRight;
    }else if(temp->getRight() == NULL)//only left so we promote left
    {
        AVLNode<Key, Value>* tempLeft = temp->getLeft();
        if(isLeftChild(temp))
        {
            //std::cout<< "is Left CHILD:remove" << std::endl;            
            AVLNode<Key, Value>* tempParent = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::deleteAndReturnParent(temp));
            if (tempParent != NULL)
            {
                tempParent->setLeft(tempLeft);
            }else
            {
                this->root_ = tempLeft;
            }
            tempLeft->setParent(tempParent);
            
        }else
        {
            //std::cout<< "is Right CHILD:remove" << std::endl;
            AVLNode<Key, Value>* tempParent = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::deleteAndReturnParent(temp));
            if (tempParent != NULL)
            {
                tempParent->setRight(tempLeft);
            }else
            {
                this->root_ = tempLeft;
            }
            tempLeft->setParent(tempParent);
            
        }
        return tempLeft;
    }else//node has two children - promote predecessor and leave the other to the right
    {
        AVLNode<Key, Value>* toSwap = static_cast<AVLNode<Key,Value>*> (BinarySearchTree<Key, Value>::downLeftToGreatest(temp));
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
            (temp->getParent())->setRight(NULL);
        }
        if (toSwap->getParent() == NULL)
        {
            this->root_ = toSwap;
        }
        delete temp;
        return toSwap;
    }
    }else return NULL;

}

#endif
