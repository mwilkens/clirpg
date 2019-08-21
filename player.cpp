#include "player.h"

void Player::lookLeft(){
    _a -= (_speed * 0.75f) * elapsedTime;
}
void Player::lookRight(){
    _a += (_speed * 0.75f) * elapsedTime;
}
void Player::moveForward(){
    _x += sinf(_a) * _speed * elapsedTime;
	_y += cosf(_a) * _speed * elapsedTime;
}
void Player::moveBackwards(){
    _x -= sinf(_a) * _speed * elapsedTime;
	_y -= cosf(_a) * _speed * elapsedTime;
}

float Player::getRayAngleX(int col_x, float width){
    return (_a - _fov/2.0f) + ((float)col_x / (float)width) * _fov;
}

float Player::getRayAngleY(int row_y, float height){
    float yfov = _fov/2.0f;
    return (yfov * (float)row_y / (float)height) - (yfov/2.0f);
}