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

void UpdateMario(int *hit_cooldown_current, int hit_cooldown_max, int *botao_current, Vector3 cano_pos[9], Rectangle Canos[9], Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Chao, Rectangle Botao, bool *apertado, Sound SomPulo){
    *isFalling = true;
    *marioSpeedLeft = 8;
    *marioSpeedRight = 8;
    bool PuloAnterior = *isJumping;

    //Testa colis�o com o ch�o e base da plataforma
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
    //Testa colis�o com o teto
    for(int i = 0; i<n_ind.y; i++){
        if(CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width, (*Mario).y}, Plts[i]) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y}, Plts[i])){
            *isJumping = false;
        }
    }
    //Testa colis�o com o bot�o por baixo
    if(CheckCollisionPointRec((Vector2){(*Mario).x+(*Mario).width-5, (*Mario).y}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x+5, (*Mario).y}, Botao)){
        *isJumping = false;
        if((*botao_current)<3 && (*hit_cooldown_current)>=hit_cooldown_max){
            *hit_cooldown_current = 0;
            *apertado = true;
            *botao_current += 1;
        }
    }

    //Testa colis�o com a parede pela esquerda. Se colidir, n�o pode ir pra esquerda
    for(int i = 0; i<n_ind.y; i++){
        if(((!(*lado)) && (CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+1}, *Mario))) || (CheckCollisionPointRec((Vector2){Plts[i].x+Plts[i].width, Plts[i].y+Plts[i].height-1}, *Mario))){
            *marioSpeedLeft = 0;
        }
    }
    //Testa colis�o com o bot�o pela esquerda. Se colidir, n�o pode ir pra esquerda.
    if(!(*lado) && CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y+(*Mario).height}, Botao) || CheckCollisionPointRec((Vector2){(*Mario).x, (*Mario).y+((*Mario).height/2)}, Botao)){
        *marioSpeedLeft = 0;
    }
    //Testa colis�o com os canos pela esquerda
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
    //Testa colis�o com os canos pela direita
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
    //Testa colis�o com a parede pela direita. Se colidir, n�o pode ir pra direita.
    for(int i = 0; i<n_ind.y; i++){
        if(*lado && CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+1}, *Mario) || CheckCollisionPointRec((Vector2){Plts[i].x, Plts[i].y+Plts[i].height-1}, *Mario)){
            *marioSpeedRight = 0;
        }
    }
    //Testa colis�o com o bot�o pela direita. Se colidir, n�o pode ir pra direita.
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
    //Se aperta D e n�o tiver caindo, pula
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

void InitEnemies(int *crab_atual, int *turtle_atual,int n_crab, int n_turtle, CRAB crab[20], TURTLE turtle[20], bool *flag_cano, int *cano_atual, Vector2 n_ind, Vector3 cano_pos[9], Rectangle Canos[9]){
    //se houver tartarugas, o primeiro inimigo a sair � tartaruga, senao � caranguejo
    if(*turtle_atual<n_turtle)
        *turtle_atual = 1;
    else if(*crab_atual<n_turtle)
        *crab_atual = 1;
    //inicializa tartarugas
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
        //inicializa caranguejos
    for(int i=0; i<n_crab; i++){
        crab[i].crabRec.width = 48;
        crab[i].crabRec.height = 48;
        while(!(*flag_cano)){
            *cano_atual = 0 + (rand() % ((int)n_ind.x - 0 + 1));
            if(cano_pos[(int)*cano_atual].z==0){
                if(Canos[(int)*cano_atual].x<LARGURA_TELA/2){
                    crab[i].crabRec.x = Canos[0].x+Canos[0].width;
                    crab[i].crabRec.y = Canos[0].y+15;
                    crab[i].sentido = 1;
                }
                else{
                    crab[i].crabRec.x = Canos[1].x-crab[i].crabRec.width;
                    crab[i].crabRec.y = Canos[1].y+15;
                    crab[i].sentido = -1;
                }
                *flag_cano = true;
            }
        }
        *flag_cano = false;
        crab[i].estado = 0;
        crab[i].isThere = false;
        crab[i].fall = false;
    }
}

void UpdateTurtle(CRAB crab[20], int *crab_atual, int n_crab, bool *apertado, int *hit_cooldown_current, int hit_cooldown_max, int *turtle_atual, int n_turtle, int tempo_espera, int *tempo_atual, TURTLE turtle[20], Vector2 n_ind, Rectangle Canos[9], Vector3 cano_pos[9],Rectangle Plts[10], Rectangle Mario, Rectangle Chao){

    //vai spawnando os tartarugas a cada "tempo_espera" segundos (ou a cada 30 frames, como foi escrito)
    if(*turtle_atual<n_turtle){
        if((*tempo_atual)<30*tempo_espera){
            *tempo_atual = (*tempo_atual)+1;
        }
        else{
            *turtle_atual = (*turtle_atual)+1;
            *tempo_atual = 0;
        }
    }
    //vai spawnando os caranguejos a cada "tempo_espera" segundos (ou a cada 30 frames, como foi escrito)
    if(*turtle_atual>=n_turtle && *crab_atual<n_crab){
        if((*tempo_atual)<30*tempo_espera){
            *tempo_atual = (*tempo_atual)+1;
        }
        else{
            *crab_atual = (*crab_atual)+1;
            *tempo_atual = 0;
        }
    }
    DrawText(TextFormat("%d", *crab_atual), 600, 100, 30, RED);

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
            //rebate nos inimigos e muda de dire��o
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
                    if(CheckCollisionPointRec((Vector2){Mario.x+(Mario.width/2), Mario.y-20}, turtle[i].turtleRec) && turtle[i].estado==0){
                        if((*hit_cooldown_current)>=hit_cooldown_max){
                            turtle[i].estado = turtle[i].estado+1;
                            *hit_cooldown_current = 0;
                        }
                    }
                }
            }//atualiza o turtle.fall
            if(CheckCollisionRecs(turtle[i].turtleRec, Chao)){
                turtle[i].fall = false;
            }

            if(turtle[i].estado==0){ //ESTADO INVULNERAVEL
                turtle[i].speed = 2;
                turtle[i].isThere = true;
                if(CheckCollisionRecs(Mario, turtle[i].turtleRec)){
                    //MARIO PERDE VIDA
                }
                if(*apertado && turtle[i].isThere){
                    turtle[i].estado += 1;
                }
            }
            else if(turtle[i].estado==1){//ESTADO VULNERAVEL
                turtle[i].isThere = true;
                turtle[i].speed = 0;
                if(CheckCollisionRecs(Mario, turtle[i].turtleRec)){
                    turtle[i].estado += 1;
                }
                if(*apertado && turtle[i].isThere){
                    turtle[i].estado += 1;
                }
            }
            else if(turtle[i].estado==2){//ESTADO MORTO
                turtle[i].isThere = false;//para de desenhar o inimigo
                turtle[i].turtleRec.y = ALTURA_TELA;//joga ele pra fora da tela (embaixo)
            }
            else{
                turtle[i].estado = 2;
            }
        }
        //---------------------------------------CARANGUEJOS------------------------------------------------------
        for(int i=0; i<*crab_atual; i++){
            //DrawText(TextFormat("%d", (int)n_ind.x), 600, 100, 30, RED);
            //atualiza o crabRec.x
            crab[i].crabRec.x = crab[i].crabRec.x + (crab[i].speed*crab[i].sentido);
            //logica dos canos de retorno
            for(int j=0;j<(int)n_ind.x;j++){
                if(CheckCollisionRecs(Canos[j], crab[i].crabRec) && cano_pos[j].z!=0){
                    if(cano_pos[j].x<600){
                        crab[i].crabRec.x = Canos[0].x+Canos[0].width;
                        crab[i].crabRec.y = Canos[0].y+15;
                    }
                    else{
                        crab[i].crabRec.x = Canos[1].x-crab[i].crabRec.width;
                        crab[i].crabRec.y = Canos[1].y+15;
                    }
                    if(crab[i].sentido==1)
                        crab[i].sentido=-1;
                    else if(crab[i].sentido==-1)
                        crab[i].sentido=1;
                }
            }
            //rebate nos inimigos e muda de dire��o
            for(int j=0;j<*crab_atual;j++){
                if(CheckCollisionRecs(crab[i].crabRec, crab[j].crabRec) && i!=j){
                    if(crab[i].sentido==1){
                        crab[i].crabRec.x = crab[i].crabRec.x-4;
                        crab[i].sentido=-1;
                        crab[j].sentido=1;
                    }
                    else if(crab[i].sentido==-1){
                        crab[i].crabRec.x = crab[i].crabRec.x+4;
                        crab[i].sentido=1;
                        crab[j].sentido=-1;
                    }
                }
            }
            //passando da direita pra esquerda
            if(crab[i].crabRec.x+(crab[i].crabRec.width/2)>=LARGURA_TELA){
                crab[i].crabRec.x = 0-(crab[i].crabRec.width/2);
            }//passando da esquerda pra direita
            else if(crab[i].crabRec.x+(crab[i].crabRec.width/2)<0){
                crab[i].crabRec.x = LARGURA_TELA-(crab[i].crabRec.width/2);
            }
            //atualiza o crabRec.y
            if(crab[i].fall==true){
                crab[i].crabRec.y = crab[i].crabRec.y+4;
            }

            //atualiza o crab.fall
            crab[i].fall = true;
            for(int j=0; j<n_ind.y;j++){
                if(CheckCollisionRecs(crab[i].crabRec, Plts[j])){
                    crab[i].fall = false;
                    //atualiza o crab.estado
                    if(CheckCollisionPointRec((Vector2){Mario.x+(Mario.width/2), Mario.y-20}, crab[i].crabRec) && crab[i].estado<2){
                        if((*hit_cooldown_current)>=hit_cooldown_max){
                            crab[i].estado = crab[i].estado+1;
                            *hit_cooldown_current = 0;
                        }
                    }
                }
            }//atualiza o crab.fall
            if(CheckCollisionRecs(crab[i].crabRec, Chao)){
                crab[i].fall = false;
            }

            if(crab[i].estado==0){ //ESTADO INVULNERAVEL
                crab[i].speed = 2;
                crab[i].isThere = true;
                if(CheckCollisionRecs(Mario, crab[i].crabRec)){
                    //MARIO PERDE VIDA
                }
                if(*apertado && crab[i].isThere){
                    crab[i].estado += 1;
                }
            }
            else if(crab[i].estado==1){//ESTADO FURIOSO
                crab[i].isThere = true;
                crab[i].speed = 4;
                if(CheckCollisionRecs(Mario, crab[i].crabRec)){
                    //MARIO PERDE VIDA
                }
                if(*apertado && crab[i].isThere){
                    crab[i].estado += 1;
                }
            }
            else if(crab[i].estado==2){//ESTADO VULNERAVEL
                crab[i].isThere = true;
                crab[i].speed = 0;
                if(CheckCollisionRecs(Mario, crab[i].crabRec)){
                    crab[i].estado += 1;
                }
                if(*apertado && crab[i].isThere){
                    crab[i].estado += 1;
                }
            }
            else if(crab[i].estado==3){//ESTADO MORTO
                crab[i].isThere = false;//para de desenhar o inimigo
                crab[i].crabRec.y = ALTURA_TELA;//joga ele pra fora da tela (embaixo)
            }
            else{
                crab[i].estado = 3;
            }
        }
        *apertado = false;
        *hit_cooldown_current = *hit_cooldown_current+1;
}
