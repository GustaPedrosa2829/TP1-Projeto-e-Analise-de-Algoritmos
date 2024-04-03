#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo_entrada\n", argv[0]);
        return 1;
    }

    struct rusage uso_inicio_cpu, uso_fim_cpu;
    struct timeval inicio_clock, fim_clock;

    // Início da medição do tempo de CPU
    getrusage(RUSAGE_SELF, &uso_inicio_cpu);

    // Início da medição do tempo de relógio
    gettimeofday(&inicio_clock, NULL);

    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        printf("Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    int n, m, k;
    fscanf(arquivo, "%d %d %d", &n, &m, &k);

    Grafo grafo;
    inicializarGrafo(&grafo, n);

    // Leitura das arestas
    for (int i = 0; i < m; i++) {
        int a, b, c;
        fscanf(arquivo, "%d %d %d", &a, &b, &c);
        adicionarAresta(&grafo, a - 1, b - 1, c);
    }

    fclose(arquivo);

    // Executa o algoritmo de Dijkstra
    int distancias[MAX_N];
    dijkstra(&grafo, 0, distancias);

    // Ordena as distâncias
    qsort(distancias, n, sizeof(int), compara);

    // Imprime as k menores distâncias
    for (int i = 0; i < k; i++) {
        printf("%d ", distancias[i]);
    }
    printf("\n");

    // Fim da medição do tempo de CPU
    getrusage(RUSAGE_SELF, &uso_fim_cpu);

    // Fim da medição do tempo de relógio
    gettimeofday(&fim_clock, NULL);

    // Cálculo dos tempos
    double tempo_cpu = (uso_fim_cpu.ru_utime.tv_sec - uso_inicio_cpu.ru_utime.tv_sec) +
                        (uso_fim_cpu.ru_utime.tv_usec - uso_inicio_cpu.ru_utime.tv_usec) / 1000000.0;

    double tempo_clock = (fim_clock.tv_sec - inicio_clock.tv_sec) +
                        (fim_clock.tv_usec - inicio_clock.tv_usec) / 1000000.0;

    // Impressão dos tempos
    imprimirTempos(tempo_cpu, tempo_clock);

    return 0;
}
