#include<stdio.h>
#include<string.h>//FILE
#include<stdlib.h>//exit(1)

#define true 1
#define error 0
int num;

int num_file(char *filename) { //��ȡ�ļ����м�������
    FILE *fp=fopen(filename,"r");
    if(!fp) {
        printf("��ȡ�ļ�����!");
        return -1;
    }
    char buf[10000]= {0};
    char *p=NULL;
    int num=0;
    while((p=fgets(buf,sizeof(buf)-1,fp))!=NULL) {
        if(buf[strlen(buf)-1]=='\n')
            num++;
    }
    fclose(fp);
    return num+1;
}

int read_file(char *filename,char array1[][1000]) {
    FILE *fd=fopen(filename,"rt+");
    if(fd==NULL) {
        printf("�ļ���ʧ�ܣ�");
        exit(1);
    }
    num=num_file(filename);
    for(int i=0; i<num; i++) {
        fscanf(fd,"%s\n",array1[i]);
    }
    fclose(fd);
    return true;
}


int write_file(char array2[],int flag,float sum) {
    FILE *fd=fopen("c:\\codeblocks\\���ʽ��ֵ\\output.txt","awb");
    if(fd==NULL) {
        printf("�ļ���ʧ�ܣ�");
        exit(1);
    }
    if(flag==true) {
        fprintf(fd,"%s%s",array2,"=");
        fprintf(fd,"%f\n",sum);
    }else {
        fprintf(fd,"%s%s",array2,"=");
        fprintf(fd,"%s\n","�ñ��ʽ����");
    }
    fclose(fd);
    return true;
}
