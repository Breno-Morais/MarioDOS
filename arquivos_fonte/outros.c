#include "../headers/menu.h"

void DrawAjuda(Font fonte){
        char *texto_base="Texto base apenas para eu saber como ficara formatado";
        Vector2 posicao_texto;
        // Apenas formatação
        //----------------------------------------------------------------------------------
        posicao_texto.x = (LARGURA_TELA - MeasureTextEx(fonte, texto_base, 20, 2).x)/2;
        posicao_texto.y = (ALTURA_TELA - MeasureTextEx(fonte, texto_base, 20, 2).y)/2;
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Desenha o texto
            DrawTextEx(fonte, texto_base, posicao_texto, 20, 2, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
}

void DrawSobre(Font fonte){
        char *texto_base="Texto base apenas para eu saber como ficara formatado";
        Vector2 posicao_texto;
        posicao_texto.x = (LARGURA_TELA - MeasureTextEx(fonte, texto_base, 20, 2).x)/2;
        posicao_texto.y = (ALTURA_TELA - MeasureTextEx(fonte, texto_base, 20, 2).y)/2;
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Desenha o texto
            DrawTextEx(fonte, texto_base, posicao_texto, 20, 2, WHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
}

void UpdateVoltar(int *prox){
    if(IsKeyPressed(KEY_BACKSPACE)){
        *prox = N_MENU;
    }
}
