#ifndef BLACKBLACK_H
#define BLACKJACK_H
#include "Stack.h"

void Start(TypeStack *S);
void Shuffle(TypeStack *S);
void PushEntireDeck(TypeStack *S);
void Bootvec(TypeCard *C, TypeCard *D);
void ShowHand(TypeCard *C, TypeCard *D);
void BootDeck(TypeCard *C);
void RebootDeck(TypeStack *S, TypeCard *C);
void DealerChoice(TypeStack *S, TypeCard *C);
void ChooseOptions(TypeStack *S, TypeCard *C, TypeCard *D, int *B,int Cash, int O);
void Game(TypeStack *S);

#endif
