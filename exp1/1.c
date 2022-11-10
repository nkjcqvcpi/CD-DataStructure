#include <stdio.h>

typedef struct complex{
    float a, b;
} complex;

void scanc(complex *x);
void printc(complex y);

complex i1,i2,o1,o2,o3;

complex sum(complex x1,complex x2);
complex sub(complex x1,complex x2);
complex mul(complex x1,complex x2);

int main(){
    puts("C Ver.");
    scanc(&i1);printf("x1 = ");printc(i1);
    scanc(&i2);printf("x2 = ");printc(i2);
    o1 = sum(i1,i2);printf("sum = ");printc(o1);
    o2 = sub(i1,i2);printf("sub = ");printc(o2);
    o3 = mul(i1,i2);printf("mul = ");printc(o3);
}

void scanc(complex *x){
    float i,j;
    printf("输入实部 a = ");scanf("%f",&i);
    printf("输入虚部 b = ");scanf("%f",&j);
    (*x).a=i;x->b=j;
}

void printc(complex y){
    if (y.b<0) printf("%f%fi\n",y.a,y.b);
    else printf("%f+%fi\n",y.a,y.b);
}

complex sum(complex x1,complex x2){
    complex z;
    z.a = x1.a + x2.a;
    z.b = x1.b + x2.b;
    return(z);
}

complex sub(complex x1,complex x2){
    complex z;
    z.a = x1.a - x2.a;
    z.b = x1.b - x2.b;
    return(z);
}

complex mul(complex x1,complex x2){
    complex z;
    z.a = x1.a * x2.a - x1.b * x2.b;
    z.b = x1.a * x2.b + x2.a * x1.b;
    return(z);
}
