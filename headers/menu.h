#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <stdio.h>
#define ALTURA_TELA 700
#define LARGURA_TELA 1200
#define NUM_OPCOES 7
#define TAM_FONTE 25
#define N_MENU -1
#define N_NOVO 0
#define N_CONTINUAR 1
#define N_CARREGAR_MAPA 2
#define N_RANKING 3
#define N_AJUDA 4
#define N_SOBRE 5
#define N_SAIR 6

// Definição Jogador
typedef struct stc_player{
    char nome[10];
    int pontuacao;
    int vidas;
} PLAYER;

// Definição de Funções
void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox, Sound SomOpcaoMenu, Sound SomSelecinaOpcao);
void DrawMenu(Texture textura_logo, Vector2 posicao_logo, Font fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]);
void DrawAjuda(Font fonte);
<<<<<<< Updated upstream
void InitSpread(void);
=======
void DrawSobre(Font fonte);
void DrawTela(PLAYER jogador, Texture sheet);
void UpdateVoltar(int *prox);
void InitSpread(Texture2D sheet);
>>>>>>> Stashed changes

#endif // MENU_H
