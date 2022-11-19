#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>

int main(int argc,char** argv){

        int a,b;
        mkfifo("a",0600);
        mkfifo("b",0600);
        srand(time(0));
        int nr = (rand()%(10-1+1))+1;
        a=open("a",O_RDONLY);
        b=open("b",O_WRONLY);
        printf("The number that has to be guessed is %d\n",nr);
        while(1){

                int x;
                char y[3]="";
                if(read(a,&x,sizeof(int))<=0)
                        break;
                printf("B sends to A %d\n",x);
                if(x<nr){
                        strcpy(y,"<=");
                        y[2]='\0';
                        write(b,y,sizeof(char)*3);
                }
                else
                        if(x>nr)
                        {
                                strcpy(y,">=");
                                y[2]='\0';
                                write(b,y,sizeof(char)*3);
                        }
                        else
                                if(x==nr){
                                        strcpy(y,"=");
                                        y[2]='\0';
                                        write(b,y,sizeof(char)*3);}

        }

        close(a);
         close(b);
        unlink("a");
        unlink("b");

     

return 0;

}
