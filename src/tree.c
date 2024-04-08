#include <stdio.h>
#include <stdlib.h>
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

btree BtreeInit(){
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
