/**
*   @author Patrick Araújo: https://github.com/patrickaraujo
*   Árvore Rubro Negra caída para esquerda (LLRB)
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "TRB.c"
#include "TRB.h"

int main(){
    TRB *main = NULL;
    int i, N = 10, dados[10] = {1, 2, 3, 10, 4, 5, 9, 7, 8, 6};
    int dados2[9] = {11, 2, 14, 15, 1, 7, 8, 5, 4};
    int dados3[7] = {7, 6, 5, 4, 3, 2, 1};

    for(i = 0; i < 9; i++)
        inserir(&main, dados2[i]);
    imprimir(main);
    printf("\n");
    remover(&main, 14);
    imprimir(main);

    return 0;
}
