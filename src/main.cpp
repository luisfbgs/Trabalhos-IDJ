#include "Game.h"

int main (int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    Game::GetInstance().Run();

    return 0;
}
