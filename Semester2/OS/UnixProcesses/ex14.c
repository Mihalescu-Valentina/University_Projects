#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char**argv){

        int a,b,nr=0,n;
        int* arr;
        a=open("a",O_RDONLY);
        b=open("b",O_WRONLY);
        if(read(a,&n,sizeof(int))<=0)
                perror("the reading of n went wrong\n");
        arr= (int*)malloc(sizeof(int)*n);
        if(read(a,arr,n*sizeof(int))<=0)
                perror("the reading of the array went wrong\n");
        for(int i=0;i<n;i++)
                if(arr[i]%10==5)
                        nr++;
        write(b,&nr,sizeof(int));
        close(a);
        close(b);
        free(arr);
        return 0;}
