#include "list.h"

void InitList(LNode *L){
    LNode * p, * s; ElemType x;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    p = L;
    /*printf("\n data=?");
    scanf_s("%d", &x);
    while (x != L"n"){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x; s->next = NULL;
        p->next = s; p = s;
        printf("data=?( -111 end) ");
        scanf_s("%d",&x);
    }*/
}

void ListTraverse(LNode L){
    LNode* p;
    p = L.next; printf("\n\n");
    while (p != NULL) {
        printf("%s", p->data);
        p = p->next;
    };
}

void ListInsert(LNode* L, int i, ElemType e) {
    LNode* s, * p; int j = 0;
    p = L;
    while (p != NULL && j < i - 1) {
        p = p->next; j++;
    }
    if (p == NULL || j > i - 1)
        printf("\n i ERROR !");
    else {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
    }
    
}

void ListDelete(LNode* L, int i, ElemType *e){
    LNode* p, * q; int j; p = L; j = 0;
    while (p->next != NULL && j < i - 1) {
        p = p->next; j++;
    }
    if (p->next == NULL) {
        printf("\n i ERROR !");
    }
    else {
        q = p->next; *e = q->data; p->next = q->next; free(q);
    }
}

int LocateElem(LNode L, ElemType e){
    LNode* p; int j = 1;
    p = L.next;
    while (p != NULL) {
        if (p->data == e) return j;
        p = p->next;
        j++;
    }
    return(0);
}
