#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>

int maxim(int a,int b){
        if(a>=b)
                return 1;
        else return 2;}

int main(int argc,char **argv){
    int n=atoi(argv[1]);
    int a2p[2],b2p[2];
    pipe(a2p); pipe(b2p);
    int freq1[10]={0},freq2[10]={0};
    if(fork()==0){//A
      close(b2p[0]); close(b2p[1]);
      close(a2p[0]);
      int num;
      int freq[10]={0};
      printf("Child 1 generates: ");
      srand(time(NULL) ^ (getpid()<<16));
      for(int i=0;i<n;i++)
      {
       num = (rand() % (999 - 100 + 1)) + 100;
       printf("%d, ",num);
       while(num!=0){
            freq[num%10]++;
            num=num/10;}}
      printf("\n");
      printf("The frequency array for child 1 will be: \n");
      for(int i=0;i<10;i++)
              printf("%d ",freq[i]);
      printf("\n");
      write(a2p[1],freq,sizeof(int)*10);
      close(a2p[1]);
    exit(1);
    }

   if(fork()==0){
     int freq[10]={0};
     close(a2p[1]); close(a2p[0]); close(b2p[0]);
     int num2;
     printf("Child 2 generates: ");
     srand(time(NULL) ^ (getpid()<<16));
     for(int i=0;i<n;i++)
         {
          num2 = (rand()%900)+100;
                 printf("%d, ",num2);
             while(num2!=0){                                                 
             freq[num2%10]++;
                num2=num2/10;}}
     printf("\n");
     printf("The frequency array for child 2 will be: \n");
     for(int i=0;i<10;i++)
             printf("%d ",freq[i]);
     printf("\n");
    write(b2p[1],freq,sizeof(int)*10);
    close(b2p[1]);
    exit(1);
   }

    wait(0);
    wait(0);
    close(a2p[1]); close(b2p[1]);
    read(a2p[0],freq1,sizeof(int)*10);
    close(a2p[0]);
    read(b2p[0],freq2,sizeof(int)*10);
    close(b2p[0]);
    printf("The parent will print\n");
    for(int i=0;i<=9;i++)
            if(freq1[i]==freq2[i])
              printf("%d - Equal\n",i);
            else
               printf("%d - Child %d\n",i,maxim(freq1[i],freq2[i]));
    
    return 0;

}
                    printf("%d - Equal\n",i);
