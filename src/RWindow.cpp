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
//C++
#include <algorithm>

namespace Realio {
RWindow::RWindow(const std::string & title = "")
{
    m_title = title;

    if(!initializeSDL())
    {
        std::cerr << "Exiting.\n";
        SDL_Quit();
        std::exit(1);
    }

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, m_width, m_height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    quit = false;
    m_cursorType = CURSOR_ARROW;
}

RWindow::~RWindow()
{
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

bool RWindow::initializeSDL()
{
    SDL_DisplayMode current;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Could not initialize SDL: " << SDL_GetError();
        std::cerr << std::endl;
        std::exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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
                m_title.data(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width, m_height,
                SDL_WINDOW_OPENGL |
                //SDL_WINDOW_FULLSCREEN_DESKTOP |
                SDL_WINDOW_HIDDEN);

    if(m_window == nullptr)
    {
        std::cerr << "Could not iniialize SDL Window: " << SDL_GetError();
        std::cerr << std::endl;
        return false;
    }

    m_surface = SDL_GetWindowSurface(m_window);
    m_context = SDL_GL_CreateContext(m_window);

    //Init cursors
    m_systemCursors[0] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    m_systemCursors[1] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    m_systemCursors[2] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
    m_systemCursors[3] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
    m_systemCursors[4] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    m_systemCursors[5] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    return true;
}

void RWindow::show()
{
    m_shown = true;
    SDL_ShowWindow(m_window);
}

void RWindow::close()
{
    quit = true;
    m_shown = false;
    SDL_DestroyWindow(m_window);
}

void RWindow::hide()
{
    SDL_HideWindow(m_window);
}

void RWindow::setTitle(const std::string & title = "")
{
    m_title = title;
    SDL_SetWindowTitle(m_window, m_title.c_str());
}

std::string RWindow::getTitle()
{
    return m_title;
}

void RWindow::setCursor(const char *filename, const Uint32 type)
{
    if ((type & CURSOR_ARROW) == CURSOR_ARROW)
    {
        if(m_customCursors[0] == nullptr)
            m_customCursors[0] = new RPixmap;
        m_customCursors[0]->loadFile(filename);
    }
    if ((type & CURSOR_IBEAM) == CURSOR_IBEAM)
    {
        if(m_customCursors[1] == nullptr)
            m_customCursors[1] = new RPixmap;
        m_customCursors[1]->loadFile(filename);
    }
    if ((type & CURSOR_WAIT) == CURSOR_WAIT)
    {
        if(m_customCursors[2] == nullptr)
            m_customCursors[2] = new RPixmap;
        m_customCursors[2]->loadFile(filename);
    }
    if ((type & CURSOR_HAND) == CURSOR_HAND)
    {
        if(m_customCursors[3] == nullptr)
            m_customCursors[3] = new RPixmap;
        m_customCursors[3]->loadFile(filename);
    }
}

void RWindow::setCurrentCursor(const Uint32 type)
{
    m_cursorType = type;

    if ((m_cursorType & CURSOR_ARROW) == CURSOR_ARROW)
        if(m_customCursors[0])
        {
            SDL_ShowCursor(0);
            m_customCursors[0]->show();
        }
        else
        {
            SDL_ShowCursor(1);
            SDL_SetCursor(m_systemCursors[0]);
        }

    if ((m_cursorType & CURSOR_IBEAM) == CURSOR_IBEAM)
        if(m_customCursors[1])
        {
            SDL_ShowCursor(0);
            m_customCursors[1]->show();
        }
        else
        {
            SDL_ShowCursor(1);
            SDL_SetCursor(m_systemCursors[1]);
        }

    if ((m_cursorType & CURSOR_WAIT) == CURSOR_WAIT)
        if(m_customCursors[2])
        {
            SDL_ShowCursor(0);
            m_customCursors[2]->show();
        }
        else
        {
            SDL_ShowCursor(1);
            SDL_SetCursor(m_systemCursors[2]);
        }

    if ((m_cursorType & CURSOR_HAND) == CURSOR_HAND)
        if(m_customCursors[3])
        {
            SDL_ShowCursor(0);
            m_customCursors[3]->show();
        }
        else
        {
            SDL_ShowCursor(1);
            SDL_SetCursor(m_systemCursors[4]);
        }

    if ((m_cursorType & CURSOR_NO) == CURSOR_NO)
    {
        SDL_ShowCursor(0);
        SDL_SetCursor(m_systemCursors[3]);
    }
}

void RWindow::addWidget(RWidget *wgt)
{
    m_widgets.push_back(wgt);
    m_IDs.push_back(wgt->getID());
    wgt->setWindowSize(m_width, m_height);
}

void RWindow::deleteWidget(const unsigned ID)
{
    unsigned widgetPos;
    std::vector<unsigned>::iterator it;

    it = std::find(m_IDs.begin(), m_IDs.end(), ID);

    if(it != m_IDs.end())
    {
        widgetPos = std::distance(m_IDs.begin(), it);
        m_widgets.erase(m_widgets.begin() + widgetPos);
        m_IDs.erase(m_IDs.begin() + widgetPos);
    }
    else
        std::cerr << "Could not delete widget with ID = " << ID <<
                     ": Widget not found" << std::endl;
}

/*virtual*/ void RWindow::update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        //User requests quit
        switch(e.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_APP_TERMINATING:
                quit = true;
                break;
            case SDL_MOUSEMOTION:

            default:
                callback(e);
        }

        if(quit)
        {
            close();
            return;
        }
    }


    for(unsigned i = 0; i < m_widgets.size(); ++i)
        m_widgets[i]->update();

    drawCursor();

    SDL_UpdateWindowSurface(m_window);
    SDL_GL_SwapWindow(m_window);
}

void RWindow::drawCursor()
{
    if ((m_cursorType & CURSOR_ARROW) == CURSOR_ARROW)
    {
        if(m_customCursors[0])
            m_customCursors[0]->update();
    }

    if ((m_cursorType & CURSOR_IBEAM) == CURSOR_IBEAM)
    {
        if(m_customCursors[1])
            m_customCursors[1]->update();
    }

    if ((m_cursorType & CURSOR_WAIT) == CURSOR_WAIT)
    {
        if(m_customCursors[2])
            m_customCursors[2]->update();
    }

    if ((m_cursorType & CURSOR_HAND) == CURSOR_HAND)
    {
        if(m_customCursors[3])
            m_customCursors[3]->update();
    }
}

bool RWindow::shouldQuit()
{
    return quit;
}

void RWindow::setKeyCallback(void (*func)(SDL_Event e))
{
    callback = func;
}
}
