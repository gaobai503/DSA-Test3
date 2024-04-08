#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
void PrintData(btree bt){
    if(!IsEmpty(bt)){
	printf("%d->", Data(bt));
	return;
    }
}

void FreeBtree(btree bt){
    free(bt);
    return;
}

int main(int argc, char* argv[]){
    elemtype dataset[21] = {1,2,4,6,0,0,7,0,0,5,8,0,0,0,3,9,0,0,10,0,0};
    btree bt = PreCreBtree(dataset, 21);
    PreOrder(bt, PrintData);
    printf("\n");
    InOrder(bt, PrintData);
    printf("\n");
    PostOrder(bt, PrintData);
    PostOrder(bt, FreeBtree);
    return 0;
}
