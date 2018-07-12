#ifndef TREE_H
#define TREE_H

typedef struct TypeItem {
    int Pos;
    int Up;
    int Left;
    int Right;
    int Down;
}TypeItem;

typedef struct TypeNode {
    TypeItem Item;
    struct TypeNode *Left;
    struct TypeNode *Right;
}TypeNode;

typedef TypeNode *TypePointer;

typedef TypePointer TypeTree;

void NewTree(TypeTree *T);
void Insert(TypeTree *T, TypeItem I);
void Remove(TypeTree *T, TypeItem I);
TypeItem SearchByItem(TypeTree *T, TypeItem I);
int Empty(TypeTree *T);
TypeItem SearchByPos(TypeTree *T, int P);
void ShowTree(TypeTree *T);
void ClearTree(TypeTree *T);

#endif
