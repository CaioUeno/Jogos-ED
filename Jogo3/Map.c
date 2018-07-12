#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Map.h"
#include "Tree.h"


void Start(TypeTree *T){
    NewTree(T);
    // PickMap(T, 1);
}

void PickMap(TypeTree *T, int O){
    TypeItem J;
    FILE *PFile;
    if(O == 1)
        PFile = fopen("map_1.txt", "r");
    if(O == 2)
        PFile = fopen("map_2.txt", "r");
    if(O == 3)
        PFile = fopen("map_3.txt", "r");
    if(PFile != NULL){
        while (fscanf(PFile, "%d %d %d %d %d\n", &J.Pos, &J.Up, &J.Left, &J.Right, &J.Down) != EOF) {
            Insert(T, J);
        }

        fclose(PFile);
        // ShowMap(O);
    }
}

void ShowMap(int O){
    switch (O) {
      case 3:
          printf("            FASE 3 \n");
          printf("  Início\n");
          printf("    ║\n");
          printf("╔═══╩═══╦═════╦══════╦═════▲\n");
          printf("║       ║     ║      ║\n");
          printf("╠═══╦═══╩═════╣       \n");
          printf("║   ║         ║ \n");
          printf("║   ║         ║\n");
          printf("║   ▲         ╠══════╦═══════╗\n");
          printf("╠═══════      ║      ║       ║\n");
          printf("║             ║      ║       ║\n");
          printf("║                    ╠═══════╩══════ -> Saída\n");
          printf("║                    ║\n");
          printf("╚═════▲              ║\n");
          break;
      case 2:
          printf("            FASE 2 \n");
          printf("                     Saída   \n");
          printf("                       ║     \n");
          printf("                       ║\n");
          printf("          ▲════╦═══════╩═══════╦════▲\n");
          printf("               ║               ║\n");
          printf("               ║               ║\n");
          printf("           ╔═══╩═══════════════╩═══╗\n");
          printf("           ║                       ║\n");
          printf("Início ════╣                       ║\n");
          printf("           ║                       ║\n");
          printf("           ╚══════         ▲═══════╝\n");
          break;
      case 1:
          printf("            FASE 1 \n");
          printf("                             ▲═══════╗ \n");
          printf("▲                                    ║\n");
          printf("║                                    ║ \n");
          printf("║          ╔═══════════╦═════════════╬════════\n");
          printf("║          ║           ║             ║\n");
          printf("╠══════════╝           ║             ║\n");
          printf("║                      ║\n");
          printf("║              ▲═══════╩═══════╗ \n");
          printf("║                              ║ \n");
          printf("║                              ║ \n");
          printf("╚══════════╗                 Saída\n");
          printf("           ║\n");
          printf("           ║\n");
          printf("           ╠══════════ Início\n");
          printf("           ║\n");
          printf("           ║\n");
          printf("═══════════╝\n");
          printf("\n");
          break;
    }
}

void CheckItem(TypeItem Q, int O, int *I){
    switch (O) {
      case 1:
          if(Q.Pos == 8 && I[0] == 0){
              I[0] = 8;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 14 && I[1] == 0){
              I[1] = 14;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 18 && I[2] == 0){
              I[2] = 18;
              printf("Você pegou um Triângulo!\n");
          }
          break;
      case 2:
          if(Q.Pos == 8 && I[0] == 0){
              I[0] = 8;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 14 && I[1] == 0){
              I[1] = 14;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 15 && I[2] == 0){
              I[2] = 15;
              printf("Você pegou um Triângulo!\n");
          }
          break;
      case 3:
          if(Q.Pos == 7 && I[0] == 0){
              I[0] = 7;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 13 && I[1] == 0){
              I[1] = 13;
              printf("Você pegou um Triângulo!\n");
          }
          if(Q.Pos == 17 && I[2] == 0){
              I[2] = 17;
              printf("Você pegou um Triângulo!\n");
          }
          break;
    }

}

void static ShowOp(TypeItem H){
    if(H.Left != 0)
        printf("1 - Ir para a esquerda\n");
    if(H.Up != 0)
        printf("2 - Subir\n");
    if(H.Right != 0)
        printf("3 - Ir para a direita\n");
    if(H.Down != 0)
        printf("4 - Descer\n");

}

int static Full(int *V){
    if(V[0] != 0 && V[1] != 0 && V[2] != 0)
        return 1;
    else
        return 0;
}

int Final(int O){
    if(O == 1)
        return 20;
    if(O == 2)
        return 16;
    if(O == 3)
        return 25;
}

void Game(TypeTree *T){
    Start(T);
    TypeItem R;
    int Itens[3];
    int Op, Flag;
    printf("\e[H\e[2J");
    printf("LabirinteX ▲\n");
    for (int i = 1; i <= 3; i++) {
        printf("Carregando");
        printf(".");
        printf(".");
        printf(".\n");
        sleep(1);
        sleep(1);
        sleep(1);
        Itens[0] = 0;
        Itens[1] = 0;
        Itens[2] = 0;
        R.Pos = 1;
        PickMap(T, i);
        R = SearchByItem(T, R);
        while (R.Pos != Final(i) || !Full(Itens)) {
            printf("\e[H\e[2J");
            ShowMap(i);
            CheckItem(R, i, &Itens[0]);
            do {
                Flag = 1;
                printf("Escolha uma opção:\n");
                ShowOp(R);
                scanf("%d", &Op);
                if(Op == 1)
                    if(R.Left != 0){
                        Flag = 0;
                        R = SearchByPos(T, R.Left);
                    }
                if(Op == 4)
                    if(R.Down != 0){
                        Flag = 0;
                        R = SearchByPos(T, R.Down);
                    }
                if(Op == 3)
                    if(R.Right != 0){
                        Flag = 0;
                        R = SearchByPos(T, R.Right);
                    }
                if(Op == 2)
                    if(R.Up != 0){
                        Flag = 0;
                        R = SearchByPos(T, R.Up);
                    }
            } while(Flag);
        }
        ClearTree(T);
    }
    printf("\e[H\e[2J");
    printf("Você ganhou!\n");
    sleep(3);
}
