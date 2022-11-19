#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv){

        int p[2];
        pipe(p);

        if(fork()==0){

                close(p[0]);
                char name[255];
                printf("Introduceti numele unui fisier existent: ");
                scanf("%s",name);
                int nr;
                printf("Introduceit un numar natural de la tastatura: ");
                scanf("%d",&nr);
                FILE* f;
                f= fopen(name,"r");
                int numbers[nr];
                write(p[1],&nr,sizeof(int));
                for(int i=0;i<nr;i++)
                        fscanf(f,"%d",&numbers[i]);
                write(p[1],numbers,sizeof(int)*nr);
                close(p[1]);
                exit(1);

        }

        wait(0);
        if(fork()==0){
           int a;
           mkfifo("a",0600);
           a= open("a",O_WRONLY);
           int n;
           close(p[1]);
           read(p[0],&n,sizeof(int));
           int numbers[n];
           read(p[0],numbers,n*sizeof(int));
           close(p[0]);
           int s=0;
           for(int i=0;i<n;i++)
                   s=s+numbers[i];
                  write(a,&s,sizeof(int));
                   close(a);
                exit(1);
        }
        wait(0);
        close(p[0]);
        close(p[1]);
        return 0;

}
