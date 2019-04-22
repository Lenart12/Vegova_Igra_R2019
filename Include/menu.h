#if !defined(MENU_H)
#define MENU_H

class Game;

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <functional>

class TextBlock{
public:
    std::string text;
    SDL_Rect *destR;
    SDL_Color color;
    SDL_Color nColor;
    SDL_Color oColor;
    std::function<void()> callbackFunction;
    TextBlock(std::string _text, int x, int y, int w, int h, SDL_Color _nColor, SDL_Color _oColor, std::function<void()> _callbackFunction);
};

class Menu{
private:
    TTF_Font *font;
    std::vector<TextBlock> textBlocks;
    void renderText(TextBlock*, SDL_Renderer*);
public:
    Menu(Game*);
    ~Menu();
    void update();
    void render(SDL_Renderer*);
};




#endif // MENU_H
