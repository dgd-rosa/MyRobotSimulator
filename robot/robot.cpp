#include "robot.hpp"

Robot::Robot(int start_x, int start_y){
    m_position.x = start_x;
    m_position.y = start_y;
}

void Robot::moveUp(){
    m_position.x -= 1;
}

void Robot::moveDown(){
    m_position.x += 1;
}

void Robot::moveLeft(){
    m_position.y -= 1;
}

void Robot::moveRight(){
    m_position.y += 1;
}

Position Robot::getPosition(){
    return m_position;
}