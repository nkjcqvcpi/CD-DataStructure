//
//  ContiguousList.h
//  Code
//
//  Created by Houtong Lei on 2021/4/1.
//


#ifndef ContiguousList_h
#define ContiguousList_h

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200

typedef int ElemType;

typedef struct{
    ElemType a[MAXSIZE];
    int length;
}SqList;

void InitList_C(SqList *L){
    int i = 0;
    L->length = 0;
    while ((void)(printf("data %d = ", i)), scanf("%d",&L->a[i]) > 0){
        i++;L->length++;
    }
    getchar();
}

void ListTraverse_C(SqList L){
    for(int i=0;i<=L.length-1;i++) printf("%5d",L.a[i]);
    puts("");
}

void ListInsert_C(SqList *L,int i,ElemType e){
    int j;
    if (L->length == MAXSIZE) exit(-1);
    else if(i < 1 || i > L->length+1) exit(1);
    else{
        for(j = L->length-1; j >= i-1; j--) L -> a[j+1] = L -> a[j];
        L -> a[i-1] = e;L -> length++;
    }
}
#endif /* ContiguousList_h */
