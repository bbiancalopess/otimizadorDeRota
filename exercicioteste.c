#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 6

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


void main(){

    int n = 6;
    int teste[6] = {8, 2, 1, 0, 19, 3};

    int custo[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, 56, 11},
                                     { 5, -1, 12,  4, 74, 13},
                                     {84, 12, -1,  7, 23, 1},
                                     {10,  4,  7, -1, 32, 8},
                                     {56, 74, 23, 32, -1, 90},
                                     {11, 13,  1,  8, 90, -1}};

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, 56, 11},
                                     { 5, -1, 12,  4, 74, 13},
                                     {84, 12, -1,  7, 23, 1},
                                     {10,  4,  7, -1, 32, 8},
                                     {56, 74, 23, 32, -1, 90},
                                     {11, 13,  1,  8, 90, -1}};


    /*
    4 3 1

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, -1},
                                       { 5, -1, 12,  4, -1},
                                       {84, 12, -1,  7, -1},
                                       {10,  4,  7, -1, -1},
                                       {-1, -1, -1, -1, -1}};

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, -1, -1},
                                       { 5, -1, 12, -1, -1},
                                       {84, 12, -1, -1, -1},
                                       {-1, -1, -1, -1, -1},
                                       {-1, -1, -1, -1, -1}};

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, -1, -1},
                                       { 5, -1, 12, -1, -1},
                                       {84, 12, -1, -1, -1},
                                       {-1, -1, -1, -1, -1},
                                       {-1, -1, -1, -1, -1}};

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  -1, 84, -1, -1},
                                       { -1, -1, -1, -1, -1},
                                       {84, 12, -1, -1, -1},
                                       {-1, -1, -1, -1, -1},
                                       {-1, -1, -1, -1, -1}};
    
    */

    int caminho[MAX_SIZE] = {1, 5, 2, 3, 4, 0}, caminho_otimizado[MAX_SIZE];
    int inicial = caminho[0], final = caminho[MAX_SIZE - 1];
    caminho_otimizado[0] = inicial;
    caminho_otimizado[MAX_SIZE - 1] = final;

    // imprimeMatriz(reserva);
    int menor_valor, posicao = 0, index;

    for (int i = 0; i < MAX_SIZE; i++){
            reserva[i][final] = -1;
            reserva[final][i] = -1;
    }



    imprimeMatriz(reserva);
    printf("#--------------------#\n");
    imprimeVetor(6, caminho);
    printf("\n#--------------------#\n");


    do{
        menor_valor = 99999999;
        printf("menor_valor  %d\n", menor_valor);
        printf("inicial = %d\n", inicial);
        //printf("final = %d\n", final);
        // roda pela linha e acha o menor caminho
        for(int i = 0; i < MAX_SIZE; i++){
            printf("i = %d\n", i);
            // printf("i = %d\n",i);
            // printf("custo[inicial][i] = %d\n",reserva[inicial][i]);
            // printf("x = %d\n",x);
            if(reserva[inicial][i] != -1 && reserva[inicial][i] <= menor_valor){ 
                
                menor_valor = reserva[inicial][i];
                index = i;
                printf("entrei | index = %d | menor_valor = %d\n", index, menor_valor);
                // printf("x alterado = %d\n",x);
            }
        }

        // conta quantos pontos já foram achados
        posicao++;
        // adiciona o ponto ao caminho otimizado
        printf("posicao = %d\n",posicao);
        printf("index = %d\n",index);
        printf("menor_valor  %d\n", menor_valor);
        caminho_otimizado[posicao] = index;
        // substitui por zero o caminho já percorrido
        printf("zerou em %d\n", inicial);
        for (int i = 0; i < MAX_SIZE; i++){
            reserva[i][inicial] = -1;
            reserva[inicial][i] = -1;
        }
        inicial = index;
        
        printf("--------------------\n");
        imprimeMatriz(reserva);


        //printf("x = %d | index = %d", x, index);
        printf("#--------------------#\n");
    } while(posicao < MAX_SIZE-2);

    //caminho_otimizado[0] = caminho[0];
    //caminho_otimizado[MAX_SIZE - 1] = caminho[MAX_SIZE - 1];
    
    imprimeVetor(6, caminho_otimizado);

}