
#ifndef MST_H
#define MST_H

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
void processarRotas(DadosEntrada *dados, int *resultado);
void escreverSaida(const char *nomeArquivo, int *resultado);

#endif
