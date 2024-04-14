#pragma once
#ifndef TREE_H
#define TREE_H

#include "link.h"

typedef struct LINK *link;
typedef link stack;

typedef int elemtype; 
extern const elemtype EmptyElem;
extern const elemtype ErrorElem;

struct BTREE{
    struct BTREE *lchild;
    struct BTREE *rchild;
    elemtype node;
};
typedef struct BTREE *btree;

int ElemCom(elemtype a, elemtype b);

int IsEmpty(btree bt);
int IsComTree(btree bt);

unsigned BtreeWidth(btree bt);

elemtype Data(btree bt);

btree EmptyBtree();
btree BtreeCreate(elemtype data, btree lchild, btree rchild);
btree PreCreBtree(elemtype *dataset, unsigned n);
btree Lchild(btree bt);
btree Rchild(btree bt);

void PreOrder(btree bt, stack S, void visit(btree, stack));
void PreOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void InOrder(btree bt, stack S, void (*visit)(btree, stack));
void InOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void PostOrder(btree bt, stack S, void (*visit)(btree, stack));
void PostOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void LevelOrder(btree bt, stack S, void (*visit)(btree, stack));

#endif //!TREE_H
