// C++ Headers
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

// C Headers
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

// User Headers
#include "entities.h"
#include "player.h"
#include "hand.h"

#define MAP_PAIR    1
#define HANDS_PAIR  2
#define FLOOR_PAIR  3
#define SKY_PAIR    4
#define BORDER_PAIR 5

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
    // Initialize random numbers
    srand (time(NULL));

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    // initialize ncurses colors
    start_color();

    init_pair(MAP_PAIR,    COLOR_GREEN, COLOR_BLACK);
    init_pair(HANDS_PAIR,  COLOR_YELLOW,COLOR_BLACK);
    init_pair(FLOOR_PAIR,  COLOR_MAGENTA,   COLOR_BLACK);
    init_pair(SKY_PAIR,    COLOR_BLACK, COLOR_BLACK);
    init_pair(BORDER_PAIR, COLOR_BLACK, COLOR_WHITE);
    int currPair = 0;

    // Create the window to draw on
    WINDOW * win = newwin(SCREEN_H, SCREEN_W, 0,0);

    // String container to hold the map
    std::string map =

        "####################" // 1
        "#........##........#" // 2
        "#........##........#" // 3
        "#........##........#" // 4
        "#........##........#" // 5
        "#........##........#" // 6
        "#........##........#" // 7
        "#........##........#" // 8
        "##..############..##" // 9 
        "#.....###..........#" // 10
        "#.....####.........#" // 11
        "#..#..####.........#" // 12
        "#.....####.........#" // 13
        "##....####.........#" // 14
        "#...#.####.........#" // 15
        "#.....####.........#" // 16
        "#..#..####.........#" // 17
        "#.....####.........#" // 18
        "#.......##.........#" // 19
        "####################" // 20

        "####################" // 1
        "#........##........#" // 2
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
        "####################" // 20

        "####################" // 1
        "#FFFFFFFFFFFFFFFFFF#" // 2
        "#FFFFFFFFFFFFFFFFFF#" // 3
        "#FFFFFFFFFFFFFFFFFF#" // 4
        "#FFFFFFFFFFFFFFFFFF#" // 5
        "#FFFFFFFFFFFFFFFFFF#" // 6
        "#FFFFFFFFFFFFFFFFFF#" // 7
        "#FFFFFFFFFFFFFFFFFF#" // 8
        "#FFFFFFFFFFFFFFFFFF#" // 9 
        "#FFFFFFFFFFFFFFFFFF#" // 10
        "#FFFFFFFFFFFFFFFFFF#" // 11
        "#FFFFFFFFFFFFFFFFFF#" // 12
        "#FFFFFFFFFFFFFFFFFF#" // 13
        "#FFFFFFFFFFFFFFFFFF#" // 14
        "#FFFFFFFFFFFFFFFFFF#" // 15
        "#FFFFFFFFFFFFFFFFFF#" // 16
        "#FFFFFFFFFFFFFFFFFF#" // 17
        "#FFFFFFFFFFFFFFFFFF#" // 18
        "#FFFFFFFFFFFFFFFFFF#" // 19
        "####################"; // 20

        

    unsigned int map_w = 20;
    unsigned int map_h = 20;
    unsigned int map_d = 3;

    char debugbuff[100];

    unsigned int wall_h = 8;

    bool hand_dir = false;
    bool hand_rand = 0;

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

    // step size for the ray tracer
    float stepSize = 0.05f;

    while (running){
        // Calculate the time exactly one frame took
        tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

        // Update the speed (does for all entities)
        plr->updateFrame(fElapsedTime);

        getmaxyx(stdscr, SCREEN_H, SCREEN_W);

        float fpX = plr->getX();
        float fpY = plr->getY();
        float fpZ = plr->getZ();
        int ipX = (int)floor(fpX);
        int ipY = (int)floor(fpY);
        int ipZ = (int)floor(fpZ);
        int mapOffset = ipZ*map_w*map_h + ipY*map_w + ipX;
        

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
            if (map.c_str()[mapOffset] == '#')
			{
				plr->moveBackwards();
			}
        }

        if(ch == 'S' || ch == 's'){
            plr->moveBackwards();
            if (map.c_str()[mapOffset] == '#')
			{
				plr->moveForward();
			}
        }

        if(ch == 'Q' || ch == 'q'){
            running=false;            
        }

        if(ch == 'i') plr->lookUp();
        //if(ch == 'l') wall_h += 1;
        if(ch == 'k') plr->lookDown();
        //if(ch == 'j') wall_h -= 1;

        for(int x = 0; x < SCREEN_W; x++) {

            // Calculate the ray angle based on the FOV
            float xRay = plr->getRayAngleX(x,SCREEN_W); 

            // Create a unit vector based on our ray tracing angle
            float eyeX = sinf(xRay);
            float eyeY = cosf(xRay);

            for (int y = 0; y < SCREEN_H; y++){

                // Calculate the ray angle based on the FOV
                float yRay = plr->getRayAngleY(y, SCREEN_H);

                // Create a unit vector based on our ray tracing angle
                float eyeZ = tanf(yRay);


                // Calculate the distance to the wall
                float distanceToWall = 0.0f;

                // variable to keep track of whether we hit the wall or not
                bool hitWall = false;
                bool hitFloor = false;
                bool hitOOB = false;

                // Darkness modifier
                float darknessMod = 1.0f;

                // Move the ray along the vector in incriments
                // Use this to determine if we've hit a wall
                // This is the horizontal distance
                while ((!hitOOB || !hitWall || !hitFloor) && distanceToWall < plr->getDepth()){

                    // incriment the ray
                    distanceToWall += stepSize;

                    // Generate point with the players position as a seed
                    float ftestX = fpX + eyeX*distanceToWall;
                    float ftestY = fpY + eyeY*distanceToWall;
                    float ftestZ = fpZ + 0.3f + eyeZ*distanceToWall;
                    int testX = (int) (ftestX);
                    int testY = (int) (ftestY);
                    int testZ = (int) (ftestZ);

                    // Check if the ray has moved out of bounds
                    if(ftestX < 0 || ftestX > map_w || ftestY < 0 || ftestY > map_h || ftestZ < 0 || ftestZ > map_d){
                        hitOOB = true;
                        distanceToWall = plr->getDepth();
                        break;
                    } else {

                        // check if we've hit a wall on the map
                        if ( map.c_str()[ testZ*map_w*map_h + testY*map_w + testX] == '#') {
                            hitWall = true;
                            
                            
                            int edgeDetectX = 1000 * abs(ftestX - testX);
                            int edgeDetectY = 1000 * abs(ftestY - testY);
                            int edgeDetectZ = 1000 * abs(ftestZ - testZ);
                            // Closer to zero, closer to edge
                            edgeDetectX = min( edgeDetectX, 1000 - edgeDetectX);
                            edgeDetectY = min( edgeDetectY, 1000 - edgeDetectY);
                            edgeDetectZ = min( edgeDetectZ, 1000 - edgeDetectZ);

                            // Detect if we're close to the edge and darken it slightly
                            float thresh = 50;

                            if ( edgeDetectX < thresh && edgeDetectY < thresh ||
                                 edgeDetectX < thresh && edgeDetectZ < thresh ||
                                 edgeDetectY < thresh && edgeDetectZ < thresh){
                               //darknessMod += 64.0f * (edgeDetectX + edgeDetectY) / distanceToWall;
                               attron(COLOR_PAIR(BORDER_PAIR));
                               currPair = BORDER_PAIR;
                            }
                            
                            break;

                        }

                        // What if we hit the floor huh.
                        else if ( map.c_str()[ testZ*map_w*map_h + testY*map_w + testX] == 'F'){
                            hitFloor = true;
                            break;
                        }

                    }
                } // end of ray tracing loop

                // Calculate a shade index based on horizontal distance
                char shade = ' ';

                if( hitWall ){
                    int sIdx = darknessMod * colorMapLen * distanceToWall / plr->getDepth();
                    //snprintf(debugbuff,100,"sIdx: %d", sIdx);
                    mvaddch(y,x,colorMap[sIdx+1]);
                }
                if(hitFloor) {
                    attron(COLOR_PAIR(FLOOR_PAIR));
                    currPair = FLOOR_PAIR;
                    mvaddch(y,x,x%2==y%2?'#':'-');
                }
                if(hitOOB){
                    attron(COLOR_PAIR(SKY_PAIR));
                    currPair = SKY_PAIR;
                    mvaddch(y,x,' ');
                }

                if(!hitOOB && !hitFloor && !hitWall) {
                    mvaddch(y,x,'X');
                }

                if(currPair != 0)
                    attroff(COLOR_PAIR(currPair));
                currPair = 0;
            }
        }


        // Display Stats
        char buff[100];
        snprintf(buff,100,"X:%3.2f, Y:%3.2f Z:%3.2f, FPS:%3.2f",
            fpX, fpY, fpZ, 1.0f/fElapsedTime);
        mvaddnstr(0,map_w + 1,buff,100);


        // print the debug buffer
        mvaddnstr(1,map_w + 1,debugbuff,100);

        {
            attron(COLOR_PAIR(MAP_PAIR));
            for(int nx = 0; nx < map_w; nx++)
                for(int ny=0; ny < map_h; ny++){
                    mvaddch(ny,nx,map[ipZ*map_w*map_h + ny*map_w + (map_w - nx - 1)]);
                }
            
            // add the player to the screen :)
            mvaddch(ipY,map_w - ipX - 1,'P');
            attroff(COLOR_PAIR(MAP_PAIR));
        }

        if (map.c_str()[mapOffset] == 'W'){
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

        unsigned int random = rand() % 300;

        if(random == 0){
            if(hand_rand > 4 || hand_rand < 4){
                hand_dir = !hand_dir;
            }
            hand_rand += hand_dir?1:-1;
        }

        unsigned int hand_offset = hand_rand + 5 + SCREEN_H - hand_height;


        {
            attron(COLOR_PAIR(HANDS_PAIR));
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
            attroff(COLOR_PAIR(HANDS_PAIR));
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