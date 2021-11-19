#include "../headers/menu.h"
#include <time.h>

void Anima(int *framesCounter, int *ind_animaMa, int *ind_animaBo, bool isFalling, bool isJumping){
    *framesCounter+=1;

    if(isJumping){
        *ind_animaMa = 6;
    }
    else if(isFalling){
        *ind_animaMa = 7;
    } else if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)){
        if(*framesCounter >= (30/10)){
            *framesCounter = 0;
            *ind_animaMa+=1;

            if(*ind_animaMa == 5 || *ind_animaMa >= 7) *ind_animaMa = 0;
            if(*ind_animaMa == 2) *ind_animaMa = 3;
        }
    } else *ind_animaMa=0;
}

void UpdateMario(Vector3 cano_pos[9], Rectangle Canos[9], Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Chao, Rectangle Botao, bool *apertado, Sound SomPulo){
    *isFalling = true;
    *marioSpeedLeft = 8;
    *marioSpeedRight = 8;
    bool PuloAnterior = *isJumping;

    //Testa colisão com o chão e base da plataforma
    if(CheckCollisionPointRec((Vector2){(*Mario).x+1, (*Mario).y+(*Mario).height}, Chao) || CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width-1, (*Mario).y+(*Mario).height}, Chao)){
        *isFalling = false;
        (*Mario).y = Chao.y-(*Mario).height+5;
    }
    for(int i = 0; i<n_ind.y; i++){
        if(CheckCollisionPointRec((Vector2){(*Mario).x+1, (*Mario).y+(*Mario).height}, Plts[i]) || CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width-1, (*Mario).y+(*Mario).height}, Plts[i])){
            *isFalling = false;
            (*Mario).y = Plts[i].y-(*Mario).height;
        }
    }
    //Testa colisão com o teto
    for(int i = 0; i<n_ind.y; i++){
        if(CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y}, Plts[i]) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y}, Plts[i])){
            *isJumping = false;
        }
    }
    //Testa colisão com o botão por baixo
    if(CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y}, Botao)){
        *isJumping = false;
        *apertado = true;
    }

    //Testa colisão com a parede pela esquerda. Se colidir, não pode ir pra esquerda
    for(int i = 0; i<n_ind.y; i++){
        if(((!(*lado)) && (CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+1}, *Mario))) || (CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+Plts[i].height-1}, *Mario))){
            *marioSpeedLeft = 0;
        }
    }
    //Testa colisão com o botão pela esquerda. Se colidir, não pode ir pra esquerda.
    if(!(*lado) && CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y+(*Mario).height}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y+((*Mario).height/2)}, Botao)){
        *marioSpeedLeft = 0;
    }
    //Testa colisão com os canos pela esquerda
    for(int i=0; i<n_ind.x; i++){
        if(cano_pos[i].z==0){
            if(!(*lado) && CheckCollisionRecs((Rectangle){Canos[i].x,0,Canos[i].width,Canos[i].y+Canos[i].height}, *Mario)){
                *marioSpeedLeft = 0;
            }
        }
        else{
            if(!(*lado) && CheckCollisionRecs(Canos[i], *Mario)){
                *marioSpeedLeft = 0;
            }
        }
    }
    //Testa colisão com os canos pela direita
    for(int i=0; i<n_ind.x; i++){
        if(cano_pos[i].z==0){
            if((*lado) && CheckCollisionRecs((Rectangle){Canos[i].x,0,Canos[i].width,Canos[i].y+Canos[i].height}, *Mario)){
                *marioSpeedRight = 0;
            }
        }
        else{
            if((*lado) && CheckCollisionRecs(Canos[i], *Mario)){
                *marioSpeedRight = 0;
            }
        }
    }
    //Testa colisão com a parede pela direita. Se colidir, não pode ir pra direita.
    for(int i = 0; i<n_ind.y; i++){
        if(*lado && CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+1}, *Mario) || CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+Plts[i].height-1}, *Mario)){
            *marioSpeedRight = 0;
        }
    }
    //Testa colisão com o botão pela direita. Se colidir, não pode ir pra direita.
    if(*lado && CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y+(*Mario).height}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y+((*Mario).height/2)}, Botao)){
        *marioSpeedRight = 0;
    }

    //Se aperta a seta direita, vai pra direita
    if(IsKeyDown(KEY_RIGHT)){
        (*Mario).x += *marioSpeedRight;
        *lado = true;
    }
    //Se aperta a seta esquerda, vai pra esquerda
    else if(IsKeyDown(KEY_LEFT)){
        (*Mario).x -= *marioSpeedLeft;
        *lado = false;
    }
    //Se aperta D e não tiver caindo, pula
    if(IsKeyPressed(KEY_D)){
        if(*isFalling==false)
            *isJumping = true;
    }

    if(*isJumping != PuloAnterior){
        PlaySound(SomPulo);
    }

    //Pulo do Mario
    if(*isJumping){
        *jumpFrameCurrent = *jumpFrameCurrent+1;
        (*Mario).y -= 20;
        if(*jumpFrameCurrent>=frameMax){
            *jumpFrameCurrent = 0;
            *isJumping = false;
            *isFalling = true;
        }
    }
    //Queda do Mario
    else if(*isFalling){
        *jumpFrameCurrent = 0;
        (*Mario).y+=10;
    }

    //Mario passa da direita pra esquerda da tela
    if((*Mario).x+((*Mario).width/2)>=LARGURA_TELA){
        (*Mario).x = 0-((*Mario).width/2);
    }
    //Mario passa da esquerda pra direita da tela
    if((*Mario).x+((*Mario).width/2)<0){
        (*Mario).x = LARGURA_TELA-((*Mario).width/2);
    }
}

void InitTurtle(int *turtle_atual, int n_turtle, TURTLE turtle[20], bool *flag_cano, int *cano_atual, Vector2 n_ind, Vector3 cano_pos[9], Rectangle Canos[9]){
    if(*turtle_atual<n_turtle)
        *turtle_atual = 1;
    for(int i=0; i<n_turtle; i++){
        turtle[i].turtleRec.width = 48;
        turtle[i].turtleRec.height = 48;
        while(!(*flag_cano)){
            *cano_atual = 0 + (rand() % ((int)n_ind.x - 0 + 1));
            if(cano_pos[(int)*cano_atual].z==0){
                if(Canos[(int)*cano_atual].x<LARGURA_TELA/2){
                    turtle[i].turtleRec.x = Canos[0].x+Canos[0].width;
                    turtle[i].turtleRec.y = Canos[0].y+15;
                    turtle[i].sentido = 1;
                }
                else{
                    turtle[i].turtleRec.x = Canos[1].x-turtle[i].turtleRec.width;
                    turtle[i].turtleRec.y = Canos[1].y+15;
                    turtle[i].sentido = -1;
                }
                *flag_cano = true;
            }
        }
        *flag_cano = false;

        turtle[i].estado = 0;
        turtle[i].isThere = false;
        turtle[i].fall = false;
    }
}

void UpdateTurtle(bool apertado, int *hit_cooldown_current, int hit_cooldown_max, int *turtle_atual, int n_turtle, int tempo_espera, int *tempo_atual, TURTLE turtle[20], Vector2 n_ind, Rectangle Canos[9], Vector3 cano_pos[9],Rectangle Plts[10], Rectangle Mario, Rectangle Chao){

    //vai spawnando os inimigos a cada "tempo_espera" segundos (ou a cada 30 frames, como foi escrito)
    if(*turtle_atual<n_turtle){
        if((*tempo_atual)<30*tempo_espera){
            *tempo_atual = (*tempo_atual)+1;
        }
        else{
            *turtle_atual = (*turtle_atual)+1;
            *tempo_atual = 0;
        }
    }

    for(int i=0; i<*turtle_atual; i++){
            //DrawText(TextFormat("%d", (int)n_ind.x), 600, 100, 30, RED);
            //atualiza o turtleRec.x
            turtle[i].turtleRec.x = turtle[i].turtleRec.x + (turtle[i].speed*turtle[i].sentido);
            //logica dos canos de retorno
            for(int j=0;j<(int)n_ind.x;j++){
                if(CheckCollisionRecs(Canos[j], turtle[i].turtleRec) && cano_pos[j].z!=0){
                    if(cano_pos[j].x<600){
                        turtle[i].turtleRec.x = Canos[0].x+Canos[0].width;
                        turtle[i].turtleRec.y = Canos[0].y+15;
                    }
                    else{
                        turtle[i].turtleRec.x = Canos[1].x-turtle[i].turtleRec.width;
                        turtle[i].turtleRec.y = Canos[1].y+15;
                    }
                    if(turtle[i].sentido==1)
                        turtle[i].sentido=-1;
                    else if(turtle[i].sentido==-1)
                        turtle[i].sentido=1;
                }
            }
            //rebate nos inimigos e muda de direção
            for(int j=0;j<*turtle_atual;j++){
                if(CheckCollisionRecs(turtle[i].turtleRec, turtle[j].turtleRec) && i!=j){
                    if(turtle[i].sentido==1){
                        turtle[i].turtleRec.x = turtle[i].turtleRec.x-4;
                        turtle[i].sentido=-1;
                        turtle[j].sentido=1;
                    }
                    else if(turtle[i].sentido==-1){
                        turtle[i].turtleRec.x = turtle[i].turtleRec.x+4;
                        turtle[i].sentido=1;
                        turtle[j].sentido=-1;
                    }
                }
            }
            //passando da direita pra esquerda
            if(turtle[i].turtleRec.x+(turtle[i].turtleRec.width/2)>=LARGURA_TELA){
                turtle[i].turtleRec.x = 0-(turtle[i].turtleRec.width/2);
            }//passando da esquerda pra direita
            else if(turtle[i].turtleRec.x+(turtle[i].turtleRec.width/2)<0){
                turtle[i].turtleRec.x = LARGURA_TELA-(turtle[i].turtleRec.width/2);
            }
            //atualiza o turtleRec.y
            if(turtle[i].fall==true){
                turtle[i].turtleRec.y = turtle[i].turtleRec.y+4;
            }

            //atualiza o turtle.fall
            turtle[i].fall = true;
            for(int j=0; j<n_ind.y;j++){
                if(CheckCollisionRecs(turtle[i].turtleRec, Plts[j])){
                    turtle[i].fall = false;
                    //atualiza o turtle.estado
                    if(CheckCollisionPointRec((Vector2){Mario.x+(Mario.width/2), Mario.y-20}, turtle[i].turtleRec)){
                        if((*hit_cooldown_current)>=hit_cooldown_max){
                            turtle[i].estado = turtle[i].estado+1;
                            *hit_cooldown_current = 0;
                        }
                    }
                }
            }
            if(CheckCollisionRecs(turtle[i].turtleRec, Chao)){
                turtle[i].fall = false;
            }

            if(turtle[i].estado==0){ //ESTADO INVULNERAVEL
                turtle[i].speed = 2;
                turtle[i].isThere = true;
                if(CheckCollisionRecs(Mario, turtle[i].turtleRec)){
                    //MARIO PERDE VIDA
                }
            }
            else if(turtle[i].estado==1){//ESTADO VULNERAVEL
                turtle[i].isThere = true;
                turtle[i].speed = 0;
                if(CheckCollisionRecs(Mario, turtle[i].turtleRec)){
                    turtle[i].estado++;
                }
            }
            else if(turtle[i].estado==2){//ESTADO MORTO
                turtle[i].isThere = false;//para de desenhar o inimigo
                turtle[i].turtleRec.y = ALTURA_TELA;//joga ele pra fora da tela (embaixo)
            }
        }
        *hit_cooldown_current = *hit_cooldown_current+1;
}
