#ifndef AA_H_INCLUDED
#define AA_H_INCLUDED
#define SIZE 100

//栈的动态分配存储结构（存储的是字符）
typedef char Elemtype;
typedef struct{
    Elemtype *base;
    Elemtype *top;
    int StackSize;
}Stack;

//栈的动态分配存储结构（存储的是数值）
typedef struct{
    float *base;
    float *top;
    int StackSize;
}Stack1;


#endif // AA_H_INCLUDED
