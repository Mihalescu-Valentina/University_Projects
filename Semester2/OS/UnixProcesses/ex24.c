#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc,char **argv){

        int a,v[5];
        a=open("a",O_RDONLY);
        read(a,v,sizeof(int)*5);
        printf("the frequency of A is %d \n",v[0]);
        printf("the frequency of E is %d \n",v[1]);
        printf("the frequency of I is %d \n",v[2]);
        printf("the frequency of O is %d \n",v[3]);
        printf("the frequency of U is %d \n",v[4]);
        close(a);
        unlink("a");
        return 0;

}
