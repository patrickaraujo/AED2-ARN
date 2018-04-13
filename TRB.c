#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "TRB.h"

TRB* rotacionaEsquerda(TRB *main){
    TRB *aux = main->dir;
    main->dir = aux->esq;
    aux->esq = main;
    aux->cor = main->cor;
    main->cor = RED;
    return aux;
}

TRB* rotacionaDireita(TRB *main){
    TRB* aux = main->esq;
    main->esq = aux->dir;
    aux->dir = main;
    aux->cor = main->cor;
    main->cor = RED;
    return aux;
}

TRB* move2EsqRED(TRB *main){
    trocaCor(main);
    if( cor(main->dir->esq) == RED ){
        main->dir = rotacionaDireita(main->dir);
        main = rotacionaEsquerda(main);
        trocaCor(main);
    }
    return main;
}

TRB* move2DirRED(TRB *main){
    trocaCor(main);
    if( cor(main->esq->esq) == RED ){
        main = rotacionaDireita(main);
        trocaCor(main);
    }
    return main;
}

TRB* procuraMenor(TRB *main){
    TRB *aux = main;
    TRB *temp = main->esq;
    while(temp){
        aux = temp;
        temp = temp->esq;
    }
    return aux;
}

TRB* balancear(TRB* main){
    //  nó Vermelho é sempre filho à esquerda
    if( cor(main->dir) == RED )
        main = rotacionaEsquerda(main);

    //  Filho da direita e neto da esquerda são vermelhos
    if( (main->esq && cor(main->dir) == RED) && (cor(main->esq->esq) == RED) )
        main = rotacionaDireita(main);

    //  2 filhos Vermelhos: troca cor!
    if( (cor(main->esq) == RED) && (cor(main->dir) == RED) )
        trocaCor(main);

    return main;
}

TRB* removerMenor(TRB *main){
    if(!main->esq){
        free(main);
        return NULL;
    }
    if( (cor(main->esq) == BLACK) && (cor(main->esq->esq) == BLACK) )
        main = move2EsqRED(main);

    main->esq = removerMenor(main->esq);
    return balancear(main);
}

TRB* remove_NO(TRB *main, int num){
    if(num < main->info){
        if( (cor(main->esq) == BLACK) && (cor(main->esq->esq) == BLACK) )
            main = move2EsqRED(main);

        main->esq = remove_NO(main->esq, num);
    }
    else{
        if(cor(main->esq) == RED)
            main = rotacionaDireita(main);

        if( (num == main->info) && (!main->dir) ){
            free(main);
            return NULL;
        }

        if( (cor(main->dir) == BLACK) && (cor(main->dir->esq) == BLACK) )
            main = move2DirRED(main);

        if(num == main->info){
            TRB *aux = procuraMenor(main->dir);
            main->info = aux->info;
            main->dir = removerMenor(main->dir);
        }
        else
            main->dir = remove_NO(main->dir, num);
    }
    return balancear(main);
}

int remover(TRB **main, int num){
    if(consulta(main, num)){
        TRB *aux = *main;
        *main = remove_NO(aux, num);
        if(*main)
            (*main)->cor = BLACK;
        return 1;
    }
    else
        return NULL;
}

int consulta(TRB **main, int num){
    TRB *aux = *main;
    while(aux){
        if(num == aux->info)
            return 1;
        if(num > aux->info)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    return NULL;
}

int cor(TRB *main){
    if(main)
        return main->cor;
	return BLACK;
}

void trocaCor(TRB *main){
    main->cor = !main->cor;
    if(main->esq)
        main->esq->cor = !main->esq->cor;
    if(main->dir)
        main->dir->cor = !main->dir->cor;
}



TRB* insereNO(TRB *main, int num, int *resp){
    if(!main){
        TRB *aux = (TRB *)malloc(sizeof(TRB));
        if(!aux){
            *resp = 0;
            return NULL;
        }

        aux->info = num;
        aux->cor = RED;
        aux->dir = aux->esq = NULL;
        *resp = 1;
        return aux;
    }

    if(num == main->info)
        *resp = 0;  //  Valor duplicado
    else{
        if(num < main->info)
            main->esq = insereNO(main->esq, num, resp);
        else
            main->dir = insereNO(main->dir, num, resp);
    }

    //  nó Vermelho é sempre filho à esquerda
    if( (cor(main->dir) == RED) && (cor(main->esq) == BLACK) )
        main = rotacionaEsquerda(main);

    //  Filho e Neto são vermelhos
    //  Filho vira pai de 2 nós vermelhos
    if( (cor(main->esq) == RED) && (cor(main->esq->esq) == RED) )
        main = rotacionaDireita(main);

    //  2 filhos Vermelhos: troca cor!
    if( (cor(main->esq) == RED) && (cor(main->dir) == RED) )
        trocaCor(main);

    return main;
}

int inserir(TRB **main, int num){
    int resp;

    *main = insereNO(*main, num, &resp);
    if(*main)
        (*main)->cor = BLACK;

    return resp;
}


void imprimir(TRB *main){
    //  Essa função imprime os elementos de forma recursiva

    printf("(");    //  notação para organizar na hora de mostrar os elementos
    if(main) {  //  se a árvore não for vazia...
        //  Mostra os elementos em pré-ordem
        if(main->cor == RED){
            textbackground(4);
            printf("%d ", main->info);  //  mostra a raiz
            textbackground(0);
        }
        else
            printf("%d ", main->info);

        imprimir(main->esq);   //  mostra a sae (subárvore à esquerda)
        imprimir(main->dir);   //  mostra a sad (subárvore à direita)
    }
    printf(")");    //  notação para organizar na hora de mostrar os elementos
}
