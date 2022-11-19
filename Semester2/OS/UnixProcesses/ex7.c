#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(int argc, char **argv){
        int N=(rand() % (30 - 10 + 1)) + 10;
        char *string = (char*) malloc(sizeof(string)*N);
        for(int i=0;i<N;i++)
                string[i]='a';
        int p2a[2],a2p[2];
        pipe(p2a); pipe(a2p);
        if(fork()==0){
            close(p2a[1]);
            close(a2p[0]);
            read(p2a[0],string,sizeof(char)*N);
            close(p2a[0]);
            for(int i=0;i<N;i++)
                 string[i]=string[i]+ rand() % (24 + 1);
            write(a2p[1],string,sizeof(char)*N);
            close(a2p[1]);
        exit(1);

        }
         close(p2a[0]); close(a2p[1]);
         write(p2a[1],string,sizeof(char)*N);
         close(p2a[1]);
         read(a2p[0],string,sizeof(char)*N);
         close(a2p[0]);
         wait(0);
         printf("N is %d \n",N);
         printf("The string is %s \n",string);
        return 0;
}
