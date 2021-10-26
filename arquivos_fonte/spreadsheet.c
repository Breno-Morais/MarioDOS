#include "../headers/sprites.h"

void InitSpread(void){
        Texture2D sheet  = LoadTexture("imagens/sprite_geral.png");

        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Sprite 1
            DrawTexturePro(sheet, MarioSprite1.esq[0], MarioSprite1.esq[1], (Vector2){0,0}, 0, WHITE);
            DrawRectangleLines(MarioSprite1.esq[1].x, MarioSprite1.esq[1].y, MarioSprite1.esq[1].width, MarioSprite1.esq[1].height, RED);


        EndDrawing();
        //----------------------------------------------------------------------------------

        UnloadTexture(sheet);
}
