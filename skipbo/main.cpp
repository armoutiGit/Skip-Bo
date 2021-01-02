#include "CommandLineError.h"
#include "SkipBoGame.h"

int main(int argc, char **argv) {
    std::ifstream stream;
    // Check for command line errors
    if (CommandLineError(argc, argv)) {
        return 1;
    }

    SkipBoGame* game;

    // Loading from saved game
    if (argc == 3) {
        if (fileCheckOpen(argv[2]) == 1) {
            std::cout << "invalid program usage: can't open input game file" << std::endl;
            return 1;
        }
        stream.open(argv[2], std::ifstream::in);
        game = new SkipBoGame(&stream);
    } 
    // Creating new game
    else {
        if (fileCheckOpen(argv[4]) == 1) {
            std::cout << "invalid program usage: can't open deck file" << std::endl;
            return 1;
        }
        stream.open(argv[4], std::ifstream::in);
        game = new SkipBoGame();
        game->setUpDraw(stream);
        game->setUpPlayers(argv);
    }
    std::cout << std::endl;
    
    game->play();
    delete game;    
    return 0;
}