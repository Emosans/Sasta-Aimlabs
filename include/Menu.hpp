#pragma once
#include<SDL.h>
#include<SDL_image.h>
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
        QUIT
    };

    void setMenu(SDL_Renderer* renderer,GameState &state);
    void render();
    void setGridShot(SDL_Renderer* renderer,RenderWindow window);
    void setMicroFlick(SDL_Renderer* renderer);

private:
    SDL_Renderer* renderer;
    SDL_Rect gridShotButton;
};