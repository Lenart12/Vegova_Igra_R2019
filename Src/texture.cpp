#include <texture.h>

#include <SDL2/SDL_image.h>

void Texture::loadTextures(const char *textureLocation, SDL_Renderer *renderer){
    SDL_Texture *tmp = IMG_LoadTexture(renderer, textureLocation);
    textures.push_back(tmp);
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