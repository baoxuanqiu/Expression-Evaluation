#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include"aa.h"

#define INITSIZE 7
#define INCREMENT 7
#define LEN sizeof(float)

//初始化栈
void InitStack_1(Stack1 *S){
    S->base=(float*)malloc(LEN*INITSIZE);
    assert(S->base!=NULL);//判断是否扩容成功
    S->top=S->base;//将top赋值到base处
    S->StackSize=INITSIZE;
}

//压栈操作
void PushStack_1(Stack1 *S,float c){
    if(S->top - S->base >= S->StackSize){
/*realloc()函数分配第二个参数指定的内存量，并把第一个参数指针指向的之前分配的内容复制到新配的内存中，
且复制的内容长度等于新旧内存区域中较小的那一个。
即新内存大于原内存，则原内存所有内容复制到新内存，如果新内存小于原内存，只复制长度等于新内存空间的内容。*/
        S->base=(float*)realloc(S->base,LEN*(S->StackSize+INCREMENT));
        assert(S->base!=NULL);
        S->top=S->base+S->StackSize;//将top重新赋值到“新的”base的StackSize
        S->StackSize+=INCREMENT;
    }
    *S->top++ = c;//将c赋值给top，然后top增一
}

//栈长
int StackLength_1(Stack1 *S){
    return (S->top - S->base);
}

//出栈操作，将出栈的值赋值给*c
int PopStack_1(Stack1 *S,float *c){
    if(!StackLength_1(S)){
        return 0;
    }
    *c=*--S->top;//S的最外位为NULL，所以要先自减一，再赋值
    return 1;
}
