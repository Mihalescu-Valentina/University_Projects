#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct {
   int *v;
   int *s;
   int *id;
   pthread_mutex_t *m;

}data;


  void* f(void *arg){
          data dt = *((data*)arg);

          pthread_mutex_lock(dt.m);
          int var = dt.v[*(dt.id)];
          printf("%d \n",var);
          *dt.s=0;
          while(var>0){
                *(dt.s)=*(dt.s)+var%10;
                var = var/10;}
          printf("s is %d \n",*(dt.s));
          dt.v[*(dt.id)]=*(dt.s);
          pthread_mutex_unlock(dt.m);
   return NULL;

  }
  int main(int argc,char* argv[]){
         int n,i;
         printf("n is\n");
         scanf("%d",&n);
         int *v = (int*)malloc(sizeof(int)*n);
         data *args = (data*)malloc(sizeof(data)*n);
         for(i=0;i<n;i++){
                 printf("enter a number\n");
                 scanf("%d",&v[i]);
            }

         pthread_t* t = (pthread_t*)malloc(sizeof(pthread_t)*n);
         pthread_mutex_t *m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
         int *s = malloc(sizeof(int));
         int *id = malloc(sizeof(int));
         pthread_mutex_init(m,NULL);
         for(i=0;i<n;i++){
            args[i].v= v;
            args[i].s= s;
            args[i].m = m;
            args[i].id= &i;
            if(0>pthread_create(&t[i],NULL,f,(void*)&args[i])){
                    perror("Error creating thread\n");
                    exit(1);}
          }

          for(i=0;i<n;i++){
                  pthread_join(t[i],NULL);}

          pthread_mutex_destroy(m);
         for(i=0;i<n;i++)
                printf("the new vector is %d \n",v[i]);
           free(s);
           free(v);
           free(id);
           free(args);
           free(t);
           free(m);
         return 0;}
