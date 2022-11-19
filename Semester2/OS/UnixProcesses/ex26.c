#include<sys/wait.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc,char **argv){

        int i,s=0;
        for(i=1;i<argc;i++){
                int a;
                mkfifo("a",0600);
                if(fork()==0){
                        a=open("a",O_WRONLY);
                        dup2(a,1);
                        execlp("./exec3","./exec3",argv[i],NULL);
                        exit(1);
                }
                wait(0);
                close(a);
                int nr;
                //a=open("a",O_RDONLY);
                if(read(a,&nr,sizeof(int))<0){
                        perror("Error reading\n");
                        exit(1);}
                close(a);
                unlink("a");
                printf("The number is %d\n",nr);
                s=s+nr;}
                printf("the sum is %d\n",s);


        return 0;

}
