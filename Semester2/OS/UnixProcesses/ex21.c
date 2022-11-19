#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv){

        int n;
        char name[255];
        int p[2];
        pipe(p);
        printf("Please enter a valid filename\n");
        scanf("%s",name);
        printf("Please enter an integer number\n");
        scanf("%d",&n);
        if(fork()==0){
           close(p[0]);
           FILE* f;
           f= fopen(name,"r");
           char text[500];
           fscanf(f,"%s",text);
           write(p[1],&text[n-1],sizeof(char));
           close(p[1]);
                exit(0);
        }

        wait(0);
        if(fork()==0){
          close(p[1]);
          char c;
          read(p[0],&c,sizeof(char));
          close(p[0]);
          if((c>='a' && c<='z') || (c>='A' && c<='Z'))
                  printf("%c is a letter\n",c);
          else
                  if(c>='0'&&c<='9')
                          printf("%c is a digit\n",c);
          else
                  printf("%c is something else\n",c);
          int a;
          mkfifo("a",0600);
          a= open("a",O_WRONLY);
          write(a,&c,sizeof(char));
          close(a);
          exit(1);
        }
        wait(0);
        close(p[0]);
        close(p[1]);
        return 0;}
