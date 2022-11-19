#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

void calculate(char* s){
  int i,nr=0,op1=0,op2=0,p1=1;
  char operator=s[0];
        for(i=2;i<strlen(s)-1;i++){
                if(s[i]!=' ')
                        nr++;
         if(nr>0){
            op1=p1*op1+(s[i]-'0');
            p1=p1*10;
            //printf("%d\n",op1);
            if(s[i+1]==' ')
            {
             op2=op1;
             nr=0;
             op1=0;
             p1=1;
        }

        }}
        printf("operator 1 %d operator 2 %d\n",op2,op1);
         if(operator=='*')
         printf("%d\n",op1*op2);
         if(operator=='+')
          printf("%d\n",op2+op1);
         if(operator=='-')
           printf("%d\n",op2-op1);
         if(operator==':')
           printf("%d\n",op2/op1);
}

int main(int argc,char** argv){
    int p2a[2],a2b[2],b2p[2];
    pipe(p2a); pipe(a2b); pipe(b2p);
    FILE* file;
    char *text;
    file=fopen(argv[1],"r");
    text=(char*)malloc(sizeof(char)*100);
    if(fork()==0){//A
     close(p2a[1]); close(a2b[0]); close(b2p[0]); close(b2p[1]);
     fgets(text,100,(FILE*)file);
     write(a2b[1],text,sizeof(char)*100);
     while(1){
     if(read(p2a[0],text,sizeof(char)*100)<=0)
             break;
        break;
     if(fgets(text,100,(FILE*)file)==NULL)
             break;
     write(a2b[1],text,sizeof(char)*100);

     }
     close(p2a[0]);close(a2b[1]);
      exit(1);
    }
    if(fork()==0){ //B
    close(a2b[1]); close(b2p[0]); close(p2a[0]); close(p2a[1]);
    while(1){
    if(read(a2b[0],text,sizeof(char)*100)<=0)
            break;
    calculate(text);
    write(b2p[1],text,sizeof(char)*100);
    }
    close(a2b[0]); close(b2p[1]);
    exit(1);
    }


    close(p2a[0]); close(b2p[1]);
     close(a2b[0]); close(a2b[1]);
  while(1){
    if(read(b2p[0],text,sizeof(char)*100)<=0)
            break;
    write(p2a[1],text,sizeof(char)*100);
    }
    close(p2a[1]); close(b2p[0]);
    wait(0); wait(0);
    free(text);
    fclose(file);
    return 0;}
