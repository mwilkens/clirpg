// C++ Headers
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

// C Headers
#include <stdio.h>
#include <ncurses.h>

// User Headers
#include "entities.h"
#include "player.h"

#define FULL_COLOR

int main(){

    unsigned int SCREEN_W = 120;
    unsigned int SCREEN_H = 40;

    // Initialize ncurses mode
    initscr();
    // Disable line buffering
    raw();
    // Enable keypresses
    keypad(stdscr, TRUE);
    // Disable key echoing
    noecho();
    // Prevent Delays
    nodelay(stdscr, TRUE);

    // Create the window to draw on
    WINDOW * win = newwin(SCREEN_H, SCREEN_W, 0,0);

    // String container to hold the map
    std::string map =
        "####################" // 1
        "#..................#" // 2
        "#..................#" // 3
        "#..................#" // 4
        "#..................#" // 5
        "#..................#" // 6
        "#..................#" // 7
        "#####...###........#" // 8
        "#.........#........#" // 9 
        "#.........#........#" // 10
        "#.........#........#" // 11
        "####################";// 12

    unsigned int map_w = 20;
    unsigned int map_h = 12;

    unsigned int wall_h = 15;

#ifdef FULL_COLOR
    char colorMap[] = "BQ@$8%&WMkbdpqZO0UmwaCXhfo#Jzcvun1xt[]{}IlYLi()?r/|\\+<>^!\"*;:,~_-\'`";
    int colorMapLen = 68;
#else
    char colorMap[] = "BMZC[lYL/!<:-";
    int colorMapLen = 14;
#endif

    // Need some test points to determine how fast the game is running
    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    // Some internal variables for the game engine
    char ch;
    bool running=true;

    move(0,0);

    // Create our player
    Player * plr = new Player();

    while (running){
        // Calculate the time exactly one frame took
        tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

        // Update the speed (does for all entities)
        plr->updateFrame(fElapsedTime);

        getmaxyx(stdscr, SCREEN_H, SCREEN_W);

        // Get Input
        ch = getch();
        if(ch == 'A' || ch == 'a'){
            plr->lookLeft();
        }

        if(ch == 'D' || ch == 'd'){
            plr->lookRight();
        }

        if(ch == 'W' || ch == 'w'){
            plr->moveForward();
            if (map.c_str()[(int)plr->getY()*map_w + (int)plr->getX()] == '#')
			{
				plr->moveBackwards();
			}
        }

        if(ch == 'S' || ch == 's'){
            plr->moveBackwards();
            if (map.c_str()[(int)plr->getY()*map_w + (int)plr->getX()] == '#')
			{
				plr->moveForward();
			}
        }

        if(ch == 'Q' || ch == 'q'){
            running=false;            
        }

        for(int x = 0; x < SCREEN_W; x++) {

            // Calculate the ray angle based on the FOV
            float rayAngle = plr->getRayAngle(x,SCREEN_W); 

            // Calculate the distance to the wall
            float stepSize = 0.1f;
            float distanceToWall = 0.0f;

            // variable to keep track of whether we hit the wall or not
            bool hitWall = false;

            // Create a unit vector based on our ray tracing angle
            float eyeX = sinf(rayAngle);
            float eyeY = cosf(rayAngle);

            // Move the ray along the vector in incriments
            // Use this to determine if we've hit a wall
            // This is the horizontal distance
            while (!hitWall && distanceToWall < plr->getDepth()){

                // incriment the ray
                distanceToWall += stepSize;

                // Generate point with the players position as a seed
                int testX = (int)(plr->getX() + eyeX*distanceToWall);
                int testY = (int)(plr->getY() + eyeY*distanceToWall);

                // Check if the ray has moved out of bounds
                if(testX<0 || testX > map_w || testY<0 || testY > map_h){
                    hitWall = true;
                    distanceToWall = plr->getDepth();
                } else {
                    // check if we've hit a wall on the map
                    if (map.c_str()[testY*map_w + testX] == '#'){
                        hitWall = true;

                        // tutorial does some wacky vector stuff, haha skipping that
                    }
                }
            }

            // Calculate a shade index based on horizontal distance
            char shade = ' ';
            int sIdx = colorMapLen * distanceToWall / plr->getDepth();

            // Calculate distance from ceiling to floor
            int ceiling = (float)(SCREEN_H/1.8f) - (SCREEN_H / distanceToWall);
            int floor   = SCREEN_H - ceiling;
        
            for (int y = 0; y < SCREEN_H; y++){
                // each row
                if(y <= ceiling)
                    mvaddch(y,x,' ');
                else if( y > ceiling && y <= floor)
                    mvaddch(y,x,colorMap[sIdx]);
                else {
                    mvaddch(y,x,'.');
                }
            }
        }


        // Display Stats
        char buff[100];
        snprintf(buff,100,"X:%3.2f, Y:%3.2f A:%3.2f, FPS:%3.2f",
            plr->getX(), plr->getY(), plr->getA(), 1.0f/fElapsedTime);
        mvaddnstr(0,map_w + 1,buff,100);

        for(int nx = 0; nx < map_w; nx++)
            for(int ny=0; ny < map_h; ny++){
                mvaddch(ny,nx,map[ny*map_w + (map_w - nx - 1)]);
            }
        
        // add the player to the screen :)
        mvaddch(plr->getY(),map_w - plr->getX() - 1,'P');

        // Write buffer
        wrefresh(win);
    }

    // Exit ncurses mode
    endwin();

    // Delete the player, oh no!
    delete plr;

    return 0;
}