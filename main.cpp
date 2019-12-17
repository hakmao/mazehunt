#include <iostream>
// #include <string>
// #include <ncurses.h>
// #include "defs.h"
// #include "grid.h"
// #include "defs.h"
#include "input_parser.h"
#include "game.h"

#define VERSION "0.0.1"

int main(int argc, char *argv[])
{
    InputParser input(argc, argv);
    if (input.exists("-h") || input.exists("--help"))
    {
        std::cout << "mazehunt version " << VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "mazehunt is a simple terminal game written in C++ with ncurses." << std::endl;
        std::cout << "Move the player with the arrows, [wasd] or [hjkl]." << std::endl;
        std::cout << "Use [q] to quit." << std::endl;
        std::cout << "Usage: mazehunt [OPTION]..." << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << " -h, --help";
        std::cout << "\t\tshows usage information" << std::endl;
        std::cout << " -v, --version";
        std::cout << "\t\tprints version and exit" << std::endl;

        return 0;
    }
    if (input.exists("-v") || input.exists("--version"))
    {
        std::cout << "mazehunt version " << VERSION << std::endl;
        return 0;
    }
    //
    Game game{};
    game.run();

    return 0;
}
