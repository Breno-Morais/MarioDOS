/*
O objetivo desse programa é rodar o jogo Mario Bros
O programa é organizado da seguinte maneira:
    1- A declaração das variáveis e o loop principal do jogo ocorre no arquivo principal main.c
    2- Todas as funções usadas para atualizar variáveis ou desenhar artefatos na tela está divido entre
        os outros arquivos fontes com menu.c, spritesheet.c, etc.

Todas as constantes são guardadas nos arquivos .h

Especificamente, o arquivo main.c está divido em 3 partes, a primeira é a inicialização de tudo, isso inclui
a declaração de variáveis, inicializar a tela, abrir texturas e sons, calcular posições, etc.
A segunda e terceira parte fazem parte da mesma etapa, o loop principal do jogo.

O loop principal do jogo envolve tudo que tem que ser atualizado 1 vez por frame, então posições de elementos,
colisões, etc. O loop é divido em 2, a segunda e terceira etapa do main.c.

A segunda etapa do main envolve a atualização de variáveis, aqui ocorre a parte de verificar as teclas digitadas,
a colisões de elementos e o movimento de tudo. Já a terceira etapa envolve mostrar isso na tela.
*/

#include "../headers/menu.h"

int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    Vector2 Tela = {LARGURA_TELA, ALTURA_TELA};
    int i, prox_tela=N_MENU; // O prox_tela é o número que será usado como o indicador do próximo passo
    bool flag_saida; // flag usada quando a opção sair for utilizada e quando for necessário abrir o arquivo highscores.bin

    InitWindow(Tela.x, Tela.y, "MARIO DOS");

    InitAudioDevice(); // Inicializa o audio

    // Inicialização e tratamento das variáveis do Menu
    //--------------------------------------------------------------------------------------
        // Carregar a logo em uma textura e cria o vetor com sua posição
        Texture2D textura_logo = LoadTexture("imagens/sprite_logo.png");        // Texture loading
        Vector2 posicao_logo = {Tela.x/2 - (textura_logo.width*4)/2, 1};

    //--------------------------------------------------------------------------------------
    Texture2D sheet  = LoadTexture("imagens/sprite_geral.png");
        //---------------------------------------------------------------------------------------
        // Inicialização da fonte, das opções e suas respectivas posições e cores
        Font fonte_mario = LoadFont("fontes_texto/SuperMario256.ttf");
        Font fonte_pixel = LoadFont("fontes_texto/Pixel.ttf");

        const char *opcoes[NUM_OPCOES] = {"NOVO JOGO", "CONTINUAR", "CARREGAR MAPA", "RANKING", "AJUDA", "SOBRE", " SAIR "};
        Color cores_opcoes[NUM_OPCOES] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};

        Rectangle posicao_opcoes[NUM_OPCOES];

        for(i=0; i<NUM_OPCOES; i++){ // Ajusta a distância entre as opções
            posicao_opcoes[i].x = Tela.x/2 - MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).x/2;
            posicao_opcoes[i].y = (textura_logo.height*4) + TAM_FONTE + 5 + 45*i;
                // Soma (no eixo y) da logo, do tamanho da fonte e das opções anteriores
            posicao_opcoes[i].width = MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).x;
            posicao_opcoes[i].height = MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).y;
        }

        //---------------------------------------------------------------------------------------
        // Inicializa os sons do menu

        Sound SomOpcaoMenu = LoadSound("som/seta_menu.wav");
        Sound SomSelecinaOpcao = LoadSound("som/sel_menu.mp3");

    //-----------------------------------------------------------------------------------
    // Variáveis do Mário
    Rectangle Mario = {0, 0, 16*4, 20*4};

    float marioSpeedLeft = 8;
    float marioSpeedRight = 8;
    bool isJumping = false;
    bool isFalling = true;
    float frameMax = 10;
    float jumpFrameCurrent = 0;
    float jumpHighMax = 200;
    bool lado = true;
    // Funções do Mário
    //-------------------------------------------------------------------------------------
    PLAYER Jog_Princ = {"Breno", 5000, 3};

    //-----------------------------------------------------------------------------------
    // Variáveis dos Arquivos
    FILE *scores;
    PLAYER melhores[5];
    bool flag_arq = false; // Essa flag é usada para que a abertura do arquivo .bin seja feita apenas uma vez

    // Variáveis do Nível
    bool flag_nivel = false; // Essa flag é usada para que o arquivo .txt seja feita apenas uma vez
    Rectangle Botao;
    Vector3 cano_pos[9];
    Vector2 n_ind; // E um vector que contém a quantidade de canos e plataformas na fase, nessa ordem
    Rectangle Plts[10];
    int n_fase = 1;
    Rectangle Chao = {0, 666, 1300, 100};

    //---------------------------------------------------------------------------------------
    // Loop principal do jogo
    SetTargetFPS(30);
    while (!WindowShouldClose() && !flag_saida)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if(prox_tela == N_MENU) UpdateMenu(cores_opcoes, posicao_opcoes, &prox_tela, SomOpcaoMenu, SomSelecinaOpcao);
        switch(prox_tela){
            /*case N_MENU: UpdateMenu(cores_opcoes, posicao_opcoes, &prox_tela, SomOpcaoMenu, SomSelecinaOpcao);
                            break;*/
            case N_NOVO: if(!flag_nivel){
                    n_ind = CarregaFase(n_fase, &Mario, &Botao, cano_pos, Plts);
                    //printf("plat.pos[0].x: %lf\n", plat.pos[0].x);
                    flag_nivel = true;
                }
                UpdateMario(Plts, n_ind, &Mario, frameMax, &marioSpeedLeft, &marioSpeedRight, &isJumping, &isFalling, &jumpFrameCurrent, &lado, Chao, Botao);
/*
                isFalling = true;
                marioSpeedLeft = 8;
                marioSpeedRight = 8;

                //Testa colisão com o chão e base da plataforma
                if(CheckCollisionPointRec((Vector2){Mario.x+1, Mario.y+Mario.height}, Chao) || CheckCollisionPointRec((Vector2){Mario.x+Mario.width-1, Mario.y+Mario.height}, Chao)){
                    isFalling = false;
                    Mario.y = Chao.y-Mario.height+5;
                }
                for(int i = 0; i<n_ind.y; i++){
                    if(CheckCollisionPointRec((Vector2){Mario.x+1, Mario.y+Mario.height}, Plts[i]) || CheckCollisionPointRec((Vector2){Mario.x+Mario.width-1, Mario.y+Mario.height}, Plts[i])){
                        isFalling = false;
                        Mario.y = Plts[i].y-Mario.height;
                    }
                }
                //Testa colisão com o teto
                for(int i = 0; i<n_ind.y; i++){
                    if(CheckCollisionPointRec((Vector2){(Mario.x+Mario.width), Mario.y}, Plts[i]) || CheckCollisionPointRec((Vector2){Mario.x, Mario.y}, Plts[i])){
                        isJumping = false;
                    }
                }
                //Testa colisão com o botão por baixo
                if(CheckCollisionPointRec((Vector2){(Mario.x+Mario.width), Mario.y}, Botao) || CheckCollisionPointRec((Vector2){Mario.x, Mario.y}, Botao)){
                    isJumping = false;
                }

                //Testa colisão com a parede pela esquerda. Se colidir, não pode ir pra esquerda
                for(int i = 0; i<n_ind.y; i++){
                    if(!lado && CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+1}, Mario) || CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+Plts[i].height-1}, Mario)){
                        marioSpeedLeft = 0;
                    }
                }
                //Testa colisão com o botão pela esquerda. Se colidir, não pode ir pra esquerda.
                if(!lado && CheckCollisionPointRec((Vector2){Mario.x, Mario.y}, Botao) || CheckCollisionPointRec((Vector2){Mario.x, Mario.y+Mario.height}, Botao) || CheckCollisionPointRec((Vector2){Mario.x, Mario.y+(Mario.height/2)}, Botao)){
                    marioSpeedLeft = 0;
                }
                //Testa colisão com a parede pela direita. Se colidir, não pode ir pra direita.
                for(int i = 0; i<n_ind.y; i++){
                    if(lado && CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+1}, Mario) || CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+Plts[i].height-1}, Mario)){
                        marioSpeedRight = 0;
                    }
                }
                //Testa colisão com o botão pela direita. Se colidir, não pode ir pra direita.
                if(lado && CheckCollisionPointRec((Vector2){Mario.x+Mario.width, Mario.y}, Botao) || CheckCollisionPointRec((Vector2){Mario.x+Mario.width, Mario.y+Mario.height}, Botao) || CheckCollisionPointRec((Vector2){Mario.x+Mario.width, Mario.y+(Mario.height/2)}, Botao)){
                    marioSpeedRight = 0;
                }

                //Se aperta a seta direita, vai pra direita
                if(IsKeyDown(KEY_RIGHT)){
                    Mario.x += marioSpeedRight;
                    lado = true;
                }
                //Se aperta a seta esquerda, vai pra esquerda
                else if(IsKeyDown(KEY_LEFT)){
                    Mario.x -= marioSpeedLeft;
                    lado = false;
                }
                //Se aperta a seta de cima e não tiver caindo, pula
                if(IsKeyPressed(KEY_UP)){
                    if(isFalling==false)
                        isJumping = true;
                }
                //Pulo do Mario
                if(isJumping){
                    jumpFrameCurrent++;
                    Mario.y -= 20;
                    if(jumpFrameCurrent>=frameMax){
                        jumpFrameCurrent = 0;
                        isJumping = false;
                        isFalling = true;
                    }
                }
                //Queda do Mario
                else if(isFalling){
                    jumpFrameCurrent = 0;
                    Mario.y+=10;
                }

                //Mario passa da direita pra esquerda da tela
                if(Mario.x+(Mario.width/2)>=LARGURA_TELA){
                    Mario.x = 0-(Mario.width/2);
                }
                //Mario passa da esquerda pra direita da tela
                if(Mario.x+(Mario.width/2)<0){
                    Mario.x = LARGURA_TELA-(Mario.width/2);
                }*/
                            break;
            case N_CONTINUAR:
    //                        break;
            case N_CARREGAR_MAPA:
    //                        break;
            case N_RANKING: Highscores(scores, melhores, &flag_arq);
            case N_AJUDA:
            case N_SOBRE: UpdateVoltar(&prox_tela);
                            break;
        }

        //----------------------------------------------------------------------------------

        // Desenhar
        //----------------------------------------------------------------------------------
        switch(prox_tela){
            case N_MENU: DrawMenu(textura_logo, posicao_logo, fonte_mario, opcoes, posicao_opcoes, cores_opcoes);
                            break;
            case N_NOVO: DrawTela(Jog_Princ, sheet, Plts, n_ind, Botao, fonte_mario, cano_pos, Mario, lado, n_fase);
                //InitSpread(sheet);
                        break;
            case N_CONTINUAR:
            //                break;
            case N_CARREGAR_MAPA:
            //                break;
            case N_RANKING: DrawScores(melhores, fonte_pixel);
                            break;
            case N_AJUDA: DrawAjuda(fonte_mario);
                            break;
            case N_SOBRE: DrawSobre(fonte_mario);
                            break;
            case N_SAIR: flag_saida=true; // Verifica se o botão saida foi apertado
                            break;
        }
    }

    // Deinicialização
    //--------------------------------------------------------------------------------------
    UnloadTexture(textura_logo);                    // Texture unloading
    UnloadTexture(sheet);                          // Texture unloading
    UnloadSound(SomOpcaoMenu);                    // Unload sound data
    UnloadSound(SomSelecinaOpcao);               // Unload sound data

    CloseAudioDevice();            // Close audio device
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
