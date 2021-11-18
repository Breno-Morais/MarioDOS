#include "../headers/menu.h"
#include <stdlib.h>

Vector2 CarregaFase(int *n_turtle,int *n_crab, int *tempo_espera, int n_fase, Rectangle *Mario, Rectangle *Botao, Vector3 cano_pos[9], Rectangle Plts[10], Rectangle Canos[9]){
    FILE *fase;
    char fase_atual[16];
    char linha_atual[120];
    int coluna, n_linha, x, y, i, n_cano=0, n_plt=0;
    bool flag_stream=false;

    // Faz a formatação do nome do arquivo da fase atual
    sprintf(fase_atual, "fases/fase%d.txt", n_fase);

    if(!(fase = fopen(fase_atual,"r"))) // abre para leitura
        // Imprime se ocorreu algum erro
        printf("Erro na abertura\n");
    else{
        // Carrega linha por linha do arquivo fase.txt
        for(n_linha=0; n_linha<29; n_linha++){
            // Guarda a linha inteira na variável linha_atual
            fscanf(fase,"%s\n", linha_atual);

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
            fgets(linha_atual, 120, fase); //Lê a última linha, guardando a quantidade de inimigos e tempo de espera
            *n_turtle = linha_atual[0]-'0';
            *n_crab = linha_atual[2]-'0';
            *tempo_espera = linha_atual[4]-'0';
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
                                // Aqui ele desenha o cano de entrada virado pra esquerda
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

    fclose(fase);

    return (Vector2){n_cano, n_plt};
}
