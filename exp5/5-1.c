//
//  5-1.c
//  Code
//
//  Created by Houtong Lei on 2021/5/6.
//

#include "5-1.h"

Status TransposeSMatrix(TSMatrix M, TSMatrix* T) {
    T->mu = M.nu;T->nu = M.mu;T->tu = M.tu;
    if (!T->tu) return ERROR;
    int col, t, p, q, num[20], cpot[20] = {0, 1};
    for (col = 1; col <= M.nu; ++col) num[col] = 0;
    for (t = 1; t <= M.tu; ++t) ++num[M.data[t].j];
    for (col = 2; col <= M.nu; ++col)
        cpot[col] = cpot[col-1] + num[col-1];
    for (p = 1; p <= M.tu; ++p) {
        col = M.data[p].j;
        q = cpot[col];
        T->data[q].i = M.data[p].j;
        T->data[q].j = M.data[p].i;
        T->data[q].e = M.data[p].e;
        ++cpot[col];
    }
    return OK;
}


Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix* Q){
    if (M.mu!=N.mu||M.nu!=N.nu) return ERROR;
    if (M.tu==0) {*Q = M;return OK;}
    else if (N.tu==0) {*Q = N;return OK;}
    int i, j, u, q[MAXSIZE][Q->nu + 1];
    Q->mu = M.mu;Q->nu = M.nu;
    for (i = 1;i<=Q->mu;i++)
        for (j = 1;j<=Q->nu;j++) q[i][j] = 0;
    for (u = 1;u<=M.tu;u++)
        q[M.data[u].i][M.data[u].j] += M.data[u].e;
    for (u = 1;u<=N.tu;u++)
        q[M.data[u].i][M.data[u].j] += N.data[u].e;
    Q->tu = 0;
    for (i = 1;i<=Q->mu;i++)
        for (j = 1;j<=Q->nu;j++) if (q[i]!=0){
            Triple temp;
            temp.e = q[i][j];
            temp.i = i;
            temp.j = j;
            Q->data[++Q->tu] = temp;
        }
    return OK;
}

void CreateSMatrix(TSMatrix *M) {
    int i,j,e;
    printf("m = ");
    scanf("%d",&M->mu);
    printf("n = ");
    scanf("%d",&M->nu);
    M->tu = 0;
    for(i = 1;i<=M->mu;i++)
        for (j = 1;j<=M->nu;j++){
            printf("[%d][%d] = ", i, j);
            scanf("%d", &e);
            if (e!=0){
                Triple temp;
                temp.i = i;
                temp.j = j;
                temp.e = e;
                M->data[++M->tu] = temp;
            }
        }
    puts("");
}

void PrintSMatrix(TSMatrix M){
    int q[MAXSIZE][M.nu];
    for (int u = 1;u<=M.tu;++u)
        q[M.data[u].i][M.data[u].j] = M.data[u].e;
    for (int i = 1;i<=M.mu;i++){
        for (int j = 1;j<=M.nu;j++)
            printf("%5d ", q[i][j]);
        puts("");
    }
    puts("");
}

int main(void){
    TSMatrix A,B,T,Q;
    CreateSMatrix(&A);
    CreateSMatrix(&B);
    TransposeSMatrix(A, &T);
    PrintSMatrix(T);
    AddSMatrix(A, B, &Q);
    PrintSMatrix(Q);
}
