#include <SDL.h>
#include<SDL_image.h>

#include "../include/RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL){
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
    }
}

SDL_Renderer* RenderWindow::getRenderer(){
    return renderer;
}

void RenderWindow::DrawCircle(SDL_Renderer *renderer,int x,int y,int radius){
    int offsetX, offsetY, d;
    offsetX = 0;
    offsetY = radius;
    d = radius - 1;
    
    while (offsetY >= offsetX) {
        // Draw horizontal lines between the points to fill the circle
        SDL_RenderDrawLine(renderer, x - offsetY, y + offsetX, x + offsetY, y + offsetX);
        SDL_RenderDrawLine(renderer, x - offsetX, y + offsetY, x + offsetX, y + offsetY);
        SDL_RenderDrawLine(renderer, x - offsetX, y - offsetY, x + offsetX, y - offsetY);
        SDL_RenderDrawLine(renderer, x - offsetY, y - offsetX, x + offsetY, y - offsetX);

        if (d >= 2 * offsetX) {
            d -= 2 * offsetX + 1;
            offsetX++;
        } else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY--;
        } else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY--;
            offsetX++;
        }
    }
}

void RenderWindow::DrawDimple(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);  // Light grey for dimples
    DrawCircle(renderer, x, y, 3);  // Draw small circles representing dimples
}

void RenderWindow::DrawGolfBall(SDL_Renderer* renderer, int x, int y, int radius) {
    // Draw the outer circle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color for the ball
    DrawCircle(renderer, x, y, radius);

    // Draw dimples (in a grid pattern for simplicity)
    for (int dimpleX = x - radius / 2; dimpleX < x + radius / 2; dimpleX += 10) {
        for (int dimpleY = y - radius / 2; dimpleY < y + radius / 2; dimpleY += 10) {
            //DrawDimple(renderer, dimpleX, dimpleY);
        }
    }
}

void RenderWindow::clear(){
    SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

