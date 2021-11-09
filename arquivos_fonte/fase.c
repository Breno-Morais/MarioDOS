#include "../headers/menu.h"

int CarregaFase(int n_fase, Vector2 *mario_pos, Vector2 *botao_pos, Vector3 cano_pos[9], Rectangle Plts[10]){
    FILE *fase;
    char fase_atual[16];
    char linha_atual[120];
    int coluna, n_linha, x, y, n_cano=0, n_plt=0;
    bool flag_stream=false;

    // Faz a formatação do nome do arquivo da fase atual
    sprintf(fase_atual, "fases/fase%d.txt", n_fase);

    if(!(fase = fopen(fase_atual,"r"))) // abre para leitura
        // Imprime se ocorreu algum erro
        printf("Erro na abertura\n");
    else{
        // Carrega linha por linha do arquivo fase.txt
        for(n_linha=0; n_linha<28; n_linha++){
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
                        mario_pos->x = x;
                        mario_pos->y = y;
                                break;

                    // Se o caractere for igual a C, guarda as coordenadas como a posição do cano, número n_cano
                    case 'c':
                        cano_pos[n_cano].x = x;
                        cano_pos[n_cano].y = y;
                        cano_pos[n_cano].z = 0;
                        n_cano++;
                                break;

                    // Se o caractere for igual a B, guarda as coordenadas como a posição do botão
                    case 'b':
                        botao_pos->x = x;
                        botao_pos->y = y;
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

        fclose(fase);
    }

    return n_plt;
}
