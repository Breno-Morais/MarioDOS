#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <unistd.h>
#include <stdio.h>
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

//Definição Tartaruga
typedef struct stc_turtle{
        Rectangle turtleRec;
        int sentido, estado, level; //estado:0-invulneravel; 1-vulneravel; 2-morto.
        float speed;
        bool fall, isThere;
}TURTLE;

//Definição Caranguejo
typedef struct stc_crab{
    Rectangle crabRec;
    int sentido, estado, level; //estado:0-invulneravel; 1-furioso; 2-vulneravel; 3-morto.
    float speed;
    bool fall, isThere;
}CRAB;

// Definição de Funções
void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox, Sound SomOpcaoMenu, Sound SomSelecinaOpcao);
void DrawMenu(Texture textura_logo, Vector2 posicao_logo, Font fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]);
void DrawAjuda(Font fonte);
void DrawSobre(Font fonte);
void DrawTela(CRAB crab[20], int n_crab, TURTLE turtle[20], int n_turtle, PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle *Mario,bool lado, int n_fase, Rectangle Canos[9], int ind_animaMa, int ind_animaBo);
void UpdateVoltar(int *prox);
void InitSpread(Texture2D sheet);
void Highscores(PLAYER melhores[5], bool *flag);
void DrawScores(PLAYER melhores[5], Font fonte);
Vector2 CarregaFase(int *n_turtle,int *n_crab, int *tempo_espera, int n_fase, Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9]);
void UpdateMario(int *hit_cooldown_current, int hit_cooldown_max, int *botao_current, Vector3 cano_pos[9], Rectangle Canos[9], Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Chao, Rectangle Botao, bool *apertado, Sound SomPulo);
void InitEnemies(int *crab_atual, int *turtle_atual,int n_crab, int n_turtle, CRAB crab[20], TURTLE turtle[20], bool *flag_cano, int *cano_atual, Vector2 n_ind, Vector3 cano_pos[9], Rectangle Canos[9]);
void UpdateTurtle(CRAB crab[20], int *crab_atual, int n_crab, bool *apertado, int *hit_cooldown_current, int hit_cooldown_max, int *turtle_atual, int n_turtle, int tempo_espera, int *tempo_atual, TURTLE turtle[20], Vector2 n_ind, Rectangle Canos[9], Vector3 cano_pos[9],Rectangle Plts[10], Rectangle Mario, Rectangle Chao);
void Anima(int *framesCounter, int *ind_animaMa, int *ind_animaBo, bool isFalling, bool isJumping);
void SalvarJogo(int n_fase, Rectangle Mario, PLAYER jogador);
Vector2 CarregaSave(Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9], PLAYER *jogador);

#endif // MENU_H
