#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include <sys/stat.h>
int main(int argc,char** argv){
        int i;
        for(i=1;i<=argc;i++){
                mkfifo("x",0600);
                mkfifo("y",0600);
                if(fork()==0){
                        execl("./retakeboian1","./retakeboian1","x","y",argv[i],NULL);
                        exit(1);}
                if(fork()==0){
                        execl("./retakeboian1","./retakeboian1","x","y",NULL);
                        exit(1);}
                wait(0);
                wait(0);
                unlink("x");
                unlink("y");}

        return 0;}
