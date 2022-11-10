#pragma once
//
//  List.h
//  1 macOS
//
//  Created by Houtong Lei on 2021/4/14.
//

#ifndef list
#define list

#include <stdio.h>
#include <stdlib.h>

typedef char *ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode* next;
}LNode;

void InitList(LNode *L);
void DestoryList(LNode&L);
void ClearList(LNode&L);
void ListEmpty(LNode L);
void ListLength(LNode L);
void GetElem(LNode L, int i, ElemType &e);
int LocateElem(LNode L, ElemType e);
void PriorElem(LNode L, ElemType cur_e, ElemType &pre_e);
void NextElem(LNode L, ElemType cur_e, ElemType &next_e);
void ListInsert(LNode* L, int i, ElemType e);
void ListDelete(LNode* L, int i, ElemType* e);
void ListTraverse(LNode L);


#endif /* List_h */
