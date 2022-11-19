#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>
int S;
int main(int argc,char** argv){

        char s[250];
        int U[20]={0};
        int L[20]={0};
        scanf("%s",s);
        while(strcmp(s,"X")!=0){
           printf("%s\n",s);
           int p[2];
           int x[2];
           int y[2];
           pipe(p);
           pipe(x);
           pipe(y);
           if(fork()==0){
                   char s[250];
                close(p[1]);
                close(x[0]);
                close(y[0]);
                read(p[0],s,sizeof(char)*250);
                close(p[0]);
                int j=0,l=0;
                for(int i=0;i<strlen(s);i++){
                        if(s[i]>='A'&&s[i]<='Z')
                        {U[j]++;
                        j++;}
                        else
                                if(s[i]>='a'&&s[i]<='z'){
                                        L[l]++;
                                        l++;}
                                else
                                        S++;}
                printf("the len of U is %d\n",j);
                printf("the length of L is %d\n",l);
                write(x[1],&S,sizeof(int));
                close(x[1]);
                write(y[1],&j,sizeof(int));
                write(y[1],U,sizeof(int)*j);
                write(y[1],&l,sizeof(int));
                write(y[1],L,sizeof(int)*l);
              close(y[1]);
                   exit(1);}
           if(fork()==0){
                   close(x[0]);close(x[1]);
                   close(p[0]); close(p[1]);
                   close(y[1]);
                   int j,l;
                   int L[20]={0},U[20]={0};
           read(y[0],&j,sizeof(int));
           read(y[0],U,sizeof(int)*j);
           read(y[0],&l,sizeof(int));
           read(y[0],L,sizeof(int)*l);
           close(y[0]);
           int sum=j+l;
           printf("The sum of the sizes is %d\n",sum);
           exit(2);
           }
           close(p[0]);
           close(x[1]);
           close(y[0]);close(y[1]);
           write(p[1],s,sizeof(char)*250);
           wait(0);
           wait(0);
           close(p[0]);
           read(x[0],&S,sizeof(int));
           close(x[0]);
           scanf("%s",s);
        }
           printf("S is %d\n",S);

        return 0;

}
