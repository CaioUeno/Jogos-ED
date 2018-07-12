#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Atom.h"

void Build(TypeList *L){
    L->First = NULL;
    L->Quant = 0;
    L->Points = 0;
}

void Insert(TypeList *L, TypeItem I, int Position){
    TypePointer P;

    P = (TypePointer) malloc(sizeof(TypeNode));
    if(P == NULL){ //Tratar se não houver memória no pc(que pc lixo nao roda esse game?)
        printf("Não há memória para rodar esse jogo. Finalizando...\n");
        End(L);
        return;
    }

    if(Position < 0 || Position > L->Quant){
        printf("Insira uma posição válida pelo amor de Deus.\n");  //Tratar se o usuário tiver problemas cerebrais
        return;
    }

    P->Element = I;

    if(L->First == NULL){ //Trata caso da lista estar vazia
        L->First = P;
        P->Next = P;
        P->Prev = P;
    }
    else{
        TypePointer Ax = L->First;

        while(Ax->Position != Position){ //Percorre a lista até achar onde
            Ax = Ax->Next;                    //o jogar quer inserir o item
        }

        P->Next = Ax->Next;
        P->Prev = Ax;
        Ax->Next = P;
        P->Next->Prev = P;
    }

    L->Quant++;
    CorrectPos(L);

}

void Remove(TypeList *L, int Position){
    TypePointer P = SeekPosition(L, Position);

    if(P == NULL){
        printf("Item cannot be found.\n");
        return;
    }

    if(P == L->First)
        L->First = L->First->Next;

    P->Prev->Next = P->Next;
    P->Next->Prev = P->Prev;
    free(P);
    L->Quant--;
    CorrectPos(L);
}

void SeekPlus(TypeList *L){ //Procura o "+" dentro da lista
    TypePointer P = L->First;
    for (int i = 1; i <= L->Quant; i++) {
        if(P->Element.AtomicN == 0)
            Fusion(L, i);   //Fusão de dois átomos
        P = P->Next;
    }

}

TypePointer SeekPosition(TypeList *L, int Position){
    int cont = 0;
    TypePointer P = L->First;
    while(P->Position != Position && cont <= L->Quant){
        P = P->Next;
        cont++;
    }

    if(cont == L->Quant)
      return NULL;
    else
      return P;
}

void Fusion(TypeList *L, int Position){
    TypePointer P = SeekPosition(L, Position);
    if(P == NULL)
        return;
    if(P->Prev->Element.AtomicN != P->Next->Element.AtomicN || P->Next == P->Prev){ //Verifica se o anterior e o próximo são diferentes
        return;
    }
    else{ // Se forem iguais funde os elementos, através do "+" ou de um elemento que acabou de ser fundido

      if(P->Element.AtomicN <= P->Prev->Element.AtomicN) //Verifica se o elemento do meio é menor que os elementos das pontas
          P->Element.AtomicN = P->Prev->Element.AtomicN;
      else{
          P->Prev->Element.AtomicN = P->Element.AtomicN;
          P->Next->Element.AtomicN = P->Prev->Element.AtomicN;
      }

      P->Element.AtomicN++; //Aumenta a quantidade de elétrons do átomo (bem nerd)
      Remove(L,P->Prev->Position); //Depois remove os elementos do lado
      Remove(L,P->Next->Position);
      L->Points = L->Points + 10;
      Show(L);
      printf("\7 \a"); //Fazer um beep maneiro pro jogador
      Fusion(L, P->Position);//Verifica se é possível fundir mais elementos
    }
}

void CorrectPos(TypeList *L){ //Corrige as posições dos elementos após inserção ou remoção
    TypePointer P = L->First;

    for (int i = 1; i <= L->Quant; i++) {
        P->Position = i;
        P = P->Next;
    }
}

void Show(TypeList *L){ //Meio óbvio
    TypePointer P = L->First;
    printf("\n");
    do {
        NameElement(P->Element.AtomicN);
        printf("_%d_", P->Position);
        P = P->Next;
    } while(P != L->First);
    printf("\n");
}

int Full(TypeList *L){
    return L->Quant > 20;
}

void End(TypeList *L){
  TypePointer P = L->First;
  TypePointer Ax;
  for (int i = 1; i <= L->Quant; i++) {
      Ax = P;
      P = P->Next;
      free(Ax);
      if(i == L->Quant)
          free(P);
  }
}

void NameElement(int AN){
    switch (AN) {
      case 0:
          printf("\33[41;1;35m + \33[0m");
          break;
      case 1:
          printf("\33[0;31m H \33[0;30m");
          break;
      case 2:
          printf("\33[0;32m He \33[0;30m");
          break;
      case 3:
          printf("\33[0;33m Li \33[0;30m");
          break;
      case 4:
          printf("\33[0;34m Be \33[0;30m");
          break;
      case 5:
          printf("\33[0;35m B \33[0;30m");
          break;
      case 6:
          printf("\33[0;36m C \33[0;30m");
          break;
      case 7:
          printf("\33[0;37m N \33[0;30m");
          break;
      case 8:
          printf("\33[1;30m O \33[0;30m");
          break;
      case 9:
          printf("\33[1;31m F \33[0;30m");
          break;
      case 10:
          printf("\33[1;32m Ne \33[0;30m");
          break;
      case 11:
          printf("\33[1;33m Na \33[0;30m");
          break;
      case 12:
          printf("\33[1;34m Mg \33[0;30m");
          break;
      case 13:
          printf("\33[1;35m Al \33[0;30m");
          break;
      case 14:
          printf("\33[1;36m Si \33[0;30m");
          break;
      case 15:
          printf("\33[1;37m P \33[0;30m");
          break;
      case 16:
          printf("\33[0;31m S \33[0;30m");
          break;
      case 17:
          printf("\33[0;32m Cl \33[0;30m");
          break;
      case 18:
          printf("\33[0;33m Ar \33[0;30m");
          break;
      case 19:
          printf("\33[0;34m K \33[0;30m");
          break;
      case 20:
          printf("\33[0;35m Ca \33[0;30m");
          break;
      case 21:
          printf("\33[0;36m Sc \33[0;30m");
          break;
      case 22:
          printf("\33[0;37m Ti \33[0;30m");
          break;
      case 23:
          printf("\33[1;30m V \33[0;30m");
          break;
      case 24:
          printf("\33[1;31m Cr \33[0;30m");
          break;
      case 25:
          printf("\33[1;32m Mn \33[0;30m");
          break;
      case 26:
          printf("\33[1;33m Fe \33[0;30m");
          break;
      case 27:
          printf("\33[1;34m Co \33[0;30m");
          break;
      case 28:
          printf("\33[1;35m Ni \33[0;30m");
          break;
      case 29:
          printf("\33[1;36m Cu \33[0;30m");
          break;
      case 30:
          printf("\33[1;37m Zn \33[0;30m");
          break;
      case 31:
          printf("\33[0;31m Ga \33[0;30m");
          break;
      case 32:
          printf("\33[0;32m Ge \33[0;30m");
          break;
      case 33:
          printf("\33[0;33m As \33[0;30m");
          break;
      case 34:
          printf("\33[0;34m Se \33[0;30m");
          break;
      case 35:
          printf("\33[0;35m Br \33[0;30m");
          break;
      case 36:
          printf("\33[0;36m Kr \33[0;30m");
          break;
      case 37:
          printf("\33[0;37m Rb \33[0;30m");
          break;
      case 38:
          printf("\33[1;30m Sr \33[0;30m");
          break;
      case 39:
          printf("\33[1;31m Y \33[0;30m");
          break;
      case 40:
          printf("\33[1;32m Zr \33[0;30m");
          break;
      case 41:
          printf("\33[1;33m Nb \33[0;30m");
          break;
      case 42:
          printf("\33[1;34m Mo \33[0;30m");
          break;
      case 43:
          printf("\33[1;35m Tc \33[0;30m");
          break;
      case 44:
          printf("\33[1;36m Ru \33[0;30m");
          break;
      case 45:
          printf("\33[1;37m Rh \33[0;30m");
          break;
      case 46:
          printf("\33[0;31m Pd \33[0;30m");
          break;
      case 47:
          printf("\33[0;32m Ag \33[0;30m");
          break;
      case 48:
          printf("\33[0;33m Cd \33[0;30m");
          break;
      case 49:
          printf("\33[0;34m In \33[0;30m");
          break;
      case 50:
          printf("\33[0;35m Sn \33[0;30m");
          break;
      case 51:
          printf("\33[0;36m Sb \33[0;30m");
          break;
      case 52:
          printf("\33[0;37m Te \33[0;30m");
          break;
      case 53:
          printf("\33[1;30m I \33[0;30m");
          break;
      case 54:
          printf("\33[1;31m Xe \33[0;30m");
          break;
      case 55:
          printf("\33[1;32m Cs \33[0;30m");
          break;
      case 56:
          printf("\33[1;33m Ba \33[0;30m");
          break;
      case 57:
          printf("\33[1;34m La \33[0;30m");
          break;
      case 58:
          printf("\33[1;35m Ce \33[0;30m");
          break;
      case 59:
          printf("\33[1;36m Pr \33[0;30m");
          break;
      case 60:
          printf("\33[1;37m Nd \33[0;30m");
          break;
      case 61:
          printf("\33[0;31m Pm \33[0;30m");
          break;
      case 62:
          printf("\33[0;32m Sm \33[0;30m");
          break;
      case 63:
          printf("\33[0;33m Eu \33[0;30m");
          break;
      case 64:
          printf("\33[0;34m Gd \33[0;30m");
          break;
      case 65:
          printf("\33[0;35m Tb \33[0;30m");
          break;
      case 66:
          printf("\33[0;36m Dy \33[0;30m");
          break;
      case 67:
          printf("\33[0;37m Ho \33[0;30m");
          break;
      case 68:
          printf("\33[1;30m Er \33[0;30m");
          break;
      case 69:
          printf("\33[1;31m Tm \33[0;30m");
          break;
      case 70:
          printf("\33[1;32m Yb \33[0;30m");
          break;
      case 71:
          printf("\33[1;33m Lu \33[0;30m");
          break;
      case 72:
          printf("\33[1;34m Hf \33[0;30m");
          break;
      case 73:
          printf("\33[1;35m Ta \33[0;30m");
          break;
      case 74:
          printf("\33[1;36m W \33[0;30m");
          break;
      case 75:
          printf("\33[1;37m Re \33[0;30m");
          break;
      case 76:
          printf("\33[0;31m Os \33[0;30m");
          break;
      case 77:
          printf("\33[0;32m Ir \33[0;30m");
          break;
      case 78:
          printf("\33[0;33m Pt \33[0;30m");
          break;
      case 79:
          printf("\33[0;34m Au \33[0;30m");
          break;
      case 80:
          printf("\33[0;35m Hg \33[0;30m");
          break;
      case 81:
          printf("\33[0;36m Tl \33[0;30m");
          break;
      case 82:
          printf("\33[0;37m Pb \33[0;30m");
          break;
      case 83:
          printf("\33[1;30m Bi \33[0;30m");
          break;
      case 84:
          printf("\33[1;31m Po \33[0;30m");
          break;
      case 85:
          printf("\33[1;32m At \33[0;30m");
          break;
      case 86:
          printf("\33[1;33m Rn \33[0;30m");
          break;
      case 87:
          printf("\33[1;34m Fr \33[0;30m");
          break;
      case 88:
          printf("\33[1;35m Ra \33[0;30m");
          break;
      case 89:
          printf("\33[1;36m Ac \33[0;30m");
          break;
      case 90:
          printf("\33[1;37m Th \33[0;30m");
          break;
      case 91:
          printf("\33[0;31m Pa \33[0;30m");
          break;
      case 92:
          printf("\33[0;32m U \33[0;30m");
          break;
      case 93:
          printf("\33[0;33m Np \33[0;30m");
          break;
      case 94:
          printf("\33[0;34m Pu \33[0;30m");
          break;
      case 95:
          printf("\33[0;35m Am \33[0;30m");
          break;
      case 96:
          printf("\33[0;36m Cm \33[0;30m");
          break;
      case 97:
          printf("\33[0;37m Bk \33[0;30m");
          break;
      case 98:
          printf("\33[1;30m Cf \33[0;30m");
          break;
      case 99:
          printf("\33[1;31m Es \33[0;30m");
          break;
      case 100:
          printf("\33[1;32m Fm \33[0;30m");
          break;
      case 101:
          printf("\33[1;33m Md \33[0;30m");
          break;
      case 102:
          printf("\33[1;34m No \33[0;30m");
          break;
      case 103:
          printf("\33[1;35m Lr \33[0;30m");
          break;
      case 104:
          printf("\33[1;36m Rf \33[0;30m");
          break;
      case 105:
          printf("\33[1;37m Db \33[0;30m");
          break;
      case 106:
          printf("\33[0;31m Sg \33[0;30m");
          break;
      case 107:
          printf("\33[0;32m Bh \33[0;30m");
          break;
      case 108:
          printf("\33[0;33m Hs \33[0;30m");
          break;
      case 109:
          printf("\33[0;34m Mt \33[0;30m");
          break;
      case 110:
          printf("\33[0;35m Ds \33[0;30m");
          break;
      case 111:
          printf("\33[0;36m Rg \33[0;30m");
          break;
      case 112:
          printf("\33[0;37m Cn \33[0;30m");
          break;
      case 113:
          printf("\33[1;30m Nh \33[0;30m");
          break;
      case 114:
          printf("\33[1;31m Fl \33[0;30m");
          break;
      case 115:
          printf("\33[1;32m Mc \33[0;30m");
          break;
      case 116:
          printf("\33[1;33m Lv \33[0;30m");
          break;
      case 117:
          printf("\33[1;34m Ts \33[0;30m");
          break;
      case 118:
          printf("\33[1;35m Og \33[0;30m");
          break;
    }
} //Uma função bem chata de fazer pra não ter que trabalhar com strings

TypeItem GenerateElement(TypeList *L, int I){ //Gera elementos aleatórios dentro de um intervalo
    TypeItem N;
    sleep(1);
    srand(time(NULL));
    N.AtomicN = (rand() % 5)+ 1;

    if((N.AtomicN == 1 || N.AtomicN == 5) && L->Quant > 5 && (L->Quant > 18 || L->Quant%3 == 0 || L->Quant%4 == 0 || L->Quant%5 == 0)){//Mexendo com probabilidades
        N.AtomicN = 0;
        return N;
    }
    N.AtomicN = N.AtomicN + I;
    return N;
}

void BeginList(TypeList *L){ //Inicia a Lista com 5 elementos maneiros
    TypeItem I;
    printf("Criando conjunto bolado de elementos...\n");
    I = GenerateElement(L, 0);
    Insert(L,I, 0);
    I = GenerateElement(L, 0);
    Insert(L,I, 1);
    I = GenerateElement(L, 0);
    Insert(L,I, 2);
    I = GenerateElement(L, 0);
    Insert(L,I, 3);
    I = GenerateElement(L, 0);
    Insert(L,I, 4);
}

int WinGame(TypeList *L){
  int Win = 0;
  TypePointer P = L->First;
  for (int i = 1; i <= L->Quant; i++) {
    if(P->Element.AtomicN == 118){
        printf("Você chegou no último elemento!\n");
        Win = 1;
        Show(L);
    }
        P = P->Next;
  }
  return Win;
}

void RemoveOldELements(TypeList *L, int I){
    TypePointer P = L->First;
    for (int i = 0; i < L->Quant; i++) {
        if(P->Element.AtomicN < I - 3 && P->Element.AtomicN != 0){
            Remove(L,P->Position);
            printf("Removendo elementos velhos...\n");
            Show(L);
        }
        P = P->Next;
    }

}

void Game(TypeList *L){
    Build(L);
    BeginList(L);
    int Choice, Turns = 0, c, Flag, WinF = 0;
    TypeItem I;
    while(!Full(L) && !WinF){
        Choice = 0;
        c = 0;
        Flag = 0;
        Show(L);
        Turns++;
        I = GenerateElement(L, Turns/8);
        RemoveOldELements(L, Turns/8);
        NameElement(I.AtomicN);
        printf("Insira o elemento onde desejar, patrão:\n");
        while(Choice <= 0 || Choice > L->Quant){
            if(Flag > 0)
                printf("Insira uma posição válida pelo amor de Deus.\n");
            scanf("%d", &Choice);
            if(Choice == 1984) //Easter egg maneiro
                I.AtomicN = 118;
            Flag++;
        }
        Insert(L,I, Choice);
        while(c <= L->Quant){
            SeekPlus(L);
            c++;
        }
        WinF = WinGame(L);
    }
    printf("Fim de Jogo!\n");
    printf("SCORE:%d\n", L->Points);

}
