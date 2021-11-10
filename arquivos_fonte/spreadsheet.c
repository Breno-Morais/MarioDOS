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


void DrawTela(PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle Mario, bool lado, int n_fase){
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

            // Desenha a pontuação e a fase
                const char *pont = TextFormat("Pontos: %d", jogador.pontuacao);
                DrawTextEx(fonte, pont, (Vector2){150, 10}, 30, 1, GREEN);

                const char *fase = TextFormat("Fase: %d", n_fase);
                DrawTextEx(fonte, fase, (Vector2){1200-250, 10}, 30, 1, GREEN);

            // Desenha as plataformas
                for(i=0; i<n_ind.y; i++){
                    DrawTextureTiled(sheet, Plt_Marrom, Plts[i], origem, 0, 3.125, WHITE);
                }

            // Desenha o botão power
                DrawTexturePro(sheet, Botao_POW1, Botao, origem, 0, WHITE);

            // Desenha o Chão
                DrawTexturePro(sheet, Chao.src, Chao.pos, origem, 0, WHITE);

            // Desenha Mario
                Rectangle mario_atual;
                if(lado){
                    mario_atual = MarioSprite1.dir;
                } else mario_atual = MarioSprite1.esq;

                DrawTexturePro(sheet, mario_atual, Mario, origem, 0, WHITE);

            // Desenha os Canos
                for(i=0; i<n_ind.x; i++){
                    // Passa por cada cano e verifica de que lado ele está
                    if(cano_pos[i].x >= 600){
                        // Se o cano estiver na direita, verifica se ele é um cano de saída ou de retorno
                        if(cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de saída virado para esquerda
                                Rectangle Cano = {cano_pos[i].x-10, cano_pos[i].y-45, Cano_Curvo_esq.width*escala,  Cano_Curvo_esq.height*escala};
                                DrawTexturePro(sheet, Cano_Curvo_esq, Cano, origem, 0, WHITE);
                        } else {
                                // Aqui ele desenha o cano de entrada virado pra esquerca
                                Rectangle Cano = {cano_pos[i].x, cano_pos[i].y, Cano_Reto_esq.width*escala,  Cano_Reto_esq.height*escala};
                                DrawTexturePro(sheet, Cano_Reto_esq, Cano, origem, 0, WHITE);
                        }

                    } else
                        // Se o cano estiver na esquerda, verifica se ele é um cano de saída ou de retorno
                        if (cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de saída virado para direita
                                Rectangle Cano = {cano_pos[i].x-196, cano_pos[i].y-45, Cano_Curvo_dir.width*escala,  Cano_Curvo_dir.height*escala};
                                DrawTexturePro(sheet, Cano_Curvo_dir, Cano, origem, 0, WHITE);
                        } else {
                                // Aqui ele desenha o cano de entrada virado para direita
                                Rectangle Cano = {cano_pos[i].x-118, cano_pos[i].y, Cano_Reto_dir.width*escala,  Cano_Reto_dir.height*escala};
                                DrawTexturePro(sheet, Cano_Reto_dir, Cano, origem, 0, WHITE);
                    }
                }


        EndDrawing();
        //----------------------------------------------------------------------------------
}
