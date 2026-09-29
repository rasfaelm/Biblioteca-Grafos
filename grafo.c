#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Cria um grafo com 'ordem' vértices.
 * A matriz será inicializada com zero.
 */
Grafo *criarGrafo(int ordem){
    Grafo *grafo;
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
    /* TODO: implementar. */
    return NULL;
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
    /* TODO: implementar. */
}

/* Retorna o grau de um vértice. */
int obterGrau(const Grafo *grafo, int vertice){
    /* TODO: implementar. */
    return 0;
}

/* Verifica se um vértice é de articulação. */
int ehArticulacao(const Grafo *grafo, int vertice){
    /* TODO: implementar. */
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
    /* TODO: implementar. */
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
