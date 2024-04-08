#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "tree.h"

const elemtype EmptyElem = 0;
const elemtype ErrorElem = -1;

int ElemCom(elemtype a, elemtype b){
    if(a > b) return 1;
    if(a < b) return -1;
    return 0;
}

int IsEmpty(btree bt){
    if(!bt){
	printf("btree given is illegal!\n");
	return -1;
    }
    if(!ElemCom(bt->node, EmptyElem)){
	if(!(bt->lchild || bt->rchild)) return 1;
    }
    return 0;
}

elemtype Data(btree bt){
    if(!bt){
	printf("btree given is illegal!\n");
	return ErrorElem;
    }
    return bt->node;
}

btree EmptyBtree(){
    btree bt = (btree)malloc(sizeof(struct BTREE));
    if(!bt){
	printf("No enough memory! Return Illegal btree\n");
	return NULL;
    }
    bt->node = EmptyElem;
    bt->lchild = NULL;
    bt->rchild = NULL;
    return bt;
}

btree BtreeCreate(elemtype data, btree lchild, btree rchild){
    btree bt = (btree)malloc(sizeof(struct BTREE));
    if(!bt){
	printf("No enough memory! Return Illegal btree\n");
	return NULL;
    }
    bt->node = data;
    bt->lchild = lchild;
    bt->rchild = rchild;
    return bt;
}

btree PreCreBtree(elemtype *dataset, unsigned n){
    stack S = MakeNullStack();
    Elem bt = {EmptyBtree(), 0};
    Elem temp = {EmptyBtree(), 0};
    for(int i=0; i<n; i++){
	if(!ElemCom(dataset[i], EmptyElem)){
	    bt = Pop(S);
	    if(!bt.flag){
		bt.flag=1;
		Push(S, bt);
	    }
	    else{
		while(Topelement(S).flag && !EmptyStack(S)){
		    temp = Pop(S);
		    temp.bt->rchild = bt.bt;
		    bt = temp;
		}
		if(!EmptyStack(S)){
		    temp = Pop(S);
		    temp.bt->lchild = bt.bt;
		    temp.flag = 1;
		    Push(S, temp);
		}
	    }
	}
	else{
	    bt.bt = BtreeCreate(dataset[i], EmptyBtree(), EmptyBtree());
	    bt.flag = 0;
	    Push(S, bt);
	}
	if(EmptyStack(S) && (i!=n-1)){
	    return EmptyBtree();
	}
    }
    return bt.bt;
}

btree Lchild(btree bt){
    if(!bt){
	printf("btree given is illegal!\n");
	return NULL;
    }
    return bt->lchild;
}

btree Rchild(btree bt){
    if(!bt){
	printf("btree given is illegal!\n");
	return NULL;
    }
    return bt->rchild;
}

void PreOrder(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	visit(bt);
	PreOrder(Lchild(bt), visit);
	PreOrder(Rchild(bt), visit);
    }
}

void InOrder(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	InOrder(Lchild(bt), visit);
	visit(bt);
	InOrder(Rchild(bt), visit);
    }
}

void PostOrder(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	PostOrder(Lchild(bt), visit);
	PostOrder(Rchild(bt), visit);
	visit(bt);
    }
}

