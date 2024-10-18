#include "grid/grid.hpp"
#include "robot/robot.hpp"

#include <termios.h>
#include <unistd.h>
#include <cstdlib>    // For system("clear") / system("cls")

using namespace std;



void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag |= (ICANON | ECHO);  // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


int main(){
    enableRawMode();


    Robot robot(4, 4);
    Grid grid(15, 15, robot.getPosition());

    grid.printGrid();

    char command;
    while(command != 'q'){
        cout << "Enter move with WSAD. Press q to quit!";
        command = getchar();  // Capture keypress

        if(grid.checkMovementFeasibility(command)){
            if(command == 'w'){
                robot.moveUp();
            }
            if(command == 's'){
                robot.moveDown();
            }
            if(command == 'a'){
                robot.moveLeft();
            }
            if(command == 'd'){
                robot.moveRight();
            }

            grid.updateRobotPos(robot.getPosition());

        }
        //clear terminal
        system("clear");
        grid.printGrid();
    }

    cout << "Robot Simulation Ended\n\n\n";
    disableRawMode();  // Restore terminal settings when done
    return 0;
}