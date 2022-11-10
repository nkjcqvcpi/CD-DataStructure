//
//  2-4.c
//  Code
//
//3. 从单链表中删除指定的元素 x，若 x 在单链表中不存在，给出提示信息。 要求: (1)指定的值 x 由键盘输入;(2)程序能处理空链表的情况。
//  Created by Houtong Lei on 2021/4/1.
//

#include <stdio.h>
#include "../LinkedList.h"

ElemType DelElem(LNode *L, ElemType x){
    if (L->next == NULL) return 1;
    int i = LocateElem_L(L, x);
    return ListDelete_L(L, i);
}

int main(){
    LNode L;
    puts("L:");
    InitList_L(&L);
    
    int x;
    printf("\nPlease input x = ");
    scanf("%d", &x);

    if (DelElem(&L, x)==1) printf("Empty LinkedList!\n");
    else ListTraverse_L(&L);
    return 0;
}
