#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

int v[10]={0};
typedef struct{
        int value;
        pthread_mutex_t m;
}data;

void* f(void *arg){

        data dt = *((data*)arg);
        int aux = dt.value;
        while(aux!=0){
                pthread_mutex_lock(&dt.m);
                v[aux%10]++;
                pthread_mutex_unlock(&dt.m);
                aux = aux/10;}
        return NULL;
}

int main(int argc,char *argv[]){
        int i;
        pthread_t * t = malloc(sizeof(pthread_t)*(argc-1));
        pthread_mutex_t m ;
        data *args = malloc(sizeof(data)*(argc-1));

        if(0>pthread_mutex_init(&m,NULL)){
                perror("Error creating the mutex");
                exit(1);}
        for(i=0;i<argc-1;i++){
                args[i].value=atoi(argv[i+1]);
                args[i].m = m;
                pthread_create(&t[i],NULL,f,(void*)&args[i]);}
        for (i = 0; i < argc - 1;i++) {
                if (0 > pthread_join(t[i], NULL)) {
                        perror("Error waiting for thread");
                         }
        }
        for(i=0;i<=9;i++)
                printf("the %d element frequency is %d \n",i,v[i]);

        pthread_mutex_destroy(&m);
        free(args);
        free(t);
        return 0;}
