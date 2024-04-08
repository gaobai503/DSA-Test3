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

btree BtreeInit();
btree BtreeCreate(elemtype data, btree lchild, btree rchild);
btree Lchild(btree bt);
btree Rchild(btree bt);



#endif //!TREE_H
