#include <menu.h>
#include <game.h>
#include <conf.h>

#include <iostream>

Menu::Menu(int hiscore){
    Conf conf;
    TTF_Init();
    font = TTF_OpenFont("Texture/8bitfont.ttf", 24);

    SDL_Rect *tmpR1 = new SDL_Rect;
    SDL_Rect *tmpR2 = new SDL_Rect;
    SDL_Rect *tmpR3 = new SDL_Rect;
    SDL_Rect *tmpR4 = new SDL_Rect;
    SDL_Color tmpNC;
    SDL_Color tmpOC;

    tmpNC.a = 255;
    tmpOC.a = 255;

    tmpR1->w = -1;
    tmpR1->h = -1;
    tmpR1->x = -1;
    tmpR1->y = conf.height / 3 + 0 * conf.tileY;
    tmpNC.r = 255;
    tmpNC.g = 255;
    tmpNC.b = 255;
    tmpOC.r = 255;
    tmpOC.g = 255;
    tmpOC.b = 255;
    TextBlock title(conf.title, tmpR1, tmpNC, tmpOC);
    title.action = -1;
    textBlocks.push_back(title);


    if(hiscore != 0){
        tmpR2->w = -1;
        tmpR2->h = -1;
        tmpR2->x = -1;
        tmpR2->y = conf.height / 3 + 1 * conf.tileY;
        TextBlock hiScore("Rezultat " + std::to_string(hiscore), tmpR2, tmpNC, tmpOC);
        hiScore.action = -1;
        textBlocks.push_back(hiScore);
    }

    tmpOC.r = 128;
    tmpOC.g = 128;

    tmpR3->w = -1;
    tmpR3->h = -1;
    tmpR3->x = -1;
    tmpR3->y = conf.height / 3 + 2 * conf.tileY;
    TextBlock novaIgra("Nova igra", tmpR3, tmpNC, tmpOC);
    novaIgra.action = 0;
    textBlocks.push_back(novaIgra);
    
    tmpR4->w = -1;
    tmpR4->h = -1;
    tmpR4->x = -1;
    tmpR4->y = conf.height / 3 + 3 * conf.tileY;
    TextBlock izhod("Izhod", tmpR4, tmpNC, tmpOC);
    izhod.action = 1;
    textBlocks.push_back(izhod);
}
Menu::~Menu(){
    TTF_CloseFont(font);
    TTF_Quit();
}

TextBlock::TextBlock(std::string _text, SDL_Rect *_destR, SDL_Color _nColor, SDL_Color _oColor){
    text = _text;
    destR = _destR;
    nColor = _nColor;
    oColor = _oColor;
    color = nColor;
}

void Menu::update(Game *game){
    int x, y;
    SDL_PumpEvents();
    bool clicked = (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT));
    for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
        SDL_Rect r = *i->destR;
        if(r.x < x && r.x + r.w > x &&
           r.y < y && r.y + r.h > y){
            i->color = i->oColor;
            if(clicked){
                switch (i->action)
                {
                    case 0:
                        delete this;
                        game->newGame();
                        game->setMenu(NULL);
                        return;

                    case 1:
                        delete game;
                        return;
                }
            }
        }
        else{
            i->color = i->nColor;
        }
    }
}

void Menu::render(SDL_Renderer *renderer){
    for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
        renderText(&*i, renderer);
    }
}

void Menu::renderText(TextBlock *textBlock, SDL_Renderer *renderer){
    SDL_Surface *txtSurface = TTF_RenderText_Solid(font, textBlock->text.c_str(), textBlock->color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, txtSurface);
    Conf conf;
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