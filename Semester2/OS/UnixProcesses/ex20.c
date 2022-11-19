#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv){
    int a,s;
    a=open("a",O_RDONLY);
    read(a,&s,sizeof(int));
    printf("the sum is %d\n",s);
    close(a);
    unlink("a");
    return 0;

}
