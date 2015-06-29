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

//Realio
#include "RWindow.h"

namespace Realio {
RWindow::RWindow(const std::string & title = "")
{
    m_title = new std::string;
    *m_title = title;

    if(!initializeSDL())
    {
        std::cerr << "Exiting.\n";
        std::exit(1);
    }
}

RWindow::~RWindow()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    delete m_title;
}

bool RWindow::initializeSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Could not initialize SDL: " << SDL_GetError();
        std::cerr << std::endl;
        std::exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_DisplayMode current;

    if(SDL_GetCurrentDisplayMode(0, &current) != 0)
    {
        // In case of error...
        std::cerr << "Could not get display mode for video display: ";
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        // Everything is normal
        m_width = current.w;
        m_height = current.h;
    }

    m_window = SDL_CreateWindow(
                m_title->data(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width, m_height,
                SDL_WINDOW_OPENGL |
                SDL_WINDOW_FULLSCREEN_DESKTOP |
                SDL_WINDOW_HIDDEN);

    return true;
}

void RWindow::show()
{
    SDL_ShowWindow(m_window);
}

void RWindow::close()
{
    SDL_DestroyWindow(m_window);
}

void RWindow::hide()
{
    SDL_HideWindow(m_window);
}

void RWindow::setTitle(const std::string & title = "")
{
    *m_title = title;
}

std::string RWindow::getTitle()
{
    return *m_title;
}

void RWindow::addWidget(RWidget & wgt)
{
    RWidget* widget = new RWidget(0, 0, 0, 0);
    *widget = wgt;
    int id = widget->getID();
    //TODO: Add objectName
    //char* chr[] = widget->getObjectName();

    int size = sizeof(m_IDs);
    int *temp;
    temp = new int[size + 1]; // Create temporary array
    memmove(temp, m_IDs, size); // Move data from original array to the temp
    delete[] m_IDs;
    m_IDs = temp;
    m_IDs[size + 1] = id;

    size = sizeof(m_widgets);
    RWidget **tmpWgt;
    tmpWgt = new RWidget*[size + 1]; // Create temporary array
    memmove(tmpWgt, m_widgets, size); // Move data from original array to the temp

    for(int i = 0; i < size; i++)
    {
        delete[] m_widgets[i];
    }
    delete[] m_widgets;

    tmpWgt[size + 1] = widget;
    memmove(m_widgets, tmpWgt, size);

    for(int i = 0; i < size; i++)
    {
        delete[] tmpWgt[i];
    }
    delete[] tmpWgt;
}
}
