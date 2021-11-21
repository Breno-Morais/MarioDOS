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
    // Inicialização
    //--------------------------------------------------------------------------------------
    Vector2 Tela = {LARGURA_TELA, ALTURA_TELA};
    int i, prox_tela=N_MENU; // O prox_tela � o n�mero que ser� usado como o indicador do pr�ximo passo
    bool flag_saida; // flag usada quando a op��o sair for utilizada e quando for necess�rio abrir o arquivo highscores.bin

    InitWindow(Tela.x, Tela.y, "MARIO DOS");

    InitAudioDevice(); // Inicializa o audio

    // Inicialização e tratamento das variáveis do Menu
    //--------------------------------------------------------------------------------------
        // Carregar a logo em uma textura e cria o vetor com sua posi��o
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
    // Variáveis do Mario
    Rectangle Mario = {0, 0, 16*4, 20*4};

    float marioSpeedLeft=8;
    float marioSpeedRight=8;
    bool isJumping = false;
    bool isFalling = true;
    float frameMax = 10;
    float jumpFrameCurrent = 0;
    bool lado = true;
    bool dano = false;
    int mario_invun = 0;
    bool perdeu = false;

    //-----------------------------------------------------------------------------------
    //Variáveis dos inimigos
    int n_turtle, turtle_atual=0;
    int n_crab, crab_atual = 0;
    int tempo_espera, tempo_atual=0;
    int hit_cooldown_current = 0, hit_cooldown_max = 10;

    TURTLE turtle[20];
    CRAB crab[20];

    //-------------------------------------------------------------------------------------
    PLAYER Jog_Princ = {"", 10000, 3};

    //-----------------------------------------------------------------------------------
    // Variáveis dos Arquivos
    PLAYER melhores[5];
    bool flag_arq = false; // Essa flag � usada para que a abertura do arquivo .bin seja feita apenas uma vez

    //-----------------------------------------------------------------------------------
    // Variáveis do Nível
    bool flag_nivel = false; // Essa flag � usada para que o arquivo .txt seja feita apenas uma vez
    bool flag_som = false;
    int botao_current = 0;
    Rectangle Botao;
    Vector3 cano_pos[9];
    Rectangle Canos[9];
    bool flag_cano = false;
    int cano_atual;
    Vector2 n_ind; // E um vector que cont�m a quantidade de canos e plataformas na fase, nessa ordem
    Rectangle Plts[10];
    int n_fase = 1;
    int vitoria = 0;
    bool flag_final=false;
    int counter_final = 0;

    // Escolha da Plataforma
    srand(time(NULL));
    int n_plat = rand()%2;

    //-----------------------------------------------------------------------------------
    // Variáveis da Animação
    Vector2 var_animaMa = {0,0};
    Vector2 var_animaBo = {0,0};
    Vector2 var_animaTar[20];
    Vector2 var_animaCar[20];
    bool apertado = false; // Essa variável é usada para saber se o botão POW foi apertado
    bool apertado_anima = false;
    bool apert_anterior = false;
    int n_apertos = 0; // O n�mero de vezes que o Botao POW foi apertado

    //-----------------------------------------------------------------------------------
    // Variáveis da Tela de Entrada
    bool flag_entrada = false;
    char nome[16] = "\0";
    int letterCount = 0;

    //-----------------------------------------------------------------------------------
    // Inicializa sons da fase
    Sound SomInicia = LoadSound("som/inicio.wav");
    Sound SomPulo = LoadSound("som/pulo.wav");
    Sound SomDano= LoadSound("som/dano.wav");
    Sound SomMoeda = LoadSound("som/smb_coin.wav");

    Sound SomVirar = LoadSound("som/virar.wav");
    Sound SomGameOver = LoadSound("som/smb_gameover.wav");
    Sound SomMorte = LoadSound("som/smb_mariodie.wav");

    //-----------------------------------------------------------------------------------
    // Variáveis Menu Carregar Mapa
    Rectangle opcoes_Mapas[6];
    bool flag_n_txts = false;
    int n_arq = 0;
    Color opcoes_cores[6] = {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

    //---------------------------------------------------------------------------------------
    // Loop principal do jogo
    SetTargetFPS(30);
    while (!WindowShouldClose() && !flag_saida)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Carrega o update do menu, está aqui para que não ocorra um Draw antes do Update
        if(prox_tela == N_MENU) UpdateMenu(cores_opcoes, posicao_opcoes, &prox_tela, SomOpcaoMenu, SomSelecinaOpcao);
        switch(prox_tela){
            case N_NOVO:
                //-----------------------------------------------------------------------------------
                // Verifica se a fase já foi carregada
                if(!flag_nivel){
                    n_ind = CarregaFase(&n_turtle, &n_crab, &tempo_espera, n_fase, &Mario, &Botao, cano_pos, Plts, Canos);
                    flag_nivel = true;
                    InitEnemies(&crab_atual, &turtle_atual, n_crab, n_turtle, crab, turtle, &flag_cano, &cano_atual, n_ind, cano_pos, Canos);
                }

                //-----------------------------------------------------------------------------------
                // Verifica se o nome já foi inserido
                if(!flag_entrada){
                    flag_entrada = Entrada(&Jog_Princ, nome, &letterCount);
                    break;
                // Se o nome já tiver sido inserido e o som não tenha tocado, toca a música inicial
                } else if(!flag_som){
                    PlaySound(SomInicia);
                    flag_som = true;
                }

                //-----------------------------------------------------------------------------------
                // Guarda o estado anterior do botão
                    apert_anterior = apertado_anima;

                // Atualiza o Mario e suas colisões
                 UpdateMario(&hit_cooldown_current, hit_cooldown_max, &botao_current, cano_pos, Canos, Plts, n_ind, &Mario, frameMax, &marioSpeedLeft, &marioSpeedRight, &isJumping, &isFalling, &jumpFrameCurrent, &lado, Botao, &apertado, &apertado_anima, SomPulo);

                // Atualiza os sprites da animação
                Anima(&var_animaMa, &var_animaBo, var_animaTar, var_animaCar, isFalling, isJumping, &apertado_anima, n_turtle, turtle, crab, n_crab, &Mario, lado);
                    // Verifica se a animação do botão acabou
                    if(!apert_anterior && apertado_anima){
                        PlaySound(SomDano);
                        PlaySound(SomMoeda);
                        n_apertos++;
                    }

                //-----------------------------------------------------------------------------------
                // Salva o jogo se a tecla A for apertada
                SalvarJogo(n_fase, Mario, Jog_Princ, n_turtle, turtle, n_crab, crab);

                // Atualiza todos os inimigos
                vitoria = UpdateTurtle(SomMorte, SomVirar, &Jog_Princ, crab, &crab_atual, n_crab, &apertado, &hit_cooldown_current, hit_cooldown_max, &turtle_atual, n_turtle, tempo_espera, &tempo_atual, turtle, n_ind, Canos, cano_pos, Plts, Mario, &dano, &mario_invun);

                // Verifica se o jogo acabou
                GanhouPerdeu(&Jog_Princ, &vitoria, &n_fase, &flag_nivel, &prox_tela, &perdeu);
                            break;
                //-----------------------------------------------------------------------------------
            case N_CONTINUAR:
                //-----------------------------------------------------------------------------------
                // Verifica se o save já foi carregado
                if(!flag_nivel){
                    n_ind = CarregaSave(&Mario, &Botao, cano_pos, Plts, Canos, &Jog_Princ, turtle, &n_turtle, crab, &n_crab);
                    PlaySound(SomInicia);
                    flag_nivel = true;
                    InitEnemiesSave(n_crab, n_turtle, crab, turtle);
                }

                //-----------------------------------------------------------------------------------
                // Guarda o estado anterior do botão
                apert_anterior = apertado_anima;

                // Atualiza o Mario e suas colisões
                 UpdateMario(&hit_cooldown_current, hit_cooldown_max, &botao_current, cano_pos, Canos, Plts, n_ind, &Mario, frameMax, &marioSpeedLeft, &marioSpeedRight, &isJumping, &isFalling, &jumpFrameCurrent, &lado, Botao, &apertado, &apertado_anima, SomPulo);

                // Atualiza os sprites da animação
                Anima(&var_animaMa, &var_animaBo, var_animaTar, var_animaCar, isFalling, isJumping, &apertado_anima, n_turtle, turtle, crab, n_crab, &Mario, lado);
                    // Verifica se a animação do botão acabou
                    if(!apert_anterior && apertado_anima){
                        PlaySound(SomDano);
                        PlaySound(SomMoeda);
                        n_apertos++;
                    }

                //-----------------------------------------------------------------------------------
                // Salva o jogo se a tecla A for apertada
                SalvarJogo(n_fase, Mario, Jog_Princ, n_turtle, turtle, n_crab, crab);

                // Atualiza todos os inimigos
                vitoria = UpdateTurtleSave(SomMorte, SomVirar, &Jog_Princ, crab, &crab_atual, n_crab, &apertado, &hit_cooldown_current, hit_cooldown_max, &turtle_atual, n_turtle, tempo_espera, &tempo_atual, turtle, n_ind, Canos, cano_pos, Plts, Mario, &dano, &mario_invun);

                // Verifica se o jogo acabou
                GanhouPerdeu(&Jog_Princ, &vitoria, &n_fase, &flag_nivel, &prox_tela, &perdeu);
                            break;
                //-----------------------------------------------------------------------------------
            case N_CARREGAR_MAPA:
                //-----------------------------------------------------------------------------------
                // Verifica as colisões e a escolha da opção
                UpdateMenuCarregar(opcoes_Mapas, &flag_n_txts, &n_arq, opcoes_cores, &n_fase, &prox_tela, SomSelecinaOpcao);
                // Verifica se a tecla BACKSPACE foi apertada, e se foi, para que volte para o menu
                UpdateVoltar(&prox_tela);
                            break;

            case N_RANKING: Highscores(melhores, &flag_arq); // Abre o arquivo highscores.bin, ele grava seu conteúdo na lista melhores
            case N_AJUDA:
            case N_SOBRE: UpdateVoltar(&prox_tela); // Verifica se a tecla BACKSPACE foi apertada, e se foi, para que volte para o menu
                            break;
            case N_OVER: if(!flag_final){
                UpdateGameOver(&Jog_Princ, melhores, &flag_arq, &flag_final);
            }
                            break;

        }

        //----------------------------------------------------------------------------------

        // Desenhar
        //----------------------------------------------------------------------------------
        switch(prox_tela){
            case N_MENU: DrawMenu(textura_logo, posicao_logo, fonte_mario, opcoes, posicao_opcoes, cores_opcoes);
                            break;

            case N_NOVO:
                if(!flag_entrada){
                        DrawEntrada(nome, letterCount);
                        break;
                }
            //            break;

            case N_CONTINUAR:
                DrawTela(var_animaCar, crab, n_crab, dano, mario_invun, turtle, n_turtle, Jog_Princ, sheet, Plts, n_ind, Botao, fonte_mario, cano_pos, &Mario, lado, n_fase, Canos, var_animaMa.x, var_animaBo.x, n_plat, var_animaTar);
                            break;

            case N_CARREGAR_MAPA: DrawCarregar(opcoes_Mapas, n_arq, opcoes_cores);
                            break;

            case N_RANKING: DrawScores(melhores, fonte_pixel);
                            break;

            case N_AJUDA: DrawAjuda(fonte_mario);
                            break;

            case N_SOBRE: DrawSobre(fonte_mario);
                            break;

            case N_SAIR: flag_saida=true; // Verifica se o bot�o saida foi apertado
                            break;

            case N_OVER: DrawFinal(sheet, &counter_final, &prox_tela, perdeu);
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
    UnloadSound(SomDano);
    UnloadSound(SomMoeda);
    UnloadSound(SomVirar);
    UnloadSound(SomGameOver);
    UnloadSound(SomMorte);

    CloseAudioDevice();            // Close audio device
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
