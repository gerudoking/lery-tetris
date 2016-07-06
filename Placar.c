#include "Placar.h"

int cria_placar(void){
  FILE* arq;
  int i;
  
  arq = fopen("placar.txt", "r");
  if (arq == NULL){
    arq = fopen("placar.txt", "w");
    
    for(i = 0; i < 5; i++)
    	fprintf(arq, "AAAAA     0\n");
  }
  
  fclose(arq);
  return 0;
}

int atualiza_placar(int pontuacao){
  FILE* arq;
  Jogador j;
  int i, checador;
  
	if (pontuacao > 99999)

  j.pontos = pontuacao;
  mvprintw(1, 1, "Digite o seu nome");
  mvprintw(2, 1, "em ate 5 letras:");
  mvscanw(3, 1, "%s", j.nome);
  
  arq = fopen("placar.txt", "r+");
	if(arq == NULL){
		perror ("Erro ao abrir placar.txt. Arquivo nao existe.\n");
		return 1;
  }
 	
	for(i = 0; i < MAX_PLACAR; i++){
    fseek(arq, sizeof(char)*5, SEEK_CUR);
    fscanf(arq, "%d", &checador);
    if(j.pontos > checador){
      fseek(arq, (sizeof(char))*(-11), SEEK_CUR);
      
      fprintf(arq, "%s ", j.nome);
			if (ferror(arq)){
				perror("Incapaz de se escrever no arquivo placar.txt.\n");
				return 2;
			}
  
      //As seguintes checagens garantem que o campo pontos tenha tamanho fixo;
      if(j.pontos < 100) fprintf(arq, "  ");
      if(j.pontos < 1000) fprintf(arq, " ");
      if(j.pontos < 10000) fprintf(arq, " ");
      fprintf(arq, "%d", j.pontos);
      
      break;
    }
  }
  
  fclose(arq);
  return 0;
}

int mostra_placar(void){
  FILE* arq;
  int i;
  char vetor[13];
  
  arq = fopen("placar.txt", "r");
	if(arq == NULL){
		perror ("Erro ao abrir placar.txt. Arquivo nao existe.\n");
		return 1;
  }
  
  for(i = 0; i < MAX_PLACAR; i++){
    fread(vetor, sizeof(char), 12, arq);
		if(ferror(arq)){
			perror("Arquvio placar.txt vazio!");
			return 2;
		}
		vetor[12] = '\0';
		mvprintw(2+(1*i), 2, "%s", vetor);
  }
  
  fclose(arq);
  return 0;
}
