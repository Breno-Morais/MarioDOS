#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#define NUM_OPCOES 7
#define TAM_FONTE 25

void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox);
void DrawMenu(Texture *textura_logo, Vector2 *posicao_logo, Font *fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]);


#endif // MENU_H
