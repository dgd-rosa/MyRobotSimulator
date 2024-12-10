//#include "Game.hpp"
#include "GameManager.hpp"
using namespace std;


int main(){
    

    try{
        srand(time(0));
        
        GameManager gameManager;
        // Main loop
        while (gameManager.running()) {
            
            //Update
            gameManager.update();

            //Render
            gameManager.render();
        }
    }
    catch(const GameException& ex){
        std::cout << ex.what() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    
    
    return 0;
}