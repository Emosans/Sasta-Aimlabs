#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;

//include files
#include "../include/enemy.hpp"
#include "../include/RenderWindow.hpp"

class Menu{
public:
    enum GameState{
        MENU,
        GRIDSHOT,
        MICROFLICK,
        TRACKING,
        QUIT
    };

    void setMenu(SDL_Renderer* renderer,GameState &state);
    void render();
    SDL_Texture* createTextTexture(const char* text, SDL_Color color);
    void renderButtonText(const char* text, SDL_Rect buttonRect, SDL_Color color);

    void setGridShot(SDL_Renderer* renderer,RenderWindow window);
    void setMicroFlick(SDL_Renderer* renderer,RenderWindow window);
    void setTracking(SDL_Renderer* renderer,RenderWindow window);

private:
    TTF_Font* font;
    SDL_Renderer* renderer;
    SDL_Rect gridShotButton;
    SDL_Rect microflicksButton;
    SDL_Rect trackingButton;
};