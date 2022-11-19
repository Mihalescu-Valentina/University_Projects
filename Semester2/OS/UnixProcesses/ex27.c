#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc,char**argv){
        int i,len=0,avg=0,sum=0;
        for(i=1;i<argc;i++){
                int p[2];
                pipe(p);
                if(fork()==0){
                        int len=0;
                        close(p[0]);
                        printf("The argument is %s\n",argv[i]);
                        len = strlen(argv[i]);
                        //printf("The length is %d\n",len);
                        write(p[1],&len,sizeof(int));
                        close(p[1]);
                        exit(1);}
                //wait(0);
                close(p[1]);
                read(p[0],&len,sizeof(int));
                printf("The length of the argument is %d\n",len);
                sum= len+sum;
                close(p[0]);
                wait(0);
        }


        avg=sum/(argc-1);
        printf("The average is %d\n",avg);


return 0;

}
