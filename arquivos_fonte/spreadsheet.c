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


void DrawTela(TURTLE turtle[10],int n_turtle, PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle *Mario, bool lado, int n_fase, Rectangle Canos[9], int ind_animaMa, int ind_animaBo, int n_plat){
        int i;

        BeginDrawing();
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
                    DrawTextureTiled(sheet, Plts_A_M[n_plat], Plts[i], origem, 0, 3.125, WHITE);
                }

            // Desenha o botão power
                if(ind_animaBo == 0){
                    DrawTexturePro(sheet, Aperta_POW[0], Botao, origem, 0, WHITE);

                } else if(ind_animaBo == 1 || ind_animaBo == 3){
                    DrawTexturePro(sheet, Aperta_POW[1], (Rectangle){Botao.x, Botao.y+6, Aperta_POW[1].width*4, Aperta_POW[1].height*4}, origem, 0, WHITE);

                } else if(ind_animaBo == 2){
                    DrawTexturePro(sheet, Aperta_POW[2], (Rectangle){Botao.x, Botao.y+14, Aperta_POW[2].width*4, Aperta_POW[2].height*4}, origem, 0, WHITE);

                }

            // Desenha o Chão
                DrawTexturePro(sheet, Chao.src, Chao.pos, origem, 0, WHITE);

            // Desenha Mario
                Rectangle mario_atual;

                if(ind_animaMa<6){
                    if(lado){
                        mario_atual = M_And_Dir[ind_animaMa];
                    } else mario_atual = M_And_Esq[ind_animaMa];
                } else if(ind_animaMa == 6){
                    if(lado){
                        mario_atual = MarioSprite6.dir;
                    } else mario_atual = MarioSprite6.esq;
                } else {
                    if(lado){
                        mario_atual = MarioSprite5.dir;
                    } else mario_atual = MarioSprite5.esq;
                }

                *Mario = (Rectangle){Mario->x, Mario->y, mario_atual.width*escala, mario_atual.height*escala};
                DrawTexturePro(sheet, mario_atual, *Mario, origem, 0, WHITE);

                //Desenha as tartarugas
                for(int i=0; i<n_turtle; i++){
                    if(turtle[i].isThere==true)
                        DrawRectangleRec(turtle[i].turtleRec, WHITE);
                }

                //DrawRectangleLines(Mario->x, Mario->y, Mario->width, Mario->height, RED); // Desenha a colisão

            // Desenha os Canos
                for(i=0; i<n_ind.x; i++){
                    // Passa por cada cano e verifica de que lado ele está
                    if(cano_pos[i].x >= 600){
                        // Se o cano estiver na direita, verifica se ele é um cano de sa�da ou de retorno
                        if(cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de sa�da virado para esquerda
                                DrawTexturePro(sheet, Cano_Curvo_esq, Canos[i], origem, 0, WHITE);
                        } else {
                                // Aqui ele desenha o cano de entrada virado pra esquerca
                                DrawTexturePro(sheet, Cano_Reto_esq, Canos[i], origem, 0, WHITE);
                        }

                    } else
                        // Se o cano estiver na esquerda, verifica se ele � um cano de sa�da ou de retorno
                        if (cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de sa�da virado para direita
                                DrawTexturePro(sheet, Cano_Curvo_dir, Canos[i], origem, 0, WHITE);
                        } else {
                                // Aqui ele desenha o cano de entrada virado para direita
                                DrawTexturePro(sheet, Cano_Reto_dir, Canos[i], origem, 0, WHITE);
                    }
                }


        EndDrawing();
        //----------------------------------------------------------------------------------
}

void DrawEntrada(char nome[16], int letterCount){
    Vector2 larg = {MeasureText(TextFormat("Número de Letras: %i/15", letterCount), 30), MeasureText("Aperte BACKSPACE para deletar uma letra...", 30)};

        BeginDrawing();
        //----------------------------------------------------------------------------------

            ClearBackground(BLACK);

            DrawText("Insira o seu Nome:", 232, 15, 80, WHITE);

            DrawRectangleLines(297, 280, 604, 70, BLUE);

            DrawText(nome, 302, 288, 60, BLUE);

            if(letterCount==15){
                DrawText(TextFormat("Número de Letras: %i/15", letterCount), (600 - (larg.x)/2), 357, 30, RED);
            } else {
                DrawText(TextFormat("Número de Letras: %i/15", letterCount), (600 - (larg.x)/2), 357, 30, DARKGRAY);
            }

            if (letterCount >= 15) DrawText("Aperte BACKSPACE para deletar uma letra...", (600 - (larg.y)/2), 397, 30, RED);


        EndDrawing();
        //----------------------------------------------------------------------------------
}

void DrawCarregar(Rectangle opcoes[6], int n_arq, Color opcoes_cores[6]){
    int i;
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            DrawText("Escolha uma Fase", 420, 20, 40, WHITE);

            for(i=0;i<n_arq;i++){
                DrawRectangleRounded(opcoes[i], 0.5, 200, WHITE);
                DrawRectangleRoundedLines(opcoes[i], 0.5, 200, 5, GRAY);

                DrawText(TextFormat("Nível %d", i+1), opcoes[i].x+10, opcoes[i].y+12, 25, opcoes_cores[i]);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
}
