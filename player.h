#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "entities.h"

#define P_DEPTH 16.0f
#define P_FOV   3.14159f/4.0f

class Player : public Entity {
    protected:
        float _fov; // Field of View
        float _depth; // View Distance
    public:
        Player(): Entity(), _fov(P_FOV),_depth(P_DEPTH) {}
        Player(float x, float y, float z, float angle, float speed):
            Entity(x,y,z,angle,speed), _fov(P_FOV),_depth(P_DEPTH) {}
        
        float getDepth(){return _depth;}
        void addHeight(){_fov += 0.1;}
        void lessHeight(){_fov -= 0.1;}

        void lookLeft();
        void lookRight();
        void lookUp();
        void lookDown();
        void moveForward();
        void moveBackwards();

        //Get ray angles based on the screen pixel
        float getRayAngleX(int col_x, float width);
        float getRayAngleY(int row_y, float height);
};

#endif