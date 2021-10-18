#include "../headers/menu.h"

int main(void)
{
    // Inicializa��o
    //--------------------------------------------------------------------------------------
    Vector2 Tela = {1200, 700};
    int i, prox_tela; // O prox_tela � o n�mero ser� usado como o indicador do pr�ximo passo

    InitWindow(Tela.x, Tela.y, "MARIO DOS");

    // Inicializa��o e tratamento das vari�veis do Menu
    //--------------------------------------------------------------------------------------
        // Carregar a logo em uma textura e cria o vetor com sua posi��o
        Texture2D textura_logo = LoadTexture("imagens/sprite_logo.png");        // Texture loading

        Vector2 posicao_logo = {Tela.x/2 - (textura_logo.width*4)/2, 1};

        //---------------------------------------------------------------------------------------
        // Inicializa��o da fonte, das op��es e suas respectivas posi��es e cores
        Font fonte_mario = LoadFont("fontes_texto/SuperMario256.ttf");

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
    // Loop principal do jogo
    SetTargetFPS(30);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMenu(cores_opcoes, posicao_opcoes, &prox_tela);
        //----------------------------------------------------------------------------------

        // Desenhar
        //----------------------------------------------------------------------------------
        DrawMenu(&textura_logo, &posicao_logo, &fonte_mario, opcoes, posicao_opcoes, cores_opcoes);
    }

    // Deinicializa��o
    //--------------------------------------------------------------------------------------
    UnloadTexture(textura_logo);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
