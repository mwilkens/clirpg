// C++ Headers
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

// C Headers
#include <stdio.h>
#include <ncurses.h>

#define SCREEN_W 120
#define SCREEN_H 40
#define MAP_W 16
#define MAP_H 16

class Entity{
    protected:
        float _x; // Position X
        float _y; // Position Y
        float _a; // Angle in Radians
        float _speed; // Speed of movement
    public:
        Entity():
            _x(0.0f),_y(0.0f),_a(0.0f),_speed(5.0f){}
        Entity(float x, float y, float angle, float speed):
            _x(x),_y(y),_a(angle),_speed(speed) {}
};

class Player : public Entity {
    protected:
        float _fov; // Field of View
        float _depth; // View Distance
    public:
        Player(): Entity(), _fov(3.14159f/4.0f),_depth(16.0f) {}
        Player(float x, float y, float angle, float speed):
            Entity(x,y,angle,speed), _fov(3.14159f/4.0f),_depth(16.0f) {}
};

void writeBuffer(char * screen){
    // Cycle through each row
    for(int i=0;i<SCREEN_H;i++){
        // Write one ROW of the screen buffer
        cout.write(screen + (i*SCREEN_W), SCREEN_W*sizeof(char));
        puts("\n");
    }

    refresh();
}

int main(){

    // Initialize ncurses mode
    initscr();
    // Disable line buffering
    raw();
    // Enable keypresses
    keypad(stdscr, TRUE);
    // Disable key echoing
    noecho();

    // Here is our screen buffer
    char * screenBuffer = new char[SCREEN_W * SCREEN_H];

    // String container to hold the map
    std::string map;

    // Need some test points to determine how fast the game is running
    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    while (1){
        tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

        // Write buffer

        // Display buffer
        screenBuffer[SCREEN_W * SCREEN_H - 1] = '\0';
    }
    
    // Make sure to clear the screen
    delete screenBuffer;

    // Exit ncurses mode
    endwin();

    return 0;
}