#include <vector>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "../cube.h"
#include "game.hpp"
#include "../objloader.hpp"
//#include "../figlet/figlet.h"

#define MAX_WIDTH 50
#define MAX_NUM_CUBES 500

#define WIDTH COLS
#define HEIGHT LINES

WINDOW *menu_win;

Game::Game()
      : GameCubeVec(), renderer(WIDTH, HEIGHT, this), direction(0.0f, 0.0f,0.2f) {
    isDead = true;
    score = 0;
    level = 0;
    int i = MAX_NUM_CUBES;
    float curr_z = 20.0f;
    srand (time(NULL));
    while (i > 0){
        int num_on_plane = (rand() % 10);
        i -= num_on_plane;
        curr_z += (float)i*80.0/100.0;
        curr_z /= 2;
        
        float rand_x = float(rand() % MAX_WIDTH - (MAX_WIDTH/2));
        float rand_y = float(rand() % MAX_WIDTH - (MAX_WIDTH/2));
        float rand_z = (float)(rand() % 50);
        //std::printf("%.2f %.2f %.2f\n", rand_x, rand_y, curr_z);
        GameCubeVec.push_back(new GameCube(glm::vec3(rand_x, rand_y, -rand_z), &renderer.lightedColorShader));
    }
    //menu_win = initscr();
    gameLoop();
}

Game::~Game() {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        delete (*it);
    }
}

void Game::renderCubes() {
    /* Render all cubes */
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->draw(renderer.view, renderer.proj);
    }
    score++;
}

float rot_curr;

//const char *menu[] = {"_________      ______               ____________","_________      ______               ____________         ","_________      ______               ____________         ","```MMMMMM   666MMMMMMbbb         666MMMMMMMMMMMMbbb      ","```MMMMMM   666MMMMMMbbb         666MMMMMMMMMMMMbbb      ","```MMMMMM   666MMMMMMbbb         666MMMMMMMMMMMMbbb      ","   MMMMMMMMM999   ```MMMbbb   MMMMMM'''      ```MMMbbb   ","   MMMMMMMMM999   ```MMMbbb   MMMMMM'''      ```MMMbbb   ","   MMMMMMMMM999   ```MMMbbb   MMMMMM'''      ```MMMbbb   ","   MMMMMM'''         MMMMMM                     MMMMMM   ","   MMMMMM'''         MMMMMM                     MMMMMM   ","   MMMMMM'''         MMMMMM                     MMMMMM   ","   MMMMMM            MMMMMM                  ...MMM999   ","   MMMMMM            MMMMMM                  ...MMM999   ","   MMMMMM            MMMMMM                  ...MMM999   ","   MMMMMM            MMMMMM         MMMMMMMMMMMM         ","   MMMMMM            MMMMMM         MMMMMMMMMMMM         ","   MMMMMM            MMMMMM         MMMMMMMMMMMM         ","   MMMMMM            MMMMMM                  ```MMMbbb   ","   MMMMMM            MMMMMM                  ```MMMbbb   ","   MMMMMM            MMMMMM                  ```MMMbbb   ","___MMMMMM___      ___MMMMMM___                  MMMMMM   ","___MMMMMM___      ___MMMMMM___                  MMMMMM   ","___MMMMMM___      ___MMMMMM___                  MMMMMM   ","                                                MMMMMM   ","                                                MMMMMM   ","                                                MMMMMM   ","                              MMMMMM...      ,,,MMM999   ","                              MMMMMM...      ,,,MMM999   ","                              MMMMMM...      ,,,MMM999   ","                                 YYYMMMMMMMMMMMM999      ","                                 YYYMMMMMMMMMMMM999      ","                                 YYYMMMMMMMMMMMM999"};

void Game::renderMenu() {
    /* CONNELLS SHIT HERE */
    /*for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->draw_big(renderer.view, renderer.proj);

    } */
    rot_curr = fmod((rot_curr+.005),(2*3.1415));
    GameCubeVec[0]->draw_big(renderer.view, renderer.proj);
    GameCubeVec[0]->draw_rotate(renderer.view, renderer.proj, rot_curr);
    for (int j =0; j < 32; j++) {
      
      //mvaddstr(j+10, 10, menu[j]);
    }
    //refresh();
}

void Game::renderScore(){
    /* CONNELLS SHIT HERE */
    //(void*) figletwrapper("hello");
}

void Game::render() {
    if (isDead) {
        renderMenu();
    } else {
        renderCubes();
    }
    renderScore();
} 

void Game::gameOver(){
    isDead = true;
    score = 0;
}

void Game::gameLoop(){
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 50000L;
 
    glm::vec2 delta;

    while(1) {
      //renderer.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, blah));
      int c = getch();
      delta = glm::vec2(0.0f,0.0f);
      float diff = 1.0f;
      switch(c) {
        case(KEY_LEFT):
            delta.x += diff;
            break;
        case(KEY_RIGHT):
            delta.x -= diff;
            break;            
        case(KEY_UP):
            delta.y -= diff;
            break;
        case(KEY_DOWN):
            delta.y += diff;
            break;
        case ' ':
            isDead = isDead ? false : true;
            break;
      }

      renderer.draw();
      refresh();
      nanosleep(&tim, &tim2);
      update(delta);
      level++;
    }
    //player.move(player.x, player.y, player.z);
    /*StartTimer */
    /*incrementLevel */
    /* Make 3D */
}

glm::vec3 Game::random_vec() {
        float rand_x = float(rand() % (MAX_WIDTH) - (MAX_WIDTH/2));
        float rand_y = float(rand() % (MAX_WIDTH) - (MAX_WIDTH/2));
        float det_z = -50.0f;
        return glm::vec3(rand_x, rand_y, det_z);
}

void Game::update(glm::vec2 delta) {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        direction.x = delta.x;
        direction.y = delta.y;
        if (isDead)
            continue;
        (*it)->position += direction;
        (*it)->position = ((*it)->position.z > 0.0f) ? random_vec() : ((*it)->position);
        if ((*it)->position.z > -0.2f) {
            if (((*it)->position.x > -2.f) && ((*it)->position.x < 2.f) &&
                ((*it)->position.y > -2.f) && ((*it)->position.y < 2.f)) {
                this->gameOver();
            }
        }

        //(*it)->position.x = ((*it)->position.x > 100.f) ? -100.0f : ((*it)->position.x);
        //(*it)->position.y = ((*it)->position.y > 0.0f) ? -100.0f : ((*it)->position.y);
    }
}

