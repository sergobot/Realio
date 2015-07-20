#include "../RWindow.h"
#include "../RPixmapWidget.h"
#include <string>

int main(int argc, char **argv)
{
    std::string name;
    name = "Test";
    Realio::RWindow realio(name);
    Realio::RPixmapWidget* pixmap;
    pixmap = new Realio::RPixmapWidget(0, 0, 800, 600);
    pixmap->loadFile("image.png");
    realio.addWidget(pixmap);
    pixmap->showPixmap();
    realio.show();
    realio.update();
    SDL_Delay(2000);
    realio.close();
    SDL_Delay(2000);
    return 0;
}
