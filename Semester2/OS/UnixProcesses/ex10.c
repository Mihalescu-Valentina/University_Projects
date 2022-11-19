#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(int argc,char **argv){
   int n,a2b,c2a;
   a2b= open("a2b",O_WRONLY);
   c2a=open("c2a",O_RDONLY);
   n=20;
   write(a2b,&n,sizeof(int));
   while(1){

    if(read(c2a,&n,sizeof(int))<=0)
            break;
    if(n<=0)
            break;
    printf("n is %d\n",n);
    n--;
    write(a2b,&n,sizeof(int));
   }
   close(a2b);
   close(c2a);
   return 0;

   }
