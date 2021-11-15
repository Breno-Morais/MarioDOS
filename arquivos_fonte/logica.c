#include "../headers/menu.h"

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

void UpdateMario(Rectangle Plts[10], Vector2 n_ind, Rectangle *Mario, float frameMax, float *marioSpeedLeft, float *marioSpeedRight, bool *isJumping, bool *isFalling, float *jumpFrameCurrent, bool *lado, Rectangle Chao, Rectangle Botao, bool *apertado, Sound SomPulo){
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
    //Se aperta a seta de cima e não tiver caindo, pula
    if(IsKeyPressed(KEY_UP)){
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
