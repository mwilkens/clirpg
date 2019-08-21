#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "entities.h"

#define P_DEPTH 16.0f
#define P_FOV   3.14159f/4.0f
#define P_HEIGHT 5.0f

class Player : public Entity {
    protected:
        float _fov; // Field of View
        float _depth; // View Distance
        float _height;
    public:
        Player(): Entity(), _fov(P_FOV),_depth(P_DEPTH), _height(P_HEIGHT) {}
        Player(float x, float y, float angle, float speed, float height):
            Entity(x,y,angle,speed), _fov(P_FOV),_depth(P_DEPTH),_height(height) {}
        
        float getDepth(){return _depth;}
        float getHeight(){return _height;}
        void addHeight(){_height += 1;}
        void lessHeight(){_height -= 1;}

        void lookLeft();
        void lookRight();
        void moveForward();
        void moveBackwards();

        float getRayAngleX(int col_x, float width);
        float getRayAngleY(int row_y, float height);
};

#endif