#ifndef ROBOT_HPP
#define ROBOT_HPP


struct Position{
    int x;
    int y;
};

class Robot{
    public:
        Robot(int start_x, int start_y);

        //Movements
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        //Gets
        Position getPosition();

    private:
        Position m_position;
};

#endif