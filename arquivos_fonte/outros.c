#include "../headers/menu.h"
#include <math.h>

void copiaJogador(PLAYER *jogador1, PLAYER jogador2);

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

void Highscores(PLAYER melhores[5], bool *flag){
    FILE *arq;
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

                copiaJogador(&melhores[i], jogador);

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

void SalvarJogo(int n_fase, Rectangle Mario, PLAYER jogador, int n_turtle, TURTLE turtle[20]){
    // Salva apenas se a tecla A for apertada
    if(IsKeyPressed(KEY_A)){
            // Inicialização das variáveis
            //----------------------------------------------------------------------------------
            FILE *fase, *save;
            char fase_atual[19];
            char linha_atual[120];
            int coluna, n_linha, x, y;

            // Faz a formatação do nome do arquivo da fase atual
            sprintf(fase_atual, "niveis/nivel%d.txt", n_fase);

            //----------------------------------------------------------------------------------
                // Abre os arquivos da fase e do save
                if(!(fase = fopen(fase_atual,"r"))) // abre para leitura
                    // Imprime se ocorreu algum erro
                    printf("Erro na abertura da fase\n");
                else if(!(save = fopen("saves/save.txt", "w"))) // abre para escrita
                    // Imprime se ocorreu algum erro
                    printf("Erro na abertura do save\n");
            //----------------------------------------------------------------------------------
                else {
                // Carrega linha por linha do arquivo fase.txt
                for(n_linha=0; n_linha<28; n_linha++){
                    // Guarda a linha inteira na variável linha_atual
                    fscanf(fase,"%s\n", linha_atual);

                    // Passa caractere por caractere da linha, analisando
                    for(coluna=0; coluna<120; coluna++){
                        // Guarda as coordenadas do caractere atual
                        x = coluna*10;
                        y = n_linha*25;

                        // Se as coordenadas atuais forem próximas o suficiente do Mario, elas são guardadas
                        if((x<=Mario.x+5 && x>=Mario.x-5) && (y<=Mario.y+12 && y>=Mario.y-12)){
                            putc('m', save);

                        // Apaga a posição do Mario no arquivo fase
                        } else if(linha_atual[coluna]=='m'){
                            putc('-', save);

                        // Guarda as outras informações da fases que são constantes
                        } else {
                            putc(linha_atual[coluna], save);
                        }

                    }

                    putc('\n', save);
                    }
                    // Guarda as outras informações do jogo
                    //----------------------------------------------------------------------------------

                    // Guarda as informações do jogador
                    const char *MarioString = TextFormat("%s;%d;%d\n", jogador.nome, jogador.pontuacao, jogador.vidas);;
                    fputs(MarioString, save);

                    // Guarda as informações do Mario


                    // Guarda as informações dos inimigos
                    fputs(TextFormat("Tartarugas:%d\n", n_turtle), save);
                    for(int i=0; i<n_turtle; i++){
                        Rectangle turtleRec;
                        int sentido, estado, level; //estado:1-inativo; 2-invulneravel; 3-vulneravel; 4-morto.
                        float speed;
                        bool fall, isThere;

                        int tx = (int)turtle[i].turtleRec.x;
                        int ty = (int)turtle[i].turtleRec.y;
                        int ts = turtle[i].sentido;
                        int te = turtle[i].estado;
                        //int tl = turtle[i].level;
                        float tsp = turtle[i].speed;

                        const char *TurtleString = TextFormat("%d;%d;%d;%d;%f\n", tx, ty, ts, te, tsp);
                        fputs(TurtleString, save);
                    }

                    fclose(fase);
                    fclose(save);
                }
            }
}

Vector2 CarregaSave(Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9], PLAYER *jogador, TURTLE turtle[20], int *n_turtle){
    FILE *save;
    char linha_atual[120];
    int coluna, n_linha, x, y, i, n_cano=0, n_plt=0;
    bool flag_stream=false;

    if(!(save = fopen("saves/save.txt","r"))) // abre para leitura
        // Imprime se ocorreu algum erro
        printf("Erro na abertura\n");
    else{
        // Carrega linha por linha do arquivo save.txt
        for(n_linha=0; n_linha<28; n_linha++){
            // Guarda a linha inteira na variável linha_atual
            fscanf(save,"%s\n", linha_atual);

            // Passa caractere por caractere da linha, analisando
            for(coluna=0; coluna<120; coluna++){
                // Guarda as coordenadas do caractere atual
                x = coluna*10;
                y = n_linha*25;

                // Verifica qual é o caractere
                switch(linha_atual[coluna]){
                    // Se o caractere for igual a M, guarda as coordenadas como a posição do mario
                    case 'm':
                        Mario->x = x;
                        Mario->y = y;
                                break;

                    // Se o caractere for igual a C, guarda as coordenadas como a posição do cano, número n_cano
                    case 'c':
                        cano_pos[n_cano].x = x+10;
                        cano_pos[n_cano].y = y+25;
                        cano_pos[n_cano].z = 0;
                        n_cano++;
                                break;

                    // Se o caractere for igual a B, guarda as coordenadas como a posição do botão
                    case 'b':
                        Botao->x = x-32;
                        Botao->y = y-32;
                        Botao->width = 64;
                        Botao->height = 64;
                                break;

                    // Se o caractere for igual a um número entre 1-9,
                    // guarda as coordenadas como a posição do cano, número n_cano, e sinaliza que é um cano de retorno
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                    case '9':
                        cano_pos[n_cano].x = x;
                        cano_pos[n_cano].y = y;
                        cano_pos[n_cano].z = linha_atual[coluna] - '0';
                        n_cano++;
                                break;

                    // Se o caractere for igual a P,
                    case 'p':
                    // primeiro ele verifica se o char atual faz parte de um sequência de P's
                        if(!flag_stream){
                            // Se não, ele sinaliza que uma sequência de P's se inicializpu
                            flag_stream = true;

                            // E então ele guarda as coordenas da nº plataforma
                            Plts[n_plt].x = x;
                            Plts[n_plt].y = y;

                            // E depois ele adiciona a largura e altura de P
                            Plts[n_plt].width = 10;
                            Plts[n_plt].height = 25;
                        } else {
                            // Se sim, ele apenas adiciona a largura de um P
                            Plts[n_plt].width = Plts[n_plt].width+10;
                        }
                        break;
                    case '-':
                        // Se o caractere for igual a -, verifica se uma sequência de P's está ligada
                        if(flag_stream){
                        // Se tiver, sinaliza que uma plataforma acabou
                            n_plt++;
                            flag_stream = false;
                        }
                }

            }
        }

    }

    // Cria o retângulo de cada cano
    for(i=0; i<n_cano; i++){
    // Passa por cada cano e verifica de que lado ele está
        if(cano_pos[i].x >= 600){
                        // Se o cano estiver na direita, verifica se ele é um cano de sa�da ou de retorno
                        if(cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de saída virado para esquerda
                                Canos[i] = (Rectangle){cano_pos[i].x-10, cano_pos[i].y-60, 196, 120};
                        } else {
                                // Aqui ele desenha o cano de entrada virado pra esquerca
                                Canos[i] = (Rectangle){cano_pos[i].x, cano_pos[i].y, 128, 72};
                        }

                    } else {
                        // Se o cano estiver na esquerda, verifica se ele é um cano de sa�da ou de retorno
                        if (cano_pos[i].z == 0){
                                // Aqui ele desenha o cano de saída virado para direita
                                Canos[i] = (Rectangle){cano_pos[i].x-196, cano_pos[i].y-60, 196, 120};
                        } else {
                                // Aqui ele desenha o cano de entrada virado para direita
                                Canos[i] = (Rectangle){cano_pos[i].x-118, cano_pos[i].y, 128, 72};
                        }
        }

    }

    // Ajusta a posição do mario no início, para evitar que ele nasça dentro da plataforma
    for(i=0;i<n_plt;i++){
        if(CheckCollisionRecs(*Mario, Plts[i])){
            Mario->y -= GetCollisionRec(*Mario, Plts[i]).height+5;
        }
    }

    // Pega as informações do jogador do save
    fscanf(save,"%s\n", linha_atual);
        int conta;
        const char **linhas = TextSplit(linha_atual, ';', &conta);
        strcpy(jogador->nome, linhas[0]);
        jogador->pontuacao = atoi(linhas[1]);
        jogador->vidas = atoi(linhas[2]);

    // Pega as informações dos inimigos do save
    fscanf(save, "Tartarugas:%s\n", linha_atual);
    *n_turtle = atoi(linha_atual);
    for(i=0; i<*n_turtle; i++){
        fscanf(save, "%s\n", linha_atual);
        linhas = TextSplit(linha_atual, ';', &conta);

        turtle[i].turtleRec = (Rectangle){atoi(linhas[0]), atoi(linhas[1]), 48, 48};
        turtle[i].sentido = atoi(linhas[2]);
        turtle[i].estado = atoi(linhas[3]);
        turtle[i].speed = atoi(linhas[4]);
    }

    fclose(save);

    return (Vector2){n_cano, n_plt};
}

bool Entrada(PLAYER *jogador, char *nome, int *letterCount){
    bool flag_retorno = false;

            // Pega o caractere pressionado da fila
            int key = GetCharPressed();

            // Verifica se tem mais caracteres pressionados no mesmo frame
            while (key > 0)
            {
                // NOTE: Apenas deixar os caracteres entre 32 e 125
                if ((key >= 32) && (key <= 125) && (*letterCount < 15))
                {
                    nome[*letterCount] = (char)key;
                    nome[*letterCount+1] = '\0'; // Adiciona a terminação da string no final.
                    *letterCount+=1;
                }

                key = GetCharPressed();  // Verifica próximo caractere na fila
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                *letterCount-=1;
                if (*letterCount < 0) *letterCount = 0;
                nome[*letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER) && *letterCount != 15)
            {
                flag_retorno = true;
                strcpy(jogador->nome, nome);
            }


        return flag_retorno;
}

void UpdateMenuCarregar(Rectangle opcoes[6], bool *flag, int *n_arq, Color opcoes_cores[6], int *n_fase, int *prox, Sound SomSelecinaOpcao){
    int i;
    char nivel[19];

    if(!*flag){
        for(i=1;i<=6;i++){
            sprintf(nivel, "niveis/nivel%d.txt", i);
            if(access(nivel, F_OK) == 0){
                *n_arq+=1;
            }
        }

        for(i=0;i<*n_arq;i++){
            if(i<= 1){
                opcoes[i] = (Rectangle){(550 - (100 * pow(-1, i))), 200, 100, 50};
            } else if(i<=3){
                opcoes[i] = (Rectangle){(550 - (100 * pow(-1, i))), 300, 100, 50};
            } else if(i<=5){
                opcoes[i] = (Rectangle){(550 - (100 * pow(-1, i))), 400, 100, 50};
            }
        }

        *flag = true;
    }

    Vector2 mouse = GetMousePosition();

    for(i=0;i<*n_arq;i++){
        if(CheckCollisionPointRec(mouse, opcoes[i])){
            opcoes_cores[i] = GOLD;

            // Se o mouse clicar na opção
            if(IsMouseButtonDown(0)){
                opcoes_cores[i] = LIGHTGRAY;
                // Devolva qual foi a opção escolhida
                *n_fase = i+1;
                *prox = N_NOVO;
                PlaySound(SomSelecinaOpcao);
            }

        } else opcoes_cores[i] = BLACK;
    }

}

void UpdateGameOver(PLAYER *jogador, PLAYER melhores[5], bool *flag_arq, bool *flag_final){
    if(!*flag_arq){
        Highscores(melhores, flag_arq);
    }

    FILE *arq;
    PLAYER aux1;
    copiaJogador(&aux1, *jogador);
    PLAYER aux2;
    for(int i=0; i<5; i++){
        if(aux1.pontuacao>melhores[i].pontuacao){
                printf("%s\n", melhores[i].nome);

            copiaJogador(&aux2, melhores[i]);

            copiaJogador(&melhores[i],aux1);

            copiaJogador(&aux1, aux2);
        }
    }

    if(!(arq = fopen("highscores.bin", "wb"))){
            printf("\nErro criacao\n");
        } else {
        // Se o arquivo highscores.bin existe, então podemos guardar todos os seus elemento em um array, para mais fácil manipulação
                //----------------------------------------------------------------------------------
                // Leia cada jogador do arquivo e os armazene no array dos melhores jogadores
                for(int i=0; i<5; i++){
                    if(fwrite(&melhores[i], sizeof(PLAYER), 1, arq) != 1){
                            printf("Erro na escrita numero: %d", i);
                    }
                }
            }
            fclose(arq);
            //----------------------------------------------------------------------------------

    *flag_final = true;
}

void copiaJogador(PLAYER *jogador1, PLAYER jogador2){
    jogador1->pontuacao = jogador2.pontuacao;
    strncpy(jogador1->nome, jogador2.nome, 15);
    jogador1->nome[strlen(jogador2.nome)] = '\0';
}

