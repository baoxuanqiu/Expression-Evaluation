#ifndef AA_H_INCLUDED
#define AA_H_INCLUDED
#define SIZE 100

//ջ�Ķ�̬����洢�ṹ���洢�����ַ���
typedef char Elemtype;
typedef struct{
    Elemtype *base;
    Elemtype *top;
    int StackSize;
}Stack;

//ջ�Ķ�̬����洢�ṹ���洢������ֵ��
typedef struct{
    float *base;
    float *top;
    int StackSize;
}Stack1;


#endif // AA_H_INCLUDED
