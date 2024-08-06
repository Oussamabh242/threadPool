#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <poll.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"


char* read_file(const char* filename){
  FILE *fp ;
  fp = fopen(filename , "r") ;
  if(fp == NULL){
    perror("error") ; 
    return NULL ; 
  }
  fseek(fp ,0 ,SEEK_END) ; 
  long filesize = ftell(fp) ; 
  fseek(fp,0,SEEK_SET) ;

  char *content = malloc(filesize +1) ; 
  if(content == NULL){
    perror("Error allocating memory") ; 
    fclose(fp) ; 
    return NULL ; 
  }
  size_t bytes_read = fread(content ,1 ,filesize,fp) ;
  if(bytes_read != filesize){
    perror("Error reading file") ; 
    free(content) ;
    fclose(fp) ; 
    return NULL ;
  }
  content[filesize]='\0' ;
  fclose(fp) ; 
  return content ; 
}



#define MAX_MESSAGE_LENGTH 100
#define MAX_FILE_LENGTH 1000000
typedef struct {
  char content[MAX_MESSAGE_LENGTH] ; 
  int sender ; 
}message ; 

void handle_connection(int client_fd){
  char buffer[MAX_MESSAGE_LENGTH] ; 
  ssize_t bytes_recived ;  

    memset(buffer ,0 ,sizeof(buffer))  ;
    bytes_recived = recv(client_fd ,buffer ,sizeof buffer ,0) ;

    message m ; 
    m.sender = client_fd ; 
    strncpy(m.content , buffer ,MAX_MESSAGE_LENGTH -1) ; 
    m.content[MAX_MESSAGE_LENGTH -1] = '\0' ; 
    printf("Recived %s from client with id : %d \n" , m.content , m.sender) ; 
    char *content = read_file(m.content) ;
    if(content == NULL){
      send(client_fd ,"Error reading file or file does not exist" , 150 , 0) ;
    }
    else{
      sleep(2) ;
      
      if(send(client_fd,content,strlen(content),0) == -1 ){
        perror("error reciveing the Client's Message .") ; 
        free(content);  
      }
  }

  close(client_fd) ; 
  printf("Connection Closed \n") ; 
  
}


//////////////////////// THREAD POOOL //////////////////////////////////
pthread_mutex_t q_mutex ;  
pthread_cond_t q_cond ; 

typedef struct {
  Queue *q ;
  int task; 
}thing ; 



void job(Val v){
  Val *x = malloc(sizeof(Val)) ;
  strncpy(x->buffer , v.buffer , 100) ; 
  x->sender = v.sender ; 
  sleep(3) ; 
  printf("yes i Just recived %s  from user number %d\n" , x->buffer , x->sender) ; 
  free(x) ; 
}

void submitTask(int client , Queue *q){
  pthread_mutex_lock(&q_mutex) ; 
  q_insert(client , q) ;
  pthread_mutex_unlock(&q_mutex); 
  pthread_cond_signal(&q_cond) ; 
}

void *start_thread(void *args){
  Queue *q = ((Queue *)args) ;
  while(1){
    int client ; 
    bool found = false  ; 
    pthread_mutex_lock(&q_mutex) ;
    while(q_empty(q)){
      pthread_cond_wait(&q_cond ,&q_mutex) ; 
    }
    client = q_pop(q) ;
    found = true ; 
    pthread_mutex_unlock(&q_mutex) ;
    handle_connection(client) ;  
  }
}


int main(int argc, char *argv[]) {
  const int MAX_THREADS = atoi(argv[1]) ;   
  pthread_mutex_init(&q_mutex,NULL) ;
  pthread_cond_init(&q_cond ,NULL) ; 
  pthread_t th[MAX_THREADS] ; 
  Queue *q = q_init() ;
  for(int i = 0 ; i<MAX_THREADS ; i++){
    if(pthread_create(&th[i] ,NULL , start_thread ,(void *)q) !=0){
      perror("Thread Creation Faild \n") ; 
    }
   }
  struct sockaddr_in client, server;
  int lfd, n, client_fd;
  char r_buff[100] = "", s_buff[100] = "";

  lfd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(65432);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(lfd, (struct sockaddr *)&server, sizeof server);
  listen(lfd, 100);

  n = sizeof client;

  while(1){
    printf("waiting for connections\n") ; 
    client_fd = accept(lfd ,(struct sockaddr*)&client ,(socklen_t *)&n) ;
    submitTask(client_fd , q) ; 
  }

  close(client_fd);
  close(lfd);




  
  
  //stating the threads  

  for(int i = 0 ; i<MAX_THREADS ; i++){
      if(pthread_join(th[i] , NULL) != 0){
        perror("Faild to join the thread .. \n") ;
      }
    }
  



  pthread_mutex_destroy(&q_mutex) ; 
  pthread_cond_destroy(&q_cond) ; 
  q_destroy(q) ; 

  return 0;
}
