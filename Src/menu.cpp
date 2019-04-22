#include <menu.h>
#include <game.h>
#include <conf.h>

#include <iostream>

Menu::Menu(Game *game){
    static Conf conf;
    font = TTF_OpenFont("Texture/8bitfont.ttf", 24);

    SDL_Color tmpNC;
    SDL_Color tmpOC;

    tmpNC.a = 255;
    tmpOC.a = 255;
    tmpNC.r = 255;
    tmpNC.g = 255;
    tmpNC.b = 255;
    tmpOC.r = 128;
    tmpOC.g = 128;
    tmpOC.b = 255;

    textBlocks.push_back(TextBlock(conf.title, -1, conf.height / 3 + 0 * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));
    textBlocks.push_back(
        TextBlock(
            "Nova Igra",
            -1, conf.height / 3 + 2 * conf.tileY,
            -1, -1,
            tmpNC, tmpOC,
            [this, game](){
                delete this;
                game->newGame();
                game->setMenu(NULL);
            }
        )
    );
    textBlocks.push_back(
        TextBlock(
            "Izhod",
            -1, conf.height / 3 + 3 * conf.tileY,
            -1, -1,
            tmpNC, tmpOC,
            [game](){
                game->Running(false);
            }
        )
    );
}
Menu::~Menu(){
    TTF_CloseFont(font);
}

TextBlock::TextBlock(std::string _text, int x, int y, int w, int h, SDL_Color _nColor, SDL_Color _oColor, std::function<void()> _callbackFunction){
    text = _text;
    destR = new SDL_Rect();
    destR->x = x;
    destR->y = y;
    destR->w = w;
    destR->h = h;
    nColor = _nColor;
    oColor = _oColor;
    color = nColor;
    callbackFunction = _callbackFunction;
}

void Menu::update(){
    int x, y;
    SDL_PumpEvents();
    bool clicked = (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT));
    for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
        SDL_Rect r = *i->destR;
        if(r.x < x && r.x + r.w > x &&
           r.y < y && r.y + r.h > y){
            i->color = i->oColor;
            if(clicked){
                if(i->callbackFunction != NULL)
                    i->callbackFunction();
            }
        }
        else{
            i->color = i->nColor;
        }
    }
}

void Menu::render(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 18, 35, 95, 255);
    SDL_RenderFillRect(renderer, NULL);
    for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
        renderText(&*i, renderer);
    }
}

void Menu::renderText(TextBlock *textBlock, SDL_Renderer *renderer){
    SDL_Surface *txtSurface = TTF_RenderText_Solid(font, textBlock->text.c_str(), textBlock->color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, txtSurface);
    static Conf conf;
    if(textBlock->destR != NULL){
        if(textBlock->destR->w == -1)
            textBlock->destR->w = txtSurface->w;
        if(textBlock->destR->h == -1)
            textBlock->destR->h = txtSurface->h;
        if(textBlock->destR->x == -1)
            textBlock->destR->x = conf.width / 2 - textBlock->destR->w / 2;
        if(textBlock->destR->y == -1)
            textBlock->destR->y = conf.height / 2 - textBlock->destR->h / 2;
    }
    SDL_RenderCopy(renderer, tex, NULL, textBlock->destR);
    SDL_FreeSurface(txtSurface);
}