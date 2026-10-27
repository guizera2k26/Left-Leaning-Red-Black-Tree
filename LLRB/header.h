#ifndef HEADER_H
#define HEADER_H


typedef struct No
{
    int valorArmz;
    struct No *esq;
    struct No* dir;
    int cor;
}no;


typedef struct Arv
{
    no *raiz;
    int altura_arvore;
    int altura_max;
    long qtd_rotacao;
    double qtd_rotacao_media;
    long qtd_troca_cor;
    double qtd_media_troca_cor;
   
}arv;



int verCor(no* no);
no* rotacaoEsq(arv *arv, no *A);
no* rotacaoDir(arv *arv, no *A);
void trocarCor(arv *arv, no *no);
no *inserirNovo(arv *arv, no *N, int chave, int *resp);
no* move2DirRED(arv *arv, no* h);
no* move2EsqRED(arv *arv, no* h);
int inserirNaArv(arv *arv, int chave);
no* removerMenor(arv *arv, no *h);
no *procurarMenor(no* atual);
no *balancear(arv *arv, no *h);
no *removeNo(arv *arv, no *h, int valor);
int consultaArv(no* N, int chave);
int removeNaArv(arv *arv, int chave);
arv* criarArvore();
int buscarMin(no* raiz);
int buscarMax(no* raiz);



void prencherAleatorio(arv *arv, int instancia);
void preencherOrdenadaCrescente(arv *arv, int instancia);
void preencherOrdenadaDescrescente(arv *arv, int instancia);
void buscaAleatoria(arv *arv);
void remocaoAleatoria(arv *arv);
void imprimirArvore(no *raiz);
void imprimirArvoreDescre(no *raiz);
double calcularMediaRotacao(arv *arv, int instancia);
double calcularMediaCor(arv *arv, int instancia);
void apagarNos(no *raiz);
int obterAltura(no *raiz);
void imprimirArvoreFormatada(no *raiz, int espaco);

#endif