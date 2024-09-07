#include<vector>
#include<SDL.h>
#include<SDL_image.h>
#include<vector>
#include<iostream>
#include "../include/Enemy.hpp"
using namespace std;

void Enemy::spawnEnemy(vector<Enemies> &enemies, int width, int height) {
    Enemies newEnemy;
    newEnemy.EnemyRect = {(rand()%width), rand() % height, 32, 32};
    newEnemy.spawnTime = SDL_GetTicks();
    newEnemy.active = true;
    enemies.push_back(newEnemy);
}

void Enemy::enemyTimeOut(vector<Enemies> &enemies,Uint32 timeout) {
    Uint32 currentTime = SDL_GetTicks();
    for(Enemies &enemy : enemies){
        if(enemy.active && currentTime - enemy.spawnTime > timeout){
            enemy.active = false;
        }
    }
}

void Enemy::checkCollision(vector<Enemies> &enemies, SDL_Point &playerPos) {
    for(Enemies &enemy : enemies){
        if(enemy.active && SDL_PointInRect(&playerPos, &enemy.EnemyRect)){
            enemy.active = false;
            printf("\nHit Object Score: %d",count);
            count++;
        }
    }  
}


void Enemy::updateEnemyPosition(vector<Enemies>& enemies, int stepX) {
    for (Enemies& enemy : enemies) {
        if (enemy.active) {
            enemy.EnemyRect.x += stepX; // Move the enemy by stepX
            // Optional: Reset position if it moves off-screen
            if (enemy.EnemyRect.x > 500) {
                enemy.EnemyRect.x = 0;
            }
        }
    }
}