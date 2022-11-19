#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv){
        int p[2];
        pipe(p);
        mkfifo("a",0600);
        if(fork()==0){
                close(p[0]);
                char path[100];
                printf("Enter the file name\n");
                scanf("%s",path);
                write(p[1],path,sizeof(char)*100);
                close(p[1]);
                exit(1);
        }

        wait(0);
        if(fork()==0){
                //close(p[1]);
                int a;
                char c=' ';
                char path[100];
                a=open("a",O_WRONLY);
                if(read(p[0],path,sizeof(char)*100)<=0)
                        perror("error reading the path\n");

                close(p[0]);
                FILE* f;
                f=fopen(path,"r");
                int freq[5]={0};
                while(fscanf(f,"%c",&c)!=EOF)
                {
                        if(c=='A') freq[0]++;
                        else if(c=='E') freq[1]++;
                        else if(c=='I') freq[2]++;
                        else if(c=='O') freq[3]++;
                        else if(c=='U') freq[4]++;

                }
                printf("the freq of I is %d\n",freq[2]);
                write(a,freq,sizeof(int)*5);
                close(a);

                exit(1);
        }
        close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
        return 0;}
