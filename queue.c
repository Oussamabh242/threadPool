#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

void q_insert(int val , Queue *q) {
  struct QueueNode *node = malloc(sizeof(QueueNode)) ; 
  node->val = val ; 
  node->next = NULL ;
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
  int nodeInt; 
  nodeInt = q->head->val ;
  struct QueueNode* hhead = q->head ; 
  q->head = q->head->next ; 
  if (q->head == NULL) {
    q->tail = NULL;
  }
  free(hhead) ; 
  return nodeInt ; 
}

void print(Queue *q){
  QueueNode *temp = q->head ; 
  while(temp !=NULL){
    printf("%d | " , temp->val) ;
    temp = temp->next ; 
  }
}
