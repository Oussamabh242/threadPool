#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

#include "queue.h" 

Queue *q_init(){
  Queue *q = malloc(sizeof(Queue)) ; 
  q->head = NULL ;
  q->tail = NULL ; 
  return q ; 
}

void q_destroy(Queue *q){
  if(q != NULL){
    free(q) ; 
  }
}

bool q_empty(Queue *q){
  if(q->tail == NULL && q->head == NULL){
    return true; 
  }
  return false ;
}

void q_insert(int client_fd , Queue *q) {
  /*struct QueueNode *node = malloc(sizeof(QueueNode)) ;*/
  /*printf("sender : %d\n" , val.sender) ; */
  /*strncpy(node->val.buffer ,val.buffer ,MAX_STRING-1) ; */
  /*node->val.buffer[MAX_STRING-1]= '\0' ;*/
  /*node->val.sender = val.sender; */
  QueueNode *node = malloc(sizeof(QueueNode)) ; 
  node->next = NULL ;
  node->val = client_fd ;  


  if(q_empty(q)){
    q->head = node ; 
    q->tail = node ;
    return ;
  }
  else {
    q->tail->next = node ; 
    q->tail = node ; 
    return ;
  }
   
}

int q_pop(Queue *q){
  int v = q->head->val; 
  QueueNode *node_to_remove = q->head ; 
  q->head = q->head->next ; 
  if(q->head == NULL){
    q->tail = NULL ; 
  } 
  free(node_to_remove) ; 
  return v; 

}

/*int q_pop(Queue *q){*/
/*  int nodeInt; */
/*  nodeInt = q->head->val ;*/
/*  struct QueueNode* hhead = q->head ; */
/*  q->head = q->head->next ; */
/*  if (q->head == NULL) {*/
/*    q->tail = NULL;*/
/*  }*/
/*  free(hhead) ; */
/*  return nodeInt ; */
/*}*/

void print(Queue *q){
  QueueNode *temp = q->head ; 
  while(temp !=NULL){
    printf("%i | " , temp->val) ;
    temp = temp->next ; 
  }
  printf("\n") ; 
}
