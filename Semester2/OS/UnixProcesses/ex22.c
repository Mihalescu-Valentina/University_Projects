#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv){
  int a;
  char c;
  a=open("a",O_RDONLY);
  read(a,&c,sizeof(char));
  printf("The ascii code of %c is %d\n",c,c);

  unlink("a");
  return 0;

}
