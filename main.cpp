#include<stdio.h>
#include"aa.h"
#define true 1
#define error 0
char arr[20][1000];//����ļ������еı��ʽ
extern int num;//�ļ��б��ʽ�ĸ���

extern void InitStack(Stack *S);
extern int read_file(char *filename,char array1[][1000]);
extern int Stack_Queue(Stack *S);
extern void Result(Stack1 *stack1);

extern char a[20][1000];
int main() {
    char *filename1="c:\\codeblocks\\���ʽ��ֵ\\input.txt";
    Stack S;
    Stack1 stack1;
    read_file(filename1,arr);
    Stack_Queue(&S);
    Result(&stack1);
    return 0;
}
