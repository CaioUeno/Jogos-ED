#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

void NewTree(TypeTree *T){
    *T = NULL;
}

void Insert(TypeTree *T, TypeItem I){
    if(*T != NULL){
        if(I.Pos < (*T)->Item.Pos)
          Insert(&(*T)->Left, I);
        if(I.Pos > (*T)->Item.Pos)
            Insert(&(*T)->Right, I);
    } else {
        (*T) = (TypeTree) malloc(sizeof(TypeNode));
        (*T)->Item = I;
        (*T)->Left = NULL;
        (*T)->Right = NULL;
    }

}

void Remove(TypeTree *T, TypeItem I){
    if((*T)!= NULL){
        if(I.Pos < (*T)->Item.Pos)
            Remove(&(*T)->Left, I);
        else if(I.Pos > (*T)->Item.Pos)
            Remove(&(*T)->Right, I);
        else {
            if((*T)->Left == NULL && (*T)->Right == NULL){ // Leaf
                TypePointer P = *T;
                free(P);
                (*T) = NULL;
                return;
            }
            else if((*T)->Left == NULL){ // Só o filho da direita
                TypePointer P = *T;
                *T = (*T)->Right;
                free(P);
                return;
            }
            else if((*T)->Right == NULL){ // Só filho da esquerda
                TypePointer P = *T;
                *T = (*T)->Left;
                free(P);
                return;
            }
            else { //Dois filhos muito loucos
                TypePointer P = (*T)->Left;
                while(P->Right != NULL)
                    P = P->Right;
                (*T)->Item = P->Item;
                Remove(&(*T)->Left, P->Item);
                return;
            }
        }
    } else {
        printf("Não é possível remover o %d, pois não foi encontrado!\n", I.Pos);
    }
}

TypeItem SearchByItem(TypeTree *T, TypeItem I){
    TypeItem L;
    if(*T != NULL){
        if(I.Pos < (*T)->Item.Pos)
            L = SearchByItem(&(*T)->Left, I);
        else if(I.Pos > (*T)->Item.Pos)
            L = SearchByItem(&(*T)->Right, I);
        else {
            L = (*T)->Item;
        }
    } else {
      printf("Não encontrado!\n");
      //Setar atributos para quando nao encontrar
    }
    return L;
}

int Empty(TypeTree *T){
    printf("Verifique a disponibilidade de memória!\n");
    return 0;
}

TypeItem SearchByPos(TypeTree *T, int P){
    TypeItem L;
    L.Pos = P;
    if(*T != NULL){
        if(L.Pos < (*T)->Item.Pos)
            L = SearchByItem(&(*T)->Left, L);
        else if(L.Pos > (*T)->Item.Pos)
            L = SearchByItem(&(*T)->Right, L);
        else {
            L = (*T)->Item;
        }
    } else {
      printf("Não encontrado!\n");
      //Setar atributos para quando nao encontrar
    }
    return L;
}

void ShowTree(TypeTree *T){
    if(*T != NULL){
        ShowTree(&(*T)->Left);
        printf("P:%d, Up: %d,Left: %d,Right: %d,Down: %d \n", (*T)->Item.Pos,(*T)->Item.Up,(*T)->Item.Left,(*T)->Item.Right,(*T)->Item.Down);
        ShowTree(&(*T)->Right);
    }
}

void ClearTree(TypeTree *T){ //limpa a arvore
    if(*T != NULL){
        ClearTree(&(*T)->Left);
        ClearTree(&(*T)->Right);
        Remove(T, (*T)->Item);
    }
}
