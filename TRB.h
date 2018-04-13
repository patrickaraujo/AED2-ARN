#ifndef TRB_H_INCLUDED
#define TRB_H_INCLUDED

//  enum Cor{VERMELHO = 4, PRETO = 15}cor;

#define RED 1
#define BLACK 0

typedef struct RB{
    int info, cor;
    struct RB *esq, *dir;
}TRB;

TRB* rotacionaEsquerda(TRB *A);
TRB* rotacionaDireita(TRB *A);
TRB* move2EsqRED(TRB *H);
TRB* move2DirRED(TRB *H);
TRB* procuraMenor(TRB *atual);
TRB* balancear(TRB* H);
TRB* removerMenor(TRB *H);
TRB* remove_NO(TRB *H, int valor);
int remover(TRB **raiz, int valor);
int consulta(TRB **raiz, int valor);
int cor(TRB *H);
void trocaCor(TRB *H);
TRB* insereNO(TRB *H, int valor, int *resp);
int inserir(TRB **raiz, int valor);
int empty(TRB *main);
void imprimir(TRB *main);

#endif // TRB_H_INCLUDED
