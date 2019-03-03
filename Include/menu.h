#if !defined(MENU_H)
#define MENU_H

class Game;

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class TextBlock{
public:
    const char *text;
    SDL_Rect *destR;
    SDL_Color color;
    SDL_Color nColor;
    SDL_Color oColor;
    TextBlock(const char*, SDL_Rect*, SDL_Color, SDL_Color);
    int action;
};

class Menu{
private:
    TTF_Font *font;
    std::vector<TextBlock> textBlocks;
    void renderText(TextBlock*, SDL_Renderer*);
public:
    Menu(int);
    ~Menu();
    void update(Game*);
    void render(SDL_Renderer*);
};




#endif // MENU_H
