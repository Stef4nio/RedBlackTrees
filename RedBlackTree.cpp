//
// Created by stef4 on 5/24/2020.
//

#include "RedBlackTree.h"

Node *RedBlackTree::SearchElement(int data)
{
    Node* treeCopy = root;
    while(treeCopy)
    {
        if(data>treeCopy->data)
        {
            treeCopy = treeCopy->rigth;
        }
        else if(data<treeCopy->data)
        {
            treeCopy = treeCopy->left;
        } else
        {
            return treeCopy;
        }
    }
    return nullptr;
}

void RedBlackTree::InsertElement(int data)
{
    Node* currNodeParent = NIL;
    Node* currNode = root;
    while(currNode!=NIL)
    {
        currNodeParent = currNode;
        if(data>currNode->data)
        {
            currNode = currNode->rigth;
        } else
        {
            currNode = currNode->left;
        }
    }
    Node* newNode = createNode(data,Red);
    newNode->parent = currNodeParent;
    if(currNodeParent = NIL)
    {
        root = newNode;
    }
    else if (data<currNodeParent->data)
    {
        currNodeParent->left = newNode;
    }
    else
    {
        currNodeParent->rigth = newNode;
    }
    InsertionFixup(newNode);
}

void RedBlackTree::RemoveElement(int data)
{
    Node* nodeToRemove = SearchElement(data);
    Node* nodeCopy = nodeToRemove;
    Color originalColor = nodeCopy->color;
    Node* x;
    if(nodeToRemove->left == NIL)
    {
        x = nodeToRemove->rigth;
        Transplant(nodeToRemove,nodeToRemove->rigth);
    }
    else if(nodeToRemove->rigth == NIL)
    {
        x = nodeToRemove->left;
        Transplant(nodeToRemove,nodeToRemove->left);
    }
    else
    {
        nodeCopy = treeMinimum(nodeToRemove->rigth);
        originalColor = nodeCopy->color;
        x = nodeCopy->rigth;
        if(nodeCopy->parent == nodeToRemove)
        {
            x->parent = nodeCopy;
        }
        else
        {
            Transplant(nodeCopy,nodeCopy->rigth);
            nodeCopy->rigth = nodeToRemove->rigth;
            nodeCopy->rigth->parent = nodeCopy;
        }
        Transplant(nodeToRemove,nodeCopy);
        nodeCopy->left = nodeToRemove->left;
        nodeCopy->left->parent = nodeCopy;
        nodeCopy->color = nodeToRemove->color;
    }
    if(originalColor == Black)
    {
        RemovalFixup(x);
    }
    return;
}

void RedBlackTree::InsertionFixup(Node *nodeToFix)
{
    while (nodeToFix->parent->color == Red)
    {
        if(nodeToFix->parent == nodeToFix->parent->parent->left)
        {
            Node* uncle = nodeToFix->parent->parent->rigth;
            if(uncle->color == Red)
            {
                nodeToFix->parent->color = Black;
                nodeToFix->parent->parent->color = Red;
                uncle->color = Black;
                nodeToFix = nodeToFix->parent->parent;
            }
            else if(nodeToFix == nodeToFix->parent->rigth)
            {
                nodeToFix = nodeToFix->parent;
                LeftRotate(nodeToFix);
            }
            nodeToFix->parent->color = Black;
            nodeToFix->parent->parent->color = Red;
            RightRotate(nodeToFix->parent->parent);
        }
        else
        {
            Node* uncle = nodeToFix->parent->parent->left;
            if(uncle->color == Red)
            {
                nodeToFix->parent->color = Black;
                nodeToFix->parent->parent->color = Red;
                uncle->color = Black;
                nodeToFix = nodeToFix->parent->parent;
            }
            else if(nodeToFix == nodeToFix->parent->left)
            {
                nodeToFix = nodeToFix->parent;
                RightRotate(nodeToFix);
            }
            nodeToFix->parent->color = Black;
            nodeToFix->parent->parent->color = Red;
            LeftRotate(nodeToFix->parent->parent);
        }
    }
}

void RedBlackTree::LeftRotate(Node *nodeToRotate)
{
    Node* newRoot = nodeToRotate->rigth;
    if(nodeToRotate->parent == NIL)
    {
        root = newRoot;
    }
    else if(nodeToRotate->parent->left == nodeToRotate)
    {
        nodeToRotate->parent->left = newRoot;
    }
    else
    {
        nodeToRotate->parent->rigth = newRoot;
    }
    newRoot->parent = nodeToRotate->parent;
    nodeToRotate->parent = newRoot;
    nodeToRotate->rigth = newRoot->left;
    newRoot->left = nodeToRotate;

    if(newRoot->left!=NIL)
    {
        newRoot->left->parent = nodeToRotate;
    }
}

void RedBlackTree::RightRotate(Node *nodeToRotate)
{
    Node* newRoot = nodeToRotate->left;
    if(nodeToRotate->parent == NIL)
    {
        root = newRoot;
    }
    else if(nodeToRotate->parent->left == nodeToRotate)
    {
        nodeToRotate->parent->left = newRoot;
    }
    else
    {
        nodeToRotate->parent->rigth = newRoot;
    }
    newRoot->parent = nodeToRotate->parent;
    nodeToRotate->parent = newRoot;
    nodeToRotate->left = newRoot->rigth;
    newRoot->rigth = nodeToRotate;

    if(newRoot->rigth!=NIL)
    {
        newRoot->rigth->parent = nodeToRotate;
    }
}

void RedBlackTree::Transplant(Node *transplantedNode, Node *transplantNode)
{
    if(transplantedNode->parent == NIL)
    {
        root = transplantNode;
    }
    else if (transplantedNode->parent->left == transplantedNode)
    {
        transplantedNode->parent->left = transplantNode;
    }
    else
    {
        transplantedNode->parent->rigth = transplantNode;
    }
    transplantNode->parent = transplantedNode->parent;
}

void RedBlackTree::RemovalFixup(Node *nodeToFix)
{
    while (nodeToFix!=root&&nodeToFix->color == Black)
    {
        if(nodeToFix == nodeToFix->parent->left)
        {
            Node* sibling = nodeToFix->parent->rigth;
            if(sibling->color == Red)
            {
                sibling->color = Black;
                nodeToFix->parent->color = Red;
                LeftRotate(nodeToFix->parent);
                sibling = nodeToFix->parent->rigth;
            }
            if(sibling->left->color == Black && sibling->rigth->color == Black)
            {
                sibling->color = Red;
                nodeToFix = nodeToFix->parent;
            }
            else if(sibling->rigth->color == Red)
            {
                sibling->left->color = Black;
                sibling->color = Red;
                RightRotate(sibling);
                sibling = nodeToFix->parent->rigth;
            }
            sibling->color = nodeToFix->parent->color;
            nodeToFix->parent->color = Black;
            sibling->rigth->color = Black;
            LeftRotate(nodeToFix->parent);
            nodeToFix = root;
        }
        else
        {
            Node* sibling = nodeToFix->parent->left;
            if(sibling->color == Red)
            {
                sibling->color = Black;
                nodeToFix->parent->color = Red;
                LeftRotate(nodeToFix->parent);
                sibling = nodeToFix->parent->left;
            }
            if(sibling->left->color == Black && sibling->rigth->color == Black)
            {
                sibling->color = Red;
                nodeToFix = nodeToFix->parent;
            }
            else if(sibling->left->color == Red)
            {
                sibling->rigth->color = Black;
                sibling->color = Red;
                RightRotate(sibling);
                sibling = nodeToFix->parent->left;
            }
            sibling->color = nodeToFix->parent->color;
            nodeToFix->parent->color = Black;
            sibling->left->color = Black;
            LeftRotate(nodeToFix->parent);
            nodeToFix = root;
        }
    }
    nodeToFix->color = Black;
}

Node *RedBlackTree::treeMinimum(Node *subtreeRoot)
{
    while (subtreeRoot->left)
    {
        subtreeRoot = subtreeRoot->left;
    }
    return subtreeRoot;
}

