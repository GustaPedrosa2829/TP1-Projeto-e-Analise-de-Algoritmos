#include <stdio.h>
#include <stdlib.h>
#include "magicos.h"

void lerEntrada(const char *nomeArquivo, DadosEntrada *dados) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d %d %d", &dados->n, &dados->m, &dados->k);

    dados->voos = malloc(dados->m * sizeof(Voo));

    for (int i = 0; i < dados->m; i++) {
        fscanf(arquivo, "%d %d %d", &dados->voos[i].a, &dados->voos[i].b, &dados->voos[i].c);
    }

    fclose(arquivo);
}

void dijkstra(int n, int inicio, int *distancias, int *visitado, int *result, int **grafo) {
    for (int i = 0; i < n; i++) {
        distancias[i] = INT_MAX;
        visitado[i] = 0;
    }

    distancias[inicio] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = INT_MAX;
        int minIndex;

        for (int j = 0; j < n; j++) {
            if (!visitado[j] && distancias[j] <= min) {
                min = distancias[j];
                minIndex = j;
            }
        }

        visitado[minIndex] = 1;

        for (int j = 0; j < n; j++) {
            if (!visitado[j] && grafo[minIndex][j] != -1 &&
                distancias[minIndex] != INT_MAX &&
                distancias[minIndex] + grafo[minIndex][j] < distancias[j]) {
                distancias[j] = distancias[minIndex] + grafo[minIndex][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        result[i] = distancias[i];
    }
}

void processarRotas(DadosEntrada *dados, int *result) {
    int **grafo = (int **)malloc(dados->n * sizeof(int *));
    for (int i = 0; i < dados->n; i++) {
        grafo[i] = (int *)malloc(dados->n * sizeof(int));
        for (int j = 0; j < dados->n; j++) {
            grafo[i][j] = -1;  // Inicializando o grafo com -1 (sem conexão)
        }
    }

    for (int i = 0; i < dados->m; i++) {
        grafo[dados->voos[i].a - 1][dados->voos[i].b - 1] = dados->voos[i].c;
    }

    int *distancias = (int *)malloc(dados->n * sizeof(int));
    int *visitado = (int *)malloc(dados->n * sizeof(int));

    dijkstra(dados->n, 0, distancias, visitado, result, grafo);

    for (int i = 0; i < dados->n; i++) {
        free(grafo[i]);
    }
    free(grafo);
    free(distancias);
    free(visitado);
}

void escreverSaida(const char *nomeArquivo, int *resultado) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dados->k; i++) {
        fprintf(arquivo, "%d ", resultado[i]);
    }

    fclose(arquivo);
}
