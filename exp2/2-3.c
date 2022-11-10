//
//  2-3.c
//  Code
//

//2. 一个线性表有 n 个元素(n<MAXSIZE, MAXSIZE 指线性表的最大长度)，且递增有。 现有一元素 x 要插入到线性表的适当位置上，并保持线性表原有的顺序不变。设计程序实现。
//要求:采用顺序存储表示实现;采用链式存储表示方法实现;比较两种方法的优劣。

//  Created by Houtong Lei on 2021/4/1.
//

#include <stdio.h>
#include <time.h>
#include "../LinkedList.h"
#include "../ContiguousList.h"

int main(){
    int i;
    
    printf("Position: ");
    scanf("%d", &i);
    ElemType e;
    printf("Element: ");
    scanf("%d", &e);
    
    LNode LA;
    puts("\nLA:");
    InitList_L(&LA);
    
    unsigned long t0 = clock();
    ListInsert_L(&LA, i, e);
    unsigned long t1 = clock();
    puts("LA = ");
    ListTraverse_L(&LA);
    printf("time = %lf\n", (t1-t0)/(double)CLOCKS_PER_SEC);
    
    SqList LB;
    puts("\nLB:");
    InitList_C(&LB);
    
    t0 = clock();
    ListInsert_C(&LB, i, e);
    t1 = clock();
    puts("LB = ");
    ListTraverse_C(LB);
    printf("time = %lf\n", (t1-t0)/(double)CLOCKS_PER_SEC);
    
    return 0;
}
