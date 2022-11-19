#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc,char **argv){
  int a,cmmmc=1;
  int p[2];
  pipe(p);
  if(fork()==0){
  close(p[0]);
  a= open("a",O_RDONLY);
  if(a<=0){
          perror("an error occur when readin from the fifo\n");
          close(a);
          exit(1);
  }

  read(a,&cmmmc,sizeof(int));
  int div[50],j=0;
  for(int i=1;i<=cmmmc;i++)
          if(cmmmc%i==0){
                  div[j]=i;
                  j++;
          }
  write(p[1],&j,sizeof(int));
  write(p[1],div,sizeof(int)*j);
  close(p[1]);
  close(a);
  exit(1);
  }
  if(fork()==0){
    close(p[1]);
    int div[50],n;
    read(p[0],&n,sizeof(int));
    read(p[0],div,sizeof(int)*n);
    for(int i=0;i<n;i++)
            printf("%d\n",div[i]);
    close(p[0]);
    exit(1);
  }
  wait(0);
  wait(0);
  unlink("a");
  return 0;}
