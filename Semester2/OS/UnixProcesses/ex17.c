#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int cmmmcfunc(int nr1,int nr2){

    int cmmmc,ok=0;
    if(nr1>nr2)
            cmmmc=nr1;
    else
            cmmmc= nr2;
    while(ok==0){
          if(cmmmc%nr1==0 && cmmmc%nr2==0)
                  ok=1;
          else
                cmmmc++;

}
return cmmmc;}

int main(int argc,char **argv){
        int nr1,nr2;
        int a;
        mkfifo("a",0600);
        scanf("%d",&nr1);
        scanf("%d",&nr2);
        int cmmmc=cmmmcfunc(nr1,nr2);
        printf("cmmmc is %d\n",cmmmc);
        a= open("a",O_WRONLY);
        if(a==-1){
                perror("Error opening fifo\n");
                close(a);
                exit(1);}
        write(a,&cmmmc,sizeof(int));
        close(a);

        return 0;


}
