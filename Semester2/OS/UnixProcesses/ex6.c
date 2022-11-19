#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char **argv){


        for(int i=1;i<argc;i++){
            int a[2];
            pipe(a);
                if(fork()==0){
                close(a[0]);
                dup2(a[1],1);
                execl("./exec","./exec",argv[i],NULL);
                exit(1);
          }
                  close(a[1]);
                  wait(0);
                  char s[512];
                  if(read(a[0],s,512)<0){
                         close(a[0]);
                         exit(1);}
                  close(a[0]);
                  if(fork()==0){
                    execl("./exec1","./exec1",s,NULL);
                    exit(1);
                  }
          wait(0);

        }

        return 0;}
