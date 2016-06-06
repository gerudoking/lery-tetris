#define MAX_PLACAR 5

struct tipojogador{
  char nome[6];
  int pontos;
};
typedef struct tipojogador Jogador;

void cria_placar(void);

void atualiza_placar(int pontuacao);

void mostra_placar(void);
