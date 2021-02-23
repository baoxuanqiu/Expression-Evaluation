#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"aa.h"

#define INITSIZE 7
#define INCREMENT 7
#define LEN sizeof(float)

//��ʼ��ջ
void InitStack_1(Stack1 *S){
    S->base=(float*)malloc(LEN*INITSIZE);
    assert(S->base!=NULL);//�ж��Ƿ����ݳɹ�
    S->top=S->base;//��top��ֵ��base��
    S->StackSize=INITSIZE;
}

//ѹջ����
void PushStack_1(Stack1 *S,float c){
    if(S->top - S->base >= S->StackSize){
/*realloc()��������ڶ�������ָ�����ڴ��������ѵ�һ������ָ��ָ���֮ǰ��������ݸ��Ƶ�������ڴ��У�
�Ҹ��Ƶ����ݳ��ȵ����¾��ڴ������н�С����һ����
�����ڴ����ԭ�ڴ棬��ԭ�ڴ��������ݸ��Ƶ����ڴ棬������ڴ�С��ԭ�ڴ棬ֻ���Ƴ��ȵ������ڴ�ռ�����ݡ�*/
        S->base=(float*)realloc(S->base,LEN*(S->StackSize+INCREMENT));
        assert(S->base!=NULL);
        S->top=S->base+S->StackSize;//��top���¸�ֵ�����µġ�base��StackSize
        S->StackSize+=INCREMENT;
    }
    *S->top++ = c;//��c��ֵ��top��Ȼ��top��һ
}

//ջ��
int StackLength_1(Stack1 *S){
    return (S->top - S->base);
}

//��ջ����������ջ��ֵ��ֵ��*c
int PopStack_1(Stack1 *S,float *c){
    if(!StackLength_1(S)){
        return 0;
    }
    *c=*--S->top;//S������λΪNULL������Ҫ���Լ�һ���ٸ�ֵ
    return 1;
}
