#include "RWindow.h"
#include <string>
int main(int argc, char **argv)
{
    std::string name;
    name = "Test";
    Realio::RWindow realio(name);
    realio.show();
    SDL_Delay(2000);
    realio.close();
    SDL_Delay(2000);
    return 0;
}
