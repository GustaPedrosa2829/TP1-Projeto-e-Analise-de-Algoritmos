#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "magicos.h"
#include <limits.h>

int main(int argc, char *argv[]) {
    char *arquivoEntrada = NULL;
    char *arquivoSaida = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                arquivoEntrada = optarg;
                break;
            case 'o':
                arquivoSaida = optarg;
                break;
            default:
                printf(stderr, "Uso: %s -i arquivo_entrada -o arquivo_saida\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf(stderr, "Ambos os arquivos de entrada e saída são necessários.\n");
        exit(EXIT_FAILURE);
    }

    DadosEntrada dados;
    lerEntrada(arquivoEntrada, &dados);

    int *resultado = malloc(dados.k * sizeof(int));
    processarRotas(&dados, resultado);
    escreverSaida(arquivoSaida, resultado);

    free(dados.voos);
    free(resultado);

    return 0;
}
