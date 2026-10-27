#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void prencherAleatorio(arv *arv, int instancia){
    for(int i = 0; i < instancia; i++){

        int numero_grande = (int)(((long long)rand() * ((long long)RAND_MAX + 1)) + rand()); 
        
        inserirNaArv(arv, numero_grande);
    }
}

void preencherOrdenadaCrescente(arv *arv, int instancia){
        for (int i = 1; i < instancia + 1; i++)
        {
          inserirNaArv(arv, i);
        }
        
}

void preencherOrdenadaDescrescente(arv *arv, int instancia){
        for (int i = instancia; i > 0; i--)
        {
          inserirNaArv(arv, i);
        }
}

void buscaAleatoria(arv *arv){
    int numAleatorio = rand();
    printf("numero a buscar: %d.\n", numAleatorio);
        if (consultaArv(arv->raiz, numAleatorio) == 0){
             printf("++======================================================++\n");
            printf("Chave gerada %d nao se encontra na arvore.\n", numAleatorio);
             printf("++======================================================++\n\n");
        }
        else {
             printf("++======================================================++\n");
            printf("chave gerada %d encontrada!\n", numAleatorio);
             printf("++======================================================++\n\n");
        }
}

void remocaoAleatoria(arv *arv){
    int numAleatorio = rand();
 printf("numero a remover: %d.\n", numAleatorio);
 if (removeNaArv(arv, numAleatorio) == 1)
 { 
    printf("++======================================================++\n");
  printf("Numero %d encontrado e removido.\n", numAleatorio);
   printf("++======================================================++\n");
 } else {
    printf("++======================================================++\n");
    printf("Numero %d NAO encontrado. Nao foi possivel remover.\n", numAleatorio);
     printf("++======================================================++\n");
 }
 


}

void imprimirArvore(no *raiz) {
    if (raiz != NULL) {
        imprimirArvore(raiz->esq); 
        printf("%d - ", raiz->valorArmz); 
          if (raiz->cor == 1)
        {
        printf("(BLACK)\n");
        } else{
            printf("(RED)\n");
        }  
 
        imprimirArvore(raiz->dir);

      
    }
}

void imprimirArvoreDescre(no *raiz) {
    if (raiz != NULL) {
          imprimirArvoreDescre(raiz->dir); 
        printf("%d - ", raiz->valorArmz);
      if (raiz->cor == 1)
      {
       printf("(BLACK)\n");
      } else{
        printf("(RED)\n");
      }
         
          imprimirArvoreDescre(raiz->esq);  
      
         
    }
}

double calcularMediaRotacao(arv *arv, int instancia){
arv->qtd_rotacao_media = (double)arv->qtd_rotacao / instancia;
return arv->qtd_rotacao_media;
}

double calcularMediaCor(arv *arv, int instancia){
arv->qtd_media_troca_cor = (double)arv->qtd_troca_cor / instancia;
return arv->qtd_media_troca_cor;
}


void apagarNos(no *raiz) {
    if (raiz != NULL) {
        apagarNos(raiz->esq); 
        apagarNos(raiz->dir); 
        free(raiz);           
    }
}



int obterAltura(no *raiz) {
    if (raiz == NULL) {
        return -1; 
    }

    int altEsq = obterAltura(raiz->esq);
    int altDir = obterAltura(raiz->dir);

    
    if (altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

void imprimirArvoreFormatada(no *raiz, int espaco) {

    if (raiz == NULL) {
        return;
    }
    
    espaco += 6;
    imprimirArvoreFormatada(raiz->dir, espaco);

   
    printf("\n");
    for (int i = 6; i < espaco; i++) {
        printf(" ");
    }
 
    if (raiz->cor == 0) { 
        printf("[%d-R]<", raiz->valorArmz); 
    } else {
        printf("[%d-B]", raiz->valorArmz);
    }

    imprimirArvoreFormatada(raiz->esq, espaco);
}