#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

int S=0;
int main(){
        int p2a[2],a2p[2],a2b[2];
        char* text;
        size_t size= 50;
        int u=0,l=0;
        char U[200],L[200];
        text = (char*)malloc(size);
        while(1){
        pipe(p2a); pipe(a2b); pipe(a2p);
        getdelim(&text,&size,'X',stdin);
                text[strlen(text)-1]='\0';
        if(fork()==0){//A
        close(p2a[1]); close(a2b[0]); close(a2p[0]);

          if(read(p2a[0],text,sizeof(char)*50)<=0)
                 break;
         close(p2a[0]);
         for(int i=0;i<strlen(text);i++){
            if(text[i]>='a' && text[i]<='z')
            {L[l]=text[i];
             l++;}
           else if(text[i]>='A'&& text[i]<='Z')
            {
              U[u]=text[i];
              u++;
            }
            else
                  S++;

         }


         write(a2b[1],&u,sizeof(int));
         write(a2b[1],U,sizeof(char)*u);
         write(a2b[1],&l,sizeof(int));
         write(a2b[1],L,sizeof(char)*l);
         close(a2b[1]);
         write(a2p[1],&S,sizeof(int));
         close(a2p[1]);



        exit(1);
        }
          if(fork()==0){//B
                close(a2b[1]); close(p2a[0]); close(p2a[1]); close(a2p[1]); close(a2p[0]);



          if(read(a2b[0],&u,sizeof(int))<=0 ||
          read(a2b[0],U,sizeof(char)*u)<=0 ||
          read(a2b[0],&l,sizeof(int))<=0 ||
          read(a2b[0],L,sizeof(char)*l)<=0)
                  break;
           close(a2b[0]);
             printf("The sum of lengths is %d\n",u+l);


        exit(1);
        }

        close(p2a[0]); close(a2b[0]); close(a2b[1]);

        write(p2a[1],text,sizeof(char)*50);
        close(p2a[1]);
              if(read(a2p[0],&S,sizeof(int))<=0)
                      break;

                close(a2p[0]);
        if(S!=0||l!=0||u!=0)
                break;
          wait(0); wait(0);}
        printf("S is %d\n",S);
        free(text);
        return 0;}
