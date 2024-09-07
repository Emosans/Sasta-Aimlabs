#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
using namespace std;

#include "../include/Menu.hpp"
#include "../include/Enemy.hpp"
#include "../include/RenderWindow.hpp"

void Menu::setMenu(SDL_Renderer* renderer, GameState &state) {
    this->renderer = renderer;
    gridShotButton = {200, 150, 200, 50};
    microflicksButton = {200, 250, 200, 50};
    trackingButton = {200,350,200,50};

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state = QUIT;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x > gridShotButton.x && x < gridShotButton.x + gridShotButton.w &&
                y > gridShotButton.y && y < gridShotButton.y + gridShotButton.h) {
                state = GRIDSHOT;
            } else if (x > microflicksButton.x && x < microflicksButton.x + microflicksButton.w &&
                       y > microflicksButton.y && y < microflicksButton.y + microflicksButton.h) {
                state = MICROFLICK;
            } else if (x > trackingButton.x && x < trackingButton.x + trackingButton.w &&
                       y > trackingButton.y && y < trackingButton.y + trackingButton.h) {
                state = TRACKING;
            }
        }
    }
}

void Menu::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render gridshot button
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &gridShotButton);

    //microflick button
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &microflicksButton);

    //tracking button
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderFillRect(renderer,&trackingButton);

    SDL_RenderPresent(renderer);
}

void Menu::setMicroFlick(SDL_Renderer* renderer,RenderWindow window){

    const int WINDOW_WIDTH = 580;
    const int WINDOW_HEIGHT = 600;
    const int ENEMY_HEIGHT = 32;
    const int ENEMY_WIDTH = 32;

    //variables
    int mouseX,mouseY;
    int ballPosX = 300;
    int ballPosY = 300;
    float sensitivity = 1.0f;
    int prevMouseX,prevMouseY;
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
    
    Menu::GameState gameState;
    Menu menu;
    
    bool quit=false;
    SDL_Event event;
    SDL_ShowCursor(SDL_DISABLE);

    // Lock the mouse inside the window
    SDL_SetWindowGrab(window.getWindow(), SDL_TRUE);

    while(!quit){
        while(SDL_PollEvent(&event)!=0){
            if(event.type==SDL_QUIT){
                window.cleanUp();
                SDL_Quit();
                SDL_ShowCursor(SDL_ENABLE);
                SDL_SetWindowGrab(window.getWindow(),SDL_FALSE);
                gameState = Menu::QUIT;
                quit=true;
            } else if(event.type==SDL_MOUSEBUTTONDOWN){
                enemy.checkCollision(enemies,playerPoint);
            } else if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                    sensitivity+=0.1f;
                    break;
                    case SDLK_DOWN:
                    sensitivity-=0.1f;
                    break;
                    default:
                    sensitivity=sensitivity;
                }
            }



            if (sensitivity < 0.1f) sensitivity = 0.1f;
            printf("Sensitivity%.2f\n",sensitivity);

            SDL_GetMouseState(&mouseX,&mouseY);
            prevMouseX=mouseX;
            prevMouseY=mouseY;

            int deltaX = (mouseX) * sensitivity;
            int deltaY = (mouseY) * sensitivity;

            //printf("Mouse button clicked at: %d, %d\n", mouseX, mouseY);
            ballPosX = (deltaX);
            ballPosY = (deltaY);

            if (ballPosX < 0) {ballPosX = 0; /*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosX > WINDOW_WIDTH) {ballPosX = WINDOW_WIDTH;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}
            if (ballPosY < 0) {ballPosY = 0;/*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosY > WINDOW_HEIGHT) {ballPosY = WINDOW_HEIGHT;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}



            playerPoint = {ballPosX, ballPosY};
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

        //fill the enemy rect on the renderer
        SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
        for(Enemy::Enemies &enemy : enemies){
            if(enemy.active){
                SDL_RenderFillRect(renderer, &enemy.EnemyRect);
            }
        }

        //fill the player object on the renderer
        //SDL_SetRenderDrawColor(window.getRenderer(), 255,255,255, 255);
        window.DrawCrosshair(renderer,ballPosX,ballPosY,12);
        
        window.display();

        
    }
    exit(0);
}

void Menu::setGridShot(SDL_Renderer* renderer,RenderWindow window){


    const int WINDOW_WIDTH = 580;
    const int WINDOW_HEIGHT = 600;
    const int ENEMY_HEIGHT = 32;
    const int ENEMY_WIDTH = 32;

    //variables
    int mouseX,mouseY;
    int ballPosX = 300;
    int ballPosY = 300;
    float sensitivity = 1.0f;
    int prevMouseX,prevMouseY;
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
        },
        {
            {rand()%WINDOW_WIDTH,rand()%WINDOW_HEIGHT,ENEMY_WIDTH,ENEMY_HEIGHT},
            SDL_GetTicks(),
            true
        },
        {
            {rand()%WINDOW_WIDTH,rand()%WINDOW_HEIGHT,ENEMY_WIDTH,ENEMY_HEIGHT},
            SDL_GetTicks(),
            true
        }
    };
    
    Menu::GameState gameState;
    Menu menu;
    
    bool quit=false;
    SDL_Event event;
    SDL_ShowCursor(SDL_DISABLE);

    // Lock the mouse inside the window
    SDL_SetWindowGrab(window.getWindow(), SDL_TRUE);

    while(!quit){
        while(SDL_PollEvent(&event)!=0){
            if(event.type==SDL_QUIT){
                window.cleanUp();
                SDL_Quit();
                SDL_ShowCursor(SDL_ENABLE);
                SDL_SetWindowGrab(window.getWindow(),SDL_FALSE);
                gameState = Menu::QUIT;
                quit=true;
            } else if(event.type==SDL_MOUSEBUTTONDOWN){
                enemy.checkCollision(enemies,playerPoint);
            } else if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                    sensitivity+=0.1f;
                    break;
                    case SDLK_DOWN:
                    sensitivity-=0.1f;
                    break;
                    default:
                    sensitivity=sensitivity;
                }
            }



            if (sensitivity < 0.1f) sensitivity = 0.1f;
            printf("Sensitivity%.2f\n",sensitivity);

            SDL_GetMouseState(&mouseX,&mouseY);
            prevMouseX=mouseX;
            prevMouseY=mouseY;

            int deltaX = (mouseX) * sensitivity;
            int deltaY = (mouseY) * sensitivity;

            //printf("Mouse button clicked at: %d, %d\n", mouseX, mouseY);
            ballPosX = (deltaX);
            ballPosY = (deltaY);

            if (ballPosX < 0) {ballPosX = 0; /*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosX > WINDOW_WIDTH) {ballPosX = WINDOW_WIDTH;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}
            if (ballPosY < 0) {ballPosY = 0;/*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosY > WINDOW_HEIGHT) {ballPosY = WINDOW_HEIGHT;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}



            playerPoint = {ballPosX, ballPosY};
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
            enemy.spawnEnemy(enemies, WINDOW_WIDTH, WINDOW_HEIGHT);
            enemy.spawnEnemy(enemies, WINDOW_WIDTH, WINDOW_HEIGHT); 
            lastSpawnTime = SDL_GetTicks();
        }
        //make enemy disappear after some time
        enemy.enemyTimeOut(enemies,enemySpawnTime);

        window.clear();

        //fill the enemy rect on the renderer
        SDL_SetRenderDrawColor(renderer, 255,0,0, 255);
        for(Enemy::Enemies &enemy : enemies){
            if(enemy.active){
                SDL_RenderFillRect(renderer, &enemy.EnemyRect);
            }
        }

        //fill the player object on the renderer
        //SDL_SetRenderDrawColor(window.getRenderer(), 255,255,255, 255);
        window.DrawCrosshair(renderer,ballPosX,ballPosY,12);
        
        window.display();

        
    }
    exit(0);
}

void Menu::setTracking(SDL_Renderer* renderer,RenderWindow window){
    const int WINDOW_WIDTH = 580;
    const int WINDOW_HEIGHT = 600;
    const int ENEMY_HEIGHT = 32;
    const int ENEMY_WIDTH = 32;

    //variables
    int mouseX,mouseY;
    int ballPosX = 300;
    int ballPosY = 300;
    float sensitivity = 1.0f;
    int prevMouseX,prevMouseY;
    int countForX = 0;

    SDL_Point playerPoint;
    Uint32 enemySpawnTime = 3000; // 3 seconds timeout before enemy disappears
    Uint32 enemySpawnInterval = 1000; // Spawn new enemy every 2 seconds
    Uint32 lastSpawnTime = SDL_GetTicks();

    Enemy enemy; // object of enemy class
    vector<Enemy::Enemies> enemies; 

    enemies = {
        {
            {rand()%WINDOW_WIDTH,rand()%WINDOW_HEIGHT,ENEMY_WIDTH,ENEMY_HEIGHT},
            SDL_GetTicks(),
            true
        }
    };

    Menu::GameState gameState;
    Menu menu;
    
    bool quit=false;
    SDL_Event event;
    SDL_ShowCursor(SDL_DISABLE);

    // Lock the mouse inside the window
    SDL_SetWindowGrab(window.getWindow(), SDL_TRUE);

    while(!quit){
        while(SDL_PollEvent(&event)!=0){
            if(event.type==SDL_QUIT){
                window.cleanUp();
                SDL_Quit();
                SDL_ShowCursor(SDL_ENABLE);
                SDL_SetWindowGrab(window.getWindow(),SDL_FALSE);
                gameState = Menu::QUIT;
                quit=true;
            } else if(event.type==SDL_MOUSEBUTTONDOWN){
                enemy.checkCollision(enemies,playerPoint);
            } else if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                    sensitivity+=0.1f;
                    break;
                    case SDLK_DOWN:
                    sensitivity-=0.1f;
                    break;
                    default:
                    sensitivity=sensitivity;
                }
            }



            if (sensitivity < 0.1f) sensitivity = 0.1f;
            printf("Sensitivity%.2f\n",sensitivity);

            SDL_GetMouseState(&mouseX,&mouseY);
            prevMouseX=mouseX;
            prevMouseY=mouseY;

            int deltaX = (mouseX) * sensitivity;
            int deltaY = (mouseY) * sensitivity;

            //printf("Mouse button clicked at: %d, %d\n", mouseX, mouseY);
            ballPosX = (deltaX);
            ballPosY = (deltaY);

            if (ballPosX < 0) {ballPosX = 0; /*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosX > WINDOW_WIDTH) {ballPosX = WINDOW_WIDTH;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}
            if (ballPosY < 0) {ballPosY = 0;/*SDL_WarpMouseInWindow(window.getWindow(), mouseX, mouseY);*/}
            if (ballPosY > WINDOW_HEIGHT) {ballPosY = WINDOW_HEIGHT;/*SDL_WarpMouseInWindow(window.getWindow(),0,0);*/}



            playerPoint = {ballPosX, ballPosY};
        }

        // Check if it's time to spawn a new enemy
        bool activeEnemyExists = false;
        for (const Enemy::Enemies& enemy : enemies) {
            if (enemy.active) {
                activeEnemyExists = true;
                break;
            }
        }

        if (!activeEnemyExists && SDL_GetTicks() - lastSpawnTime > enemySpawnInterval) {

            enemy.spawnEnemy(enemies, WINDOW_WIDTH, WINDOW_HEIGHT);
            enemy.updateEnemyPosition(enemies,5);
            lastSpawnTime = SDL_GetTicks();
        }
        
        //make enemy disappear after some time
        enemy.enemyTimeOut(enemies,enemySpawnTime);

        window.clear();

        //fill the enemy rect on the renderer
        SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
        for(Enemy::Enemies &enemy : enemies){
            if(enemy.active){
                SDL_RenderFillRect(renderer, &enemy.EnemyRect);
            }
        }
        enemy.updateEnemyPosition(enemies,5);

        //fill the player object on the renderer
        //SDL_SetRenderDrawColor(window.getRenderer(), 255,255,255, 255);
        window.DrawCrosshair(renderer,ballPosX,ballPosY,12);
        
        window.display();


    }
    exit(0);
}