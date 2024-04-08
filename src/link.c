#include <stdlib.h>
#include <stdio.h>
#include "link.h"
#include "tree.h"

const Elem EmptyTemp = {NULL, 0};

/* 返回一个空链表*/
link MakeNull(){
    link L = (link)malloc(sizeof(struct LINK));
    if(L == NULL){
	printf("No enough memory\n");
	return L;
    }
    L->x.bt = EmptyBtree();
    L->x.flag = 0;
    L->next = NULL;
    return L;
}

/* 
 *传入一个逻辑位置与一个元素，使这个新元素在表中成为新的该逻辑位置
 *逻辑位置包括First(L)~End(L)+EOL(Next(END(L)))
 *EOL表示在链表的末尾插入
 * */
void Insert(position p, Elem x){
    position q = NULL;
    q = (link)malloc(sizeof(struct LINK));
    q->next = p->next;
    q->x = x;
    p->next = q;
}

/*
 *传入一个逻辑位置，删除该逻辑位置的元素;
 *合理的逻辑位置包括First(L)~End(L);
 * */
void Delete(position p){
    if(IsEOL(p)) 
	/* 不是合理的逻辑位置(EOL)*/
	return;
    position q = p->next;
    p->next = p->next->next;
    free(q);
}

/* 判断一个位置是否是EOL,
 * 是返回1, 否返回0;
 * 主要用于表的遍历
 * */
bool IsEOL(position p){
    if(!p->next) return 1;
    return 0;
}

/* 对于给出位置，给出其前趋位置
 * 如果给出了EOL或是First(L)返回NULL
 * */
position Previous(link L, position p){
    position q = First(L);
    if(p == q) 
	/* 无前趋元素 */
	return NULL;
    while(!IsEOL(q)){
	if(Next(L, q) == p){
	    return q;
	}
	q = Next(L, q);
    }
    /* 到达了EOL */
    return NULL;
}

position Next(link L, position p){
    if(!p) return L;
    return p->next;
    /* if(p == EOL) return NULL;*/
}

position First(link L){
    return L;
}

position End(link L){
    position p = L;
    if(!p->next)
    {
	/*Empty link*/
	return NULL;
    }
    while(p->next->next) p=p->next;
    return p;
}

/* 对于给出的位置，返回该位置对应的元素 */
Elem Retrieve(position p){
    if(!IsEOL(p)) return p->next->x;
    /* 非法位置 */
    return EmptyTemp;
}

queue MakeNullQueue(void){
    link L = MakeNull();
    queue Q = (queue)malloc(sizeof(link)*2);
    Q->front = L;
    Q->rear = NULL;
    return Q;
}

void EnQueue(Elem x, queue Q){
    if(!Q->rear){
	Insert(Q->front, x);
	Q->rear = Q->front;
	return;
    }
    Insert(Next(Q->front, Q->rear), x);
    Q->rear = Next(Q->front, Q->rear);
    return;
}

void DeQueue(queue Q){
    if(EmptyQueue(Q)) return;
    Delete(Q->front);
    if(Q->rear == Q->front){
	Q->rear = NULL;
	return;
    }
    Q->rear = End(Q->front);
    return;
}

bool EmptyQueue(queue Q){
    if(!Q->rear) return 1;
    return 0;
}

Elem Front(queue Q){
    return Retrieve(Q->front);
}

stack MakeNullStack(){
    stack S = (stack)malloc(sizeof(struct LINK));
    if(S == NULL){
	printf("No enough memory\n");
	return S;
    }
    S->next = NULL;
    return S;
}

void Push(stack S, Elem x){
    Insert(S, x);
}

Elem Pop(stack S){
    Elem temp = Retrieve(S);
    Delete(S);
    return temp;
}

Elem Topelement(stack S){
    return Retrieve(S);
}

bool EmptyStack(stack S){
    if(End(S) == NULL) return 1;
    return 0;
}
