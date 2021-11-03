#include "../headers/sprites.h"
#include "../headers/menu.h"

<<<<<<< Updated upstream
void InitSpread(void){
        Texture2D sheet  = LoadTexture("imagens/sprite_geral.png");
=======
void InitSpread(Texture2D sheet){
        Rectangle atual = Mario_Vida;
        Rectangle atual_pos = {0, 0, atual.width*escala, atual.height*escala};
>>>>>>> Stashed changes

        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Sprite 1
<<<<<<< Updated upstream
            DrawTexturePro(sheet, MarioSprite1.esq[0], MarioSprite1.esq[1], (Vector2){0,0}, 0, WHITE);
            DrawRectangleLines(MarioSprite1.esq[1].x, MarioSprite1.esq[1].y, MarioSprite1.esq[1].width, MarioSprite1.esq[1].height, RED);

=======
            DrawTexturePro(sheet, atual, atual_pos, origem, 0, WHITE);
            DrawRectangleLinesEx(atual_pos, 1, RED);
>>>>>>> Stashed changes

        EndDrawing();
        //----------------------------------------------------------------------------------
}
<<<<<<< Updated upstream
=======

void DrawTela(PLAYER jogador, Texture sheet){
        int i;

        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Desenha os simbolos da vida
            for(i=0; i<jogador.vidas; i++){
                DrawTexturePro(sheet, Mario_Vida, (Rectangle){10+(Mario_Vida.width*escala)*i, 10, Mario_Vida.width*escala, Mario_Vida.height*escala}, origem, 0, WHITE);
            }

            // Desenha o Chão
            DrawTexturePro(sheet, Chao.src, Chao.pos, origem, 0, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
}
>>>>>>> Stashed changes
