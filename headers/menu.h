#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    char nome[15];
    int pontuacao;
    int vidas;
} PLAYER;

// Definição de Funções
    // Funções de Updates/Atualizações
    void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox, Sound SomOpcaoMenu, Sound SomSelecinaOpcao);
    void UpdateVoltar(int *prox);
    void UpdateMario(Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Botao, bool *apertado, Sound SomPulo);
    void Anima(Vector2 *var_animaMa, Vector2 *var_animaBo, bool isFalling, bool isJumping, bool *apertado);
    void UpdateMenuCarregar(Rectangle opcoes[6], bool *flag, int *n_arq, Color opcoes_cores[6], int *n_fase, int *prox, Sound SomSelecinaOpcao);

    // Funções de Arquivos
    void Highscores(PLAYER melhores[5], bool *flag);
    Vector2 CarregaSave(Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9], PLAYER *jogador);
    Vector2 CarregaFase(int n_fase, Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9]);
    void SalvarJogo(int n_fase, Rectangle Mario, PLAYER jogador);
    bool Entrada(PLAYER *jogador, char *nome, int *letterCount);

    // Funções de Desenhar
    void DrawMenu(Texture textura_logo, Vector2 posicao_logo, Font fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]);
    void DrawAjuda(Font fonte);
    void DrawSobre(Font fonte);
    void DrawTela(PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle *Mario,bool lado, int n_fase, Rectangle Canos[9], int ind_animaMa, int ind_animaBo, int n_plat);
    void DrawScores(PLAYER melhores[5], Font fonte);
    void DrawEntrada(char nome[16], int letterCount);
    void DrawCarregar(Rectangle opcoes[6], int n_arq, Color opcoes_cores[6]);
    void InitSpread(Texture2D sheet);

#endif // MENU_H
