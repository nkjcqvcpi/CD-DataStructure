//
//  BinaryTree.c
//  Code
//
//  Created by Houtong Lei on 2021/5/11.
//

#include "BinaryTree.h"

void CreateBiTree(BiTree *T){
    TElemType ch;
    if(!scanf("%d",&ch)) {
        *T = NULL;
        fflush(stdin);
    }
    else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!*T) exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

Status PrintElement(TElemType e) {
    printf("%d ", e);
    return OK;
}

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType)) {
    if (T) {
        if (Visit(T->data))
            if (PreOrderTraverse(T->lchild, Visit))
                if (PreOrderTraverse(T->rchild, Visit))
                    return OK;
        return ERROR;
    } else
        return OK;
}

Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType)) {
    if (T == NULL)
        return ERROR;
    BiTree s[10000];
    int front, rear;
    front = rear = -1;
    s[++rear] = T;
    while (front != rear){
        BiTree q = s[++front];
        printf("%d ", q->data);
        if (q->lchild)
            s[++rear] = q->lchild;
        if (q->rchild)
            s[++rear] = q->rchild;
    }
    return OK;
}

int BiTreeDepth(BiTree T){
    int l_depth = 0, r_depth = 0;
    if(T == NULL)
        return 0;
    else{
        l_depth = BiTreeDepth(T -> lchild) + 1;
        r_depth = BiTreeDepth(T -> rchild) + 1;
    }
    int depth = (l_depth > r_depth) ? l_depth : r_depth;
    return depth;
}
