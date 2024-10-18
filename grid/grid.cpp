#include "grid.hpp"

Grid::Grid(int row, int col, Position robot_start){
    m_row = row;
    m_col = col;

    m_grid = vector<vector<char>>(m_row, vector<char>(m_col, '.'));

    m_robot_pos = robot_start;
    m_grid[m_robot_pos.x][m_robot_pos.y] = 'R';
}

void Grid::printGrid(){
    for(int i=0; i < m_row; i++){
        for(int j=0; j < m_col; j++){
            std::cout << m_grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool Grid::checkMovementFeasibility(char command){

    if(command == 'w' && m_robot_pos.x > 0){
        if(m_grid[m_robot_pos.x-1][m_robot_pos.y] == '.')
            return true;
    }

    if(command == 's' && m_robot_pos.x < m_row - 1){
        if(m_grid[m_robot_pos.x+1][m_robot_pos.y] == '.')
            return true;
    }

    if(command == 'a' && m_robot_pos.y > 0){
        if(m_grid[m_robot_pos.x][m_robot_pos.y-1] == '.')
            return true;
    }

    if(command == 'd' && m_robot_pos.y < m_col-1){
        if(m_grid[m_robot_pos.x][m_robot_pos.y+1] == '.')
            return true;
    }

    return false;
}

void Grid::updateRobotPos(Position robot_new_pos){
    m_grid[m_robot_pos.x][m_robot_pos.y] = '.';
    m_robot_pos = robot_new_pos;
    m_grid[m_robot_pos.x][m_robot_pos.y] = 'R';
}