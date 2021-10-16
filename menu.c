#include "raylib.h"
#define NUM_OPCOES 7
#define TAM_FONTE 25

int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int TelaLargura = 1200;
    const int TelaAltura = 700;
    bool colisao;
    Vector2 posicao_mouse;
    int i;
    Vector2 TelaMeio = {TelaLargura/2, TelaAltura/2};

    InitWindow(TelaLargura, TelaAltura, "MARIO DOS");

    //--------------------------------------------------------------------------------------
    // Carregar a logo em uma textura e cria o vetor com sua posição
    Texture2D textura_logo = LoadTexture("imagens/sprite_logo.png");        // Texture loading

    float escala_logo = 4;

    Vector2 posicao_logo = {TelaMeio.x - (textura_logo.width*escala_logo)/2, 1};

    //---------------------------------------------------------------------------------------
    // Inicialização da fonte, das opções e suas respectivas posições e cores
    Font fonte_mario = LoadFont("fontes_texto/SuperMario256.ttf");

    const char *opcoes[NUM_OPCOES] = {"NOVO JOGO", "CONTINUAR", "CARREGAR MAPA", "RANKING", "AJUDA", "SOBRE", " SAIR "};
    Color cores_opcoes[NUM_OPCOES] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};

    Rectangle posicao_opcoes[NUM_OPCOES];

    for(i=0; i<NUM_OPCOES; i++){ // Ajuta a distância entre as opções
        posicao_opcoes[i].x = TelaMeio.x - MeasureTextEx(fonte_mario, opcoes[i], TAM_FONTE, 2).x/2;
        posicao_opcoes[i].y = (textura_logo.height*escala_logo) + TAM_FONTE + 5 + 45*i;
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
        // Checa colisão entre o mouse e as opções
        for(i=0; i < NUM_OPCOES; i++){
            posicao_mouse = GetMousePosition();
            colisao = CheckCollisionPointRec(posicao_mouse, posicao_opcoes[i]);
            // Se o mouse estiver em cima de uma opção, ela muda de cor
            if(colisao){
                cores_opcoes[i] = SKYBLUE;

                // Se o mouse clicar na opção
                if(IsMouseButtonDown(0)){
                    cores_opcoes[i] = YELLOW;
                    // Faça algo, dependendo da opção
                    switch(i){
                        case 0: break;
                        case 1: break;
                        case 2: break;
                        case 3: break;
                        case 4: break;
                        case 5: break;
                        case 6: break;
                    }
                }

            } else cores_opcoes[i] = WHITE;

        }

        //----------------------------------------------------------------------------------

        // Desenhar
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawTextureEx(textura_logo, posicao_logo, 0, escala_logo, WHITE);

            for(i=0; i < NUM_OPCOES; i++){
                DrawTextRec(fonte_mario, opcoes[i], posicao_opcoes[i], TAM_FONTE, 2, false, cores_opcoes[i]);
            }

            /*
                // Linhas guia
                DrawLine(0, TelaMeio.y, TelaLargura, TelaMeio.y, GRAY);
                DrawLine(TelaMeio.x, 0, TelaMeio.x, TelaAltura, GRAY);
            */

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Deinicialização
    //--------------------------------------------------------------------------------------
    UnloadTexture(textura_logo);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
