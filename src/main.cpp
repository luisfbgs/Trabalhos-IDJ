#include "Game.h"
#include "TitleState.h"

int main (int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    Game::GetInstance().Push(new TitleState());
    Game::GetInstance().Run();

    return 0;
}
