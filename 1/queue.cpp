#include "queue.h"

void InitQueue(L_Queue* Q){
    QNode* p;
    p = (QNode*)malloc(sizeof(QNode));
    p->next = NULL;
    Q->front = p;
    Q->rear = p;
}


void QueueTraverse(L_Queue Q){
    QNode * p; char ch;
    p = Q.front->next;
    while (p != NULL) {
        printf("\n % d",p->data);
        p = p->next;
    }
}

void EnQueue(L_Queue *Q, ElemType e)
{
    QNode *s;
    s = (QNode*)malloc(sizeof(QNode));
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

void DeQueue(L_Queue *Q, ElemType* e) {
    QNode* p;
    if (Q->front == Q->rear) {
        printf("\n Queue is NULL!"); *e = -1;
    }else{
        p = Q->front->next;
        *e = p->data;
        Q->front->next = p->next;
        if(Q->rear == p) Q->rear = Q->front;
        free(p);
    }
}
