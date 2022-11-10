//
//  BinaryTree.h
//  Code
//
//  Created by Houtong Lei on 2021/5/11.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#include <stdio.h>
#include <stdlib.h>

typedef int TElemType;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *T);
Status PrintElement(TElemType e);
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType));
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType));
int BiTreeDepth(BiTree T);

#endif /* BinaryTree_h */
