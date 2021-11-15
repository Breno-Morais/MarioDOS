#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

Vector2 origem = {0,0};
int escala = 4;

// Definição de Estruturas
//--------------------------------------------------------------------------------------
// Sprites do Mario e da Tartaruga, usam o retângulo usado na lógica do jogo
typedef struct stc_a_sprite{
    Rectangle esq; // O retângulo representa a posição do sprite no spritesheet
    Rectangle dir; // O retângulo representa a posição do sprite no spritesheet
} A_SPRITE;

// Sprites das contantes do jogo, como o chão e as vidas.
typedef struct stc_c_sprite{
    Rectangle src; // O retângulo que representa a posição do sprite no spritesheet
    Rectangle pos; // A posição do sprite na tela
} C_SPRITE;

//--------------------------------------------------------------------------------------

// Definição dos sprites do Mario
A_SPRITE MarioSprite1 = {{3, 604, 16, 20}, {3, 634, 16, 20}};
A_SPRITE MarioSprite2 = {{22, 604, 12, 20}, {22, 634, 12, 20}};
A_SPRITE MarioSprite3 = {{36, 604, 14, 20}, {36, 634, 14, 20}};
A_SPRITE MarioSprite4 = {{53, 604, 14, 20}, {53, 634, 14, 20}};
A_SPRITE MarioSprite5 = {{73, 603, 15, 20}, {73, 633, 15, 20}};
A_SPRITE MarioSprite6 = {{93, 604, 15, 20}, {93, 634, 15, 20}};
A_SPRITE MarioSprite7 = {{113, 603, 16, 22}, {113, 633, 16, 22}};
A_SPRITE MarioSprite8 = {{129, 604, 15, 20}, {129, 634, 15, 20}};

// Simbolo de vida
Rectangle Mario_Vida = {6, 591, 10, 8};

// Defini��o Lista de Anima��o
Rectangle M_And_Esq[6] = {{3, 604, 16, 20}, {22, 604, 12, 20}, {36, 604, 14, 20}, {53, 604, 14, 20}, {36, 604, 14, 20}};
Rectangle M_And_Dir[6] = {{3, 634, 16, 20}, {22, 634, 12, 20}, {36, 634, 14, 20}, {53, 634, 14, 20}, {36, 634, 14, 20}};

//--------------------------------------------------------------------------------------

// Definição dos Sprites do Nivel
C_SPRITE Chao = {{4, 292, 260, 20}, {-5, 616+(50), 1300, 100}};

// Definição dos Sprites com posições variáveis
Rectangle Cano_Reto_dir = {11, 215, 32, 18};
Rectangle Cano_Reto_esq = {11, 258, 32, 18};
Rectangle Cano_Curvo_esq = {51, 203, 49, 30};
Rectangle Cano_Curvo_dir = {50, 246, 49, 30};

// Definição dos Sprites do Botão Pow
Rectangle Botao_POW1 = {133, 243, 16, 16};
Rectangle Botao_POW2 = {153, 246, 16, 13};
Rectangle Botao_POW3 = {173, 250, 16, 9};

Rectangle Aperta_POW[3] = {{133, 243, 16, 16}, {153, 246, 16, 13}, {173, 250, 16, 9}};

// Tipos de Plataformas
Rectangle Plt_Azul = {112, 274, 7, 8};
Rectangle Plt_Marrom = {133, 266, 8, 8};

// Moedas
Rectangle Moeda_1 = {154, 138, 1, 11};
Rectangle Moeda_2 = {160, 138, 4, 11};
Rectangle Moeda_3 = {169, 138, 8, 11};

// Tela de Game Over
Rectangle GAME_OVER = {67, 150, 73, 9};

// Definição Inimigos
//--------------------------------------------------------------------------------------
// Sprites da Tartaruga andando
A_SPRITE TartA_1 = {{7, 332, 16, 16}, {7, 352, 16, 16}};
A_SPRITE TartA_2 = {{31, 333, 16, 15}, {31, 353, 16, 15}};
A_SPRITE TartA_3 = {{55, 333, 16, 15}, {55, 353, 16, 15}};
A_SPRITE TartA_4 = {{79, 332, 16, 16}, {79, 352, 16, 16}};
A_SPRITE TartA_5 = {{103, 333, 16, 15}, {103, 353, 16, 15}};

// Sprite da Tartaruga Caida
Rectangle TartC = {216, 337, 10, 10};

// Sprite da Tartaruga Levantando
A_SPRITE TartCL = {{234, 337, 12, 11}, {234, 337, 12, 11}};

// Sprite do Carangueigo
Rectangle Carg_1 = {6, 422, 16, 13};
Rectangle Carg_2 = {32, 422, 14, 13};
Rectangle Carg_3 = {56, 419, 16, 16};
Rectangle Carg_4 = {83, 419, 16, 16};
Rectangle Carg_5 = {109, 417, 15, 16};
Rectangle Carg_6 = {132, 418, 16, 15};
Rectangle Carg_7 = {161, 420, 16, 13};
//--------------------------------------------------------------------------------------

#endif // SPRITE_H
