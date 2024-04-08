#pragma once
#ifndef TREE_H
#define TREE_H

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

elemtype Data(btree bt);

btree EmptyBtree();
btree BtreeCreate(elemtype data, btree lchild, btree rchild);
btree PreCreBtree(elemtype *dataset, unsigned n);
btree Lchild(btree bt);
btree Rchild(btree bt);

void PreOrder(btree bt, void visit(btree));
void PreOrderRec(btree bt, void (*visit)(btree));
void InOrder(btree bt, void (*visit)(btree));
void InOrderRec(btree bt, void (*visit)(btree));
void PostOrder(btree bt, void (*visit)(btree));
void PostOrderRec(btree bt, void (*visit)(btree));

#endif //!TREE_H
