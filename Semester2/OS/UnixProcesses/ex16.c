#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>
int main(int argc,char** argv){

        int a,n,sum=0;
        int arr[255];
        int p[2];
        pipe(p);
        a=open("a",O_RDONLY);

        if(fork()==0){
                close(p[0]);
                if(read(a,&n,sizeof(int))<=0){
                        perror("error reading the length\n");
                        close(a);}
                if(read(a,arr,sizeof(arr))<=0)
                {perror("error reading from fifo\n");
                        close(a);}
        for(int i=0;i<n;i++)
                sum=sum+arr[i];
        write(p[1],&sum,sizeof(int));
        close(p[1]);
        close(a);
        exit(1);}

        if(fork()==0){
                close(p[1]);
                read(p[0],&sum,sizeof(int));
                for(int i=1;i<=sum;i++)
                        if(sum%i==0)
                                printf("%d is a divisor of %d\n",i,sum);
             close(p[0]);
             exit(1);}

        unlink("a");
        wait(0);
        wait(0);

        return 0;}
~                   
