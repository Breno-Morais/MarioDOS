#include "../headers/sprites.h"

void InitSpread(int x, int y){
        Texture2D sheet  = LoadTexture("imagens/sprite_geral.png");

        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Sprite 1
            DrawTexturePro(sheet, MarioSprite1.dir[0], MarioSprite1.dir[1], (Vector2){x,y}, 0, WHITE);
            DrawRectangleLines(MarioSprite1.dir[1].x, MarioSprite1.dir[1].y, MarioSprite1.dir[1].width, MarioSprite1.dir[1].height, RED);


        EndDrawing();
        //----------------------------------------------------------------------------------

        UnloadTexture(sheet);
}

//void DrawMario()
