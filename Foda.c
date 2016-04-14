#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

struct tipomatriz{
	int ocupado;
	int pardecor;
	char caracter;
};
typedef struct tipomatriz Tipomatriz;

struct tela{
	Tipomatriz matriz_gui[15][25];
};
typedef struct tela Tela;

typedef struct peca{
	int posicao_x; 
	int posicao_y;
	int tamanho;
	int orientacao;
	int cor;
}peca;

WINDOW* cria_nova_janela(int alt, int larg, int starty, int startx){
	WINDOW* janela_local;

	janela_local = newwin(alt, larg, starty, startx);
	box(janela_local, 0 , 0);
	
	wrefresh(janela_local);

	return janela_local;
}

void destroi_janela(WINDOW* janela_local){//Não sei se será necessária. É usada pra apagar as bordinhas.
	wborder(janela_local, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(janela_local);
	delwin(janela_local);
}

Tela* cria_tela(void){
	Tela* t;
	int i, j;

	t = (Tela*) malloc(sizeof(Tela));
	if(t == NULL) return NULL;
	
	for(i = 0; i<25; i++){
		for(j = 0; j<15; j++){
			(*t).matriz_gui[j][i].caracter = 32;
			(*t).matriz_gui[j][i].ocupado = 0;
			(*t).matriz_gui[j][i].pardecor = 1;
		}
	}

	return t;
}

int mostra_tela(Tela* t){
	int i, j;
	WINDOW* janela = cria_nova_janela(18,27,0,0);
	refresh();

	for(i = 0; i<15; i++){
		for(j = 0; j<25; j++){
			attrset(COLOR_PAIR((*t).matriz_gui[i][j].pardecor));
			mvaddch(i+1, j+1, (*t).matriz_gui[i][j].caracter);
		}
	}
	return 0;
}

int mostra_tela_inicial(void){
	Tela* t = cria_tela();
	mostra_tela(t);

	attrset(COLOR_PAIR(3));
	mvprintw(5, 7, "LERY TETRIS");
	attrset(COLOR_PAIR(2));
	mvprintw(10, 3, "Pressione qualquer");
	mvprintw(11, 3, "tecla para começar");

	free(t);
	return 0;
}

int mostra_tela_final(int pont){
	Tela* t = cria_tela();
	mostra_tela(t);

	attrset(COLOR_PAIR(3));
	mvprintw(5, 8, "GAME OVER");
	attrset(COLOR_PAIR(2));
	mvprintw(10, 4, "Sua pontuação é:");
	mvprintw(11, 12, "%d", pont);

	free(t);
	return 0;
}

peca* nova_peca(Tela* tela){
	int i;
	peca* a;
	if((*tela).matriz_gui[1][13].caracter=='X') return NULL;
	a=(peca*)malloc(sizeof(peca));
	(*a).tamanho=((rand() %3)+3);/*Escolhe um tamanho entre 3 e 5 para a peca*/
	(*a).orientacao=rand() %2;/*Define a orientação: 0 e vertical, 1 e horizontal*/
	(*a).cor=rand() %3;
	(*a).posicao_x=13;
	(*a).posicao_y=1;
		if((*a).orientacao==0){
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1+i][13].caracter='X';
			}
		}
		else{
			for(i=0;i<(*a).tamanho;i++){
				(*tela).matriz_gui[1][13+i].caracter='X';
			}
		}
	return a;
}

int move_peca_x(Tela* tela,peca* a,int direcao){/*vai receber um inteiro, que vai ser ou -1 ou 1, para mostrar se e para mover para a esquerda ou direita, respectivamente*/
	int i,flag=0,x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho;
		if((*a).orientacao==0){/*dependendo da orientacao da peca(vertical ou horizontal), agiremos diferentemente*/
			/*primeiro verificamos se a peca ja 								esta nos extremos da tela. Nesse caso, ela
								nao pode mover*/
			if(direcao==1){/*dependendo da direcao desejada do movimento, checaremos se ha parte de outra peca do lado adequado*/
				if(x==23) return 1;
				for(i=0;i<Tamanho;i++){
					if((*tela).matriz_gui[y+i][x+1].ocupado==1){/*aqui checamos se ha parte de outra peca ao lado da peca ativa. a flag sera usada para sair da funcao caso isso seja verdade*/
						flag=1;
						i=Tamanho;
					}
				}
				if(flag!=0) return 2;/*cada possivel caso de erro tem o seu retorno, permitindo
						acoes de acordo com cada caso*/
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter=' ';/*Temos que limpar o lugar que a peca ocupava antes de move-la*/
				}
				((*a).posicao_x)++;/*finalmente, a posicao na struct da peca e mudada*/			x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter='X';
				}
				return 5;
			}

			if(direcao==-1){
				if(x==1) return 1;
				for(i=0;i<Tamanho;i++){
					if((*tela).matriz_gui[y+i][x-1].ocupado==1){
						flag=1;
						i=Tamanho;
					}
				}
				if(flag!=0) return 3;
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter=' ';
				}
				((*a).posicao_x)--;/*finalmente, a posicao na struct da peca e mudada*/			x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y+i][x].caracter='X';
				}
				return 5;
			}
		return 3;/*nesse ponto, se a funcao nao terminou, alguma coisa deu errado*/
		}
		if((*a).orientacao==1){
			if(direcao==1){
				if(x+Tamanho==24) return 4;
				if((*tela).matriz_gui[y][x+Tamanho].ocupado==1) return 5;/*com pecas horizontais, so precisamos checar 2 posicoes*/
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter=' ';
				}
				((*a).posicao_x)++;
				x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter='X';
				}
				return 5;
			}
			if(direcao==-1){
				if(x==1) return 4;
				if((*tela).matriz_gui[y][x-1].ocupado==1) return 6;
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter=' ';
				}
				((*a).posicao_x)--;
				x=((*a).posicao_x);
				for(i=0;i<Tamanho;i++){
					(*tela).matriz_gui[y][x+i].caracter='X';
				}
				return 5;	
			}
			return 6;
		}
	return 8;
}

int move_peca_y(Tela* tela,peca* a){/*Como so podemos mover para baixo, nao necessitamos de entrada de inteiros*/
	int x=(*a).posicao_x,y=(*a).posicao_y,Tamanho=(*a).tamanho,i,flag=0;
	if((*a).orientacao==0){
		if(y+Tamanho==15) return 1; /*Caso a peca ja esteja no fim da tela, ela nao pode mover*/
		if((*tela).matriz_gui[y+Tamanho][x].ocupado==1) return 2; /*Caso exista parte de uma peca embaixo da peca, ela deve parar*/
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter=' ';
		}
		((*a).posicao_y)+=1;
		y=((*a).posicao_y);
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y+i][x].caracter='X';
		}
	return 5;
	}
	
	if((*a).orientacao==1){
		if(y==14) return 3;/*teste de encontro com borda da tela*/
		
		for(i=0;i<Tamanho;i++){
			if((*tela).matriz_gui[y+1][x+i].ocupado==1){
				flag=1;
				i=Tamanho;
			}
		}
		if(flag==1) return 4;
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y][x+i].caracter=' ';
		}
		((*a).posicao_y)+=1;
		y=((*a).posicao_y);
		for(i=0;i<Tamanho;i++){
			(*tela).matriz_gui[y][x+i].caracter='X';
		}
		return 5;
	}
	return 6;
}

void inicia_ncurses(){
	initscr();
	keypad(stdscr, TRUE);
 	start_color();
  	init_pair(1, COLOR_RED, COLOR_BLACK);//Trataremos o 1 como a cor vermelha nos caracteres
	init_pair(2, COLOR_BLUE, COLOR_BLACK);//E o 2 como azul
	init_pair(3, COLOR_GREEN, COLOR_BLACK);//por sua vez o 3 como verde
}

void finaliza_ncurses(){
	endwin();
}

void fixa_peca(Tela* tela, peca* tetromino){
	int x, y, i;
  
  x = tetromino->posicao_x;
  y = tetromino->posicao_y;
  
  for(i=0; i<tetromino->tamanho; i++){
    if(tetromino->orientacao == 1){
		tela->matriz_gui[y][x+i].ocupado = 1;
    	tela->matriz_gui[y][x+i].caracter = 'X';  
	}
    if(tetromino->orientacao == 0){
		tela->matriz_gui[y+i][x].ocupado = 1;
    	tela->matriz_gui[y+i][x].caracter = 'X';  
  	}
  }
  free(tetromino);
}

void deleta_linha(Tela* tela, int linha){
  int i, vert, hori;
  for (i=0; i<25; i++){
    tela->matriz_gui[linha][i].ocupado = 0;
    tela->matriz_gui[linha][i].caracter = 32;
  }
  for(vert = linha; vert > 0; vert--){
    for(hori=0; hori < 25; hori++){
      tela->matriz_gui[vert][hori].caracter = tela->matriz_gui[vert-1][hori].caracter; 
      tela->matriz_gui[vert][hori].ocupado = tela->matriz_gui[vert-1][hori].ocupado; 
    }  
  }
}

int movimento(Tela* tela, int* pontuacao){
  
	int locked, resultado, cont, cont2, fechou=0;
	peca* tetromino = nova_peca(tela);

	if(tetromino == NULL)
		return 1;

  	mostra_tela(tela);

	locked = 0;
	while(locked == 0) {
		switch(getch()) {
			case KEY_LEFT:
				move_peca_x(tela, tetromino, -1);
				break;
			case KEY_RIGHT:
				move_peca_x(tela, tetromino, 1);
				break;
			case KEY_DOWN:
				resultado = move_peca_y(tela, tetromino);
				break;
			case 'q':  // 'q' de "Quit"
      			return 1;
      			break;
      		default:
      			break;
		}
		mostra_tela(tela);
		refresh();

		if (resultado < 5){
			fixa_peca(tela, tetromino);
			locked = 1;
		}
	}
  
  	for(cont = 0; cont < 15; cont++){
	    fechou = 0;
	    for(cont2=0; cont2 < 25; cont2++){
	    	if(tela->matriz_gui[cont][cont2].caracter == 'X')
	      	fechou++;
  		}
    	if(fechou == 23){
    		pontuacao += 1; 
    		deleta_linha(tela, cont);
    	}
  	}
    
  return 0;
}

int main(){

	srand(time(NULL));

	int end = 0;
	int pontuacao = 0;
	
	inicia_ncurses();

	Tela* t = cria_tela();

	mostra_tela_inicial();
	getch();
  
	while(end == 0){
  	
  		mostra_tela(t);
  		//getch();
		end = movimento(t, &pontuacao);
	}

	mostra_tela_final(pontuacao*100);
	getch();

	free(t);
	finaliza_ncurses();

	return 0;
}
