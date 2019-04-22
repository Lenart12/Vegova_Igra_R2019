#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <vector>
#include <SDL2/SDL.h>

class Texture{
protected:
    std::vector< SDL_Texture* > textures;
public:
    ~Texture();
    void loadTextures(const char*, SDL_Renderer*);
    SDL_Texture* getTexture(int);
    void renderTile(int, int, SDL_Texture*, SDL_Renderer*);
    void renderTileRotation(int, int, int, SDL_Texture*, SDL_Renderer*);
};

#endif // TEXTURE_H
