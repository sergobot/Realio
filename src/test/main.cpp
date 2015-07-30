#include "../RWindow.h"
#include "../RPixmapWidget.h"
#include <string>

Realio::RWindow window("Test");

void keyCallback(SDL_Event e);
int main(int argc, char **argv)
{
    Realio::RPixmapWidget *pixmap;
    pixmap = new Realio::RPixmapWidget(100, 100, 440, 512);
    pixmap->loadFile("image.png");
    window.addWidget(pixmap);
    window.setKeyCallback(keyCallback);
    pixmap->show();
    window.show();

    while(!window.shouldQuit())
    {
        pixmap->update();
        window.update();
    }

    delete pixmap;

    return 0;
}

void keyCallback(SDL_Event e)
{
    switch(e.type)
    {
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_ESCAPE)
                window.close();
            break;
    }
}
