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

void main(){

    // matrizes dos fatores
    int distancia[MAX_SIZE][MAX_SIZE], criminalidade[MAX_SIZE][MAX_SIZE], transito[MAX_SIZE][MAX_SIZE];
    // matriz custo
    int custo[MAX_SIZE][MAX_SIZE], reserva[MAX_SIZE][MAX_SIZE];

    // pega os dados das matrizes dos fatores
    txtToMatriz("distancia.txt", distancia);
    txtToMatriz("criminalidade.txt", criminalidade);
    txtToMatriz("transito.txt", transito);

    // Gera a matriz custo
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            if(distancia[i][j] == -1 || criminalidade[i][j] == -1 || transito[i][j] == -1){
                custo[i][j] = -1;
                reserva[i][j] = -1;
            } else {
                custo[i][j] = calculaCusto(distancia, criminalidade, transito, i, j);
                reserva[i][j] = calculaCusto(distancia, criminalidade, transito, i, j);
            }            
        }
    }
    // caminho inicial e caminho otimizado
    int caminho[MAX_SIZE] = {1, 5, 2, 3, 4, 0,7,8,9,10,11,12,14,15,16,17,18,19,6,14}, caminho_otimizado[MAX_SIZE];
    //variáveis utilizadas para achar o caminho otimizado
    int inicial = caminho[0], final = caminho[MAX_SIZE - 1], menor_valor, posicao = 0, index;

    printf("Digite um valor de 0 a 19 para ser o ponto inicial da rota: ");
    scanf("%d",&inicial);
    printf("Digite um valor de 0 a 19 para ser o ponto final da rota: ");
    scanf("%d",&final);

    caminho_otimizado[0] = inicial;
    caminho_otimizado[MAX_SIZE - 1] = final;

    // coloca como -1 a posicao final do caminho na matriz para que essa nao seja levada em consideracao no algoritmo
    for (int i = 0; i < MAX_SIZE; i++){
            reserva[i][final] = -1;
            reserva[final][i] = -1;
    }

    // imprimeMatriz(reserva);
    // printf("#--------------------#\n");
    // imprimeVetor(MAX_SIZE, caminho);
    // printf("\n#--------------------#\n");

    do{
        menor_valor = 99999999;
        // printf("menor_valor  %d\n", menor_valor);
        // printf("inicial = %d\n", inicial);
        //printf("final = %d\n", final);
        // roda pela linha e acha o menor caminho
        for(int i = 0; i < MAX_SIZE; i++){
            // printf("i = %d\n", i);
            // printf("i = %d\n",i);
            // printf("custo[inicial][i] = %d\n",reserva[inicial][i]);
            // printf("x = %d\n",x);
            if(reserva[inicial][i] != -1 && reserva[inicial][i] <= menor_valor){ 
                
                menor_valor = reserva[inicial][i];
                index = i;
                // printf("entrei | index = %d | menor_valor = %d\n", index, menor_valor);
                // printf("x alterado = %d\n",x);
            }
        }

        // conta quantos pontos já foram achados
        posicao++;
        // adiciona o ponto ao caminho otimizado
        // printf("posicao = %d\n",posicao);
        // printf("index = %d\n",index);
        // printf("menor_valor  %d\n", menor_valor);
        caminho_otimizado[posicao] = index;
        // substitui por zero o caminho já percorrido
        // printf("zerou em %d\n", inicial);
        // coloca a posicao que acabou de ser analisada como -1 para deixar claro que nao se pode voltar para a posicao antiga
        for (int i = 0; i < MAX_SIZE; i++){
            reserva[i][inicial] = -1;
            reserva[inicial][i] = -1;
        }

        // define a atual posicao como a que acabou de ser encontrada para que se ache a proxima posicao
        inicial = index;
        
        // printf("--------------------\n");
        // imprimeMatriz(reserva);


        //printf("x = %d | index = %d", x, index);
        // printf("#--------------------#\n");
    } while(posicao < MAX_SIZE-2);

    //caminho_otimizado[0] = caminho[0];
    //caminho_otimizado[MAX_SIZE - 1] = caminho[MAX_SIZE - 1];
    
    printf("o caminho otimizado eh: \n");
    imprimeVetor(MAX_SIZE, caminho_otimizado);
    printf("\n");
}