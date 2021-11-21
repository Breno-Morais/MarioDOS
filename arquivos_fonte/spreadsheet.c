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


void DrawTela(CRAB crab[20], int n_crab, TURTLE turtle[20],int n_turtle, PLAYER jogador, Texture sheet, Rectangle Plts[10], Vector2 n_ind, Rectangle Botao, Font fonte, Vector3 cano_pos[9], Rectangle *Mario, bool lado, int n_fase, Rectangle Canos[9], int ind_animaMa, int ind_animaBo){
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
                DrawTexturePro(sheet, Aperta_POW[ind_animaBo], Botao, origem, 0, WHITE);

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
                //Desenha os caranguejos
                for(int i=0; i<n_crab; i++){
                    if(crab[i].isThere==true)
                        DrawRectangleRec(crab[i].crabRec, RED);
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
