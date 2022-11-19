#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

int main(int argc,char **argv){
        int n,a2b,b2c;
        a2b= open("a2b",O_RDONLY);
        b2c=open("b2c",O_WRONLY);
        while(1){

                if(read(a2b,&n,sizeof(int))<=0)
                        break;
                if(n<=0)
                        break;
                printf("n is %d\n",n);
                n--;
                write(b2c,&n,sizeof(int));
        }

        close(a2b);
        close(b2c);
        return 0;

}
