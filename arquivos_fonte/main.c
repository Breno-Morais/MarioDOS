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
    bool lado = true;

    //Variáveis dos inimigos
    int n_turtle, turtle_atual=0;
    int n_crab;
    int tempo_espera, tempo_atual=0;
    int hit_cooldown_current = 0, hit_cooldown_max = 10;

    TURTLE turtle[20];
    CRAB crab[10];

    //-------------------------------------------------------------------------------------
    PLAYER Jog_Princ = {"Breno", 5000, 3};

    //-----------------------------------------------------------------------------------
    // Variáveis dos Arquivos
    PLAYER melhores[5];
    bool flag_arq = false; // Essa flag é usada para que a abertura do arquivo .bin seja feita apenas uma vez

    // Variáveis do Nível
    bool flag_nivel = false; // Essa flag é usada para que o arquivo .txt seja feita apenas uma vez
    bool apertado = false; // Essa variável é usada para saber se o botão POW foi apertado
    Rectangle Botao;
    Vector3 cano_pos[9];
    Rectangle Canos[9];
    bool flag_cano = false;
    int cano_atual;
    Vector2 n_ind; // E um vector que contém a quantidade de canos e plataformas na fase, nessa ordem
    Rectangle Plts[10];
    int n_fase = 1;
    Rectangle Chao = {0, 666, 1300, 100};
    int ind_animaMa = 0;
    int ind_animaBo = 0;
    int framesCounter = 0;
    srand(time(NULL));

    // Inicializa sons da fase
    Sound SomInicia = LoadSound("som/inicio.wav");
    Sound SomPulo = LoadSound("som/pulo.wav");

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
                    n_ind = CarregaFase(&n_turtle, &n_crab, &tempo_espera, n_fase, &Mario, &Botao, cano_pos, Plts, Canos);
                    PlaySound(SomInicia);
                    flag_nivel = true;
                    InitTurtle(&turtle_atual, n_turtle, turtle, &flag_cano, &cano_atual, n_ind, cano_pos, Canos);
            }

    //                        break;
            case N_CONTINUAR: if(!flag_nivel){
                    n_ind = CarregaSave(&Mario, &Botao, cano_pos, Plts, Canos, &Jog_Princ);
                    PlaySound(SomInicia);
                    flag_nivel = true;
                }
                UpdateMario(cano_pos, Canos, Plts, n_ind, &Mario, frameMax, &marioSpeedLeft, &marioSpeedRight, &isJumping, &isFalling, &jumpFrameCurrent, &lado, Chao, Botao, &apertado, SomPulo);
                Anima(&framesCounter, &ind_animaMa, &ind_animaBo, isFalling, isJumping);
                UpdateVoltar(&prox_tela);
                SalvarJogo(n_fase, Mario, Jog_Princ);
                UpdateTurtle(apertado, &hit_cooldown_current, hit_cooldown_max, &turtle_atual, n_turtle, tempo_espera, &tempo_atual, &turtle, n_ind, Canos, cano_pos, Plts, Mario, Chao);
                            break;
            case N_CARREGAR_MAPA:
    //                        break;
            case N_RANKING: Highscores(melhores, &flag_arq);
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
            case N_NOVO:
            //            break;
            case N_CONTINUAR: DrawTela(turtle, n_turtle, Jog_Princ, sheet, Plts, n_ind, Botao, fonte_mario, cano_pos, &Mario, lado, n_fase, Canos, ind_animaMa, ind_animaBo);
                            break;
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
    UnloadSound(SomInicia);
    UnloadSound(SomPulo);

    CloseAudioDevice();            // Close audio device
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
