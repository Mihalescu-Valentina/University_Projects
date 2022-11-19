#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char**argv){

        char s[20]="intelligent";
        printf("(A) -> %s\n",s);
        int p1[2],p2[2];
        pipe(p1);
        pipe(p2);
        while(1){
        if(fork()==0){
        close(p1[1]);
        close(p2[0]);
        char s[20]="";
        read(p1[0],s,sizeof(char)*20);
        close(p1[0]);
        printf("(A) ->%s\n",s);
        if(strlen(s)<=3)
                break;
        int k=2;
        while(k!=0){
                for(int i=0;i<strlen(s);i++)
                        s[i]=s[i+1];
          k--;
        }
        write(p2[1],s,sizeof(char)*20);
        close(p2[1]);
        exit(1);
        }

        close(p1[0]);
        close(p2[1]);
        write(p1[1],s,sizeof(char)*20);
        close(p1[1]);
        wait(0);

        if(strlen(s)<=3)
                break;
        s[strlen(s)-1]='\0';
        read(p2[0],s,sizeof(char)*20);
        printf("(B) ->%s\n",s);
        close(p2[0]);

        }
        return 0;}
