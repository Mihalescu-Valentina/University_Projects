#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char **argv){

        int a,b;
        a=open("a",O_WRONLY);
        b=open("b",O_RDONLY);
        while(1){
                int x;
                x= (rand()%(10-1+1))+1;
                write(a,&x,sizeof(int));
                char res[3]="";
                if(read(b,res,sizeof(char)*3)<=0)
                        break;
                printf("A sends to B %s\n",res);
                char a[3]="=";
                a[2]='\0';
                if(strcmp(res,a)==0)
                {
                        break;
                }


        }

        close(a);
        close(b);
        return 0;


}
