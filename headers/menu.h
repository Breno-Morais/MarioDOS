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
#define N_OVER 7

// Defini��o Jogador
typedef struct stc_player{
    char nome[15];
    int pontuacao;
    int vidas;
} PLAYER;

//Defini��o Tartaruga
typedef struct stc_turtle{
        Rectangle turtleRec;
        int sentido, estado, level; //estado:0-invulneravel; 1-vulneravel; 2-morto.
        float speed;
        bool fall, isThere;
}TURTLE;

//Defini��o Caranguejo
typedef struct stc_crab{
    Rectangle crabRec;
    int sentido, estado, level; //estado:0-invulneravel; 1-furioso; 2-vulneravel; 3-morto.
    float speed;
    bool fall, isThere;
}CRAB;

// Defini��o de Fun��es
    // Fun��es de Updates/Atualiza��es
    void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox, Sound SomOpcaoMenu, Sound SomSelecinaOpcao);
    void UpdateVoltar(int *prox);
    Vector2 CarregaFase(int *n_turtle,int *n_crab, int *tempo_espera, int n_fase, Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9]);
    void Anima(Vector2 *var_animaMa, Vector2 *var_animaBo, Vector2 var_animaTar[20], Vector2 var_animaCar[20], bool isFalling, bool isJumping, bool *apertado, int n_turtle, TURTLE turtle[20], CRAB crab[20], int n_crab, Rectangle *Mario, bool lado);
    void UpdateMenuCarregar(Rectangle opcoes[6], bool *flag, int *n_arq, Color opcoes_cores[6], int *n_fase, int *prox, Sound SomSelecinaOpcao);
    void InitEnemies(int *crab_atual, int *turtle_atual,int n_crab, int n_turtle, CRAB crab[20], TURTLE turtle[20], bool *flag_cano, int *cano_atual, Vector2 n_ind, Vector3 cano_pos[9], Rectangle Canos[9]);
    int UpdateTurtle(int n_fase, Sound SomMorte, Sound SomVirei, PLAYER *jogador, CRAB crab[20], int *crab_atual, int n_crab, bool *apertado, int *hit_cooldown_current, int hit_cooldown_max, int *turtle_atual, int n_turtle, int tempo_espera, int *tempo_atual, TURTLE turtle[20], Vector2 n_ind, Rectangle Canos[9], Vector3 cano_pos[9],Rectangle Plts[10], Rectangle Mario, bool *dano, int *mario_invun);
    void UpdateMario(int *hit_cooldown_current, int hit_cooldown_max, int *botao_current, Vector3 cano_pos[9], Rectangle Canos[9], Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Botao, bool *apertado, bool *apertado_anima, Sound SomPulo);
    void GanhouPerdeu(PLAYER *jogador, int *vitoria, int *n_fase, bool *flag, int *prox, bool *perdeu);

    // Fun��es de Arquivos
    void Highscores(PLAYER melhores[5], bool *flag);
    Vector2 CarregaSave(Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9], PLAYER *jogador, TURTLE turtle[20], int *n_turtle);
    Vector2 CarregaFase(int *n_turtle,int *n_crab, int *tempo_espera, int n_fase, Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9]);
    void SalvarJogo(int n_fase, Rectangle Mario, PLAYER jogador, int n_turtle, TURTLE turtle[20]);
    bool Entrada(PLAYER *jogador, char *nome, int *letterCount);

    // Fun��es de Desenhar
    void DrawMenu(Texture textura_logo, Vector2 posicao_logo, Font fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]);
    void DrawAjuda(Font fonte);
    void DrawSobre(Font fonte);
    void DrawTela(Vector2 var_animaCar[20], CRAB crab[20], int n_crab, bool dano, int mario_invun, TURTLE turtle[20],int n_turtle, PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle *Mario, bool lado, int n_fase, Rectangle Canos[9], int ind_animaMa, int ind_animaBo, int n_plat, Vector2 var_animaTar[20]);
    void DrawScores(PLAYER melhores[5], Font fonte);
    void DrawEntrada(char nome[16], int letterCount);
    void DrawCarregar(Rectangle opcoes[6], int n_arq, Color opcoes_cores[6]);
    void InitSpread(Texture2D sheet);
    void DrawFinal(Texture sheet, int *counter, int *prox, bool perdeu);
    void UpdateGameOver(PLAYER *jogador, PLAYER melhores[5], bool *flag_arq, bool *flag_final);


#endif // MENU_H
