#ifndef STACK_H
#define STACK_H

#define MAXTAM 52

typedef struct TypeCard {
    int Number;
    int Suit;
}TypeCard;

typedef struct TypeStack {
    TypeCard Deck[MAXTAM];
    int Top;
}TypeStack;

void NewStack(TypeStack *S);
void PushCard(TypeStack *S, TypeCard C);
TypeCard PopCard(TypeStack *S);
int Length(TypeStack *S);
void ShowCard(TypeCard C);
void ShowDeck(TypeStack *S);
TypeCard Top(TypeStack *S);
int Full(TypeStack *S);
int Empty(TypeStack *S);

#endif
