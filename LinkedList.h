//
//  LinkedList.h
//  Code
//
//  Created by Houtong Lei on 2021/3/31.
//


#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode;

void ListTraverse_L(LNode *L){
    LNode *p;p=L->next;
    while(p!=NULL){printf("%5d",p->data); p=p->next;};
    puts("");
}

void InitList_L(LNode *L){
    LNode *p,*s; ElemType x;int i=0;
    *L = *(LNode *)malloc(sizeof(LNode));
    (*L).next = NULL;p = L;
    while ((void)(printf("data %d = ", i)), scanf("%d",&x) > 0){
        s = (LNode *)malloc(sizeof(LNode));
        s -> data = x; s -> next = NULL;
        p -> next = s; p = s;i++;
    }
    getchar();
}

void ListInsert_L(LNode *L,int i ,ElemType e){
    LNode *s,*p; int j = 0;
    p = L;
    while(p!=NULL && j<i-1) { p=p->next; j++; }
    if(p==NULL || j>i-1) exit(1);
    else {
        s=(LNode *)malloc(sizeof(LNode));s->data=e;
        s->next=p->next;p->next=s;
    }
}

int LocateElem_L(LNode *L,ElemType e){
    LNode *p; int j=1;
    p = L->next;
    while(p != NULL && p->data != e){p = p->next; j++;}
    if (p != NULL) return(j);
    else exit(1);
}

ElemType ListDelete_L(LNode *L,int i){
    LNode *p, *q; int j = 0; ElemType x; p = L;
    while (p->next != NULL && j < i-1){p = p->next; j++;}
    if(p->next == NULL) exit(1);
    else {
        q = p->next; x = q->data; p->next = q->next; free(q);
        return(x);
    }
}

#endif /* LinkedList_h */
