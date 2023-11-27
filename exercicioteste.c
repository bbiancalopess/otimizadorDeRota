#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5
#define TAMANHO_VETOR_CAMINHO 4 

void main(){

    int n = 6;
    int teste[6] = {8, 2, 1, 0, 19, 3};

    int custo[MAX_SIZE][MAX_SIZE] = {{-1,  5, 84, 10, 56},
                                     { 5, -1, 12,  4, 74},
                                     {84, 12, -1,  7, 23},
                                     {10,  4,  7, -1, 32},
                                     {56, 74, 23, 32, -1}};

    int caminho[TAMANHO_VETOR_CAMINHO] = {4, 1, 0, 3};

    for(int i = 0; i < TAMANHO_VETOR_CAMINHO; i++){
        int posAtual = caminho[i];
        for(int k = 0; k < TAMANHO_VETOR_CAMINHO; k++){
            int posProxima = caminho[k];

            int caminhoDireto = custo[posAtual][posProxima];

            if(custo[posAtual][k] < custo[posAtual][posProxima]){
                
            }

            printf("posAtual = %d | posProxima = %d | caminhoDireto = %d\n", posAtual, posProxima, caminhoDireto);
        }
    }

    





}