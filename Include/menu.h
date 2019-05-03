#if !defined(MENU_H)
#define MENU_H

class Game;

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <functional>

enum ReturnAction {
    MENU_NOTHING,
    MENU_SAVE_GAME,
    MENU_NEW_GAME,
    MENU_QUIT,
    MENU_LOAD_GAME,
    MENU_RESUME,
    MENU_SAVE_RESULT,
    MENU_INPUT_NAME,
    MENU_WATCH_REPLAY
};

enum GameState{
    STATE_NOTHING,
    STATE_ACTIVE,
    STATE_TEXT_INPUT,
    STATE_GAME_OVER
};

enum MenuPage{
    PAGE_START,
    PAGE_PAUSED,
    PAGE_RESULT,
    PAGE_SAVE_RESULT,
    PAGE_SAVE_STATE
};

class TextBlock{
public:
    std::string text;
    SDL_Rect *destR;
    SDL_Color color;
    SDL_Color nColor;
    SDL_Color oColor;
    std::function<ReturnAction()> callbackFunction;
    TextBlock(std::string _text, int x, int y, int w, int h, SDL_Color _nColor, SDL_Color _oColor, std::function<ReturnAction()> _callbackFunction);
};

class Menu{
private:
    TTF_Font *font;
    std::vector<TextBlock> textBlocks;
    void renderText(TextBlock*, SDL_Renderer*);
    GameState currentState;
public:
    std::string message;
    Menu();
    ~Menu();
    ReturnAction update(GameState state, SDL_Renderer *renderer);
    void render(SDL_Renderer*);

    void loadPage(MenuPage page);
};




#endif // MENU_H
