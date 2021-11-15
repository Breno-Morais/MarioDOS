/*
O objetivo desse programa � rodar o jogo Mario Bros
O programa � organizado da seguinte maneira:
    1- A declara��o das vari�veis e o loop principal do jogo ocorre no arquivo principal main.c
    2- Todas as fun��es usadas para atualizar vari�veis ou desenhar artefatos na tela est� divido entre
        os outros arquivos fontes com menu.c, spritesheet.c, etc.

Todas as constantes s�o guardadas nos arquivos .h

Especificamente, o arquivo main.c est� divido em 3 partes, a primeira � a inicializa��o de tudo, isso inclui
a declara��o de vari�veis, inicializar a tela, abrir texturas e sons, calcular posi��es, etc.
A segunda e terceira parte fazem parte da mesma etapa, o loop principal do jogo.

O loop principal do jogo envolve tudo que tem que ser atualizado 1 vez por frame, ent�o posi��es de elementos,
colis�es, etc. O loop � divido em 2, a segunda e terceira etapa do main.c.

A segunda etapa do main envolve a atualiza��o de vari�veis, aqui ocorre a parte de verificar as teclas digitadas,
a colis�es de elementos e o movimento de tudo. J� a terceira etapa envolve mostrar isso na tela.
*/

#include "../headers/menu.h"

int main(void)
{
    // Inicializa��o
    //--------------------------------------------------------------------------------------
    Vector2 Tela = {LARGURA_TELA, ALTURA_TELA};
    int i, prox_tela=N_MENU; // O prox_tela � o n�mero que ser� usado como o indicador do pr�ximo passo
    bool flag_saida; // flag usada quando a op��o sair for utilizada e quando for necess�rio abrir o arquivo highscores.bin

    InitWindow(Tela.x, Tela.y, "MARIO DOS");

    InitAudioDevice(); // Inicializa o audio

    // Inicializa��o e tratamento das vari�veis do Menu
    //--------------------------------------------------------------------------------------
        // Carregar a logo em uma textura e cria o vetor com sua posi��o
        Texture2D textura_logo = LoadTexture("imagens/sprite_logo.png");        // Texture loading
        Vector2 posicao_logo = {Tela.x/2 - (textura_logo.width*4)/2, 1};

    //--------------------------------------------------------------------------------------
    Texture2D sheet  = LoadTexture("imagens/sprite_geral.png");
        //---------------------------------------------------------------------------------------
        // Inicializa��o da fonte, das op��es e suas respectivas posi��es e cores
        Font fonte_mario = LoadFont("fontes_texto/SuperMario256.ttf");
        Font fonte_pixel = LoadFont("fontes_texto/Pixel.ttf");

        const char *opcoes[NUM_OPCOES] = {"NOVO JOGO", "CONTINUAR", "CARREGAR MAPA", "RANKING", "AJUDA", "SOBRE", " SAIR "};
        Color cores_opcoes[NUM_OPCOES] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};

        Rectangle posicao_opcoes[NUM_OPCOES];

        for(i=0; i<NUM_OPCOES; i++){ // Ajusta a dist�ncia entre as op��es
            posicao_opcoes[i].x = Tela.x/2 - MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).x/2;
            posicao_opcoes[i].y = (textura_logo.height*4) + TAM_FONTE + 5 + 45*i;
                // Soma (no eixo y) da logo, do tamanho da fonte e das op��es anteriores
            posicao_opcoes[i].width = MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).x;
            posicao_opcoes[i].height = MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).y;
        }

        //---------------------------------------------------------------------------------------
        // Inicializa os sons do menu

        Sound SomOpcaoMenu = LoadSound("som/seta_menu.wav");
        Sound SomSelecinaOpcao = LoadSound("som/sel_menu.mp3");

    //-----------------------------------------------------------------------------------
    // Vari�veis do M�rio
    Rectangle Mario = {0, 0, 16*4, 20*4};

    float marioSpeedLeft = 8;
    float marioSpeedRight = 8;
    bool isJumping = false;
    bool isFalling = true;
    float frameMax = 10;
    float jumpFrameCurrent = 0;
    bool lado = true;

    //-------------------------------------------------------------------------------------
    PLAYER Jog_Princ = {"Breno", 5000, 3};

    //-----------------------------------------------------------------------------------
    // Vari�veis dos Arquivos
    PLAYER melhores[5];
    bool flag_arq = false; // Essa flag � usada para que a abertura do arquivo .bin seja feita apenas uma vez

    // Vari�veis do N�vel
    bool flag_nivel = false; // Essa flag � usada para que o arquivo .txt seja feita apenas uma vez
    bool apertado = false; // Essa vari�vel � usada para saber se o bot�o POW foi apertado
    Rectangle Botao;
    Vector3 cano_pos[9];
    Rectangle Canos[9];
    Vector2 n_ind; // E um vector que cont�m a quantidade de canos e plataformas na fase, nessa ordem
    Rectangle Plts[10];
    int n_fase = 1;
    Rectangle Chao = {0, 666, 1300, 100};
    int ind_animaMa = 0;
    int ind_animaBo = 0;
    int framesCounter = 0;

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
                    n_ind = CarregaFase(n_fase, &Mario, &Botao, cano_pos, Plts, Canos);
                    PlaySound(SomInicia);
                    flag_nivel = true;
                }
    //                        break;
            case N_CONTINUAR: if(!flag_nivel){
                    n_ind = CarregaSave(&Mario, &Botao, cano_pos, Plts, Canos, &Jog_Princ);
                    PlaySound(SomInicia);
                    flag_nivel = true;
                }
                UpdateMario(Plts, n_ind, &Mario, frameMax, &marioSpeedLeft, &marioSpeedRight, &isJumping, &isFalling, &jumpFrameCurrent, &lado, Chao, Botao, &apertado, SomPulo);
                Anima(&framesCounter, &ind_animaMa, &ind_animaBo, isFalling, isJumping);
                UpdateVoltar(&prox_tela);
                SalvarJogo(n_fase, Mario, Jog_Princ);
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
            case N_CONTINUAR: DrawTela(Jog_Princ, sheet, Plts, n_ind, Botao, fonte_mario, cano_pos, &Mario, lado, n_fase, Canos, ind_animaMa, ind_animaBo);
                            break;
            case N_CARREGAR_MAPA:
            //                break;
            case N_RANKING: DrawScores(melhores, fonte_pixel);
                            break;
            case N_AJUDA: DrawAjuda(fonte_mario);
                            break;
            case N_SOBRE: DrawSobre(fonte_mario);
                            break;
            case N_SAIR: flag_saida=true; // Verifica se o bot�o saida foi apertado
                            break;
        }
    }

    // Deinicializa��o
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
