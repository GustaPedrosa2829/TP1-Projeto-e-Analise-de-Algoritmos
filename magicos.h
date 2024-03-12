
#ifndef MAGICOS_H
#define MAGICOS_H

typedef struct {
    int a;
    int b;
    int c;
} Voo;

typedef struct {
    int n;
    int m;
    int k;
    Voo *voos;
} DadosEntrada;

void lerEntrada(const char *nomeArquivo, DadosEntrada *dados);
void dijkstra(int n, int inicio, int *distancias, int *visitado, int *result, int **grafo);
void processarRotas(DadosEntrada *dados, int *resultado);
void escreverSaida(const char *nomeArquivo, int *resultado);

#endif
