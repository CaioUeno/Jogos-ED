#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"


void NewStack(TypeStack *S){
    S->Top = -1;
}

void PushCard(TypeStack *S, TypeCard C){
    if(!Full(S)){
        S->Top++;
        S->Deck[S->Top] = C;
    } else {
        printf("Ta cheio \n");
    }
}

TypeCard PopCard(TypeStack *S){
    if(!Empty(S)){
        S->Top--;
        return S->Deck[S->Top + 1];
    } else {
        printf("Vazia\n");
    }
}

int Length(TypeStack *S){
    return S->Top + 1;
}

void ShowCard(TypeCard C){
  switch (C.Suit) {
    case 1:
        switch (C.Number) {
            case 1:
                printf("\33[1;30mA ♣\33[0m");
                break;
            case 11:
                printf("\33[1;30mJ ♣\33[0m");
                break;
            case 12:
                printf("\33[1;30mQ ♣\33[0m");
                break;
            case 13:
                printf("\33[1;30mK ♣\33[0m");
                break;
            default:
                printf("\33[1;30m%d ♣\33[0m", C.Number);
                break;
        }
        break;
    case 2:
        switch (C.Number) {
            case 1:
                printf("\33[1;31mA ♥\33[0m");
                break;
            case 11:
                printf("\33[1;31mJ ♥\33[0m");
                break;
            case 12:
                printf("\33[1;31mQ ♥\33[0m");
                break;
            case 13:
                printf("\33[1;31mK ♥\33[0m");
                break;
            default:
                printf("\33[1;31m%d ♥\33[0m", C.Number);
                break;
        }
        break;
    case 3:
        switch (C.Number) {
            case 1:
                printf("\33[1;30mA ♠\33[0m");
                break;
            case 11:
                printf("\33[1;30mJ ♠\33[0m");
                break;
            case 12:
                printf("\33[1;30mQ ♠\33[0m");
                break;
            case 13:
                printf("\33[1;30mK ♠\33[0m");
                break;
            default:
                printf("\33[1;30m%d ♠\n\33[0m", C.Number);
                break;
        }
        break;
    case 4:
        switch (C.Number) {
            case 1:
                printf("\33[1;31mA ♦\33[0m");
                break;
            case 11:
                printf("\33[1;31mJ ♦\33[0m");
                break;
            case 12:
                printf("\33[1;31mQ ♦\33[0m");
                break;
            case 13:
                printf("\33[1;31mK ♦\33[0m");
                break;
            default:
                printf("\33[1;31m%d ♦\33[0m", C.Number);
                break;

       }
       break;
  }
}

void ShowDeck(TypeStack *S){
    if(!Empty(S))
        for (int i = 0; i <= S->Top; i++)
            ShowCard(S->Deck[i]);
    else
        printf("Vazio\n");
}

TypeCard Top(TypeStack *S){
    return S->Deck[S->Top];
}

int Full(TypeStack *S){
    return S->Top == MAXTAM - 1;
}

int Empty(TypeStack *S){
    return S->Top == -1;
}
