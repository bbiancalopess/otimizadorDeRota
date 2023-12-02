#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20 //quantidade de pontos do trajeto

//Funcao que imprime uma matriz no console
void imprimeMatriz(int matriz[MAX_SIZE][MAX_SIZE]){

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

//Funcao que imprime um vetor no console 
void imprimeVetor(int tamanho_vetor, int vetor[tamanho_vetor]){
    for (int i = 0; i < tamanho_vetor; i++) {
        printf("%d ", vetor[i]);
    }
}

//Funcao que pega os dados de um arquivo txt e cria a matriz correspondente
void txtToMatriz(char nome_file[50], int matriz[MAX_SIZE][MAX_SIZE]){
    FILE *arquivo;
    int linha, coluna, valor;

    
    //Define todos os valores da matriz como -1 para que, após definir a matriz com os valores do aruqivo txt, 
    //o valores que não estão definidos sejam -1, dizendo que não existe aquele caminho
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            matriz[i][j] = -1;
        }
    }

    arquivo = fopen(nome_file, "r"); //abre o arquivo na funcao ler

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo"); //retorna uma mensagem de erro caso a abertura nao seja mal executada
    }

    //enquanto sao encontrados 3 valores, a matriz eh preenchida
    while (fscanf(arquivo, "%d, %d, %d", &linha, &coluna, &valor) == 3) { 
        matriz[linha][coluna] = valor;
    }

    //fecha o arquivo
    fclose(arquivo);
}

//funcao que constroi a matriz custo (resolvemos criar uma funcao para isso pois utilizamos essa funcao mais de 1 vez no codigo, para nao poluir a main)
void geraMatrizCusto(int matriz[][MAX_SIZE], int distancia[][MAX_SIZE], int criminalidade[][MAX_SIZE], int transito[][MAX_SIZE]){
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            if(distancia[i][j] == -1 || criminalidade[i][j] == -1 || transito[i][j] == -1){             //se for encontrado o valor -1 em qualquer uma das matrizes 
                matriz[i][j] = -1;                                                                      //significa que aquele caminho nao existe
            } else {
                matriz[i][j] = distancia[i][j] + (3 * criminalidade[i][j]) + (2 * transito[i][j]);      //caso nao sejam encontrados -1's, calcula-se o custo daquela rota
                                                                                                        // a partir da equacao distancia + 3*criminalidade + 2*transito
            }            
        }
    }

    /*
    Explicacao dos pesos:
    - o transito tem um peso maior que a distancia, pois um lugar longe sem trânsito é tranquilo de ir, um perto com transito se torna longe
    - o fator criminalidade recebe o maior peso pois é melhor percorrer uma distancia um pouco maior ou um caminho com um pouco mais de transito do que passar por um lugar muito perigoso
    */
}

//funcao que acha a rota de menor custo a partir de um ponto inicial
int achaRota(int caminho[MAX_SIZE], int inicial, int custo[][MAX_SIZE]){

    int menor_valor, posicao = 0, index, soma_custo = 0;
    caminho[0] = inicial; //define o primeiro ponto do caminho otimizado sendo o ponto inicial passado

    do{
        menor_valor = 2147483647;  //define o menor valor de custo como o maior valor que cabe em um int para que o primeiro valor analisado seja tomado como menor valor  

        //percorre a linha do ponto de origem atual buscando o ponto de menor custo para que seja o sucedente do ponto atual
        for(int i = 0; i < MAX_SIZE; i++){
            if(custo[inicial][i] != -1 && custo[inicial][i] <= menor_valor){ //verifica se o custo eh diferente de -1 e menor que o menor custo encontrado anteriormente 
                menor_valor = custo[inicial][i];                             //caso seja menor, substitui a variavel com o atual menor valor e o armazena o index
                index = i;                                                   //para que ele seja adicionado ao vetor de caminho otimizado e para que seja utilizado como o
            }                                                                //proximo valor de origem a ser analisado no loop
        }

        posicao++; //contador de quantas posicoes ja foram encontradas
        caminho[posicao] = index; //armazena o ponto encontrado no vetor
        soma_custo += menor_valor; //realiza a soma do custo total do caminho otimizado para que seja utilizado como metodo de comparacao com os
                                   //caminhos encontrados partindo dos demais pontos iniciais

        //define a coluna e a linha do ponto de origem atual como -1, significando que aquele ponto ja foi visitado e nao deve ser encontrado novamente
        //na busca pelos proximos pontos do caminho
        for (int i = 0; i < MAX_SIZE; i++){
            custo[i][inicial] = -1;
            custo[inicial][i] = -1;
        }

        inicial = index;//define o ponto encontrado para sucedente do ponto atual como o novo ponto atual para que, ao rodar o loop, seja encontrado 
                        //o seu sucedente
        
    } while(posicao < MAX_SIZE-1);//roda o loop enquanto nao tenham sido encontrados os 19 sucedentes, considerando a matriz com 20 pontos e o ponto inicial sendo fixo

    return soma_custo; //retorna o valor total de custo do caminho otimizado 
}

void main(){

    int distancia[MAX_SIZE][MAX_SIZE], criminalidade[MAX_SIZE][MAX_SIZE], transito[MAX_SIZE][MAX_SIZE];
    int custo[MAX_SIZE][MAX_SIZE];
    int caminho[MAX_SIZE], custo_rota_otimizada = 2147483647, caminho_otimizado[MAX_SIZE], inicial;
                           //define-se tambem a variavel com um alto valor para que o primeiro encontrado possa ser utilizado na comparacao

    // pega os dados das matrizes dos fatores
    txtToMatriz("distancia.txt", distancia);
    txtToMatriz("criminalidade.txt", criminalidade);
    txtToMatriz("transito.txt", transito);

    //gera a matriz custo a partir das outras matrizes
    geraMatrizCusto(custo, distancia, criminalidade, transito);

    //iteriza por todos os pontos utilizando-os como ponto inicial do caminho otimizado para encontrar a melhor opcao
    for(int i = 0; i < MAX_SIZE; i++){
        int retorno = achaRota(caminho, i, custo); //acha a rota otimizada com o valor i como inicial e armazena a rota no vetor caminho

        if(retorno < custo_rota_otimizada){        //checa se o custo da rota com o valor inicial sendo i eh menor que o antigo armazenado
            custo_rota_otimizada = retorno;        //se sim, atualiza a variavel de comparacao
            for(int j = 0; j < MAX_SIZE; j++){     //iteriza pelo caminho otimizado encontrado para i como inicial 
                caminho_otimizado[j] = caminho[j]; //e substitui o antigo caminho otimizado pelo atual de menor custo
            }
        }

        geraMatrizCusto(custo, distancia, criminalidade, transito); //como na funcao de achar a rota modificamos a matriz substituindo os valores por -1, 
    }                                                               //agora precisamos gerá-la novamente para que seja utilizada na proxima analise

    //imprime a rota com menor custo
    printf("o caminho otimizado eh: \n"); 
    imprimeVetor(MAX_SIZE, caminho_otimizado);
    printf("\n");
}