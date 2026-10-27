#include "header.h"
#include <stdlib.h>
#include <stdio.h>

#define BLACK 1
#define RED 0




int verCor(no* no){

    if (no == NULL)
    {
      return BLACK;
    }
    else {
        return no->cor;
    }
}


no* rotacaoEsq(arv *arv, no *A){
    no* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
arv->qtd_rotacao++;

    return B;


}

no* rotacaoDir(arv *arv, no *A){
    no* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
arv->qtd_rotacao++;
    return B;


}




void trocarCor(arv *arv, no *no){
 
    no->cor = !no->cor;

    if (no->esq != NULL)
    {
       no->esq->cor = !no->esq->cor;
    }
    if(no->dir != NULL){
        no->dir->cor = !no->dir->cor;
    }

arv->qtd_troca_cor++;
}



no *inserirNovo(arv *arv, no *N, int chave, int *resp){
    if (N == NULL)
    {
        no* novo = (no*) malloc(sizeof(no));
        if (novo == NULL)
        {
           *resp = 0;
           return NULL;
        }
        novo->valorArmz = chave;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = -1;
        return novo;

    }
if (chave == N->valorArmz)
{
    *resp = 0; // verifica valor dup;
    return N;
} else {
    if (chave < N->valorArmz)
    {
       N->esq = inserirNovo(arv, N->esq, chave, resp);
    }
    else{
         N->dir = inserirNovo(arv, N->dir, chave, resp);
    }
}
    if(verCor(N->dir) == RED && verCor(N->esq) == BLACK){
       N = rotacaoEsq(arv, N);
    }
    if(verCor(N->esq) == RED && verCor(N->esq->esq) == RED){
        N = rotacaoDir(arv, N);
    }
    if(verCor(N->esq)  == RED && verCor(N->dir) == RED){
        trocarCor(arv, N);
    }
    
return N;
}





no* move2DirRED(arv *arv, no* h){
    trocarCor(arv, h);
    if (verCor(h->esq->esq)==RED)
    {
       h = rotacaoDir(arv, h);
       trocarCor(arv, h);
    }
    return h;
}


no* move2EsqRED(arv *arv, no* h){
    trocarCor(arv, h);
    if (verCor(h->dir->esq)==RED)
    {
       h->dir = rotacaoDir(arv, h->dir);
       h= rotacaoEsq(arv, h);
       trocarCor(arv, h);
    }
    return h;
}





int inserirNaArv(arv *arv, int chave){

int resp;
arv->raiz = inserirNovo(arv, arv->raiz, chave, &resp);
if (arv->raiz != NULL)
{
   arv->raiz->cor = BLACK;
}
arv->altura_arvore = obterAltura(arv->raiz);
    if (arv->altura_arvore > arv->altura_max)
    {
    arv->altura_max = arv->altura_arvore;
    }

return resp;

}

no* removerMenor(arv *arv, no *h){
    if(h->esq == NULL){
        free(h);
        return NULL;
    }
    if (verCor(h->esq) == BLACK && verCor(h->esq->esq) == BLACK)
    {
        h = move2EsqRED(arv, h);
    }
    h->esq = removerMenor(arv, h->esq);
    return balancear(arv, h);
   

}



no *procurarMenor(no* atual){
    no* no1 = atual;
    no* no2 = atual->esq;
    while (no2 != NULL)
    {
     no1 = no2;
     no2 = no2->esq;
    }
    return no1;
}

no *procurarMaior(no* atual){
    no* no1 = atual;
    no* no2 = atual->dir;
    while (no2 != NULL)
    {
     no1 = no2;
     no2 = no2->dir;
    }
    return no1;
}

no *balancear(arv *arv, no *h){

    if (verCor(h->dir) == RED && verCor(h->esq) == BLACK)
    {
       h = rotacaoEsq(arv, h);
    }
     if (verCor(h->esq) == RED && verCor(h->esq->esq) == RED)
    {
       h = rotacaoDir(arv, h);
    }
    if (verCor(h->esq) == RED && verCor(h->dir) == RED)
    {
        trocarCor(arv, h);
    }
    return h;
}



no *removeNo(arv *arv, no *h, int valor){
    if (valor < h->valorArmz)
    {
     if (verCor(h->esq) == BLACK && verCor(h->esq->esq) == BLACK){
        h = move2EsqRED(arv, h);
     }
     h->esq = removeNo(arv, h->esq, valor);
    } else {
        if (verCor(h->esq) == RED)
        {
            h = rotacaoDir(arv, h);
        }
        if (valor == h->valorArmz && (h->dir == NULL))
        {
            free(h);
            return  NULL;
        }
        if (verCor(h->dir) == BLACK && verCor(h->dir->esq ) == BLACK)
        {
            h = move2DirRED(arv, h);
        }
        if (valor == h->valorArmz)
        {
            no* x = procurarMenor(h->dir);
            h->valorArmz = x->valorArmz;
            h->dir = removerMenor(arv, h->dir);
        } else {
                 h->dir = removeNo(arv, h->dir, valor);
        }
        
    }
     
 return balancear(arv, h);
}



int consultaArv(no* N, int chave) {
    
    if (N == NULL) {
        return 0;
    }

  
    if (chave == N->valorArmz) {
        return 1;
    }

    
    if (chave < N->valorArmz) {
        return consultaArv(N->esq, chave); 
    } else {
        return consultaArv(N->dir, chave); 
    }
}

int removeNaArv(arv *arv, int chave){
    if (consultaArv(arv->raiz, chave)){
       no* h = arv->raiz;
       arv->raiz = removeNo(arv, h, chave);
       if (arv->raiz != NULL)
       {
        arv->raiz->cor = BLACK;
      
       } 
        arv->altura_arvore = obterAltura(arv->raiz);
         return 1;
    } 
    else { return 0; }

}


arv* criarArvore(){
    arv* arvore = (arv *)malloc(sizeof(arv));
    if(arvore != NULL){
        arvore->altura_arvore = 0;
        arvore->altura_max = 0;
        arvore->qtd_media_troca_cor = 0;
        arvore->raiz = NULL;
        arvore->qtd_rotacao = 0;
        arvore->qtd_rotacao_media = 0;
        arvore->qtd_troca_cor = 0;
        return arvore;
    } else {
        printf("Sua arvore nao foi criada.\n");
        return NULL;
    }
}


int buscarMin(no* raiz){
if(raiz == NULL){
   return -1;
}
if(raiz->esq == NULL){
   return raiz->valorArmz;
    
}
return buscarMin(raiz->esq);

}

int buscarMax(no* raiz){
if(raiz == NULL){
   return -1;
}
if(raiz->dir == NULL){
   return raiz->valorArmz;
    
}
return buscarMax(raiz->dir);

}





