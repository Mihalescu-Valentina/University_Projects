#include<stdlib.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char** argv){
  for(int i=1;i<argc;i++){
    int a[2];
    pipe(a);

    if(fork()==0){
      dup2(a[2],1);


     exit(1);
    }


  }

  return 0;

}
