#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void exibirMenu() {
    printf("\n========================================\n");
    printf("          MENU - GRAFO\n");
    printf("========================================\n");
    printf("1. Informacoes do grafo\n");
    printf("2. Listar vizinhos de um vertice\n");
    printf("3. Obter grau de um vertice\n");
    printf("4. Verificar vertice de articulacao\n");
    printf("5. Busca em largura (BFS)\n");
    printf("6. Contar componentes conexas\n");
    printf("7. Listar componentes conexas\n");
    printf("8. Verificar se possui ciclo\n");
    printf("9. Caminhos minimos\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Opcao: ");
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nDigite qualquer tecla para continuar...");
    getchar();
    getchar();
    limparTela();
}

int main() {

    Grafo *grafo = NULL;
    char nomeArquivo[256];
    int opcao;
    int vertice;
    int origem;

    printf("Digite o nome do arquivo do grafo: ");
    scanf("%255s", nomeArquivo);

    grafo = lerGrafo(nomeArquivo);

    if (grafo == NULL) {
        printf("Nao foi possivel carregar o grafo.\n");
        return 1;
    }

    do {
        exibirMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("\n--- Informacoes do grafo ---\n");
                printf("Ordem: %d\n", obterOrdem(grafo));
                printf("Tamanho: %d\n", obterTamanho(grafo));
                printf("Densidade: %.4f\n", calcularDensidade(grafo));
                break;
            case 2:
                printf("\n--- Listar vizinhos ---\n");
                printf("Digite o vertice: ");
                scanf("%d", &vertice);
                listarVizinhos(grafo, vertice);
                break;
            case 3:
                printf("\n--- Grau do vertice ---\n");
                printf("Digite o vertice: ");
                scanf("%d", &vertice);
                printf("Grau do vertice %d: %d\n", vertice, obterGrau(grafo, vertice));
                break;
            case 4:
                printf("\n--- Vertice de articulacao ---\n");
                printf("Digite o vertice: ");
                scanf("%d", &vertice);
                if (ehArticulacao(grafo, vertice)) {
                    printf("O vertice %d e um vertice de articulacao.\n", vertice);
                } else {
                    printf("O vertice %d nao e um vertice de articulacao.\n", vertice);
                }
                break;
            case 5:
                printf("\n--- Busca em largura (BFS) ---\n");
                printf("Digite o vertice inicial: ");
                scanf("%d", &vertice);
                buscaLargura(grafo, vertice);
                break;
            case 6:
                printf("\n--- Componentes conexas ---\n");
                printf("Quantidade de componentes conexas: %d\n", contarComponentesConexas(grafo));
                break;
            case 7:
                printf("\n--- Listar componentes conexas ---\n");
                listarComponentesConexas(grafo);
                break;
            case 8:
                printf("\n--- Ciclos ---\n");
                if (possuiCiclo(grafo)) {
                    printf("O grafo possui ciclo.\n");
                } else {
                    printf("O grafo nao possui ciclo.\n");
                }
                break;
            case 9:
                printf("\n--- Caminhos minimos ---\n");
                printf("Digite o vertice de origem: ");
                scanf("%d", &origem);
                caminhosMinimos(grafo, origem);
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
    pausar();
    } while (opcao != 0);
    liberarGrafo(grafo);
    return 0;
}