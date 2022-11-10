#pragma once
//
//  Queue.h
//  1 macOS
//
//  Created by Houtong Lei on 2021/4/14.
//

#ifndef queue
#define queue

#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

typedef struct QNode
{
    ElemType data;
    struct QNode* next;
}QNode;

typedef struct{
    QNode* front, * rear;
}L_Queue;

void InitQueue(L_Queue* Q);
void DestoryQueue(L_Queue& Q);
void ClearQueue(L_Queue& Q);
void QueueEmpty(L_Queue Q);
void QueueLength(L_Queue Q);
void GetHead(L_Queue Q, L_Queue& e);
void EnQueue(L_Queue* Q, ElemType e);
void DeQueue(L_Queue* Q, ElemType* e);
void QueueTraverse(L_Queue Q);

#endif /* Queue_h */
