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
int flag_stack[20];//存放每一个中缀表达式是否正确，正确为true，错误为error
char a[20][1000];//存放后缀表达式
char arr1[20][1000];//存放文件中所有的表达式与运算结果
//中缀表达式转后缀表示式
int Stack_Queue(Stack *S) {
    for(int x=0; x<num; x++) {
        flag_stack[x]=true;
        InitStack(S);
        Elemtype e;
        int n=0;//表示a的列坐标
        int i=0;
        while(arr[x][i]!='\0') {
            //过滤数字字符，直接输出，直到下一位不是数字字符打印空格跳出循环
            while(isdigit(arr[x][i]) || arr[x][i]=='.') {
                a[x][n++]=arr[x][i++];
                if(!isdigit(arr[x][i]) && arr[x][i]!='.') {
                    a[x][n++]=' ';
                }
            }

            //加减运算优先级最低
            if(arr[x][i]=='+' || arr[x][i]=='-') {
                if(!StackLength(S)) { //栈顶元素为空则直接进栈
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
            /*当遇到右括号是，把括号里剩余的运算符弹出，直到匹配到左括号为止
            左括号只弹出不打印（右括号也不压栈）*/
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

            //^优先级最高
            else if(arr[x][i]=='^') {
                if(!StackLength(S)) { //栈顶元素为空则直接进栈
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

            /*乘、除、求余都是优先级次高，先判断栈里面有没有^,再压栈*/
            else if(arr[x][i]=='*' || arr[x][i]=='/' || arr[x][i]=='%') {
                if(!StackLength(S)) { //栈顶元素为空则直接进栈
                    PushStack(S,arr[x][i]);
                } else {
                    PopStack(S,&e);//出栈
                    if(e=='^') {
                        a[x][n++]=e;
                        PushStack(S,arr[x][i]);
                    } else {
                        PushStack(S,e);
                        PushStack(S,arr[x][i]);
                    }
                }//else
            }
            //左括号优先级最高
            else if(arr[x][i]=='(') {
                PushStack(S,arr[x][i]);
            }

            else if(arr[x][i]=='\0') {
                break;
            }

            else {
                printf("\n输入格式错误！\n");
                return 0;
            }
            i++;
        }//while

        /*最后把栈中剩余的运算符依次弹栈打印*/
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
    char *filename2="c:\\codeblocks\\表达式求值\\output.txt";
    for(int i=0; i<num; i++) {
        int flag=true;
        float f1,f2,c;
        InitStack_1(stack1);//初始化栈
        char p[20];
        int m=0;//p的个数
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
                            float f=atof(p);//将数值取出来赋值到f上
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
                            //printf("输入出错，分母为零！\n");
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
                            //printf("输入出错，求余除数与被除数应为整数！\n");
                            flag=error;
                            write_file(arr[i],flag,0.0);
                            break;
                        }
                        PushStack_1(stack1,(int)f2%(int)f1);
                        break;
                    case '^':
                        PopStack_1(stack1,&f1);
                        if(f1 != int(f1)) {
                            //printf("输入出错，幂指数应为整数！\n");
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



