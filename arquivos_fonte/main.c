#include "../headers/menu.h"

int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    Vector2 Tela = {1200, 700};
    int i, prox_tela; // O prox_tela é o número será usado como o indicador do próximo passo

    InitWindow(Tela.x, Tela.y, "MARIO DOS");

    // Inicialização e tratamento das variáveis do Menu
    //--------------------------------------------------------------------------------------
        // Carregar a logo em uma textura e cria o vetor com sua posição
        Texture2D textura_logo = LoadTexture("imagens/sprite_logo.png");        // Texture loading

        Vector2 posicao_logo = {Tela.x/2 - (textura_logo.width*4)/2, 1};

        //---------------------------------------------------------------------------------------
        // Inicialização da fonte, das opções e suas respectivas posições e cores
        Font fonte_mario = LoadFont("fontes_texto/SuperMario256.ttf");

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

    // Deinicialização
    //--------------------------------------------------------------------------------------
    UnloadTexture(textura_logo);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
