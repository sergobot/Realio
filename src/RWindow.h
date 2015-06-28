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

#ifndef RWINDOW_H
#define RWINDOW_H

//C++
#include <iostream>
#include <string>
#include <vector>
//SDL2
#include <SDL2/SDL.h>
//Realio
#include "RWidget.h"

namespace Realio {
class RWindow
{
public:
    RWindow(const std::string & title);
    ~RWindow();

    /**
     * @brief shows the window.
     * @param void.
     * @return void.
     */
    void show();

    /**
     * @brief closes the window.
     * @param void.
     * @return void.
     */
    void close();

    /**
     * @brief hides the window.
     * @param void.
     * @return void.
     */
    void hide();

    /**
     * @brief sets the window's title to a new one.
     * @param reference to a user's std::string.
     * @return void.
     */
    void setTitle(const std::string & title);

    /**
     * @brief returns the window's title.
     * @param void.
     * @return current title, placed in std::string.
     */
    std::string getTitle();

    /**
     * @brief adds a widget to the window.
     * @param reference to a RWidget object.
     * @return void.
     */
    void addWidget(RWidget & wgt);

private:
    std::string *m_title;
    SDL_Window* m_window;
    std::vector<RWidget*> m_widgets;

    // Window's width and height
    int m_width;
    int m_height;

    /**
     * @brief initializes SDL.
     * @param void.
     * @return True, if SDL is initialized. False, if not.
     */
    bool initializeSdl();
};
}

#endif // RWINDOW_H
