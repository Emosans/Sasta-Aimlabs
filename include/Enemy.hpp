#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<vector>
using namespace std;

class Enemy{
    public:
        struct Enemies{
            SDL_Rect EnemyRect;
            Uint32 spawnTime;
            bool active;
        };
        void spawnEnemy(vector<Enemies> &enemies, int width, int height);
        void enemyTimeOut(vector<Enemies> &enemies,Uint32 timeout);
        void checkCollision(vector<Enemies> &enemies, SDL_Point &playerPos);
};