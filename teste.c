#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 5

void dijkstra(int custo[MAX_SIZE][MAX_SIZE], int n, int inicio, int destino) {
    int distancia[MAX_SIZE];
    int predecessores[MAX_SIZE];
    int visitado[MAX_SIZE];

    // Inicializa as distâncias, predecessores e nós como não visitados
    for (int i = 0; i < n; i++) {
        distancia[i] = INT_MAX;
        predecessores[i] = -1;
        visitado[i] = 0;
    }

    // A distância do nó de início para ele mesmo é 0
    distancia[inicio] = 0;

    // Encontrar o caminho mais curto para todos os nós
    for (int count = 0; count < n - 1; count++) {
        int minDistancia = INT_MAX;
        int u = -1;

        // Escolher o nó com a menor distância não processada
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && distancia[v] <= minDistancia) {
                minDistancia = distancia[v];
                u = v;
            }
        }

        // Marcar o nó escolhido como visitado
        visitado[u] = 1;

        // Atualizar as distâncias e predecessores dos vizinhos do nó escolhido
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && custo[u][v] != -1 && distancia[u] != INT_MAX && distancia[u] + custo[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + custo[u][v];
                predecessores[v] = u;
            }
        }
    }

    // Exibir a distância mínima e a rota
    printf("A menor distancia de %d para %d: %d\n", inicio, destino, distancia[destino]);

    // Construir e exibir a rota
    printf("Rota: %d ", destino);
    int precursor = predecessores[destino];
    while (precursor != -1) {
        printf("<- %d ", precursor);
        precursor = predecessores[precursor];
    }
    printf("\n");
}

int main() {
    int custo[MAX_SIZE][MAX_SIZE] = {{-1, 5, 84, 10, 56},
                                     {5, -1, 12, 4, 74},
                                     {84, 12, -1, 7, 23},
                                     {10, 4, 7, -1, 32},
                                     {56, 74, 23, 32, -1}};

    int inicio, destino;

    printf("Digite o ponto de inicio (0 a %d): ", MAX_SIZE - 1);
    scanf("%d", &inicio);

    printf("Digite o ponto de destino (0 a %d): ", MAX_SIZE - 1);
    scanf("%d", &destino);

    if (inicio < 0 || inicio >= MAX_SIZE || destino < 0 || destino >= MAX_SIZE) {
        printf("Pontos de inicio ou destino invalidos.\n");
        return 1;
    }

    dijkstra(custo, MAX_SIZE, inicio, destino);

    return 0;
}