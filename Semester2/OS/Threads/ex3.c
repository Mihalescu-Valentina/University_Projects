#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//se citesc stringuri de la tastatura pana la scrierea lui x; sa se creeze n/2 threaduri unde n este numarul de stringuri citite iar fiecare thread(i) sa retina stringurile de pe pozitiile i si i+1 contopite iar vocalele sa se transforme in cifra 1 iar la final sa se adauge nr de conoane din cuvantul nou format


int main(int argc, char *argv[]){
        /* char strings[100][20];
        //strings = (char**)malloc(sizeof(char*)*10);
        int i=0,ok=0;
        scanf("%s",strings[0]);
        while(ok==0){
        if(strcmp(strings[i],"x")==0)
        ok=1;
        i++;
        scanf("%s",strings[i]);
        }*/

        int n=atoi(argv[1]);
        char read [n][20];
        for(int i=0;i<n;i++)
                scanf("%s",read[i]);
        int i;
        int m=n/2;
        pthread_t t[m];
        for(i=0;i<n/2;i++)
                pthread_create(&t[i],NULL,f,(void*)args*)


        return 0;}
