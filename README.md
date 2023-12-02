Programa que visa buscar a rota com melhor custo entre pontos seguindo as instrucoes abaixo:


Desafios relacionados ao planejamento eficiente de rotas para otimizar o transporte de bens, serviços ou pessoas 
tem  sua  devida  importância  nos  dias  atuais.  Resolver  problemas  como  esse  permite  que  as  pessoas  possam 
chegar aos lugares de forma mais rápida, empresas economize recursos financeiros ou que criem rotas através de caminhos mais seguros.   

Neste  trabalho,  você  deverá  criar  um  algoritmo  que  seja  capaz  de  propor  uma  rota  para  um  problema  de 
planejamento  de  rota.  Siga  os  passos  propostos  para  que  o  problema  possa  ser  resolvido  corretamente.  

 a) Contexto:  No  contexto  do  problema  do  planejamento  de  transporte,  os  pontos  ou  nós  representam  as 
cidades/bairros/locais  que um determinado  meio de  transporte  ou pessoa  precisa visitar em sua rota.  A 
solução desejada consiste em encontrar a ordem mais eficiente de visitar todos os pontos, de modo que o custo seja o menor possível.  

 b) Leitura  de  arquivo:  foram  disponibilizados  três  arquivos contendo informações  sobre distância, 
congestionamento e criminalidade encontrados nos caminhos entre os pontos. O arquivo tem o seguinte formato: 
 
<origem>, <destino>, <metrica>   
Exemplo: 0,1,11 -> significa que do ponto 0 para o ponto 1 a distância é igual a 11  Fique  atento,  só  serão  disponibilizados  nesse  arquivo  os  caminhos  existentes  entre  os  pontos.  Alguns caminhos são inexistetes e precisarão de tratamento no seu algoritmo.    
  
c) Criação  da  matriz  custo:  Considerando  os  dados  contidos  nos  arquivos  disponibilizados,  crie  uma 
fórmula para combinar distância, congestionamento e criminalidade para preencher a sua matriz de custo de deslocamento entre os pontos.   

    1. O  exemplo  abaixo  mostra  que  o  custo  entre  o  ponto  de  origem  0  para  o 
    ponto de  destino 3 é  igual a  55.  Já o valor entre  o ponto de  origem 3 e  o ponto de  destino 2 é 
    igual a -1, pois neste caso não há uma rota disponível.    

                                            M = 0  11 30 55 
                                                11 0  51 30
                                                30 51  0 -1
                                                55 30 -1  0

    2. Você  poderá  criar  qualquer fórmula  para  obter  um  custo considerando  as 
    informações de distância, congestionamento e criminalidade. Será necessário justificar a fórmula 
    criada. Exemplo: distancia²+congestionamento+2*criminalidade.   
                                               
d) Representação  de  uma  rota:  A  representação  de  uma  rota  para  esse  desafio  envolve  descrever  de 
maneira  sistemática  a  ordem  em  que  os  pontos  serão  visitados.  Uma  das  formas  mais  comuns  de 
representação  é  através  de  um  vetor  que  contém  a  sequência  de  pontos  (lugares)  a  serem  percorridos.  
  
Exemplo: Se tivermos 4 pontos (0, 1, 2, 3), uma possível representação de rota poderia ser V = [2, 1, 0, 3], indicando que o primeiro ponto da 
rota é o 2, depois 1, 0 e 3.       
    
e) Avaliação  de custo  de  uma  rota:  O  custo  de  uma  rota  poderá  ser obtido  combinando  as informações 
contidas  no  vetor  (V)  e  a  matriz  de  custo  (M).  Considere  os  valores  estabelecidos  nos  itens  anteriores 
para M e V. Assim sendo, temos que o custo da rota presente em V é dado por:  

V = [2, 1, 0, 3] 
Custo da Rota = M[2][1] + M[1][0] + M[0][3]              
Custo da Rota = 51 + 11 + 55 = 117        

f) Criando  rotas:  Use  a  criatividade  para  criar  um  algoritmo  que  seja  capaz  de  retornar  uma  rota 
otimizada para este problema. As restrições abaixo devem ser obedecidas: 

    1. Um ponto deve ser visitado somente uma vez 
    2. Todos os pontos devem ser visitados  


