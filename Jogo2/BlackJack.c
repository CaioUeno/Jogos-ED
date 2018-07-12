#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BlackJack.h"
#include "Stack.h"

void Start(TypeStack *S){
    NewStack(S);
    PushEntireDeck(S);
    Shuffle(S);
}
void Shuffle(TypeStack *S){
    TypeCard Vec_aux[MAXTAM];
    TypeCard Card_aux;
    int pos, lim = Length(S); //lim é usado para quando acaba a pilha no meio do jogo
    srand(time(NULL));
    BootDeck(&Vec_aux[0]);
    for (int i = 0; i < lim; i++){
        do {
            pos = rand() % lim; //escolhe aleatoriamente uma posição
        } while(Vec_aux[pos].Number != 0);
            Vec_aux[pos] = PopCard(S); //Pop na pilha e insere no vetor auxiliar - aleatorio
    }
    for (int i = 0; i < lim; i++){
        PushCard(S, Vec_aux[i]); //Push nas cartas embaralhadas
    }
}

void PushEntireDeck(TypeStack *S){
    TypeCard C;
    for (int i = 0; i < MAXTAM/52; i++) { //Quantidade de baralhos
        for (int i = 1; i < 5; i++) { //naipes
            C.Suit = i;
            for (int j = 1; j < 14; j++) { //Cartas de A a K
                C.Number = j;
                PushCard(S, C);
            }
        }
    }
}

void Trash(TypeCard *D, TypeCard *C){ //Põe no lixo as cartas do jogador/Dealer
    int i = 0;
    while(D[i].Number != 0)
        i++;
    D[i] = *C;
}

void Bootvec(TypeCard *C){ //Coloca 0's na mão do jogador/Dealer
  for (int i = 0; i < 10; i++)
        C[i].Number = 0;
}


void PutOnTrash(TypeCard *C, TypeCard *D){
    int i = 0;
    while (C[i].Number != 0) { //Chama a função para por no lixo
        Trash(D,&C[i]);
        i++;
    }
    for (i = 0; i < 10; i++) // Coloca 0's na mão do jogador/Dealer
          C[i].Number = 0;
}

void BootDeck(TypeCard *C){ // Coloca 0's no lixo
    for (int i = 0; i < MAXTAM; i++)
        C[i].Number = 0;
}

void ShowHand(TypeCard *C){
    int i = 0;
    while (C[i].Number != 0) {
        ShowCard(C[i]);
        i++;
    }
    printf("\n");
}

void RebootDeck(TypeStack *S, TypeCard *C){ // Tira as cartas do lixo, põe a pilha e embaralha
    int i = 0;
    while (C[i].Number != 0) {
        PushCard(S,C[i]);
        C[i].Number = 0;
        i++;
    }
    Shuffle(S);
}

void Show(TypeCard *C){
    for (int i = 0; i < MAXTAM; i++)
        printf("%d \n", C[i].Number);
}

void ChooseOptions(TypeStack *S, TypeCard *C, TypeCard *A, int *B, int Cash, int O){
    switch (O) {
      case 1:
          if(Empty(S))
              RebootDeck(S,A);
          for (int i = 0; i < 10; i++) {
              if(C[i].Number == 0){
                  C[i] = PopCard(S);
                  break;
              }
          }
          break;
      case 3:
          if(*B + *B < Cash)
              *B = *B + *B;
          else
              printf("Você não pode dobrar a aposta!\n");
          break;
      case 4:
          printf("Desistiu!\n");
          break;
    }

}

void DealerChoice(TypeStack *S, TypeCard *C, TypeCard *D){ //Como o Dealer vai jogar
    int Sum = 0, i = 0;
    if(C[0].Number == 1 && C[1].Number > 10 || C[1].Number == 1 && C[0].Number > 10){
        if(C[2].Number == 0){
            return;
        }
    }
    do {
        if(C[i].Number > 10)
            Sum = Sum + 10;
        else
            Sum = Sum + C[i].Number;
        i++;
    } while(C[i].Number != 0);
    TypeCard A = Top(S);
    do {
      if(Sum + A.Number <= 21){
          if(Empty(S))
              RebootDeck(S,D);
            i = 0;
            while (C[i].Number != 0)
                i++;
            C[i] = PopCard(S);
            if(C[i].Number > 10)
                Sum = Sum + 10;
            else
                Sum = Sum + C[i].Number;
      }
      A = Top(S);
    } while(Sum + A.Number <= 21);
}

int CheckHand(TypeCard *P, TypeCard *D){ //Verifica se ganhou/perdeu/empatou
    int SumP = 0, SumD = 0, i = 0, FlagP = 0, FlagD = 0;
    if((P[0].Number == 1 && P[1].Number > 10) || (P[1].Number == 1 && P[0].Number > 10)){
        if(P[2].Number == 0){
            FlagP = 1;
            SumP = 21;
        }
    }
    if(D[0].Number == 1 && D[1].Number > 10 || D[1].Number == 1 && D[0].Number > 10){
        if(D[2].Number == 0){
            FlagD = 1;
            SumD = 21;
        }
    }
    while(P[i].Number != 0 && FlagP == 0) {
        if(P[i].Number > 10)
            SumP = SumP + 10;
        else
            SumP = SumP + P[i].Number;
        i++;
    }
    i = 0;
    while(D[i].Number != 0 && FlagD == 0) {
        if(D[i].Number > 10)
            SumD = SumD + 10;
        else
            SumD = SumD + D[i].Number;
        i++;
    }
    if(SumP > SumD && SumP <= 21){
        printf("Você ganhou a mão!\n");
        return 1;
    } else if(SumD > SumP || SumP > 21) {
        printf("Você perdeu a mão!\n");
    } else {
        printf("Empate!\n");
        return 3;
    }
    return 0;
}

void Game(TypeStack *S){
    TypeCard Vec_aux[MAXTAM];
    TypeCard Player[10], Dealer[10];
    int Options, Cash = 500, Beat, Answer;
    BootDeck(&Vec_aux[0]);
    Bootvec(&Player[0]);
    Bootvec(&Dealer[0]);
    Start(S);
    printf("\33[1;30mBlack\33[1;31mJack!\33[0m\n");
    printf("Seu dinheiro: %d\n", Cash);
    do {
        if(Empty(S))
            RebootDeck(S,&Vec_aux[0]);
        PutOnTrash(&Player[0],&Vec_aux[0]);
        PutOnTrash(&Dealer[0],&Vec_aux[0]);
        Options = 0;
        do {
            printf("Quanto você deseja apostar?\n");
            scanf("%d", &Beat);
        } while(Beat > Cash);
        printf("\e[H\e[2J");
        Player[0] = PopCard(S);
        Dealer[0] = PopCard(S);
        printf("Mão do Dealer:\n");
        ShowHand(&Dealer[0]);
        Player[1] = PopCard(S);
        Dealer[1] = PopCard(S);
        printf("Sua mão:\n");
        ShowHand(&Player[0]);
        printf("Sua aposta: %d\n", Beat);
        while(Options != 2 && Options != 4){
            printf("Escolha uma opção:\n");
            printf("1 - HIT\n");
            printf("2 - Parar\n");
            printf("3 - Dobrar aposta\n");
            printf("4 - Desistir\n");
            scanf("%d", &Options);
            printf("\e[H\e[2J");
            ChooseOptions(S,&Player[0],&Vec_aux[0],&Beat,Cash,Options);
            printf("Mão do Dealer:\n");
            ShowCard(Dealer[0]);
            printf("\n");
            printf("Sua mão:\n");
            ShowHand(&Player[0]);
            printf("Sua aposta: %d\n", Beat);
        }
            DealerChoice(S,&Dealer[0],&Vec_aux[0]);
            printf("\e[H\e[2J");
            if(Options == 2)
                switch (CheckHand(&Player[0],&Dealer[0])) {
                  case 1:
                          Cash = Cash + Beat + Beat;
                  case 0:
                      Cash -= Beat;
                }
            else {
                Cash -= Beat;
                printf("Você Desistiu!\n");
            }
            printf("Mão do Dealer:\n");
            ShowHand(&Dealer[0]);
            printf("Sua mão:\n");
            ShowHand(&Player[0]);
            printf("Seu Saldo: %d\n", Cash);
            printf("Jogar novamente? 0 - n / 1 - Y\n");
            scanf("%d", &Answer);
    } while(Answer == 1 && Cash > 0);
    if (Cash <= 0) {
        printf("Acabou seu dinheiro! ¯\\_(ツ)_/¯\n");
    }


}
