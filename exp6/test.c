#include <stdio.h>
#include <stdlib.h>
#define MAX 20
typedef int VexType;
typedef VexType Mgraph[MAX][MAX];
void creat_mg(Mgraph G);
void out_mg(Mgraph G);
Mgraph G1;
int n,e,vO;
void main()
{ 
    creat_mg(G1);
    out_mg(G1);
}/* main*/
void creat_mg(Mgraph G)
{     int i,j,k,w;
    printf("\n n,e=");
    scanf("%d,%d", &n,&e);
    for(i=1 ; i<=n;i++)
        for(j=1;j<=n;j++)
            G[i][j]=32767;
    for(k=1;k<=e;k++)
    {
        printf("\n vi,vj,w=");
        scanf(" %d,%d,%d",&i,&j,&w);
        G[i][j]=w;
        G[j][i]=w;
    }
} /* creat_mg */
void out_mg(Mgraph G)
{
    int i,j;
    char ch;
    for(i=1 ; i<=n;i++)
    {
        printf("\n ");
        for(j=1;j<=n;j++)
            printf("%5d",G[i][j]);
    }
    for(i=1 ; i<=n;i++)
        for(j=1;j<=n;j++)
            if(G[i][j]==1 )
                printf("\n存在边<%d,%d >",i,j);
    printf("\n\n打回车键，继续。");
    ch=getchar();
}/*out_mg */
