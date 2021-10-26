#include "../headers/menu.h"

void UpdateMenu(Color cores_opcoes[], Rectangle posicao_opcoes[], int *prox, Sound SomOpcaoMenu, Sound SomSelecinaOpcao){
        // Checa colisão entre o mouse e as opções
        int i,atual, anterior; // O atual e o anterior eu estou usando como flags para tocar o som
        bool colisao;

        for(i=0; i < NUM_OPCOES; i++){
            colisao = CheckCollisionPointRec(GetMousePosition(), posicao_opcoes[i]);
            // Se o mouse estiver em cima de uma opção, ela muda de cor
            if(colisao){
                atual = i;
                cores_opcoes[i] = SKYBLUE;

                // Se a opção que houve a colisão é diferente da anterior, então toca o som
                if(anterior!=atual) PlaySound(SomOpcaoMenu);

                // Se o mouse clicar na opção
                if(IsMouseButtonDown(0)){
                    cores_opcoes[i] = YELLOW;
                    // Devolva qual foi a opção escolhida
                    *prox = i;
                    PlaySound(SomSelecinaOpcao);
                }
                anterior = i;

            } else cores_opcoes[i] = WHITE;

        }
}

void DrawMenu(Texture textura_logo, Vector2 posicao_logo, Font fonte, const char *opcoes[], Rectangle posicao_opcoes[], Color cores_opcoes[]){
        int i;
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            // Desenha a logo
            DrawTextureEx(textura_logo, posicao_logo, 0, 4, WHITE);

            // Desenha as opções
            for(i=0; i < NUM_OPCOES; i++){
                DrawTextRec(fonte, opcoes[i], posicao_opcoes[i], TAM_FONTE, 2, false, cores_opcoes[i]);
            }

            /*
                // Linhas guia, usei para calibrar as posições dos itens
                DrawLine(0, TelaMeio.y, TelaLargura, TelaMeio.y, GRAY);
                DrawLine(TelaMeio.x, 0, TelaMeio.x, TelaAltura, GRAY);
            */

        EndDrawing();
        //----------------------------------------------------------------------------------
}
