#include "BinaryTree.h"

int main(){
    BiTNode T;
    BiTree t = &T;
    CreateBiTree(&t);
    puts("");
    PreOrderTraverse(t, PrintElement);
    puts("");
    LevelOrderTraverse(t, PrintElement);
    puts("");
    printf("%d\n", BiTreeDepth(t));
}
