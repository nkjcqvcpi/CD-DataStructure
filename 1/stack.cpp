#include "stack.h"

void InitStack(SqStack* S){
    S->top=-1;
}

void StackTraverse(SqStack S){
    char ch; int i; 
    if (S.top == -1) printf("\n Stack is NULL. ");
    else{
        i = S.top;
        while( i!=-1){
            printf("\n data=%s", S.a[i]);
            i--;
        }
    }
 }

void Push(SqStack* S, ElemType e){
    if (S->top == MAXSIZE - 1) printf("\n Sstack is Overflow!");
    else {
        S->top++;
        S->a[S->top] = e;
    }
}

void Pop(SqStack* S, ElemType* e) {
    if (S->top == -1) {
        printf("\n Stack is Underflow!");
        //*e = L"-1";
    }
    else {
        *e = S->a[S->top];
        S->top--;
    }
}
