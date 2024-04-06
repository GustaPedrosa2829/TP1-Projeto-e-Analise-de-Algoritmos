#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <limits.h>

#define MAX_N 100005
#define MAX_M 200005

typedef struct {
    int vertice;
    int distancia;
} NoFila;

typedef struct {
    int destino;
    int custo;
} Aresta;

typedef struct {
    Aresta *arestas;
    int num_arestas;
} Vertice;

typedef struct {
    Vertice vertices[MAX_N];
    int num_vertices;
} Grafo;

void inicializarGrafo(Grafo *grafo, int num_vertices);
void adicionarAresta(Grafo *grafo, int origem, int destino, int custo);
void dijkstra(Grafo *grafo, int inicio, int *distancias);
void dfs(Grafo *grafo, int vertice, int destino, int distancia, int *visitado, int *caminhos, int k, int *distancias, int *caminhos_mais_curto);
int compara(const void *a, const void *b);
void imprimirTempos(double tempo_cpu, double tempo_clock);
