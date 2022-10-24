#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>


int buffer[100]={0};
int var=0;


typedef struct {
        pthread_barrier_t* barrier;
        pthread_rwlock_t*  rw;
        int buffer[100];
        int s;

}data;

void* fp(void *arg){
        printf("Function for producer thread\n");
        data argc = *((data*)arg);

        pthread_barrier_wait(argc.barrier);
                pthread_rwlock_wrlock(argc.rw);
                for(int l=0;l<3;l++){
                        buffer[l]+=l;
                        var=var+10;

                }
                pthread_rwlock_unlock(argc.rw);

        return NULL;
}

void* fc( void *arg){
        printf("Function for consumer thread\n");
        data argc = *((data*)arg);

                 pthread_rwlock_rdlock(argc.rw);
                 for(int l=0;l<3;l++){
                        argc.s=argc.s+buffer[l];
                         var-= 1;


        }
                pthread_rwlock_unlock(argc.rw);

        return NULL;}


        int main(int argc,char *argv[]){
                int n= atoi(argv[1]);
                int m= atoi(argv[2]);
                pthread_t* th = (pthread_t*)malloc(sizeof(pthread_t)*(n+m));
                data *args = (data*)malloc(sizeof(data)*(n+m));
                pthread_barrier_t* b;
                pthread_rwlock_t* rw;
                 b = (pthread_barrier_t*)malloc(sizeof(pthread_barrier_t));
                 rw = (pthread_rwlock_t*)malloc(sizeof(pthread_rwlock_t));
                pthread_barrier_init(b,NULL,n);
                pthread_rwlock_init (rw,NULL);


                if(argc!=3){
                        perror("You need 3 arguments\n");
                        exit(1);
                }

                int i;
                for(i=0;i<n;i++){
                        args[i].barrier =b;
                        args[i].rw = rw;
                        args[i].s=0;
                        if(0>pthread_create(&th[i],NULL,fp,(void*)&args[i])){
                                perror("Error creating the producer threads\n");
                                exit(1);}}
                for(i=n;i<m+n;i++){
                        args[i].barrier =b;
                        args[i].rw = rw;
                        args[i].s= 0;
                        if(0>pthread_create(&th[i],NULL,fc,(void*)&args[i])){
                                perror("Error creating the consumer threads\n");
                                exit(1);}

                }

                for(i=0;i<n+m;i++)
                        pthread_join(th[i],NULL);
                pthread_barrier_destroy(b);
                pthread_rwlock_destroy(rw);
                printf("var is %d\n",var);

                free(args);
                free(b);
                free(rw);
                free(th);
                return 0;}
