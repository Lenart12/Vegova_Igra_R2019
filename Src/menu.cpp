#include <menu.h>
#include <game.h>
#include <conf.h>

#include <iostream>

Menu::Menu(){
    font = TTF_OpenFont("Texture/8bitfont.ttf", 24);
    loadPage(PAGE_START);
}
Menu::~Menu(){
    TTF_CloseFont(font);
}

void Menu::loadPage(MenuPage page){
    textBlocks.clear();

    static Conf conf;
    SDL_Color tmpNC = {255, 255, 255, 255};
    SDL_Color tmpOC = {128, 128, 255, 255};
    SDL_Color tmpAL = {255, 0, 0, 255};

    int i = 0;
    switch (page){
        case PAGE_START:{
            textBlocks.push_back(TextBlock(conf.title, -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));
            textBlocks.push_back(TextBlock("%message%", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpAL, tmpAL, NULL));
            textBlocks.push_back(TextBlock("Nova Igra", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_NEW_GAME;}));
            textBlocks.push_back(TextBlock("Nalozi igro", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_LOAD_GAME;}));
            textBlocks.push_back(TextBlock("Rezultati", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        [this]() -> ReturnAction{ loadPage(PAGE_RESULT); return MENU_NOTHING;}));
            textBlocks.push_back(TextBlock("Ogled zadnje igre", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_WATCH_REPLAY;}));
            textBlocks.push_back(TextBlock("Izhod", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_QUIT;}));
            break;
        }
        case PAGE_PAUSED: {
            textBlocks.push_back(TextBlock("Pavza", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));
            textBlocks.push_back(TextBlock("%message%", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpAL, tmpAL, NULL));
            textBlocks.push_back(TextBlock("Nadaljuj igro", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_RESUME;}));
            textBlocks.push_back(TextBlock("Zakljuci igro", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_INPUT_NAME;}));
            textBlocks.push_back(TextBlock("Nova igra", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_NEW_GAME;}));
            textBlocks.push_back(TextBlock("Shrani igro", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_SAVE_GAME;}));
            textBlocks.push_back(TextBlock("Nalozi igro", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_LOAD_GAME;}));
            textBlocks.push_back(TextBlock("Izhod", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        []() -> ReturnAction{ return MENU_QUIT;}));
            break;
        }
        case PAGE_RESULT: {
            textBlocks.push_back(TextBlock("Rezultati", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));
            textBlocks.push_back(TextBlock("%message%", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpAL, tmpAL, NULL));
            
            for(Result r : Replay::loadResult(5)){
                std::string result = r.name + (std::string)": " + std::to_string(r.score);
                textBlocks.push_back(TextBlock(result, -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));

            }

            textBlocks.push_back(TextBlock("Nazaj", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        [this]() -> ReturnAction{ loadPage(PAGE_START); return MENU_NOTHING;}));
            break;
            
        }
        case PAGE_SAVE_RESULT:{
            textBlocks.push_back(TextBlock("Tvoje ime", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpNC, NULL));
            textBlocks.push_back(TextBlock("%message%", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpAL, tmpAL, NULL));
            textBlocks.push_back(TextBlock("%input%", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpOC, tmpOC, NULL));
            textBlocks.push_back(TextBlock("Shrani", -1, conf.height / 3 + i++ * conf.tileY, -1, -1, tmpNC, tmpOC,
                        [this]() -> ReturnAction{ loadPage(PAGE_START); currentState = STATE_NOTHING; return MENU_SAVE_RESULT;}));
            break;
        }
        case PAGE_SAVE_STATE:{
            break;
        }
    }
}



TextBlock::TextBlock(std::string _text, int x, int y, int w, int h, SDL_Color _nColor, SDL_Color _oColor, std::function<ReturnAction()> _callbackFunction){
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

ReturnAction Menu::update(GameState state, SDL_Renderer *renderer){
    int x, y;
    bool clicked = (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT));
    if(currentState != state){    
        switch(state){
            case STATE_ACTIVE:{
                loadPage(PAGE_PAUSED);
                break;
            }
            case STATE_NOTHING:{
                loadPage(PAGE_START);
                break;
            }
            case STATE_TEXT_INPUT:{
                break;
            }
            case STATE_GAME_OVER:{
                loadPage(PAGE_SAVE_RESULT);
                state = STATE_TEXT_INPUT;
                break;
            }
        }
        currentState = state;
    }
    if(currentState != STATE_TEXT_INPUT){
        for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
            SDL_Rect r = *i->destR;
            if(r.x < x && r.x + r.w > x &&
            r.y < y && r.y + r.h > y){
                i->color = i->oColor;
                if(clicked){
                    if(i->callbackFunction != NULL){
                        message = "";
                        return i->callbackFunction();
                    }
                }
            }
            else{
                i->color = i->nColor;
            }
        }
        return MENU_NOTHING;
    }
    else{
        SDL_StartTextInput();
        std::string input = "";
        while(true){
            SDL_GetMouseState(&x, &y);
            SDL_Event event;
            clicked = false;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    return MENU_QUIT;
                }
                else if(event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN){
                    if(event.type == SDL_KEYDOWN){
                        if(event.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0){
                            input = input.substr(0, input.length() - 1);
                        }
                    }
                    else{
                        input +=  event.text.text;
                    }
                }
                else if(event.type == SDL_MOUSEBUTTONDOWN){
                    clicked = true;
                }
            }
            Input::textInput = input;
            for(std::vector< TextBlock > :: iterator i = textBlocks.begin(); i != textBlocks.end(); i++){
                SDL_Rect r = *i->destR;
                if(r.x < x && r.x + r.w > x &&
                r.y < y && r.y + r.h > y){
                    i->color = i->oColor;
                    if(clicked){
                        if(i->callbackFunction != NULL){
                            message = "";
                            SDL_StopTextInput();
                            return i->callbackFunction();
                        }
                    }
                }
                else{
                    i->color = i->nColor;
                }
            }

            SDL_RenderClear(renderer);
            render(renderer);
            SDL_RenderPresent(renderer);
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
    bool swap = false;
    bool swapInput = false;
    if(textBlock->text == "%message%"){
        textBlock->destR->x = -1;
        textBlock->destR->w = -1;
        textBlock->destR->h = -1;
        textBlock->text = message;
        swap = true;
    }
    else if(textBlock->text == "%input%"){
        textBlock->text = Input::textInput;
        textBlock->destR->x = -1;
        textBlock->destR->w = -1;
        textBlock->destR->h = -1;
        swapInput = true;
    }
    if(textBlock->text != ""){

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
    if(swap){
        textBlock->text = "%message%";
    }
    else if(swapInput){
        textBlock->text = "%input%";
    }
}