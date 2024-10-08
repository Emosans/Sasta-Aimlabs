#include <SDL.H>
#undef main
#include<SDL_image.h>
#include<iostream>
#include<vector>
using namespace std;

const int WINDOW_WIDTH = 580;
const int WINDOW_HEIGHT = 600;
const int ENEMY_HEIGHT = 32;
const int ENEMY_WIDTH = 32;

#include "../include/RenderWindow.hpp"
#include "../include/Enemy.hpp"
#include "../include/Menu.hpp"

Menu menu;
Menu::GameState gameState = Menu::MENU;

int main(int argc, char* argv[]){
    if(SDL_INIT_VIDEO<0){
        printf("Failed");
    }

    RenderWindow window("Rank Improver",600,600);
    SDL_Renderer* renderer = window.getRenderer();
    SDL_Window* gridWindow = window.getWindow();

    menu.setMenu(renderer,gameState);

    bool running = true;

    while (gameState != Menu::QUIT) {
        if (gameState == Menu::MENU) {
            menu.render();
            menu.setMenu(renderer,gameState);
        } else if (gameState == Menu::GRIDSHOT) {
            menu.setGridShot(renderer,window);
            if(gameState = Menu::MENU){
                menu.render();
                menu.setMenu(renderer,gameState);
            }
        } else if (gameState == Menu::MICROFLICK) {
            menu.setMicroFlick(renderer,window);
            if(gameState = Menu::MENU){
                menu.render();
                menu.setMenu(renderer,gameState);
            }
        } else if (gameState == Menu::TRACKING) {
            menu.setTracking(renderer,window);
            if(gameState = Menu::MENU){
                menu.render();
                menu.setMenu(renderer,gameState);
            }
        }
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}