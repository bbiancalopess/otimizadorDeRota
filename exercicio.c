#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

/*
Para iniciar eu precisava de uma maneira ágil de montar as matrizes de transito, criminalidade e distancia.
Para isso, criei a matriz que abre o arquivo txt, lê linha por linha, e atribui o valor à posicao dita.
*/
void txtToMatriz(char nome_file[50], int matriz[MAX_SIZE][MAX_SIZE]){
    FILE *arquivo;
    int linha, coluna, valor;

    /* 
    Define todos os valores da matriz como -1 para que, após definir a matriz com os valores do aruqivo txt, 
    o valores que não estão definidos sejam -1, dizendo que não existe aquele caminho
    */
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            matriz[i][j] = -1;
        }
    }

    arquivo = fopen(nome_file, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }

    // Leitura do arquivo e preenchimento da matriz
    while (fscanf(arquivo, "%d, %d, %d", &linha, &coluna, &valor) == 3) { //enquanto acha os 3 valores
        matriz[linha][coluna] = valor;
    }

    // Fechar o arquivo
    fclose(arquivo);
}

void imprimeMatriz(int matriz[MAX_SIZE][MAX_SIZE]){

    printf("[");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("{");
        for (int j = 0; j < MAX_SIZE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("}\n");
    }
    printf("]\n");
}

void imprimeVetor(int tamanho_vetor, int vetor[tamanho_vetor]){
    printf("[");
    for (int i = 0; i < tamanho_vetor; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\n");
}

int calculaCusto(int distancia[MAX_SIZE][MAX_SIZE], int criminalidade[MAX_SIZE][MAX_SIZE], int transito[MAX_SIZE][MAX_SIZE], int linha, int coluna){
    int soma = distancia[linha][coluna] + (3 * criminalidade[linha][coluna]) + (2 * transito[linha][coluna]);

    /*
    Explicacao dos pesos:
    - o transito tem um peso maior que a distancia, pois um lugar longe sem trânsito é tranquilo de ir, um perto com transito se torna longe
    - o fator criminalidade recebe o maior peso pois é melhor percorrer uma distancia um pouco maior ou um caminho com um pouco mais de transito do que passar por um lugar muito perigoso
    */

   return soma;
}

void main(){

    int distancia[MAX_SIZE][MAX_SIZE];
    txtToMatriz("distancia.txt", distancia);

    int criminalidade[MAX_SIZE][MAX_SIZE];
    txtToMatriz("criminalidade.txt", criminalidade);

    int transito[MAX_SIZE][MAX_SIZE];
    txtToMatriz("transito.txt", transito);

    int custo[MAX_SIZE][MAX_SIZE];

    int caminho[5] = {5, 17, 12, 1, 19};

    // Gera a matriz custo
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            if(distancia[i][j] == -1 || criminalidade[i][j] == -1 || transito[i][j] == -1){
                custo[i][j] = -1;
            } else {
                custo[i][j] = calculaCusto(distancia, criminalidade, transito, i, j);
            }            
        }
    }


    //printf("CAMINHO:\n");
    //imprimeVetor(5, caminho);

    // Imprimir a matriz (apenas para fins de verificação)
    //printf("DISTANCIA:\n");
    //imprimeMatriz(distancia);

    //printf("CRIMINALIDADE:\n");
    //imprimeMatriz(criminalidade);

    //printf("TRANSITO:\n");
    //imprimeMatriz(transito);

    //printf("CUSTO:\n");
    //imprimeMatriz(custo);

    //printf("caminho 1 -> 2 = %d", calculaCusto(distancia, criminalidade, transito, 1, 2));

}