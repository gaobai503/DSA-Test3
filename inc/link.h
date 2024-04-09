#pragma once
#ifndef LINK_H
#define LINK_H

#include "tree.h"

typedef struct BTREE *btree;
typedef struct{
    btree bt;
    int flag;
}Elem;

extern const Elem EmptyTemp;

struct LINK{
    Elem x;
    struct LINK *next;
};

typedef struct LINK *link;
typedef link stack;
struct QUEUE{
    link front;
    link rear;
};
typedef struct QUEUE *queue;
typedef link position;
typedef char bool;

link MakeNull();
void Insert(position p, Elem x);
void Delete(position p);
bool IsEOL(position p);
position Next(link L, position p);
position Previous(link L, position p);
position First(link L);
position End(link L);
Elem Retrieve(position p);

queue MakeNullQueue(void);
void EnQueue(Elem x, queue Q);
void DeQueue(queue Q);
bool EmptyQueue(queue Q);
Elem Front(queue Q);

stack MakeNullStack(void);
void Push(stack S, Elem x);
Elem Pop(stack S);
Elem Topelement(stack S);
bool EmptyStack(stack S);

#endif //!LINK_H
