// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
//Trabalho realizado por:
//Eduardo Correia - 2020139576

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "tpPROG.h"
#include "tpPROG.c"
#include "utils.h"

int main()
{
    Lista *tabuleiro=NULL;
    Lista *aux=tabuleiro;
    int escolha;

    lebinario(tabuleiro, aux);

    do
    {
        escolha=-1;
        printf("\n --> JOGO DO SEMAFORO <--\n");
        printf("\n Escolha uma das seguintes opcoes:\n");
        printf("   (1) Jogar com um amigo\n");
        printf("   (2) Jogar contra um bot\n");
        printf("   (3) Manual do jogo\n");
        printf("   (4) Sair\n");
        do
        {
            printf("\nEscolha: ");
            scanf("%d",&escolha);
            fflush(stdin);
        }
        while(escolha<1 || escolha>4);
        printf("\n\n\n");

        switch(escolha)
        {
        case 1:
            jogoNormal(NULL, 0);
            break;
        case 2:
            jogoBot();
            break;
        case 3:
            manual();
            break;
        case 4:
            break;
        }
        printf("\n\n\n\n\n\n\n");

    }while(escolha>0 && escolha<4);
    printf("\n ~~~~~ FIM ~~~~~\n");
}




