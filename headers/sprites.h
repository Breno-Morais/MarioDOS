#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

// Definição de Estruturas
typedef struct stc_sprite{
    Rectangle esq[2]; // O primeiro retângulo representa a posição do sprite no spritesheet, já o segundo retângulo é a posição na tela
    Rectangle dir[2]; // O primeiro retângulo representa a posição do sprite no spritesheet, já o segundo retângulo é a posição na tela
} SPRITE;

// Definição dos sprites
SPRITE MarioSprite1 = {{{3, 604, 16, 20}, {0, 0, 160, 200}}, {{3, 634, 16, 20}, {0, 0, 160, 200}}};
SPRITE MarioSprite2 = {{{22, 604, 12, 20}, {0, 0, 120, 200}}, {{22, 634, 12, 20}, {0, 0, 120, 200}}};
SPRITE MarioSprite3 = {{{36, 604, 14, 20}, {0, 0, 140, 200}}, {{36, 634, 14, 20}, {0, 0, 140, 200}}};
SPRITE MarioSprite4 = {{{53, 604, 14, 20}, {0, 0, 140, 200}}, {{53, 634, 14, 20}, {0, 0, 140, 200}}};
SPRITE MarioSprite5 = {{{73, 603, 15, 20}, {0, 0, 150, 200}}, {{73, 633, 15, 20}, {0, 0, 150, 200}}};
SPRITE MarioSprite6 = {{{93, 604, 15, 20}, {0, 0, 150, 200}}, {{93, 634, 15, 20}, {0, 0, 150, 200}}};
SPRITE MarioSprite7 = {{{113, 603, 16, 22}, {0, 0, 160, 220}}, {{113, 633, 16, 22}, {0, 0, 160, 220}}};
SPRITE MarioSprite8 = {{{129, 604, 15, 20}, {0, 0, 150, 200}}, {{129, 634, 15, 20}, {0, 0, 150, 200}}};

#endif // SPRITE_H
