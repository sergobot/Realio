/**
 * This file is part of Realio.
 * Realio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2015 Sergey Popov <sergobot@vivaldi.net>
**/

#include "../RWindow.h"
#include "../RAnimatedPixmap.h"
#include <string>

Realio::RWindow window("Test");
Realio::RAnimatedPixmap *pixmap;

void keyCallback(SDL_Event e);
int main(int argc, char **argv)
{
    // Unused parameters
    (void)argc;
    (void)argv;

    pixmap = new Realio::RAnimatedPixmap();
    pixmap->loadFile("image1.png");
    pixmap->loadFile("image2.png");
    window.addWidget(pixmap);
    window.setKeyCallback(keyCallback);
    window.show();
    pixmap->show();

    window.setCursor("cursor.png", Realio::CURSOR_ARROW);
    window.setCurrentCursor(Realio::CURSOR_ARROW);

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
