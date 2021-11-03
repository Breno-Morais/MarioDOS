#include "../headers/sprites.h"
#include "../headers/menu.h"


void InitSpread(Texture2D sheet){
        Rectangle atual = Mario_Vida;
        Rectangle atual_pos = {0, 0, atual.width*escala, atual.height*escala};

        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            DrawTexturePro(sheet, atual, atual_pos, origem, 0, WHITE);
            DrawRectangleLinesEx(atual_pos, 1, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
}

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
