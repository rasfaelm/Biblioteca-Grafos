#ifndef GRAFO_H
#define GRAFO_H

typedef struct {
    int ordem;          // Número de vértices
    int tamanho;        // Número de arestas
    double **matriz;    // Matriz de adjacência/pesos
} Grafo;

/* Criação e destruição */
Grafo *criarGrafo(int ordem); 
void liberarGrafo(Grafo *grafo); 

/* Entrada de dados */
Grafo *lerGrafo(const char *nomeArquivo); 

/* Informações básicas */
int obterOrdem(const Grafo *grafo);
int obterTamanho(const Grafo *grafo);
double calcularDensidade(const Grafo *grafo);

/* Vizinhança e grau */
void listarVizinhos(const Grafo *grafo, int vertice); 
int obterGrau(const Grafo *grafo, int vertice); 

/* Vértices de articulação */
int ehArticulacao(const Grafo *grafo, int vertice);

/* Busca em largura */
void buscaLargura(const Grafo *grafo, int inicio);

/* Componentes conexas */
int contarComponentesConexas(const Grafo *grafo);
void listarComponentesConexas(const Grafo *grafo);

/* Ciclos */
int possuiCiclo(const Grafo *grafo);

/* Caminhos mínimos */
void caminhosMinimos(const Grafo *grafo, int origem);
void imprimirCaminho(int origem, int destino, const int *anterior);

#endif
