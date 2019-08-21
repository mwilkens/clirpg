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
#include "hand.h"

//#define FULL_COLOR

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
        "#W.......##........#" // 2
        "#........##...###..#" // 3
        "#........##...#W#..#" // 4
        "#........##........#" // 5
        "#........##........#" // 6
        "#........##........#" // 7
        "#........##........#" // 8
        "##..############..##" // 9 
        "#.....##...####....#" // 10
        "#.#...##.#....#....#" // 11
        "#...#.##.####.#....#" // 12
        "#.....##.#....#....#" // 13
        "#..#..##.#.####....#" // 14
        "#.....##.#....#....#" // 15
        "#.#...##.####.#....#" // 16
        "#.....##.#....#....#" // 17
        "#...#.##.#.........#" // 18
        "#........#.........#" // 19
        "####################";// 20

    unsigned int map_w = 20;
    unsigned int map_h = 20;

    unsigned int wall_h = 6;

#ifdef FULL_COLOR
    char colorMap[] = "BQ@$8%&WMkbdpqZO0UmwaCXhfo#Jzcvun1xt[]{}IlYLi()?r/|\\+<>^!\"*;:,~_-\'`";
    int colorMapLen = 68;
#else
    char colorMap[] = "BMZC[lYL/!<:- ";
    int colorMapLen = 13;
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

        //if(ch == 'i') plr->addHeight();
        //if(ch == 'l') wall_h += 1;
        //if(ch == 'k') plr->lessHeight();
        //if(ch == 'j') wall_h -= 1;

        for(int x = 0; x < SCREEN_W; x++) {

            // Calculate the ray angle based on the FOV
            float rayAngle = plr->getRayAngleX(x,SCREEN_W); 

            // Calculate the distance to the wall
            float stepSize = 0.1f;
            float distanceToWall = 0.0f;

            // variable to keep track of whether we hit the wall or not
            bool hitWall = false;

            // Create a unit vector based on our ray tracing angle
            float eyeX = sinf(rayAngle);
            float eyeY = cosf(rayAngle);

            // Darkness modifier
            float darknessMod = 1.0f;

            // Move the ray along the vector in incriments
            // Use this to determine if we've hit a wall
            // This is the horizontal distance
            while (!hitWall && distanceToWall < plr->getDepth()){

                // incriment the ray
                distanceToWall += stepSize;

                // Generate point with the players position as a seed
                float ftestX = plr->getX() + eyeX*distanceToWall;
                float ftestY = plr->getY() + eyeY*distanceToWall;
                int testX = (int) ftestX;
                int testY = (int) ftestY;

                // Check if the ray has moved out of bounds
                if(testX<0 || testX > map_w || testY<0 || testY > map_h){
                    hitWall = true;
                    distanceToWall = plr->getDepth();
                } else {
                    // check if we've hit a wall on the map
                    if (map.c_str()[testY*map_w + testX] == '#'){
                        hitWall = true;

                        float edgeDetectX = abs(ftestX - testX);
                        float edgeDetectY = abs(ftestY - testY);

                        // Closer to zero, closer to edge
                        edgeDetectX = min( edgeDetectX, 1.0f - edgeDetectX);
                        edgeDetectY = min( edgeDetectY, 1.0f - edgeDetectY);

                        // Detect if we're close to the edge and darken it slightly
                        float thresh = 0.025;

                        if ( edgeDetectX < thresh && edgeDetectY < thresh )
                            darknessMod += 64.0f * (edgeDetectX + edgeDetectY) / distanceToWall;
                    }
                }
            }

            // Calculate a shade index based on horizontal distance
            char shade = ' ';

            for (int y = 0; y < SCREEN_H; y++){

                // we have a distance
                // we have an angle??
                //     _-'|
                // _-'____|

                // SOH, CAH, TOA

                // TAN(ANG) = OP / ADJ
                // ADJ * TAN(ANG) = OP

                float yRay = plr->getRayAngleY(y, SCREEN_H);
                float wallHeight = plr->getHeight() + (10.0f * distanceToWall * tanf(yRay));
                float newDist = distanceToWall / cosf(yRay);

                // Wall & more??
                if(wallHeight <= (float)wall_h && wallHeight >= 0) {
                    int sIdx = darknessMod * colorMapLen * newDist / plr->getDepth();
                    mvaddch(y,x,colorMap[sIdx]);
                } else if(wallHeight < 0){
                    mvaddch(y,x,' ');
                } else {
                    mvaddch(y,x,'.');
                }

                /*

                // each row
                if(y <= ceiling)
                    mvaddch(y,x,' ');
                else if( y > ceiling && y <= floor)
                    mvaddch(y,x,colorMap[sIdx]);
                else {
                    mvaddch(y,x,'.');
                }*/
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

        if (map.c_str()[(int)plr->getY()*map_w + (int)plr->getX()] == 'W'){
            mvaddstr(-6+SCREEN_H/2.0f,SCREEN_W/2.0f,"+------------------+");
            mvaddstr(-5+SCREEN_H/2.0f,SCREEN_W/2.0f,"+     You Win!!    +");
            mvaddstr(-4+SCREEN_H/2.0f,SCREEN_W/2.0f,"+    Congrats :)   +");
            mvaddstr(-3+SCREEN_H/2.0f,SCREEN_W/2.0f,"+                  +");
            mvaddstr(-2+SCREEN_H/2.0f,SCREEN_W/2.0f,"+   If you want    +");
            mvaddstr(-1+SCREEN_H/2.0f,SCREEN_W/2.0f,"+    just press    +");
            mvaddstr( 0+SCREEN_H/2.0f,SCREEN_W/2.0f,"+       'q'        +");
            mvaddstr( 1+SCREEN_H/2.0f,SCREEN_W/2.0f,"+     to quit..    +");
            mvaddstr( 2+SCREEN_H/2.0f,SCREEN_W/2.0f,"+                  +");
            mvaddstr( 3+SCREEN_H/2.0f,SCREEN_W/2.0f,"+   awesome job    +");
            mvaddstr( 4+SCREEN_H/2.0f,SCREEN_W/2.0f,"+    by the way    +");
            mvaddstr( 5+SCREEN_H/2.0f,SCREEN_W/2.0f,"+          haha    +");
            mvaddstr( 6+SCREEN_H/2.0f,SCREEN_W/2.0f,"+------------------+");
            nodelay(stdscr, FALSE);
            char end;
            while(end != 'q')
                end = getch();
            running = false;
        }

        // Display the hands

        unsigned int hand_offset = 5+ SCREEN_H - hand_height;

        for(int y=0; y < hand_height; y++){
            move(y+hand_offset,0);
            for(int x=0; x < hand_width; x++){
                char curr = hand_image[y*hand_width + x];
                if(curr != '?'){
                    addch(curr);
                } else {
                    move(y+hand_offset,x+1);
                }
            }
        }


        // Write buffer
        wrefresh(win);
    }

    // Exit ncurses mode
    endwin();

    // Delete the player, oh no!
    delete plr;

    return 0;
}