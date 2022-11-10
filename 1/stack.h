#pragma once

#ifndef stack
#define stack

#define MAXSIZE 32768

#include <stdio.h>

typedef char *ElemType;
typedef struct {
    ElemType  a[MAXSIZE];
    int  top;
}SqStack;

void InitStack(SqStack* S);
void DestroyStack(SqStack &S);
void ClearStack(SqStack &S);
void StackEmpty(SqStack S);
void StackLength(SqStack S);
void GetTop(SqStack S, ElemType &e);
void Push(SqStack* S, ElemType e);
void Pop(SqStack* S, ElemType* e);
void StackTraverse(SqStack S);


#endif /* Stack_h */
