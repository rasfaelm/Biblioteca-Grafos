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
    if (grafo == NULL || grafo->ordem < 2) {
        return 0.0;
    }

    /* Densidade de grafo não direcionado: 2m / (n(n-1)) */
    return (2.0 * grafo->tamanho) / ((double)grafo->ordem * (grafo->ordem - 1));
}

/* Lista os vizinhos de um vértice. */
void listarVizinhos(const Grafo *grafo, int vertice){
    /* TODO: implementar. */
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
    /* TODO: implementar. */
    return 0;
}

/* Executa busca em largura (BFS). */
void buscaLargura(const Grafo *grafo, int inicio){
    if (grafo == NULL) {
        printf("Grafo invalido.\n");
        return;
    }

    inicio--;

    if (inicio < 0 || inicio >= grafo->ordem) {
        printf("Vertice inicial invalido.\n");
        return;
    }

    int *visitado = calloc(grafo->ordem, sizeof(int));
    int *pai = malloc(grafo->ordem * sizeof(int)); 
    int *fila = malloc(grafo->ordem * sizeof(int));

    if (visitado == NULL || pai == NULL || fila == NULL) {
        printf("Erro ao alocar memoria.\n");

        free(visitado);
        free(pai);
        free(fila);

        return;
    }

    for (int i = 0; i < grafo->ordem; i++) {
        pai[i] = -1;
    }

    int inicioFila = 0;
    int fimFila = 0;

    fila[fimFila++] = inicio;
    visitado[inicio] = 1;

    printf("\nBUSCA EM LARGURA \n");
    printf("Vertice inicial: %d\n", inicio + 1);
    printf("Sequencia de vertices visitados:\n");

    while (inicioFila < fimFila) {

        int atual = fila[inicioFila++];

        printf("%d ", atual + 1);

        for (int vizinho = 0; vizinho < grafo->ordem; vizinho++) {

            if (grafo->matriz[atual][vizinho] != 0 && !visitado[vizinho]) {
                visitado[vizinho] = 1;
                pai[vizinho] = atual;
                fila[fimFila++] = vizinho;
            }
        }
    }

    printf("\n");
    printf("\nArestas da arvore de busca em largura:\n");

    int encontrouArvore = 0;

    for (int v = 0; v < grafo->ordem; v++) {

        if (pai[v] != -1) {
            printf("(%d, %d)\n", pai[v] + 1, v + 1);
            encontrouArvore = 1;
        }
    }

    if (!encontrouArvore) {
        printf("Nenhuma aresta.\n");
    }

    printf("\nArestas que nao pertencem a arvore BFS:\n");

    int encontrouNaoArvore = 0;

    for (int u = 0; u < grafo->ordem; u++) {

        for (int v = u + 1; v < grafo->ordem; v++) {

            // Verifica se existe uma aresta entre u e v.
            if (grafo->matriz[u][v] != 0) {

                int pertenceArvore = (pai[u] == v || pai[v] == u);

                if (!pertenceArvore) {

                    printf("(%d, %d)\n", u + 1, v + 1);
                    encontrouNaoArvore = 1;
                }
            }
        }
    }

    if (!encontrouNaoArvore) {
        printf("Nenhuma aresta.\n");
    }

    // Verifica se existem vertices que nao foram alcançados.
    printf("\nVertices nao alcancados a partir de %d:\n", inicio + 1);

    int encontrouNaoAlcancado = 0;

    for (int i = 0; i < grafo->ordem; i++) {

        if (!visitado[i]) {
            printf("%d ", i + 1);
            encontrouNaoAlcancado = 1;
        }
    }

    if (!encontrouNaoAlcancado) {
        printf("Nenhum");
    }

    printf("\n");

    // Libera toda a memoria utilizada pela BFS.
    free(visitado);
    free(pai);
    free(fila);
}

/*
 * Função auxiliar (Roy): rotula cada vértice com o índice da sua
 * componente conexa em comp[] e retorna o número de componentes.
 * Escolhe um vértice ainda não rotulado e propaga o rótulo a todos os
 * vértices alcançáveis a partir dele. Custo O(n^2) com matriz.
 */
static int rotularComponentes(const Grafo *grafo, int *comp){
    int n = grafo->ordem, k = 0;
    int *pilha = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        comp[i] = -1;
    }

    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) {
            continue;
        }

        int topo = 0;
        comp[s] = k;
        pilha[topo++] = s;

        while (topo > 0) {
            int u = pilha[--topo];
            for (int v = 0; v < n; v++) {
                if (grafo->matriz[u][v] != 0.0 && comp[v] == -1) {
                    comp[v] = k;
                    pilha[topo++] = v;
                }
            }
        }
        k++;
    }

    free(pilha);
    return k;
}

/* Retorna a quantidade de componentes conexas. */
int contarComponentesConexas(const Grafo *grafo){
    if (grafo == NULL) {
        return 0;
    }

    int *comp = malloc(grafo->ordem * sizeof(int));
    int k = rotularComponentes(grafo, comp);
    free(comp);
    return k;
}

/* Lista os vértices pertencentes a cada componente conexa. */
void listarComponentesConexas(const Grafo *grafo){
    if (grafo == NULL) {
        return;
    }

    int *comp = malloc(grafo->ordem * sizeof(int));
    int k = rotularComponentes(grafo, comp);

    printf("Numero de componentes conexas: %d\n", k);
    for (int c = 0; c < k; c++) {
        printf("Componente %d: {", c + 1);
        int primeiro = 1;
        for (int v = 0; v < grafo->ordem; v++) {
            if (comp[v] == c) {
                printf("%s%d", primeiro ? "" : ", ", v + 1);
                primeiro = 0;
            }
        }
        printf("}\n");
    }

    free(comp);
}

/* Verifica se o grafo possui ciclo. */
int possuiCiclo(const Grafo *grafo){
    /* TODO: implementar. */
    return 0;
}

/* Calcula caminhos mínimos a partir de uma origem. */
void caminhosMinimos(const Grafo *grafo, int origem){

    if (grafo == NULL) {
        printf("Grafo invalido.\n");
        return;
    }

    origem--;

    if (origem < 0 || origem >= grafo->ordem) {
        printf("Vertice de origem invalido.\n");
        return;
    }

    int n = grafo->ordem;

    double *dist = malloc(n * sizeof(double));

    int *anterior = malloc(n * sizeof(int));

    int *visitado = calloc(n, sizeof(int));

    if (dist == NULL || anterior == NULL || visitado == NULL) {

        printf("Erro ao alocar memoria.\n");

        free(dist);
        free(anterior);
        free(visitado);

        return;
    }

    const double INFINITO = 1e308;

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        anterior[i] = -1;
    }

    dist[origem] = 0.0;

    for (int contador = 0; contador < n; contador++) {

        int atual = -1;
        double menorDistancia = INFINITO;

        for (int i = 0; i < n; i++) {

            if (!visitado[i] && dist[i] < menorDistancia) {
                menorDistancia = dist[i];
                atual = i;
            }
        }

        if (atual == -1) {
            break;
        }

        visitado[atual] = 1;

        for (int vizinho = 0; vizinho < n; vizinho++) {

            if (grafo->matriz[atual][vizinho] != 0 && !visitado[vizinho]) {

                double peso = grafo->matriz[atual][vizinho];

                if (dist[atual] + peso < dist[vizinho]) {
                    dist[vizinho] = dist[atual] + peso;
                    anterior[vizinho] = atual;
                }
            }
        }
    }

    // Mostra os resultados.
    printf("Vertice de origem: %d\n\n", origem + 1);

    for (int destino = 0; destino < n; destino++) {

        printf("Destino: %d\n", destino + 1);

        /*
         * Se a distancia continua infinita, significa que
         * nao existe caminho entre origem e destino.
         */
        if (dist[destino] == INFINITO) {

            printf("Distancia: infinito\n");
            printf("Caminho: inexistente\n");

        } else {

            printf("Distancia: %.2f\n", dist[destino]);
            printf("Caminho: ");
            imprimirCaminho(origem, destino, anterior);
            printf("\n");
        }

        printf("\n");
    }

    free(dist);
    free(anterior);
    free(visitado);
}

/* Imprime um caminho utilizando o vetor de predecessores. */
void imprimirCaminho(int origem, int destino, const int *anterior){

    if (destino == origem) {
        printf("%d", origem + 1);
        return;
    }

    if (anterior[destino] == -1) {
        printf("inexistente");
        return;
    }

    imprimirCaminho(origem, anterior[destino], anterior);

    printf(" -> %d", destino + 1);
}