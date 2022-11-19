#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char **argv){

        int i,s=0;
        for(i=1;i<argc;i++){
        int p[2];
        pipe(p);
                if(fork()==0){
                close(p[0]);
                dup2(p[1],1);
                execlp("./exec3","./exec3",argv[i],NULL);
                exit(1);
        }


        close(p[1]);
        wait(0);
        int nr;
        if(read(p[0],&nr,sizeof(int))<0){
        close(p[0]);
        exit(0);
        }

        close(p[0]);
        printf("the nr is %d\n",nr);
        s=s+nr;
        }

        printf("the sum is %d\n",s);


        return 0;

}
