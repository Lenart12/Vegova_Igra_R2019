#include <texture.h>
#include <conf.h>

#include <iostream>
#include <SDL2/SDL_image.h>

void Texture::loadTextures(const char *textureLocation, SDL_Renderer *renderer){
    SDL_Texture *tmp = IMG_LoadTexture(renderer, textureLocation);
    if(tmp != NULL)
        textures.push_back(tmp);
    else {
        textures.push_back(tmp);
        std::cout << "Cant load texture: " << textureLocation << std::endl;
    }
}

SDL_Texture* Texture::getTexture(int index){
    for(std::vector< SDL_Texture* > :: iterator i = textures.begin(); i != textures.end(); i++)
    {
        if(index == 0){
            return *i;
        }
        else
        {
            index--;
        }
        
    }
    return nullptr;
}

Texture::~Texture(){
    for(std::vector< SDL_Texture* > :: iterator i = textures.begin(); i != textures.end(); i++)
        SDL_DestroyTexture(*i);
}

void Texture::renderTile(int pos_x, int pos_y, SDL_Texture *tex, SDL_Renderer *renderer){
    static Conf conf;
    SDL_Rect Drect;
    Drect.x = pos_x * conf.tileX;
    Drect.y = pos_y * conf.tileY;
    Drect.w = conf.tileX;
    Drect.h = conf.tileY;
    SDL_RenderCopy(renderer,
                    tex,
                    NULL, &Drect);
}
void Texture::renderTileRotation(int pos_x, int pos_y, int angle, SDL_Texture *tex, SDL_Renderer *renderer){
    static Conf conf;
    SDL_Rect Drect;
    Drect.x = pos_x * conf.tileX;
    Drect.y = pos_y * conf.tileY;
    Drect.w = conf.tileX;
    Drect.h = conf.tileY;
    SDL_RenderCopyEx(renderer, tex, NULL, &Drect, angle, NULL, SDL_FLIP_NONE);
}