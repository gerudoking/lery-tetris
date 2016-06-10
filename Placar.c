#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Placar.h"

void cria_placar(void){
  FILE* arq;
  
  arq = fopen("placar.txt", "r");
  if (arq == NULL)
    arq = fopen("placar.txt", "w");
  
  fclose(arq);
}

void atualiza_placar(int pontuacao){
  FILE* arq;
  Jogador j;
  int i, checador;
  
  j.pontos = pontuacao;
  mvprintw(1, 1, "Digite o seu nome");
  mvprintw(2, 1, "em ate 5 letras:");
  mvscanw(3, 1, "%s", j.nome);
  
  arq = fopen("placar.txt", "r+");
  
  for(i = 0; i < MAX_PLACAR; i++){
    fseek(arq, sizeof(char)*5, SEEK_CUR);
    fscanf(arq, "%d", &checador);
    if(j.pontos > checador){
      fseek(arq, (sizeof(char))*(-11), SEEK_CUR);
      
      fprintf(arq, "%s ", j.nome);
  
      //As seguintes checagens garantem que o campo pontos tenha tamanho fixo;
      if(j.pontos < 100) fprintf(arq, "  ");
      if(j.pontos < 1000) fprintf(arq, " ");
      if(j.pontos < 10000) fprintf(arq, " ");
      fprintf(arq, "%d", j.pontos);
      
      break;
    }
  }
  
  fclose(arq);
}

void mostra_placar(void){
  FILE* arq;
  int i;
  char vetor[13];
  
  arq = fopen("placar.txt", "r");
  
  for(i = 0; i < MAX_PLACAR; i++){
    fread(vetor, sizeof(char), 12, arq);
		vetor[12] = '\0';
		mvprintw(1*i, 2, "%s", vetor);
  }
  
  fclose(arq);
}
