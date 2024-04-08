#include <stdio.h>
#include "tree.h"
int main(int argc, char* argv[]){
    btree bt = BtreeInit();
    if(IsEmpty(bt)){
	printf("The btree \"bt\" is empty\n");
    }
    else{
	printf("The btree \"bt\" is %d\n", Data(bt));
    }
    btree nt = BtreeCreate(5, BtreeInit(), BtreeInit());
    if(IsEmpty(nt)){
	printf("The btree \"nt\" is empty\n");
    }
    else{
	printf("The btree \"nt\" is %d\n", Data(nt));
    }
    return 0;
}
