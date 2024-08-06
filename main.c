#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<time.h>
#include "queue.h"

#define MAX_THREADS 1 
pthread_mutex_t q_mutex ;  
pthread_cond_t q_cond ; 

typedef struct {
  Queue *q ;
  int task; 
}thing ; 



void job(int *x){
  int val = *x ; 
  sleep(3) ; 
  printf("task powerd to 2 is : %d \n" , val * val) ; 
}

void submitTask(int task , Queue *q){
  pthread_mutex_lock(&q_mutex) ; 
  q_insert(task , q) ; 
  pthread_mutex_unlock(&q_mutex); 
  pthread_cond_signal(&q_cond) ; 
}

void *start_thread(void *args){
  Queue *q = ((Queue *)args) ;
  while(1){
    int task ;
    bool found = false  ; 
    pthread_mutex_lock(&q_mutex) ;
    while(q_empty(q)){
      pthread_cond_wait(&q_cond ,&q_mutex) ; 
    }
    task = q_pop(q) ;
    found = true ; 
    pthread_mutex_unlock(&q_mutex) ; 
    job(&task) ; 
         
  }
}



int main(int argc, char *argv[])
{
  pthread_mutex_init(&q_mutex,NULL) ;
  pthread_cond_init(&q_cond ,NULL) ; 
  pthread_t th[MAX_THREADS] ; 
  Queue *q = q_init() ;
  /*srand((time(NULL))) ; */
  /*for(int i= 0 ; i<10 ; i++){*/
  /*  int task = rand()%10 ; */
  /*  printf("enqueueing %d ...\n" ,task) ; */
  /*  submitTask(task ,q) ; */
  /*} */
  /*for(int i = 0 ; i<MAX_THREADS ; i++){*/
  /*  if(pthread_create(&th[i] ,NULL , start_thread ,(void *)q) !=0){*/
  /*    perror("Thread Creation Faild \n") ; */
  /*  }*/
  /*}*/
  /*for(int i = 0 ; i<MAX_THREADS ; i++){*/
  /*  if(pthread_join(th[i] , NULL) != 0){*/
  /*    perror("Faild to join the thread .. \n") ;*/
  /*  }*/
  /*}*/
  /*submitTask(11 , q) ; */
  for(int i = 0 ; i<argc ; i++){
    printf("%s\n" , argv[i]) ; 
  } 
  for(int i = 0 ; i<MAX_THREADS ; i++){
    if(pthread_create(&th[i] ,NULL , start_thread ,(void *)q) !=0){
      perror("Thread Creation Faild \n") ; 
    }
  }
  
  for( ; ; ){
    int x ; 
    scanf("%d" , &x) ; 
    submitTask(x , q) ; 
  }


  for(int i = 0 ; i<MAX_THREADS ; i++){
      if(pthread_join(th[i] , NULL) != 0){
        perror("Faild to join the thread .. \n") ;
      }
    }
  



  pthread_mutex_destroy(&q_mutex) ; 
  pthread_cond_destroy(&q_cond) ; 
  q_destroy(q) ; 

  return EXIT_SUCCESS;
}
