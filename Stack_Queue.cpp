#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"aa.h"
#include<math.h>

#define Elemtype char
#define true 1
#define error 0

extern int write_file(char array2[],int flag,float sum);
extern int read_file(char *filename,char array1[][1000]);
extern void InitStack(Stack *S);
extern void PushStack(Stack *S,Elemtype c);
extern int StackLength(Stack *S);
extern int PopStack(Stack *S,Elemtype *c);
extern int Destorystack(Stack *S);
extern void InitStack_1(Stack1 *S);
extern void PushStack_1(Stack1 *S,float c);
extern int StackLength_1(Stack1 *S);
extern int PopStack_1(Stack1 *S,float *c);
extern char arr[20][1000];
extern int num;
int flag_stack[20];//���ÿһ����׺���ʽ�Ƿ���ȷ����ȷΪtrue������Ϊerror
char a[20][1000];//��ź�׺���ʽ
char arr1[20][1000];//����ļ������еı��ʽ��������
//��׺���ʽת��׺��ʾʽ
int Stack_Queue(Stack *S) {
    for(int x=0; x<num; x++) {
        flag_stack[x]=true;
        InitStack(S);
        Elemtype e;
        int n=0;//��ʾa��������
        int i=0;
        while(arr[x][i]!='\0') {
            //���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ��
            while(isdigit(arr[x][i]) || arr[x][i]=='.') {
                a[x][n++]=arr[x][i++];
                if(!isdigit(arr[x][i]) && arr[x][i]!='.') {
                    a[x][n++]=' ';
                }
            }

            //�Ӽ��������ȼ����
            if(arr[x][i]=='+' || arr[x][i]=='-') {
                if(!StackLength(S)) { //ջ��Ԫ��Ϊ����ֱ�ӽ�ջ
                    PushStack(S,arr[x][i]);
                } else {
                    do {
                        PopStack(S,&e);
                        if(e=='(') {
                            PushStack(S,e);
                        } else {
                            a[x][n++]=e;
                        }
                    } while(StackLength(S) && e!='(');
                    PushStack(S,arr[x][i]);
                }
            }
            /*�������������ǣ���������ʣ��������������ֱ��ƥ�䵽������Ϊֹ
            ������ֻ��������ӡ��������Ҳ��ѹջ��*/
            else if(arr[x][i]==')') {
                if(!StackLength(S)) {
                    flag_stack[x]=error;
                    break;
                }
                PopStack(S,&e);
                while(e!='(' && StackLength(S)) {
                    a[x][n++]=e;
                    PopStack(S,&e);
                }
                if(e!='(') {
                    flag_stack[x]=error;
                    break;
                }
            }

            //^���ȼ����
            else if(arr[x][i]=='^') {
                if(!StackLength(S)) { //ջ��Ԫ��Ϊ����ֱ�ӽ�ջ
                    PushStack(S,arr[x][i]);
                } else {
                    PopStack(S,&e);
                    if(e=='^') {
                        a[x][n++]=e;
                        PushStack(S,arr[x][i]);
                    } else {
                        PushStack(S,e);
                        PushStack(S,arr[x][i]);
                    }
                }
            }

            /*�ˡ��������඼�����ȼ��θߣ����ж�ջ������û��^,��ѹջ*/
            else if(arr[x][i]=='*' || arr[x][i]=='/' || arr[x][i]=='%') {
                if(!StackLength(S)) { //ջ��Ԫ��Ϊ����ֱ�ӽ�ջ
                    PushStack(S,arr[x][i]);
                } else {
                    PopStack(S,&e);//��ջ
                    if(e=='^') {
                        a[x][n++]=e;
                        PushStack(S,arr[x][i]);
                    } else {
                        PushStack(S,e);
                        PushStack(S,arr[x][i]);
                    }
                }//else
            }
            //���������ȼ����
            else if(arr[x][i]=='(') {
                PushStack(S,arr[x][i]);
            }

            else if(arr[x][i]=='\0') {
                break;
            }

            else {
                printf("\n�����ʽ����\n");
                return 0;
            }
            i++;
        }//while

        /*����ջ��ʣ�����������ε�ջ��ӡ*/
        if(flag_stack[x]==true) {
            while(StackLength(S)) {
                PopStack(S,&e);
                if(e=='(') {
                    flag_stack[x]=error;
                    break;
                }
                a[x][n++]=e;
            }//while
        }
        Destorystack(S);
    }
    return 1;
}

void Result(Stack1 *stack1) {
    char *filename2="c:\\codeblocks\\���ʽ��ֵ\\output.txt";
    for(int i=0; i<num; i++) {
        int flag=true;
        float f1,f2,c;
        InitStack_1(stack1);//��ʼ��ջ
        char p[20];
        int m=0;//p�ĸ���
        int j=0;
        if(flag_stack[i]==error) {
            flag=error;
            write_file(arr[i],flag,0.0);
        } else {
            while(a[i][j]!='\0') {
                if(flag==true) {
                    while(isdigit(a[i][j]) || a[i][j]=='.') {
                        p[m++]=a[i][j++];
                        p[m]='\0';
                        if(a[i][j]==' ') {
                            float f=atof(p);//����ֵȡ������ֵ��f��
                            PushStack_1(stack1,f);
                            m=0;
                            break;
                        }
                    }
                    switch(a[i][j]) {
                    case '+':
                        PopStack_1(stack1,&f1);
                        PopStack_1(stack1,&f2);
                        PushStack_1(stack1,f2+f1);
                        break;
                    case '-':
                        PopStack_1(stack1,&f1);
                        PopStack_1(stack1,&f2);
                        PushStack_1(stack1,f2-f1);
                        break;
                    case '*':
                        PopStack_1(stack1,&f1);
                        PopStack_1(stack1,&f2);
                        PushStack_1(stack1,f2*f1);
                        break;
                    case '/':
                        PopStack_1(stack1,&f1);
                        if(f1 == 0) {
                            flag=error;
                            //printf("���������ĸΪ�㣡\n");
                            write_file(arr[i],flag,0.0);
                            break;
                        }
                        PopStack_1(stack1,&f2);
                        PushStack_1(stack1,f2/f1);
                        break;
                    case '%':
                        PopStack_1(stack1,&f1);
                        PopStack_1(stack1,&f2);
                        if(f1 != int(f1) || f2 != int(f2) || f1==0) {
                            //printf("���������������뱻����ӦΪ������\n");
                            flag=error;
                            write_file(arr[i],flag,0.0);
                            break;
                        }
                        PushStack_1(stack1,(int)f2%(int)f1);
                        break;
                    case '^':
                        PopStack_1(stack1,&f1);
                        if(f1 != int(f1)) {
                            //printf("���������ָ��ӦΪ������\n");
                            flag=error;
                            write_file(arr[i],flag,0.0);
                            break;
                        }
                        PopStack_1(stack1,&f2);
                        PushStack_1(stack1,pow(f2,(int)f1));
                        break;
                    }
                    j++;
                }//if
            }//while
            if(flag==true) {
                PopStack_1(stack1,&c);
                write_file(arr[i],flag,c);
                //printf("%f\n",sum[i]);
            }
        }//else
    }//for
    read_file(filename2,arr1);
    for(int i=0; i<num; i++) {
        for(int j=0;; j++) {
            if(arr1[i][j]=='\0') {
                printf("\n");
                break;
            }
            printf("%c",arr1[i][j]);
        }
    }
}



