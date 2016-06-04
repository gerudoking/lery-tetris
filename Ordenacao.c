#include "Ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

void ordena(FILE* arq){
  Jogador *vetor;
  int totalRegistros = 0;
  int i;
  
  while(!feof(arq)){
    fseek(arq, sizeof(char)*12, SEEK_CUR);
    totalRegistros++;
  }
  
  fseek(arq, 0, SEEK_SET);
  
  vetor = (Jogador*) malloc(sizeof(Jogador)*totalRegistros);
  
  for(i = 0; i < totalRegistros; i++){
    fscanf(arq, "%s", vetor[i].nome);
    fscanf(arq, "%d", &(vetor[i].pontos));
  }
  
  quicksort(vetor, 0, totalRegistros - 1);
}
