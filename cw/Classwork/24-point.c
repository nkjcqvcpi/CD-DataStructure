//
//  24-point.c
//  24-point
//
//  Created by Houtong Lei on 2021/3/16.
//

/*
 口算知 (5-1/5)*5=24 为唯一解
 故使用二叉树结构如下：
       (.)
      /   \
    (.)   (n)
   /   \
 (n)   (.)
      /   \
    (n)   (n)
 其中带.的为操作节点，带n的为数值节点
 设计一较复杂方法：
 遍历给出数与4种操作符，最多需要nPr(4,4)*4*4*4=1536次
 实测知296次即可得到答案
 */

#include <stdio.h>

typedef struct Node{
    float value;
    int operation;
    struct Node *l_child,*r_child;
}Node;

typedef struct Tree{
    Node root,l,lr,lrr,lrl,ll,r;
}Tree;

void Node_cal(Node *node){
    Node *l = node->l_child,*r = node->r_child;
    switch((*node).operation){
        case 0: (*node).value = (*l).value + (*r).value;break;
        case 1: (*node).value = (*l).value - (*r).value;break;
        case 2: (*node).value = (*l).value * (*r).value;break;
        case 3: if ((*r).value != 0) node->value = (*l).value / (*r).value;break;
    }
}

void Tree_cal(Tree *tree){
    Node_cal(&tree->lr);
    Node_cal(&tree->l);
    Node_cal(&tree->root);
}

void put_c(int c){
    switch (c){
        case 0:printf("+");break;
        case 1:printf("-");break;
        case 2:printf("*");break;
        case 3:printf("/");break;
    }
}

void put_n(Tree tree){
    printf("(%.0f", tree.ll.value);
    put_c(tree.l.operation);
    printf("%.0f",tree.lrl.value);
    put_c(tree.lr.operation);
    printf("%.0f)",tree.lrr.value);
    put_c(tree.root.operation);
    printf("%.0f=%.0f\n",tree.r.value,tree.root.value);
}

int main(void){
    Tree tr[1536];
    int num[4] = {5,5,5,1};
    int i,j,k,l,m,n,o,c=0;
    
    puts("Calculating");
    for (i=0;i<4;i++){
        for (j=0;j<4;j++){
            for (k=0;k<4;k++){
                for (l=0;l<4;l++){
                    if ((i==j)||(i==k)||(i==l)||(j==k)||(j==l)||(k==l)) continue;
                    for (m=0;m<4;m++){
                        for (n=0;n<4;n++){
                            for (o=0;o<4;o++){
                                tr[c].ll.value = num[i];
                                tr[c].lrl.value = num[j];
                                tr[c].lrr.value = num[k];
                                tr[c].r.value = num[l];
                                tr[c].root.operation = m;
                                tr[c].l.operation = n;
                                tr[c].lr.operation = o;
                                tr[c].root.l_child = &tr[c].l;
                                tr[c].root.r_child = &tr[c].r;
                                tr[c].l.l_child = &tr[c].ll;
                                tr[c].l.r_child = &tr[c].lr;
                                tr[c].lr.l_child = &tr[c].lrl;
                                tr[c].lr.r_child = &tr[c].lrr;
                                Tree_cal(&tr[c]);
                                printf("%d ",c);
                                put_n(tr[c]);
                                if (tr[c].root.value==24){
                                    puts("\nThe first answer is:");
                                    put_n(tr[c]);
                                    return 0;
                                }
                                c++;
                            }
                        }
                    }
                }
            }
        }
    }
}
