#include "../RWindow.h"
#include "../RAnimatedPixmap.h"
#include <string>

Realio::RWindow window("Test");
Realio::RAnimatedPixmap *pixmap;

void keyCallback(SDL_Event e);
int main(int argc, char **argv)
{
    pixmap = new Realio::RAnimatedPixmap();
    pixmap->loadFile("image1.png");
    pixmap->loadFile("image2.png");
    window.addWidget(pixmap);
    window.setKeyCallback(keyCallback);
    window.show();
    pixmap->show();

    while(!window.shouldQuit())
    {
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
                for(int i = 0; i < 20; i++)
                    pixmap->move(pixmap->getXPos(), pixmap->getYPos() - 1);
            if(e.key.keysym.sym == SDLK_DOWN)
                for(int i = 0; i < 20; i++)
                    pixmap->move(pixmap->getXPos(), pixmap->getYPos() + 1);
            if(e.key.keysym.sym == SDLK_LEFT)
                for(int i = 0; i < 20; i++)
                    pixmap->move(pixmap->getXPos() - 1, pixmap->getYPos());
            if(e.key.keysym.sym == SDLK_RIGHT)
                for(int i = 0; i < 20; i++)
                    pixmap->move(pixmap->getXPos() + 1, pixmap->getYPos());
            if(e.key.keysym.sym == SDLK_SPACE)
            {
                pixmap->nextFrame();
            }
            break;
        case SDL_MOUSEWHEEL:
            if(e.wheel.type == SDL_MOUSEWHEEL)
                if(SDL_GetModState() & KMOD_CTRL)
                    pixmap->scale(1 + 0.1 * e.wheel.y);
    }
}
