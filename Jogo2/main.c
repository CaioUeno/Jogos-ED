#include <stdio.h>
#include <stdlib.h>
#include "BlackJack.h"
#include "Stack.h"

int main(int argc, char const *argv[]) {
    TypeStack S;
    printf("\e[H\e[2J");
    Game(&S);
    return 0;
}
