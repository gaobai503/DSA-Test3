#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "link.h"
void PrintData(btree bt, stack S){
    if(!IsEmpty(bt)){
	printf("%d  ", Data(bt));
	return;
    }
}

void FreeBtree(btree bt, stack S){
    free(bt);
    return;
}


void StoreData(btree bt, stack S){
    Elem temp = {bt, 0};
    Push(S, temp);
    return;
}

int main(int argc, char* argv[]){
    elemtype dataset[9] = {1,0,3,4,0,0,5,0,0};
    btree bt = PreCreBtree(dataset, 9);
    printf("Complete Tree?: %d\n", IsComTree(bt));
    printf("Width: %d\n", BtreeWidth(bt));
    stack S1 = MakeNullStack();
    stack S2 = MakeNullStack();
    PostOrderRec(bt, S1, PrintData);
    printf("\n");
    PostOrderRec(bt, S1, StoreData);
    while(!EmptyStack(S1)) Push(S2, Pop(S1));

    LevelOrder(bt, S1, PrintData);
    printf("\n");

    /**/
    printf("%d", Data(Pop(S2).bt));
    while(!EmptyStack(S2)){
        printf("->");
        printf("%d", Data(Pop(S2).bt));
    }
    printf("\n");
    PostOrder(bt, S1, FreeBtree);
    return 0;
}
