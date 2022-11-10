//
//  2-2.c
//  Code
//
//  Created by Houtong Lei on 2021/4/1.
//

#include <stdio.h>
#include "../LinkedList.h"

void MergeList_L(LNode *La, LNode *Lb, LNode *Lc){
    LNode *pa = La->next, *pb = Lb->next, *pc = La;
    *Lc = *pc;
    while(pa!=NULL&&pb!=NULL){
        if (pa->data<=pb->data){
            pc->next = pa;pc = pa;pa = pa->next;
        }else{
            pc->next = pb;pc = pb;pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;
}

int main(void){
    LNode LA, LB, LC;
    puts("LA:");
    InitList_L(&LA);
    puts("LA = ");
    ListTraverse_L(&LA);
    puts("LB:");
    InitList_L(&LB);
    puts("LB = ");
    ListTraverse_L(&LB);
    MergeList_L(&LA, &LB, &LC);
    puts("\nLC = ");
    ListTraverse_L(&LC);
    return 0;
}
