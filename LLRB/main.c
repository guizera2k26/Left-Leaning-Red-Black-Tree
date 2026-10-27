#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include <locale.h>




int main(){
setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int instancia;
    char acaoImprimir;
    clock_t inicioI, fimI, inicioB, fimB, inicioR, fimR, inicioM, fimM, inicioMax, fimMax;
arv* a = criarArvore();

printf("O programa vai rodar 10x sua instancia, entao digite sua instancia. \n");
scanf("%d", &instancia);



printf("Selecione o que deseja testar: \n 1 - Inserir aleatoriamente. 2 - Insercao crescente. 3 - Insercao descrescente. \n");

int acao;
scanf("%d", &acao);
getchar();
printf("\n\n\n");





switch (acao)
{
case 1: {

char nomeArq[50];
sprintf(nomeArq, "resultado_aletorio_%d.txt", instancia);

    FILE *arquivo = fopen(nomeArq, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        break;
    }
    fprintf(arquivo, "Instancia;Rodada;TempoInsercao;TempoBusca;TempoRemocao;RotacoesTotais;TrocasCorTotais\n");
   
   long totalRotacao, totalTrocaCor;
    long rotacoesInsercao, coresInsercao;
    long rotacoesRemocao, coresRemocao;
    int alturaAtualInsercao, alturaMaxInsercao;

    for (int i = 1; i <= 10; i++)
    {
        totalRotacao = 0;
        totalTrocaCor = 0;
        printf("[#%d Operacao.#]\n\n", i);
      
     
        inicioI = clock();
        prencherAleatorio(a, instancia);
        fimI = clock();

    
        rotacoesInsercao = a->qtd_rotacao;
        coresInsercao = a->qtd_troca_cor;
        alturaAtualInsercao = a->altura_arvore; 
        alturaMaxInsercao = a->altura_max;
        totalRotacao = totalRotacao  + rotacoesInsercao;
        totalTrocaCor = totalTrocaCor + coresInsercao;

        inicioB = clock();
        buscaAleatoria(a);
        fimB = clock();


        inicioM = clock();
        int menor = buscarMin(a->raiz);
        fimM = clock();

        inicioMax = clock();
        int maior = buscarMax(a->raiz);
        fimMax = clock();
      
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;

        inicioR = clock();
        remocaoAleatoria(a);
        fimR = clock();

       
        rotacoesRemocao = a->qtd_rotacao;
        coresRemocao = a->qtd_troca_cor;
         totalRotacao = totalRotacao + rotacoesRemocao ;
         totalTrocaCor = totalTrocaCor + coresRemocao ;

     
        double tempoPreencher = ((double)(fimI - inicioI) / CLOCKS_PER_SEC);
        double tempoBusca     = ((double)(fimB - inicioB) / CLOCKS_PER_SEC);
        double tempoRemover   = ((double)(fimR - inicioR) / CLOCKS_PER_SEC);
        double tempoMin   = ((double)(fimM - inicioM) / CLOCKS_PER_SEC);
        double tempoMax   = ((double)(fimMax - inicioMax) / CLOCKS_PER_SEC);

        fprintf(arquivo, "%d;%d;%.5f;%.5f;%.5f;%ld;%ld\n",
                instancia, i, tempoPreencher, tempoBusca, tempoRemover, 
                totalRotacao, totalTrocaCor);

        printf("========================================================\n");
        printf("(Instancia aplicada: %d).\n", instancia);
        
       
        printf("[Tempo]\n");
        printf("TEMPO TOTAL PARA INSERIR ELEMENTOS: %.4f segundos\n", tempoPreencher);
        printf("TEMPO TOTAL PARA BUSCAR ELEMENTO:    %.4f segundos\n", tempoBusca);
        printf("TEMPO TOTAL PARA REMOVER ELEMENTO:   %.4f segundos\n", tempoRemover);
        printf("TEMPO TOTAL PARA MAXIMO ELEMENTO:   %.4f segundis. (NUm: %d.)\n", tempoMax, maior);
        printf("TEMPO TOTAL PARA MINIMO ELEMENTO:   %.4f segundos. (Num: %d.)\n", tempoMin, menor);

        printf("\n[Cores e rotacao]\n");
        
        printf("MEDIA DE ROTACOES NA INSERCAO: %.2lf\n", (double)rotacoesInsercao / instancia);
        printf("MEDIA DE ROTACOES NA REMOCAO: %.2lf\n", (double)rotacoesRemocao / instancia);
        printf("ROTACOES NA INSERCAO: %ld\n", rotacoesInsercao);
        printf("TROCA CORES INSERCAO: %ld\n", coresInsercao);
        printf("ROTACOES NA REMOCAO:  %ld\n", rotacoesRemocao);
        printf("TROCA CORES REMOCAO:  %ld\n", coresRemocao);
        printf("TOTAL ROTACAO:  %ld\n", totalRotacao);
        printf("TOTAL TROCA CORES:  %ld\n", totalTrocaCor);

        printf("\n[ALTURA DA ESTRUTURA]\n");
        printf("ALTURA ATUAL NA ARVORE: %d.\n", alturaAtualInsercao);
        printf("ALTURA MAXIMA NA ARVORE: %d.\n", alturaMaxInsercao);
;

        printf("========================================================\n");
       
        printf("Se deseja imprimir elementos digite 's', se nao, qualquer outra tecla.\n");
        scanf(" %c", &acaoImprimir);
        while (getchar() != '\n'); 
        
        if (acaoImprimir == 's')
        {
            imprimirArvore(a->raiz);
            printf("\n");
        } 

   
        apagarNos(a->raiz);
        a->raiz = NULL; 
        a->altura_arvore = -1; 
        a->altura_max = -1;
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;
    }
    fclose(arquivo);
    break;
}

    case 2:{
        char nomeArq[50];
        sprintf(nomeArq, "resultado_crescente_%d.txt", instancia);

        FILE *arquivo = fopen(nomeArq, "w");
             if (arquivo == NULL) {
             printf("Erro ao abrir o arquivo!\n");
                break;
            }
    fprintf(arquivo, "Instancia;Rodada;TempoInsercao;TempoBusca;TempoRemocao;RotacoesTotais;TrocasCorTotais\n");
    
    long totalRotacao, totalTrocaCor;
    long rotacoesInsercao, coresInsercao;
    long rotacoesRemocao, coresRemocao;
    int alturaAtualInsercao, alturaMaxInsercao;

    


    for (int i = 1; i <= 10; i++)
    {
        totalRotacao = 0;
        totalTrocaCor = 0;
        printf("#%d Operacao.#\n\n", i);
      
     
        inicioI = clock();
        preencherOrdenadaCrescente(a, instancia);
        fimI = clock();

    
        rotacoesInsercao = a->qtd_rotacao;
        coresInsercao = a->qtd_troca_cor;
        alturaAtualInsercao = a->altura_arvore; 
        alturaMaxInsercao = a->altura_max;
         totalRotacao = totalRotacao  + rotacoesInsercao;
        totalTrocaCor = totalTrocaCor + coresInsercao;

       
        inicioB = clock();
        buscaAleatoria(a);
        fimB = clock();

        inicioM = clock();
        int menor = buscarMin(a->raiz);
        fimM = clock();

        inicioMax = clock();
        int maior = buscarMax(a->raiz);
        fimMax = clock();

      
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;

        inicioR = clock();
        remocaoAleatoria(a);
        fimR = clock();

    
        rotacoesRemocao = a->qtd_rotacao;
        coresRemocao = a->qtd_troca_cor;
        totalRotacao = totalRotacao + rotacoesRemocao ;
        totalTrocaCor = totalTrocaCor + coresRemocao ;

     
        double tempoPreencher = ((double)(fimI - inicioI) / CLOCKS_PER_SEC);
        double tempoBusca     = ((double)(fimB - inicioB) / CLOCKS_PER_SEC);
        double tempoRemover   = ((double)(fimR - inicioR) / CLOCKS_PER_SEC);
        double tempoMin   = ((double)(fimM - inicioM) / CLOCKS_PER_SEC);
        double tempoMax   = ((double)(fimMax - inicioMax) / CLOCKS_PER_SEC);

         fprintf(arquivo, "%d;%d;%.5f;%.5f;%.5f;%ld;%ld\n",
                instancia, i, tempoPreencher, tempoBusca, tempoRemover, 
                totalRotacao, totalTrocaCor);

        printf("========================================================\n\n");
        printf("(Instancia processada: %d).\n", instancia);
        
       
        printf("[TEMPO]\n");
        printf("TEMPO TOTAL PARA INSERIR ELEMENTOS: %.4f s\n", tempoPreencher);
        printf("TEMPO TOTAL PARA BUSCAR ELEMENTO:    %.4f s\n", tempoBusca);
        printf("TEMPO TOTAL PARA REMOVER ELEMENTO:   %.4f s\n", tempoRemover);
        printf("TEMPO TOTAL PARA MAXIMO ELEMENTO:   %.4f segundis. (NUm: %d.)\n", tempoMax, maior);
        printf("TEMPO TOTAL PARA MINIMO ELEMENTO:   %4f segundos. (Num: %d.)\n", tempoMin, menor);

        printf("\n[CUSTO ESTRUTURAL]\n");
        printf("ROTACOES NA INSERCAO: %ld\n", rotacoesInsercao);
        printf("TROCA CORES INSERCAO: %ld\n", coresInsercao);
        printf("ROTACOES NA REMOCAO:  %ld\n", rotacoesRemocao);
        printf("TROCA CORES REMOCAO:  %ld\n", coresRemocao);
        printf("TOTAL ROTACAO:  %ld\n", totalRotacao);
        printf("TOTAL TROCA CORES:  %ld\n", totalTrocaCor);

        printf("\n[ALTURA DA ESTRUTURA]\n");
        printf("ALTURA ATUAL NA ARVORE: %d.\n", alturaAtualInsercao);
        printf("ALTURA MAXIMA NA ARVORE: %d.\n", alturaMaxInsercao);

        printf("\t========================================================\n");
       
        printf("Se deseja imprimir elementos digite 's', se nao, qualquer outra tecla.\n");
        scanf(" %c", &acaoImprimir);
        while (getchar() != '\n'); 
        
        if (acaoImprimir == 's')
        {
            imprimirArvore(a->raiz);
            printf("\n");
        } 

   
        apagarNos(a->raiz);
        a->raiz = NULL; 
        a->altura_arvore = -1; 
        a->altura_max = -1;
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;
    }
     fclose(arquivo);
    break;
}
    

case 3:
{
  char nomeArq[50];
    sprintf(nomeArq, "resultado_decrescente_%d.txt", instancia);

    FILE *arquivo = fopen(nomeArq, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        break;
    }
    fprintf(arquivo, "Instancia;Rodada;TempoInsercao;TempoBusca;TempoRemocao;RotacoesTotais;TrocasCorTotais\n");

     long totalRotacao, totalTrocaCor;
    long rotacoesInsercao, coresInsercao;
    long rotacoesRemocao, coresRemocao;
    int alturaAtualInsercao, alturaMaxInsercao;

    for (int i = 1; i <= 10; i++)
    {
totalRotacao = 0;
totalTrocaCor = 0;

        printf("#%d Operacao.#\n\n", i);
      
     
        inicioI = clock();
        preencherOrdenadaDescrescente(a, instancia);
        fimI = clock();

    
        rotacoesInsercao = a->qtd_rotacao;
        coresInsercao = a->qtd_troca_cor;
        alturaAtualInsercao = a->altura_arvore; 
        alturaMaxInsercao = a->altura_max;
        totalRotacao = totalRotacao  + rotacoesInsercao;
        totalTrocaCor = totalTrocaCor + coresInsercao;


       
        inicioB = clock();
        buscaAleatoria(a);
        fimB = clock();

        inicioM = clock();
        int menor = buscarMin(a->raiz);
        fimM = clock();

        inicioMax = clock();
        int maior = buscarMax(a->raiz);
        fimMax = clock();


      
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;

        inicioR = clock();
        remocaoAleatoria(a);
        fimR = clock();

    
        rotacoesRemocao = a->qtd_rotacao;
        coresRemocao = a->qtd_troca_cor;
        totalRotacao = totalRotacao + rotacoesRemocao ;
        totalTrocaCor = totalTrocaCor + coresRemocao ;


     
        double tempoPreencher = ((double)(fimI - inicioI) / CLOCKS_PER_SEC);
        double tempoBusca     = ((double)(fimB - inicioB) / CLOCKS_PER_SEC);
        double tempoRemover   = ((double)(fimR - inicioR) / CLOCKS_PER_SEC);
         double tempoMin   = ((double)(fimM - inicioM) / CLOCKS_PER_SEC);
        double tempoMax   = ((double)(fimMax - inicioMax) / CLOCKS_PER_SEC);

         fprintf(arquivo, "%d;%d;%.5f;%.5f;%.5f;%ld;%ld\n",
                instancia, i, tempoPreencher, tempoBusca, tempoRemover, 
                totalRotacao, totalTrocaCor);

        printf("========================================================\n\n");
        printf("Foi processado o ciclo completo da arvore (Instancia: %d).\n", instancia);
        
       
        printf("[TEMPO]\n");
        printf("TEMPO TOTAL PARA INSERIR ELEMENTOS: %.4f s\n", tempoPreencher);
        printf("TEMPO TOTAL PARA BUSCAR ELEMENTO:    %.4f s\n", tempoBusca);
        printf("TEMPO TOTAL PARA REMOVER ELEMENTO:   %.4f s\n", tempoRemover);
        printf("TEMPO TOTAL PARA MAXIMO ELEMENTO:   %.4f segundis. (Num: %d.)\n", tempoMax, maior);
        printf("TEMPO TOTAL PARA MINIMO ELEMENTO:   %.4f segundos. (Num: %d.)\n", tempoMin, menor);

        printf("\n[CUSTO ESTRUTURAL]\n");
        printf("ROTACOES NA INSERCAO: %ld\n", rotacoesInsercao);
        printf("TROCA CORES INSERCAO: %ld\n", coresInsercao);
        printf("ROTACOES NA REMOCAO:  %ld\n", rotacoesRemocao);
        printf("TROCA CORES REMOCAO:  %ld\n", coresRemocao);
        printf("TOTAL ROTACAO:  %ld\n", totalRotacao);
        printf("TOTAL TROCA CORES:  %ld\n", totalTrocaCor);

        printf("\n[ALTURAS DA ESTRUTURA]\n");
        printf("ALTURA ATUAL NA ARVORE: %d.\n", alturaAtualInsercao);
        printf("ALTURA MAXIMA NA ARVORE: %d.\n", alturaMaxInsercao);

        printf("\t========================================================\n");
       
        printf("Se deseja imprimir elementos digite 's', se nao, qualquer outra tecla.\n");
        scanf(" %c", &acaoImprimir);
        while (getchar() != '\n'); 
        
        if (acaoImprimir == 's')
        {
            imprimirArvore(a->raiz);
            printf("\n");
        } 

   
        apagarNos(a->raiz);
        a->raiz = NULL; 
        a->altura_arvore = -1; 
        a->altura_max = -1;
        a->qtd_rotacao = 0;
        a->qtd_troca_cor = 0;
    }
     fclose(arquivo);
    break;
}




default:{
printf("acao nao implementada, rode o programa e tente novamente. \n\n");
    break;
}

}
apagarNos(a->raiz);
free(a);



getchar();
printf("Pressione qualquer tecla para finalizar.\n\n");
getchar();




    return 0;
}