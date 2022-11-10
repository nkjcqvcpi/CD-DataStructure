#include <iostream>

class complex{
    public:
    float a, b;
    void scanc(void);
    void printc(void);
};

void complex::scanc(void){
    printf("输入实部 a = ");scanf("%f",&a);
    printf("输入虚部 b = ");scanf("%f",&b);
}

void complex::printc(void){
    if (b<0) printf("%f%fi\n",a,b);
    else printf("%f+%fi\n",a,b);
}

class ComplexPair : public complex{
    public:
    complex z;
    complex sum(complex x1,complex x2);
    complex sub(complex x1,complex x2);
    complex mul(complex x1,complex x2);
};

complex ComplexPair::sum(complex x1,complex x2){
    z.a = x1.a + x2.a;
    z.b = x1.b + x2.b;
    return(z);
}

complex ComplexPair::sub(complex x1,complex x2){
    z.a = x1.a - x2.a;
    z.b = x1.b - x2.b;
    return(z);
}

complex ComplexPair::mul(complex x1,complex x2){
    z.a = x1.a * x2.a - x1.b * x2.b;
    z.b = x1.a * x2.b + x2.a * x1.b;
    return(z);
}

complex i1,i2,o1,o2,o3;
ComplexPair c;

int main(){
    puts("C++ Ver.");
    i1.scanc();printf("x1 = ");i1.printc();
    i2.scanc();printf("x2 = ");i2.printc();
    o1 = c.sum(i1,i2);printf("sum = ");o1.printc();
    o2 = c.sub(i1,i2);printf("sub = ");o2.printc();
    o3 = c.mul(i1,i2);printf("mul = ");o3.printc();
}
