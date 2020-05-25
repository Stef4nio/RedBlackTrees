//
// Created by stef4 on 5/24/2020.
//

#ifndef REDBLACKTREES_REDBLACKTREE_H
#define REDBLACKTREES_REDBLACKTREE_H

enum Color{Red = 0, Black = 1};

struct Node{
    int data;
    Node* left = nullptr;
    Node* rigth = nullptr;
    Node* parent = nullptr;
    Color color = Red;

};

class RedBlackTree
{

    public:
        Node* SearchElement(int data);
        void LeftRotate(Node* nodeToRotate);
        void RightRotate(Node* nodeToRotate);
        void Transplant(Node* transplantedNode, Node* transplantNode);
        void InsertionFixup(Node* nodeToFix);
        void RemovalFixup(Node* nodeToFix);
        void InsertElement(int data);
        void RemoveElement(int data);
        RedBlackTree()
        {
            NIL = new Node{-1, nullptr, nullptr, nullptr, Black};
        }
    private:
        Node* treeMinimum(Node* subtreeRoot);
        Node* root;
        static Node* NIL;
        Node* createNode(int data,Color color)
        {
            return new Node{data,NIL,NIL,NIL,color};
        }
};


#endif //REDBLACKTREES_REDBLACKTREE_H
