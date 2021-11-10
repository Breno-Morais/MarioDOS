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
    int marioHeight = 20*4;
    int marioWidth = 16*4;
    int marioX = 0;
    int marioY = ALTURA_TELA-(2*marioHeight);
    int marioSpeed = 8;
    bool isJumping = false;
    bool isFalling = false;
    int frameMax = 10;
    int jumpFrameCurrent = 0;
    int fallFrameCurrent = 0;
    int jumpHighMax = 150;
    // Fun��es do M�rio

    //-------------------------------------------------------------------------------------
    PLAYER Jog_Princ = {"Breno", 5000, 3};

    //-----------------------------------------------------------------------------------
    // Vari�veis dos Arquivos
    FILE *scores;
    PLAYER melhores[5];
    bool flag_arq = false; // Essa flag � usada para que a abertura do arquivo .bin seja feita apenas uma vez

    // Vari�veis do N�vel
    bool flag_nivel = false; // Essa flag � usada para que o arquivo .txt seja feita apenas uma vez
    Vector2 mario_pos, botao_pos;
    Vector3 cano_pos[9];
    Rectangle Plts[10];
    int n_fase = 1, n_plt;

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
                    n_plt = CarregaFase(n_fase, &mario_pos, &botao_pos, cano_pos, Plts);
                    //printf("plat.pos[0].x: %lf\n", plat.pos[0].x);
                    flag_nivel = true;
            }
                if(IsKeyDown(KEY_RIGHT)){
                    marioX += marioSpeed;
                }
                else if(IsKeyDown(KEY_LEFT)){
                    marioX -= marioSpeed;
                }
                if(IsKeyPressed(KEY_UP)){
                    if(isFalling==false)
                        isJumping = true;
                }
                if(isJumping==true){
                    jumpFrameCurrent++;
                    marioY -= (int)(jumpHighMax/frameMax);
                    if(jumpFrameCurrent>=frameMax){
                        jumpFrameCurrent = 0;
                        isJumping = false;
                        isFalling = true;
                    }
                }
                else if(isFalling==true){
                    fallFrameCurrent++;
                    marioY += (int)(jumpHighMax/frameMax);
                    if(fallFrameCurrent>=frameMax){
                        fallFrameCurrent = 0;
                        isFalling = false;
                    }
                }
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
            case N_NOVO: BeginDrawing();
                DrawTela(Jog_Princ, sheet, Plts, n_plt, botao_pos, fonte_mario, mario_pos, cano_pos);
                //InitSpread(sheet);
                DrawRectangle(marioX, marioY, marioWidth, marioHeight, RED);
                EndDrawing();
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

    CloseAudioDevice();            // Close audio device
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
