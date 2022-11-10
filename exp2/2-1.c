//
//  2-1.c
//  Code
//
//  Created by Houtong Lei on 2021/3/31.
//

#include <stdio.h>
#include "../LinkedList.h"

void MergeList_L(LNode *La, LNode Lb){
    LNode *pb = Lb.next, *pre_A = La, *pa = pre_A->next, *temp_b = &Lb;
    while (pa!=NULL&&pb!=NULL){
        if ((*pa).data > (*pb).data){
            temp_b = (LNode *)malloc(sizeof(LNode));
            *temp_b = *pb;
            temp_b->next = pa;
            (pre_A->next) = temp_b;
            pb = pb->next;
        } else{
            pre_A = pa;
            pa = pa->next;
        }
    }
    pre_A->next = pa?pa:pb;
}

int main(void){
    LNode LA, LB;
    puts("LA:");
    InitList_L(&LA);
    puts("LA = ");
    ListTraverse_L(&LA);
    puts("LB:");
    InitList_L(&LB);
    puts("LB = ");
    ListTraverse_L(&LB);
    MergeList_L(&LA, LB);
    puts("\nmerged LA = ");
    ListTraverse_L(&LA);
    return 0;
}
