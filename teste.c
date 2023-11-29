#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

void imprimeMatriz(int matriz[MAX_SIZE][MAX_SIZE]){

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimeVetor(int tamanho_vetor, int vetor[tamanho_vetor]){
    for (int i = 0; i < tamanho_vetor; i++) {
        printf("%d ", vetor[i]);
    }
}

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

int calculaCusto(int distancia[MAX_SIZE][MAX_SIZE], int criminalidade[MAX_SIZE][MAX_SIZE], int transito[MAX_SIZE][MAX_SIZE], int linha, int coluna){
    int soma = distancia[linha][coluna] + (3 * criminalidade[linha][coluna]) + (2 * transito[linha][coluna]);

    /*
    Explicacao dos pesos:
    - o transito tem um peso maior que a distancia, pois um lugar longe sem trânsito é tranquilo de ir, um perto com transito se torna longe
    - o fator criminalidade recebe o maior peso pois é melhor percorrer uma distancia um pouco maior ou um caminho com um pouco mais de transito do que passar por um lugar muito perigoso
    */

   return soma;
}

void geraMatrizCusto(int matriz[][MAX_SIZE], int distancia[][MAX_SIZE], int criminalidade[][MAX_SIZE], int transito[][MAX_SIZE]){
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            if(distancia[i][j] == -1 || criminalidade[i][j] == -1 || transito[i][j] == -1){
                matriz[i][j] = -1;
            } else {
                matriz[i][j] = calculaCusto(distancia, criminalidade, transito, i, j);
            }            
        }
    }
}

int achaRota(int caminho[MAX_SIZE], int inicial, int custo[][MAX_SIZE]){

    int menor_valor, posicao = 0, index, soma_custo = 0;
    caminho[0] = inicial;

    do{
        menor_valor = 99999999;

        for(int i = 0; i < MAX_SIZE; i++){
            if(custo[inicial][i] != -1 && custo[inicial][i] <= menor_valor){ 
                menor_valor = custo[inicial][i];
                index = i;
            }
        }

        posicao++;
        caminho[posicao] = index;
        soma_custo += menor_valor;

        for (int i = 0; i < MAX_SIZE; i++){
            custo[i][inicial] = -1;
            custo[inicial][i] = -1;
        }

        inicial = index;
        
    } while(posicao < MAX_SIZE-1);

    return soma_custo;
}

void main(){

    int distancia[MAX_SIZE][MAX_SIZE], criminalidade[MAX_SIZE][MAX_SIZE], transito[MAX_SIZE][MAX_SIZE];
    int custo[MAX_SIZE][MAX_SIZE];
    int caminho[MAX_SIZE], custo_rota_otimizada = 9999999, caminho_otimizado[MAX_SIZE], inicial;

    geraMatrizCusto(custo, distancia, criminalidade, transito);

    // pega os dados das matrizes dos fatores
    txtToMatriz("distancia.txt", distancia);
    txtToMatriz("criminalidade.txt", criminalidade);
    txtToMatriz("transito.txt", transito);


    for(int i = 0; i < MAX_SIZE; i++){
        int retorno = achaRota(caminho, i, custo);

        if(retorno < custo_rota_otimizada){
            custo_rota_otimizada = retorno;
            for(int j = 0; j < MAX_SIZE; j++){
                caminho_otimizado[j] = caminho[j];
            }
        }

        geraMatrizCusto(custo, distancia, criminalidade, transito);
    }

    printf("o caminho otimizado eh: \n");
    imprimeVetor(MAX_SIZE, caminho_otimizado);
    printf("\n");
}