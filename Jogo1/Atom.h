#ifndef ATOM_H
#define ATOM_H

typedef struct TypeItem {
    int AtomicN;
    //char Name[3];
} TypeItem;

typedef struct TypeNode *TypePointer;

typedef struct TypeNode {
    int Position;
    TypeItem Element;
    struct TypeNode *Next;
    struct TypeNode *Prev;
} TypeNode;

typedef struct TypeList {
    TypePointer First;
    int Quant;
    int Points;
} TypeList;

void Build(TypeList *L);
void Insert(TypeList *L, TypeItem I, int Position);
void Remove(TypeList *L, int Position);
void SeekPlus(TypeList *L);
TypePointer SeekPosition(TypeList *L, int Position);
void Fusion(TypeList *L, int Position);
void CorrectPos(TypeList *L);
void Show(TypeList *L);
int Full(TypeList *L);
void End(TypeList *L);
void NameElement(int AN);
TypeItem GenerateElement(TypeList *L, int I);
void BeginList(TypeList *L);
void RemoveOldELements(TypeList *L);
int Win(TypeList *L);
void Game(TypeList *L);
#endif
