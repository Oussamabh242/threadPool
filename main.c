#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<time.h>
#include "queue.h"

#define MAX_THREADS 5 

typedef struct {
  Queue *q ;
  int task; 
}thing ; 


pthread_mutex_t q_mutex ;  
void job(int *x){
  int val = *x ; 
  sleep(3) ; 
  printf("task powerd to 2 is : %d \n" , val * val) ; 
}

void *start_thread(void *args){
  Queue *q = ((Queue *)args) ;
  while(1){
    int task ;
    bool found = false  ; 
    pthread_mutex_lock(&q_mutex) ; 
    if(!q_empty(q)){
      task = q_pop(q) ;
      found = true ; 
    }
    pthread_mutex_unlock(&q_mutex) ; 
    if(!found){
      return NULL ; 
    }
    job(&task) ; 

  }
}



int main(int argc, char *argv[])
{
  pthread_t th[MAX_THREADS] ; 
  Queue *q = q_init() ;
  srand((time(NULL))) ; 
  for(int i= 0 ; i<10 ; i++){
    int task = rand()%10 ; 
    printf("enqueueing %d ...\n" ,task) ; 
    q_insert(task ,q) ; 
  } 
  for(int i = 0 ; i<MAX_THREADS ; i++){
    if(pthread_create(&th[i] ,NULL , start_thread ,(void *)q) !=0){
      perror("Thread Creation Faild \n") ; 
    }
  }
  for(int i = 0 ; i<MAX_THREADS ; i++){
    if(pthread_join(th[i] , NULL) != 0){
      perror("Faild to join the thread .. \n") ;
    }
  }
  pthread_mutex_init(&q_mutex,NULL) ;

  pthread_mutex_destroy(&q_mutex) ; 
  q_destroy(q) ; 

  return EXIT_SUCCESS;
}
