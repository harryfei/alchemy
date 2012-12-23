#include "game_manager.h"
#include "screen_manager.h"
#include "unistd.h"
int main(int argc, char *argv[])
{
    GameManager game_manager;
    ScreenManager screen_manager;

    return screen_manager.loop(argc, argv);
    //return 1;
}
