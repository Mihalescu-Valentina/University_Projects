#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

int main(int argc,char **argv){
        int n,b2c,c2a;
        b2c= open("b2c",O_RDONLY);
        c2a=open("c2a",O_WRONLY);
        while(1){

                if(read(b2c,&n,sizeof(int))<=0)
                        break;
                if(n<=0)
                        break;
                printf("n is %d\n",n);
                n--;
                write(c2a,&n,sizeof(int));
        }

        close(b2c);
        close(c2a);
        return 0;

}
