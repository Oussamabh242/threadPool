#ifndef __QUEUE_H__ 
#define __QUEUE_H__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_STRING 100

typedef struct {
  int sender  ; 
  char buffer[MAX_STRING] ; 
}Val ; 

typedef struct QueueNode {
  struct QueueNode *next ;
  int val ;   
}QueueNode ; 



typedef struct Queue {
  struct QueueNode* head ; 
  struct QueueNode* tail ;
}Queue ; 

Queue *q_init() ;
void q_destroy(Queue *q) ; 
void q_insert(int v , Queue *q) ; 
int q_pop(Queue *q) ;
bool q_empty(Queue *q) ;


#endif // !Queue
