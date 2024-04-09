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

void PreOrderRec(btree bt, stack S, void visit(btree, stack)){
    if(!IsEmpty(bt)){
	visit(bt, S);
	PreOrderRec(Lchild(bt), S, visit);
	PreOrderRec(Rchild(bt), S, visit);
    }
}

void PreOrder(btree bt, stack S, void visit(btree, stack)){
    if(!bt){
	printf("btree given is illegal!\n");
	return;
    }
    stack Stemp = MakeNullStack();
    visit(bt, S);
    Elem temp = {bt, 0};
    Push(Stemp, temp);
    while(!EmptyStack(Stemp)){
	if(!Topelement(Stemp).flag){
	    temp = Pop(Stemp);
	    temp.flag = 1;
	    Push(Stemp, temp);
	    if(!IsEmpty(Lchild(Topelement(Stemp).bt))){
		visit(Lchild(Topelement(Stemp).bt), S);
		temp.bt = Lchild(Topelement(Stemp).bt);
		temp.flag = 0;
		Push(Stemp, temp);
	    }
	}
	else if(!IsEmpty(Rchild(Topelement(Stemp).bt))){
	    visit(Rchild(Topelement(Stemp).bt), S);
	    temp.bt = Rchild(Topelement(Stemp).bt);
	    temp.flag = 0;
	    Pop(Stemp);
	    Push(Stemp, temp);
	}
	else {
	    Pop(Stemp);
	}
    }
}

void InOrder(btree bt, stack S, void visit(btree, stack)){
    if(!bt){
	printf("btree given is illegal!\n");
	return;
    }
    stack Stemp = MakeNullStack();
    Elem temp = {bt, 0};
    Push(Stemp, temp);
    while(!EmptyStack(Stemp)){
	if(!Topelement(Stemp).flag){
	    if(!IsEmpty(Lchild(Topelement(Stemp).bt))){
		temp = Pop(Stemp);
		temp.flag = 1;
		Push(Stemp, temp);
		temp.bt = Lchild(Topelement(Stemp).bt);
		temp.flag = 0;
		Push(Stemp, temp);
	    }
	    else{
		visit(Topelement(Stemp).bt, S);
		if(!IsEmpty(Rchild(Topelement(Stemp).bt))){
		    temp.bt = Rchild(Topelement(Stemp).bt);
		    temp.flag = 0;
		    Pop(Stemp);
		    Push(Stemp, temp);
		}
		else Pop(Stemp);
	    }
	}
	else{
	    visit(Topelement(Stemp).bt, S);
	    if(!IsEmpty(Rchild(Topelement(Stemp).bt))){
		temp.bt = Rchild(Topelement(Stemp).bt);
		temp.flag = 0;
		Pop(Stemp);
		Push(Stemp, temp);
	    }
	    else Pop(Stemp);
	}
    }
}

void InOrderRec(btree bt, stack S, void visit(btree, stack)){
    if(!IsEmpty(bt)){
	InOrderRec(Lchild(bt), S, visit);
	visit(bt, S);
	InOrderRec(Rchild(bt), S, visit);
    }
}

void PostOrder(btree bt, stack S, void visit(btree, stack)){
    if(!bt){
	printf("the btree given is illegal\n");
	return;
    }
    Elem temp = {bt, 0};
    stack Stemp = MakeNullStack();
    Push(Stemp, temp);
    while(!EmptyStack(Stemp)){
	if(Topelement(Stemp).flag<1){
	    temp = Pop(Stemp);
	    temp.flag = 1;
	    Push(Stemp, temp);
	    if(!IsEmpty(Lchild(Topelement(Stemp).bt))){
		temp.bt = Lchild(Topelement(Stemp).bt);
		temp.flag = 0;
		Push(Stemp, temp);
	    }
	}
	else if(Topelement(Stemp).flag<2){
	    temp = Pop(Stemp);
	    temp.flag = 2;
	    Push(Stemp, temp);
	    if(!IsEmpty(Rchild(Topelement(Stemp).bt))){
		temp.bt = Rchild(Topelement(Stemp).bt);
		temp.flag = 0;
		Push(Stemp, temp);
	    }
	}
	else{
	    visit(Topelement(Stemp).bt, S);
	    Pop(Stemp);
	}
    }
}

void PostOrderRec(btree bt, stack S, void visit(btree, stack)){
    if(!IsEmpty(bt)){
	PostOrderRec(Lchild(bt), S, visit);
	PostOrderRec(Rchild(bt), S, visit);
	visit(bt, S);
    }
}

