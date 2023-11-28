#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

void imprimeMatriz(int matriz[MAX_SIZE][MAX_SIZE]){

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}



void main(){

    int n = 6;
    int teste[6] = {8, 2, 1, 0, 19, 3};

    int custo[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, 56},
                                     { 5, -1, 12,  4, 74},
                                     {84, 12, -1,  7, 23},
                                     {10,  4,  7, -1, 32},
                                     {56, 74, 23, 32, -1}};

    int reserva[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, 56},
                                       { 5, -1, 12,  4, 74},
                                       {84, 12, -1,  7, 23},
                                       {10,  4,  7, -1, 32},
                                       {56, 74, 23, 32, -1}};

    int caminho[MAX_SIZE] = {4, 1, 0, 3, 2}, caminho_otimizado[MAX_SIZE];
    int inicial = caminho[0], final = caminho[MAX_SIZE - 1];
    caminho_otimizado[0] = inicial;
    caminho_otimizado[MAX_SIZE - 1] = final;

    // imprimeMatriz(reserva);
    int x = reserva[inicial][0], acha_posicao = 0, index;

    imprimeMatriz(reserva);

    do{
        // roda pela linha e acha o menor caminho
        for(int i = 0; i < MAX_SIZE; i++){
            // printf("i = %d\n",i);
            // printf("custo[inicial][i] = %d\n",reserva[inicial][i]);
            // printf("x = %d\n",x);
            if(reserva[inicial][i] != -1 && reserva[inicial][i] < x && i != final){ 
                x = reserva[inicial][i];
                index = i;
                // printf("x alterado = %d\n",x);
            }
        }

        // conta quantos pontos já foram achados
        acha_posicao++;
        // adiciona o ponto ao caminho otimizado
        printf("acha_posicao = %d\n",acha_posicao);
        printf("index = %d\n",index);
        caminho_otimizado[acha_posicao] = index;
        // substitui por zero o caminho já percorrido
        for (int i = 0; i < MAX_SIZE; i++){
            reserva[i][inicial] = -1;
            reserva[inicial][i] = -1;
        }
        inicial = index;
        
        
        imprimeMatriz(reserva);


        //printf("x = %d | index = %d", x, index);
    } while(acha_posicao < MAX_SIZE-1);
    
    

}