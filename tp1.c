#include "tp1.h"
#include <limits.h>

void inicializarGrafo(Grafo *grafo, int num_vertices) {
    grafo->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        grafo->vertices[i].num_arestas = 0;
        grafo->vertices[i].arestas = NULL;
    }
}

void adicionarAresta(Grafo *grafo, int origem, int destino, int custo) {
    Aresta nova_aresta;
    nova_aresta.destino = destino;
    nova_aresta.custo = custo;

    grafo->vertices[origem].num_arestas++;
    grafo->vertices[origem].arestas = realloc(grafo->vertices[origem].arestas, 
                                    sizeof(Aresta) * grafo->vertices[origem].num_arestas);
    grafo->vertices[origem].arestas[grafo->vertices[origem].num_arestas - 1] = nova_aresta;
}

void dijkstra(Grafo *grafo, int inicio, int *distancias) {
    int visitado[MAX_N] = {0};

    for (int i = 0; i < grafo->num_vertices; i++) {
        distancias[i] = INT_MAX;
    }

    distancias[inicio] = 0;

    while (1) {
        int vertice_atual = -1;
        int menor_distancia = INT_MAX;
        for (int i = 0; i < grafo->num_vertices; i++) {
            if (!visitado[i] && distancias[i] < menor_distancia) {
                vertice_atual = i;
                menor_distancia = distancias[i];
            }
        }

        if (vertice_atual == -1)
            break;

        visitado[vertice_atual] = 1;

        for (int i = 0; i < grafo->vertices[vertice_atual].num_arestas; i++) {
            Aresta aresta = grafo->vertices[vertice_atual].arestas[i];
            if (distancias[aresta.destino] > distancias[vertice_atual] + aresta.custo) {
                distancias[aresta.destino] = distancias[vertice_atual] + aresta.custo;
            }
        }
    }
}

int compara(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return *x - *y;
}

void imprimirTempos(double tempo_cpu, double tempo_clock) {
    printf("Tempo de CPU: %f segundos\n", tempo_cpu);
    printf("Tempo de Relógio: %f segundos\n", tempo_clock);
}
