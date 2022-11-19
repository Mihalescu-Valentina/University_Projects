#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char**argv){

        int a,b,nr,n;
        scanf("%d",&n);
        int* arr = (int*)malloc(sizeof(int)*n);
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);

        }
        a=open("a",O_WRONLY);
        b=open("b",O_RDONLY);
        write(a,&n,sizeof(int));
        write(a,arr,n*sizeof(int));
        if(read(b,&nr,sizeof(int))<=0)
                perror("the reading went wrong\n");
        close(a);
        close(b);
        printf("%d\n",nr);
        free(arr);
        return 0;}
