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
        //----------------------------------------------------------------------------------
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

void Highscores(FILE *arq, PLAYER melhores[5], bool *flag){
    if( access("highscores.bin", F_OK) != 0){
        // Se o arquivo highscores.bin não existe, crie um novo arquivo com nomes ficticios
        //----------------------------------------------------------------------------------
        if(!(arq = fopen("highscores.bin", "wb"))){
            // Testamos para ver se ocorre algum problema ao abrir o arquivo
            printf("\nErro criacao\n");
        } else {
            // Se o arquvio tiver abrido com sucesso, então podemos atribuir cada posição um jogador ficticio
            //----------------------------------------------------------------------------------
            char *nomes[5] = {"Carla","Arthur","Breno","Felipe","Tiago"};
            int pontuacoes[5] = {9000,6000,4000,3050,1000}, i;
            PLAYER jogador;

            for(i=0; i<5; i++){
                strncpy(jogador.nome, nomes[i], 15);
                jogador.nome[strlen(nomes[i])] = '\0';
                jogador.pontuacao = pontuacoes[i];

                if(fwrite(&jogador, sizeof(PLAYER), 1, arq) != 1){
                    printf("\nErro de escrita\n");
                }
            }

            fclose(arq);
            //----------------------------------------------------------------------------------
        }


    } else if(!*flag){ // Verifica se a abertura e leitura do documento já foi feita previamente, para evitar a abertura do arquivo em todo frame
        // Verifica se a abertura do documento foi feita com sucesso
        if(!(arq = fopen("highscores.bin", "rb"))){
            printf("\nErro criacao\n");
        } else {
        // Se o arquivo highscores.bin existe, então podemos guardar todos os seus elemento em um array, para mais fácil manipulação
            //----------------------------------------------------------------------------------
            PLAYER jogador;
            int i=0;
            while(!feof(arq)){ // enquanto não chegar ao fim
                // Leia cada jogador do arquivo e os armazene no array dos melhores jogadores
                if(fread(&jogador, sizeof(PLAYER), 1, arq) == 1){
                    melhores[i] = jogador;
                    i++;
                }
            }
            fclose(arq);
            //----------------------------------------------------------------------------------
        }

        *flag = true;
    }
}

void DrawScores(PLAYER melhores[5], Font fonte){
    int i;
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Limpa o background e coloque ele preto
            ClearBackground(BLACK);

            //----------------------------------------------------------------------------------
            // Desenha o Titulo
            int dist = MeasureText("TOP 5", 80);
            DrawText("TOP 5", ((LARGURA_TELA/2) - dist/2), 10, 80, GOLD);

            //----------------------------------------------------------------------------------
            // Desenha o texto
            for(i=0; i<5; i++){
                const char *texto = TextFormat("%s:", melhores[i].nome);
                Vector2 tamanho_texto = MeasureTextEx(fonte, texto, 60, 1);

                // Desenha a posição
                DrawTextEx(fonte, TextFormat("%d)", (i+1)), (Vector2){350, 150+((80+10)*i)}, 60, 1, GOLD);
                // Desenha o nome
                DrawTextEx(fonte, texto, (Vector2){450, 150+((80+10)*i)}, 60, 1, GOLD);
                // Desenha a pontuação
                DrawTextEx(fonte, TextFormat("%d", melhores[i].pontuacao), (Vector2){460+tamanho_texto.x, 150+((80+10)*i)}, 60, 1, GOLD);
            }
            //----------------------------------------------------------------------------------


        EndDrawing();
        //----------------------------------------------------------------------------------
}
