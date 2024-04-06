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

    // Adiciona a aresta de origem para destino
    grafo->vertices[origem].num_arestas++;
    grafo->vertices[origem].arestas = realloc(grafo->vertices[origem].arestas, 
                                    sizeof(Aresta) * grafo->vertices[origem].num_arestas);
    grafo->vertices[origem].arestas[grafo->vertices[origem].num_arestas - 1] = nova_aresta;
}

void dijkstra(Grafo *grafo, int inicio, int *distancias) {
    int visitado[MAX_N] = {0};

    // Inicializa todas as distâncias como infinito
    for (int i = 0; i < grafo->num_vertices; i++) {
        distancias[i] = INT_MAX;
    }
    distancias[inicio] = 0;

    // Algoritmo de Dijkstra
    for (int i = 0; i < grafo->num_vertices; i++) {
        // Encontra o vértice não visitado com a menor distância
        int vertice_atual = -1;
        for (int j = 0; j < grafo->num_vertices; j++) {
            if (!visitado[j] && (vertice_atual == -1 || distancias[j] < distancias[vertice_atual])) {
                vertice_atual = j;
            }
        }

        // Verificação adicional
        if (vertice_atual == -1 || distancias[vertice_atual] == INT_MAX) {
            // Se não houver mais vértices alcançáveis, saia do loop
            break;
        }

        // Marca o vértice atual como visitado
        visitado[vertice_atual] = 1;

        // Relaxamento das arestas do vértice atual
        for (int j = 0; j < grafo->vertices[vertice_atual].num_arestas; j++) {
            Aresta aresta = grafo->vertices[vertice_atual].arestas[j];
            if (distancias[aresta.destino] > distancias[vertice_atual] + aresta.custo) {
                distancias[aresta.destino] = distancias[vertice_atual] + aresta.custo;
            }
        }
    }
}

void dfs(Grafo *grafo, int vertice, int destino, int distancia, int *visitado, int *caminhos, int k, int *distancias, int *caminhos_mais_curto) {
    if (vertice == destino) {
        caminhos_mais_curto[*caminhos] = distancia;
        (*caminhos)++;
        return;
    }

    visitado[vertice] = 1;

    for (int i = 0; i < grafo->vertices[vertice].num_arestas; i++) {
        Aresta aresta = grafo->vertices[vertice].arestas[i];
        if (!visitado[aresta.destino]) {
            dfs(grafo, aresta.destino, destino, distancia + aresta.custo, visitado, caminhos, k, distancias, caminhos_mais_curto);
        }
    }

    visitado[vertice] = 0;
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

