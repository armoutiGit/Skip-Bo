#include <iostream>
#include <fstream>
#include <string>

#include "CommandLineError.h"

using std::cout;
using std::endl;

// Function to handle invalid # of arguments, invalid first argument, invalid # of playeres, and bad stock size errors
int CommandLineError(int argc, char** argv) {

    // Invalid # of arguments error
    if ((argc != 3) && (argc != 5)) {
        cout << "invalid program usage: invalid number of arguments" << endl;
        return 1;
    }

    // shuffle argument error check
    std::string trueorfalse = argv[1];
    if (trueorfalse != "true" && trueorfalse != "false") {
        std::cout << "invalid program usage: invalid first argument" << std::endl;
        return 1;
    }

    if (argc == 5) {
        // Checking for invalid # of players
        if (atoi(argv[2]) < 2 || atoi(argv[2]) > 6) {
            std::cout << "invalid program usage: num players must be 2-6" << std::endl;
            return 1;
        }
        std::cout << "num players is " << argv[2] << std::endl;

        // Checking for bad stock size
        if (atoi(argv[2]) < 6 && ((atoi(argv[3]) > 30) || (atoi(argv[3]) < 1))) {
            std::cout << "invalid program usage: bad stock size" << std::endl;
            return 1;
        }
        else if (atoi(argv[2]) == 6 && ((atoi(argv[3]) > 20) || (atoi(argv[3]) < 1))) {
            std::cout << "invalid program usage: bad stock size" << std::endl;
            return 1;
        }
        std::cout << "stock size is " << argv[3] << std::endl;
    }
    return 0;
}

// Makes a test stream to check if "filename" can be opened
int fileCheckOpen(std::string filename) {
    std::ifstream teststream;
    teststream.open(filename, std::ifstream::in);
        if(!teststream.is_open()) {
            // If the file cannot be opened, close the stream and exit program
            teststream.close();
            return 1;
        }
    return 0;
}