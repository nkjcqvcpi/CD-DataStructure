#include <stdio.h>
#include <stdlib.h>
#define MAX 20
typedef int VexType;
typedef VexType Mgraph[MAX][MAX]; /* Mgraph是二维数组类型标识符*/
void creat_mg(Mgraph G);
void out_mg (Mgraph G);
Mgraph G1;
/*G1是邻接矩阵的二维数组名*/
int n, e, v0;
void main()
{
    creat_mg(G1);
    out_mg(G1);
}
void creat_mg (Mgraph G)
{
    int i, j, k;
    printf("\n n, e=" );
    scanf("%d, %d", &n, &e);
    for(i=1; i<=n ; i++)
        for(j=1 ; j<=n; j++)
            G[i][j]=0;
    for(k=1 ; k<=e;k++)/*组织边数的循环*/
    {
        printf("\nvi, vj=");
        scanf("%d%d",&i,&j);
        G[i][j]=1;
        G[j][i]=1;
    }
}/* creat_mg */
void out_mg (Mgraph G)
{
    int i,j; char ch;
    for(i=1; i<=n; i++)
    {
        printf("\n ");
        for(j=1 ; j<=n;j++)
            printf("%5d",G[i][j]);
    }
    for(i=1; i<=n ; i++)
        for(j=1 ; j<=n; j++)
            if(G[i][j]==1)
        printf("\n存在边%d, %d ",i,j);
        printf("\n\n打回车键，继续。");
        ch=getchar() ;
}/*out_mg */

