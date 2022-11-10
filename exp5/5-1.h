//
//  5-1.h
//  Code
//
//  Created by Houtong Lei on 2021/5/6.
//

#ifndef __1_h
#define __1_h

#include "../Status.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 12500

typedef int ElemType;

typedef struct {
    int i,j;
    ElemType e;
}Triple;

typedef struct {
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
}TSMatrix;

Status TransposeSMatrix(TSMatrix M, TSMatrix* T);
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix* Q);
void CreateSMatrix(TSMatrix *M);
void PrintSMatrix(TSMatrix M);

#endif /* __1_h */
