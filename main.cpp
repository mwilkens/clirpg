// C++ Headers
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// C Headers
#include <stdio.h>
#include <time.h>

// User Headers
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "entities.h"
#include "player.h"
#include "hand.h"

#define SCREEN_W 480
#define SCREEN_H 240

const char colorMap[] = "BMZC[lYL/!<:- ";
const int colorMapLen = 13;

class clirpg : public olc::PixelGameEngine {
    public:

        std::string map;
        unsigned int map_w;
        unsigned int map_h;
        unsigned int map_d;
        Player * plr;

        clirpg() {
            sAppName = "clirpg";
        }

	    bool OnUserCreate() override {
		// Called once at the start, so create things here

        // String container to hold the map
        //TODO: Make this procedurally generated
        map =

            "..............###..." // 1
            "..............###..." // 2
            "..............###..." // 3
            "...................." // 4
            "...................." // 5
            "...................." // 6
            "...................." // 7
            "...................." // 8
            "...................." // 9 
            "...................." // 10
            "...................." // 11
            "...................." // 12
            "...................." // 13
            "....###............." // 14
            "....###............." // 15
            "...................." // 16
            "...................." // 17
            "...................." // 18
            "...................." // 19
            "...................." // 20
        
            "..............###..." // 1
            "..............###..." // 2
            "..............###..." // 3
            "...................." // 4
            "...................." // 5
            "...................." // 6
            "...................." // 7
            "...................." // 8
            "...................." // 9 
            "...................." // 10
            "...................." // 11
            "...................." // 12
            "....###............." // 13
            "...#####............" // 14
            "...#####............" // 15
            "....###............." // 16
            "...................." // 17
            "...................." // 18
            "...................." // 19
            "...................." // 20

            "..............###..." // 1
            "..............###..." // 2
            "..............###..." // 3
            "...................." // 4
            "...................." // 5
            "...................." // 6
            "...................." // 7
            "...................." // 8
            "...................." // 9 
            "...................." // 10
            "....###............." // 11
            "...#####............" // 12
            "..#######..........." // 13
            "..#######..........." // 14
            "..#######..........." // 15
            "..#######..........." // 16
            "...#####............" // 17
            "....###............." // 18
            "...................." // 19
            "...................." // 20

            "####################" // 1
            "#.............###..#" // 2
            "#.............###..#" // 3
            "#..................#" // 4
            "#..................#" // 5
            "#..................#" // 6
            "#..................#" // 7
            "#..................#" // 8
            "####################" // 9 
            "##########.........#" // 10
            "##########.........#" // 11
            "##########.........#" // 12
            "##########.........#" // 13
            "##########.........#" // 14
            "##########.........#" // 15
            "##########.........#" // 16
            "##########.........#" // 17
            "##########.........#" // 18
            "##########.........#" // 19
            "####################" // 20

            "####################" // 1
            "#........##...###..#" // 2
            "#........##...#.#..#" // 3
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
            "#........##...###..#" // 2
            "#........##...#W#..#" // 3
            "#........##...#.#..#" // 4
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

        map_w = 20; map_h = 20; map_d = 7;

        plr = new Player();

		return true;
	}

    ~clirpg(){
        delete plr;
    }

	bool OnUserUpdate(float fElapsedTime) override
	{
		plr->updateFrame(fElapsedTime);

        float fpX = plr->getX();
        float fpY = plr->getY();
        float fpZ = plr->getZ();
        int ipX = (int)floor(fpX);
        int ipY = (int)floor(fpY);
        int ipZ = (int)floor(fpZ);
        int mapOffset = ipZ*map_w*map_h + ipY*map_w + ipX;

        // Handle input

        if( GetKey(olc::Q).bPressed){
            return 0;
        }

        if( GetKey(olc::A).bHeld){
            plr->lookLeft();
        }

        if( GetKey(olc::D).bHeld){
            plr->lookRight();
        }

        if( GetKey(olc::W).bHeld){
            float x = plr->getX();
            float y = plr->getY();
            plr->moveForward();
            if (map.c_str()[mapOffset] == '#'){
                // reset character position
                plr->setX(x); plr->setY(y);
                plr->moveBackwards();
            }
        }

        if( GetKey(olc::S).bHeld){
            float x = plr->getX();
            float y = plr->getY();
            plr->moveBackwards();
            if (map.c_str()[mapOffset] == '#'){
                // reset character position
                plr->setX(x); plr->setY(y);
                plr->moveForward();
            }
        }

        // Do raytracing

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
                    distanceToWall += 0.25; // step size

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
                            float thresh = 75;

                            if ( edgeDetectX < thresh && edgeDetectY < thresh ||
                                 edgeDetectX < thresh && edgeDetectZ < thresh ||
                                 edgeDetectY < thresh && edgeDetectZ < thresh){
                               darknessMod = 0.8;
                               
                               // DETECT BORDER
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
                    int sIdx = 100 - (darknessMod * 100 * distanceToWall / plr->getDepth());
                    //snprintf(debugbuff,100,"sIdx: %d", sIdx);
                    //mvaddch(y,x,colorMap[sIdx+1]);
                    Draw(x, y, olc::Pixel(sIdx,sIdx,sIdx));
                }
                if(hitFloor) {
                    //mvaddch(y,x,x%2==y%2?'#':'-');
                    Draw(x, y, olc::DARK_MAGENTA);
                }
                if(hitOOB){
                    //mvaddch(y,x,' ');
                    Draw(x, y, olc::Pixel(0,0,0));
                }

                if(!hitOOB && !hitFloor && !hitWall) {
                    //mvaddch(y,x,' ');
                    Draw(x, y, olc::Pixel(0,0,0));
                }
            }
        }

		return true;
	}
};

// Main loop
int main(){

    clirpg Game;

    if (Game.Construct(SCREEN_W,SCREEN_H,4,4))
        Game.Start();

    return 0;

}

/*
/// everything after here is too much
{
    bool hand_dir = false;
    bool hand_rand = 0;

    while (running){

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

*/