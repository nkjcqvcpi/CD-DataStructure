#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20 /* 数组最大界限 */

typedef int ElemType; /* 数据元素类型 */

typedef struct{
    ElemType a[MAXSIZE]; /* 一维数组 子域 */
    int length; /* 表长度子域 */
}SqList; /* 顺序存储的结构体类型 */

SqList a,b,c;

/* 函数声明 */
void creat_list(SqList *L);
void out_list(SqList L);
void insert_sq(SqList *L,int i,ElemType e);
ElemType delete_sq(SqList *L,int i);
int locat_sq(SqList L,ElemType e);

/* 主函数 */
int main(){
    int i,k,loc;
    ElemType e,x;
    char ch;
    do{
        printf("\n\n\n");
        printf("\n     1. 建立线性表 " );
        printf("\n     2. 在 i 位置插入元素 e");
        printf("\n     3. 删除第 i 个元素，返回其值");
        printf("\n     4. 查找值为 e 的元素");
        printf("\n     6. 结束程序运行");
        printf("\n======================================");
        printf("\n 请输入您的选择(1，2，3，4，6)");
        scanf("%d",&k);
        switch(k){
            case 1:creat_list(&a); out_list(a);break;
            case 2:printf("\n i,e=?"); scanf("%d,%d",&i,&e);insert_sq(&a,i,e); out_list(a);break;
            case 3:printf("\n i=?"); scanf("%d",&i); x=delete_sq(&a,i); out_list(a);printf("\n x=%d",x);break;
            case 4:printf("\n e=?"); scanf("%d",&e); loc=locat_sq(a,e);
                if (loc==-1) printf("\n 未找到 %d",loc);
                else printf("\n 已找到，元素位置是 %d",loc);
                break;
        } /*  switch  */
    }while(k!=6);
    printf("\n           再见!");
    printf("\n           打回车键，返回。");
    ch=getchar();
}/* main */

/* 建立线性表 */
void creat_list(SqList *L){
    int i;
    printf("\n n=?"); scanf("%d",&L->length); for(i=0;i<L->length;i++){ printf("\n data %d=?",i);
    scanf("%d",&(L->a[i])); }
    } /* creat_list */

/* 输出线性表 */
void out_list(SqList L){
    int i; char ch;
    printf("\n");
    for(i=0;i<=L.length-1;i++) printf("%10d",L.a[i]);
    printf("\n\n 打回车键，继续。");
    ch=getchar();
} /*  out_list  */

/* 在线性表的第 i 个位置插入元素 e */
void insert_sq(SqList *L,int i,ElemType e){
    int j;
    if (L->length==MAXSIZE) printf("\n overflow !");
    else if(i<1||i>L->length+1) printf("\n erroe i !");
    else{
        for(j=L->length-1; j>i-1; j--) L->a[j+1]=L->a[j]; /* 向后移动数据元素 */
        L->a[i-1]=e; /* 插入元素 */
        L->length++; /* 线性表长加 1 */
    }
} /* insert_sq */

/* 删除第 i 个元素，返回其值 */
ElemType delete_sq(SqList *L, int i){
    ElemType x = 0; int j;
    if (L->length==0) printf("\n 是空表。underflow !");
    else if(i<1||i> L->length){
        printf("\n error i !");
        x=-1;
    }else{
        x=L->a[i-1];
        for(j=i; j<=L->length-1; j++) L->a[j-1]=L->a[j];
        L->length--;
    }
    return(x);
}/* delete_sq */

/* 查找值为 e 的元素，返回它的位置 */
int locat_sq(SqList L, ElemType e){
    int i=0;
    while(i<=L.length-1 && L.a[i]!=e) i++;
    if(i<=L.length-1) return(i+1);
    else return(-1);
}/* locat_sq  */
