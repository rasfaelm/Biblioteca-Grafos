#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Cria um grafo com 'ordem' vértices.
 * A matriz será inicializada com zero.
 */
Grafo *criarGrafo(int ordem){
    Grafo *grafo;
    grafo->ordem=ordem,
    grafo->tamanho=0;
    grafo->matriz=(double**)malloc(ordem*sizeof(double*)); 
    for(int i = 0; i < ordem; i++){ 
        grafo->matriz[i]=(double*)malloc(ordem*sizeof(double));}
    /* TODO: implementar. */
    return grafo;
}

/**
 * Libera toda a memória utilizada pelo grafo.
 */
void liberarGrafo(Grafo *grafo){
    
    if (grafo == NULL) {
        return;
    }

    if (grafo->matriz != NULL) {
        for (int i = 0; i < grafo->ordem; i++) {
            free(grafo->matriz[i]);
        }

        free(grafo->matriz);
    }

    free(grafo);
}

/**
 * Lê um grafo a partir do arquivo.
 *
 * Formato esperado:
 *
 * 6
 * 1 2 2.5
 * 1 4 4.0
 * ...
 */
Grafo *lerGrafo(const char *nomeArquivo){
    FILE *arquivo;
    int ordem,coluna,linha;  
    double peso;  
    arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nomeArquivo);
        return NULL; 
    }
    fscanf(arquivo,"%d",&ordem);
    Grafo *grafo = criarGrafo(ordem);
    while(fscanf(arquivo,"%d %d %lf",&linha,&coluna,&peso)!=EOF){
        grafo->matriz[coluna-1][linha-1]=peso;
        grafo->matriz[linha-1][coluna-1]=peso;
    }
    fclose(arquivo);
    return grafo;
}

/* Retorna a ordem do grafo. */
int obterOrdem(const Grafo *grafo){

    if (grafo == NULL) {
        return 0;
    }

    return grafo->ordem;
}

/* Retorna o tamanho do grafo. */
int obterTamanho(const Grafo *grafo){

    if (grafo == NULL) {
        return 0;
    }

    return grafo->tamanho;
}

/* Calcula a densidade do grafo. */
double calcularDensidade(const Grafo *grafo){
    /* TODO: implementar. */
    return 0.0;
}

/* Lista os vizinhos de um vértice. */
void listarVizinhos(const Grafo *grafo, int vertice){

    if (grafo == NULL) {
        printf("Grafo invalido.\n");
        return;
    }

    if (vertice < 1 || vertice > grafo->ordem) {
        printf("Vertice invalido.\n");
        return;
    }

    vertice--;

    printf("Vizinhos do vertice %d:\n", vertice + 1);

    int encontrou = 0;

    for (int i = 0; i < grafo->ordem; i++) {

        if (grafo->matriz[vertice][i] != 0) {

            printf("%d ", i + 1);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum");
    }

    printf("\n");
}

/* Retorna o grau de um vértice. */
int obterGrau(const Grafo *grafo, int vertice){
    int grau = 0;
    for (int i = 0; i<grafo->ordem; i++){
        if(grafo->matriz[vertice][i]!=0){
            grau+=1;
        }
    }
    return grau;
}

/* Verifica se um vértice é de articulação. */
int ehArticulacao(const Grafo *grafo, int vertice){

    if (grafo == NULL) {
        return 0;
    }

    if (vertice < 1 || vertice > grafo->ordem) {
        return 0;
    }

    vertice--;

    int n = grafo->ordem;

    int *visitado = calloc(n, sizeof(int));
    int *fila = malloc(n * sizeof(int));

    if (visitado == NULL || fila == NULL) {

        free(visitado);
        free(fila);

        return 0;
    }

    int componentesAntes = 0;

    int inicio = 0;
    int fim = 0;

    for (int i = 0; i < n; i++) {

        if (!visitado[i]) {

            componentesAntes++;

            inicio = 0;
            fim = 0;

            fila[fim] = i;
            fim++;

            visitado[i] = 1;

            while (inicio < fim) {

                int atual = fila[inicio];
                inicio++;

                for (int j = 0; j < n; j++) {

                    if (grafo->matriz[atual][j] != 0 &&
                        !visitado[j]) {

                        visitado[j] = 1;

                        fila[fim] = j;
                        fim++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
    }

    int componentesDepois = 0;

    for (int i = 0; i < n; i++) {

        if (i == vertice) {
            continue;
        }

        if (!visitado[i]) {

            componentesDepois++;

            inicio = 0;
            fim = 0;

            fila[fim] = i;
            fim++;

            visitado[i] = 1;

            while (inicio < fim) {

                int atual = fila[inicio];
                inicio++;

                for (int j = 0; j < n; j++) {

                    if (j == vertice) {
                        continue;
                    }

                    if (grafo->matriz[atual][j] != 0 &&
                        !visitado[j]) {

                        visitado[j] = 1;

                        fila[fim] = j;
                        fim++;
                    }
                }
            }
        }
    }

    free(visitado);
    free(fila);

    if (componentesDepois > componentesAntes) {
        return 1;
    }

    return 0;
}

/* Executa busca em largura (BFS). */
void buscaLargura(const Grafo *grafo, int inicio){
    /* TODO: implementar. */
}

/* Retorna a quantidade de componentes conexas. */
int contarComponentesConexas(const Grafo *grafo){
    /* TODO: implementar. */
    return 0;
}

/* Lista os vértices pertencentes a cada componente conexa. */
void listarComponentesConexas(const Grafo *grafo){
    /* TODO: implementar. */
}

/* Verifica se o grafo possui ciclo. */
int possuiCiclo(const Grafo *grafo){

    if (grafo == NULL) {
        return 0;
    }

    int n = grafo->ordem;

    int *visitado = calloc(n, sizeof(int));
    int *pai = malloc(n * sizeof(int));
    int *fila = malloc(n * sizeof(int));

    if (visitado == NULL ||pai == NULL ||fila == NULL) {

        free(visitado);
        free(pai);
        free(fila);

        return 0;
    }

    for (int i = 0; i < n; i++) {
        pai[i] = -1;
    }

    for (int i = 0; i < n; i++) {

        if (!visitado[i]) {

            int inicio = 0;
            int fim = 0;

            fila[fim] = i;
            fim++;

            visitado[i] = 1;

            while (inicio < fim) {

                int atual = fila[inicio];
                inicio++;

                for (int j = 0; j < n; j++) {

                    if (grafo->matriz[atual][j] == 0) {
                        continue;
                    }

                    if (!visitado[j]) {

                        visitado[j] = 1;
                        pai[j] = atual;

                        fila[fim] = j;
                        fim++;

                    } else if (pai[atual] != j) {

                        free(visitado);
                        free(pai);
                        free(fila);

                        return 1;
                    }
                }
            }
        }
    }

    free(visitado);
    free(pai);
    free(fila);

    return 0;
}

/* Calcula caminhos mínimos a partir de uma origem. */
void caminhosMinimos(const Grafo *grafo, int origem){
    /* TODO: implementar. */
}

/* Imprime um caminho utilizando o vetor de predecessores. */
void imprimirCaminho(int origem, int destino, const int *anterior){
    /* TODO: implementar. */
}