#include "../RWindow.h"
#include "../RPixmapWidget.h"
#include <string>

Realio::RWindow window("Test");
Realio::RPixmapWidget *pixmap;

void keyCallback(SDL_Event e);
int main(int argc, char **argv)
{
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
            if(e.key.keysym.sym == SDLK_UP)
                pixmap->move(pixmap->getXPos(), pixmap->getYPos() - 10);
            if(e.key.keysym.sym == SDLK_DOWN)
                pixmap->move(pixmap->getXPos(), pixmap->getYPos() + 10);
            if(e.key.keysym.sym == SDLK_LEFT)
                pixmap->move(pixmap->getXPos() - 10, pixmap->getYPos());
            if(e.key.keysym.sym == SDLK_RIGHT)
                pixmap->move(pixmap->getXPos() + 10, pixmap->getYPos());
            break;
        case SDL_MOUSEWHEEL:
            if(e.wheel.type == SDL_MOUSEWHEEL)
            {
                int w = pixmap->getWidth();
                int h = pixmap->getHeight();
                pixmap->resize(w + w * e.wheel.y * 0.1,
                               h + h * e.wheel.y * 0.1);
            }
    }
}
