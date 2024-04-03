
#ifndef TP1_H
#define TP1_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

#define MAX_N 100005
#define MAX_M 200005

// Estrutura para representar uma aresta
typedef struct {
    int destino;
    int custo;
} Aresta;

// Estrutura para representar um nó na lista de adjacência
typedef struct {
    Aresta *arestas;
    int num_arestas;
} Vertice;

// Estrutura para representar o grafo
typedef struct {
    Vertice vertices[MAX_N];
    int num_vertices;
} Grafo;

void inicializarGrafo(Grafo *grafo, int num_vertices);
void adicionarAresta(Grafo *grafo, int origem, int destino, int custo);
void dijkstra(Grafo *grafo, int inicio, int *distancias);
int compara(const void *a, const void *b);
void imprimirTempos(double tempo_cpu, double tempo_clock);

#endif

