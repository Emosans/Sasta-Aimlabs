#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<String>
#include<iostream>
using namespace std;

class RenderWindow{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        RenderWindow(const char* title, int width, int height);
        SDL_Texture* loadTexture(const char* filePath);
        void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
        void DrawCrosshair(SDL_Renderer* renderer, int x, int y, int radius);
        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void cleanUp();
        void clear();
        void render(SDL_Texture* texture);
        void display();
};
