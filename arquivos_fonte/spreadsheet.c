#include "../headers/sprites.h"
#include "../headers/menu.h"


void InitSpread(Texture2D sheet){
        int i = 0, x = 20, y = 200;
        Rectangle Plts[2] = {Plt_Azul, Plt_Marrom};

        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            DrawTextureTiled(sheet, Plts[i], (Rectangle){x, y, Plts[i].width*escala*10, Plts[i].height*escala}, (Vector2){0,0}, 0, escala, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
}


void DrawTela(PLAYER jogador, Texture sheet, Rectangle Plts[10], int n_plt, Vector2 botao_pos, Font fonte, Vector2 mario_pos, Vector3 cano_pos[5]){
        int i;

        //BeginDrawing();
        //----------------------------------------------------------------------------------

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);
;
            // Desenha os simbolos da vida
            for(i=0; i<jogador.vidas; i++){
                DrawTexturePro(sheet, Mario_Vida, (Rectangle){10+(Mario_Vida.width*escala)*i, 10, Mario_Vida.width*escala, Mario_Vida.height*escala}, origem, 0, WHITE);
            }

            // Desenha a pontuação
            const char *pont = TextFormat("Pontos %d", jogador.pontuacao);
            DrawTextEx(fonte, pont, (Vector2){100, 10}, 20, 1, WHITE);

            // Desenha as plataformas
            for(i=0; i<n_plt; i++){
                DrawTextureTiled(sheet, Plt_Marrom, Plts[i], origem, 0, 3.125, WHITE);
            }

            // Desenha o botão power
            DrawTexturePro(sheet, Botao_POW1, (Rectangle){botao_pos.x, botao_pos.y, Botao_POW1.width*escala, Botao_POW1.height*escala}, origem, 0, WHITE);

            // Desenha o Chão
            DrawTexturePro(sheet, Chao.src, Chao.pos, origem, 0, WHITE);


        //EndDrawing();
        //----------------------------------------------------------------------------------
}
