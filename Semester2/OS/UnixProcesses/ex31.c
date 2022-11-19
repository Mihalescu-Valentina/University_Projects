#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char** argv){
  int x,y,n;
  char s[1024];
  if(argc>3){
     x = open(argv[1],O_WRONLY);
     y = open(argv[2],O_RDONLY);
     strcpy(s,argv[3]);
     write(x,s,1024);
     read(y,&n,sizeof(int));
     printf("%d\n",n);
  }
  else{
   x = open(argv[1],O_RDONLY);
   y = open(argv[2],O_WRONLY);
   read(x,s,1024);
   n= strlen(s);
   write(y,&n,sizeof(int));
  }
  close(x);
  close(y);



  return 0;

}
