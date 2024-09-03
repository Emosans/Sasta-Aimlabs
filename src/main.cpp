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


int main(int argc, char* argv[]){
    if(SDL_INIT_VIDEO<0){
        printf("Failed");
    }

    //variables
    int mouseX,mouseY;
    int ballPosX = 300;
    int ballPosY = 300;
    SDL_Point playerPoint;
    Uint32 enemySpawnTime = 1500; // 1.5 seconds timeout before enemy disappears
    Uint32 enemySpawnInterval = 1000; // Spawn new enemy every 1 seconds
    Uint32 lastSpawnTime = SDL_GetTicks();
    Enemy enemy; // object of enemy class
    //create a vector of enemies and store it in the enemy class struct
    vector<Enemy::Enemies> enemies = {
        {
            {rand()%WINDOW_WIDTH,rand()%WINDOW_HEIGHT,ENEMY_WIDTH,ENEMY_HEIGHT},
            SDL_GetTicks(),
            true
        }
    };
    

    RenderWindow window("Golf",600,600);

    bool quit=false;
    SDL_Event event;

    while(!quit){
        while(SDL_PollEvent(&event)!=0){
            if(event.type==SDL_QUIT){
                quit=true;
            } else if(event.type==SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&mouseX,&mouseY);

                printf("Mouse button clicked at: %d, %d\n", mouseX, mouseY);

                ballPosX = mouseX;
                ballPosY = mouseY;
                playerPoint = {ballPosX, ballPosY};
                enemy.checkCollision(enemies,playerPoint);
            }
        }

        // Check if it's time to spawn a new enemy
        bool activeEnemyExists = false;
        for (const Enemy::Enemies& enemy : enemies) {
            if (enemy.active) {
                activeEnemyExists = true;
                break;
            }
        }
        // spawn the enemy
        if (!activeEnemyExists && SDL_GetTicks() - lastSpawnTime > enemySpawnInterval) {
            enemy.spawnEnemy(enemies, WINDOW_WIDTH, WINDOW_HEIGHT);
            lastSpawnTime = SDL_GetTicks();
        }
        //make enemy disappear after some time
        enemy.enemyTimeOut(enemies,enemySpawnTime);

        window.clear();

        //fill the player object on the renderer
        //SDL_SetRenderDrawColor(window.getRenderer(), 255,255,255, 255);
        window.DrawGolfBall(window.getRenderer(),ballPosX,ballPosY,12);
        
        //fill the enemy rect on the renderer
        SDL_SetRenderDrawColor(window.getRenderer(), 255,0,0, 255);
        for(Enemy::Enemies &enemy : enemies){
            if(enemy.active){
                SDL_RenderFillRect(window.getRenderer(), &enemy.EnemyRect);
            }
        }
        window.display();
    }
    window.cleanUp();
    SDL_Quit();
    return 0;
}