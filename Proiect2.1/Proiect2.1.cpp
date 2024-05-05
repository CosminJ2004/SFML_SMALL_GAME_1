// Proiect2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main()
{

    //init srand
    std::srand((time(NULL)));
    ///inint game engine
    Game game;

      //Game loop
    while (game.running()&&!game.getEndGame())
    {
       
        //UPDATE
        game.update();



        //render
        game.render();

        //draw your game 

       
    }
    //end



    return 0;
}

