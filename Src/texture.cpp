#include <texture.h>
#include <conf.h>

#include <iostream>
#include <SDL_image.h>

#include <direct.h>

SDL_Texture* Texture::getPlaceholder(int r, int g, int b, SDL_Renderer* renderer) {
	static Conf conf;
	SDL_Surface* surf = SDL_CreateRGBSurface(0, conf.tileX, conf.tileCntY, 32, 0, 0, 0, 0);
	SDL_FillRect(surf, NULL, SDL_MapRGBA(surf->format, r, g, b, 255));
	return SDL_CreateTextureFromSurface(renderer, surf);
}

void Texture::loadTextures(const char *textureLocation, SDL_Renderer *renderer){
    SDL_Texture *tmp = IMG_LoadTexture(renderer, textureLocation);
    if(tmp != NULL)
        textures.push_back(tmp);
    else {
        textures.push_back(getPlaceholder(rand() % 256, rand() % 256, rand() % 256, renderer));
        std::cout << "Cant load texture: " << _getcwd(NULL, 0) << '\\' << textureLocation << std::endl;
		std::cout << "Reason: " << SDL_GetError() << '\n';
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
	if (pos_x < 0)
		std::cout << "ALERT: Rendering outside bounds -x\n";
	if (pos_x > conf.tileCntX)
		std::cout << "ALERT: Rendering outside bounds +x\n";
	if (pos_y < 0)
		std::cout << "ALERT: Rendering outside bounds -y\n";
	if (pos_y > conf.tileCntY)
		std::cout << "ALERT: Rendering outside bounds +y\n";
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