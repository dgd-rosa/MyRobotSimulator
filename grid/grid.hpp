#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include "../robot/robot.hpp"

using namespace std;

class Grid{
    public:
        Grid(int row, int col, Position robot_start);
        bool checkMovementFeasibility(char command);
        void updateRobotPos(Position robot_new_pos);
        void printGrid();
    
    private:
        int m_row;
        int m_col;
        vector<vector<char>> m_grid;

        Position m_robot_pos;
};


#endif