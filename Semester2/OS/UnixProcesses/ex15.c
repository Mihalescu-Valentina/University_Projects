#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char** argv){

        int arr[255],i=0;
        int a;
        mkfifo("a",0600);
        while(1){
           if(scanf("%d",&arr[i])<=0)
               break;
           if(arr[i]==-1)
                   break;
           i++;
        }
        a=open("a",O_WRONLY);
        write(a,&i,sizeof(int));
        write(a,arr,sizeof(int)*i);
        close(a);


        return 0;}
