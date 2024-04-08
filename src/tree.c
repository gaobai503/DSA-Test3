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

void PreOrderRec(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	visit(bt);
	PreOrderRec(Lchild(bt), visit);
	PreOrderRec(Rchild(bt), visit);
    }
}

void PreOrder(btree bt, void (*visit)(btree)){
    if(!bt){
	printf("btree given is illegal!\n");
	return;
    }
    stack S = MakeNullStack();
    visit(bt);
    Elem temp = {bt, 0};
    Push(S, temp);
    while(!EmptyStack(S)){
	if(!Topelement(S).flag){
	    temp = Pop(S);
	    temp.flag = 1;
	    Push(S, temp);
	    if(!IsEmpty(Lchild(Topelement(S).bt))){
		visit(Lchild(Topelement(S).bt));
		temp.bt = Lchild(Topelement(S).bt);
		temp.flag = 0;
		Push(S, temp);
	    }
	}
	else if(!IsEmpty(Rchild(Topelement(S).bt))){
	    visit(Rchild(Topelement(S).bt));
	    temp.bt = Rchild(Topelement(S).bt);
	    temp.flag = 0;
	    Pop(S);
	    Push(S, temp);
	}
	else {
	    Pop(S);
	}
    }
}

void InOrder(btree bt, void (*visit)(btree)){
    if(!bt){
	printf("btree given is illegal!\n");
	return;
    }
    stack S = MakeNullStack();
    Elem temp = {bt, 0};
    Push(S, temp);
    while(!EmptyStack(S)){
	if(!Topelement(S).flag){
	    if(!IsEmpty(Lchild(Topelement(S).bt))){
		temp = Pop(S);
		temp.flag = 1;
		Push(S, temp);
		temp.bt = Lchild(Topelement(S).bt);
		temp.flag = 0;
		Push(S, temp);
	    }
	    else{
		visit(Topelement(S).bt);
		if(!IsEmpty(Rchild(Topelement(S).bt))){
		    temp.bt = Rchild(Topelement(S).bt);
		    temp.flag = 0;
		    Pop(S);
		    Push(S, temp);
		}
		else Pop(S);
	    }
	}
	else{
	    visit(Topelement(S).bt);
	    if(!IsEmpty(Rchild(Topelement(S).bt))){
		temp.bt = Rchild(Topelement(S).bt);
		temp.flag = 0;
		Pop(S);
		Push(S, temp);
	    }
	    else Pop(S);
	}
    }
}

void InOrderRec(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	InOrderRec(Lchild(bt), visit);
	visit(bt);
	InOrderRec(Rchild(bt), visit);
    }
}

void PostOrder(btree bt, void (*visit)(btree)){
    if(!bt){
	printf("the btree given is illegal\n");
	return;
    }
    Elem temp = {bt, 0};
    stack S = MakeNullStack();
    Push(S, temp);
    while(!EmptyStack(S)){
	if(Topelement(S).flag<1){
	    temp = Pop(S);
	    temp.flag = 1;
	    Push(S, temp);
	    if(!IsEmpty(Lchild(Topelement(S).bt))){
		temp.bt = Lchild(Topelement(S).bt);
		temp.flag = 0;
		Push(S, temp);
	    }
	}
	else if(Topelement(S).flag<2){
	    temp = Pop(S);
	    temp.flag = 2;
	    Push(S, temp);
	    if(!IsEmpty(Rchild(Topelement(S).bt))){
		temp.bt = Rchild(Topelement(S).bt);
		temp.flag = 0;
		Push(S, temp);
	    }
	}
	else{
	    visit(Topelement(S).bt);
	    Pop(S);
	}
    }
}

void PostOrderRec(btree bt, void (*visit)(btree)){
    if(!IsEmpty(bt)){
	PostOrderRec(Lchild(bt), visit);
	PostOrderRec(Rchild(bt), visit);
	visit(bt);
    }
}

