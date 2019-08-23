#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <math.h>

class Entity{
    protected:
        float _x; // Position X
        float _y; // Position Y
        float _z;
        float _a; // Angle in Radians
        float _ay; // Angle in Radians

        float _speed; // Speed of movement

        // Static variable for standardizing speeds
        static float elapsedTime;
    public:
        Entity():
            _x(2.0f),_y(2.0f),_z(1.0f),_a(0.0f),_ay(0.0f),_speed(10.0f){}
        Entity(float x, float y, float z, float angle, float speed):
            _x(x),_y(y), _z(z), _a(angle),_speed(speed),_ay(0.0f) {}

        float getX(){return _x;}
        float getY(){return _y;}
        float getZ(){return _z;}
        float getA(){return _a;}
        float getAY(){return _ay;}

        void updateFrame(float time){
            elapsedTime = time;
        }
};

#endif