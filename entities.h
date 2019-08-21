#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <math.h>

class Entity{
    protected:
        float _x; // Position X
        float _y; // Position Y
        float _a; // Angle in Radians
        float _speed; // Speed of movement

        // Static variable for standardizing speeds
        static float elapsedTime;
    public:
        Entity():
            _x(2.0f),_y(2.0f),_a(0.0f),_speed(50.0f){}
        Entity(float x, float y, float angle, float speed):
            _x(x),_y(y),_a(angle),_speed(speed) {}

        float getX(){return _x;}
        float getY(){return _y;}
        float getA(){return _a;}

        void updateFrame(float time){
            elapsedTime = time;
        }
};

#endif