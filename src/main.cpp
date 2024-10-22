#include "Game.hpp"
using namespace std;


int main(){
    
    srand(static_cast<unsigned>(time(NULL)));
    //init Game engine
    Game game;

    // Main loop
    while (game.running()) {
        
        //Update
        game.update();

        //Render
        game.render();
    }
    
    return 0;
}