#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE


#include "Game.h"
#include "Sprite.h"
#include <SDL_include.h>
#include <string>


using namespace engine;


Sprite::Sprite(GameObject& associated): Component(associated){
    texture = nullptr;
}


Sprite::Sprite(GameObject& associated, std::string file): Component(associated){
    texture = nullptr;
    Open(file.c_str());
}


Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}


void Sprite::Open(std::string file){
    int w = GetWidth();
    int h = GetWidth();

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    SDL_Renderer * renderer = engine::Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer,file.c_str());
    if(texture == nullptr){
        printf("Couldn't load %s\n", SDL_GetError());
    } else {
        if(SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) == 0){
            SetClip(0, 0, height, width);
        }
    }
}


void Sprite::SetClip(int x, int y, int h, int w){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}


void Sprite::Render(int x, int y){
    SDL_Rect dst;
    SDL_Renderer * renderer = engine::Game::GetInstance().GetRenderer();

    dst.x = associated.box.x;
    dst.y = associated.box.y;
    dst.h = GetHeight();
    dst.w = GetWidth();

    if(texture != nullptr){
        SDL_RenderCopy(renderer, texture, &clipRect, &dst);
    } else{
        printf("Error renderzing texture %s\n", SDL_GetError());
    }
}


int Sprite::GetHeight(){
    return height;
}


int Sprite::GetWidth(){
    return width;
}


bool Sprite::IsOpen(){
    if(texture != nullptr){
        return true;
    }
    return false;
}
