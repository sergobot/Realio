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

#ifndef RWIDGET_H
#define RWIDGET_H

//SDL2
#include <SDL2/SDL.h>

namespace Realio {
class RWidget
{
public:
    RWidget(const int x, const int y, const int w, const int h);
    ~RWidget();

    /**
     * @brief sets widget's position on a window to x and y.
     * @param references to two integers.
     * @return void.
     */
    void moveTo(const int & x, const int & y);

    /**
     * @brief sets the x and y integers to current position.
     * @param pointers to two integers.
     * @return void.
     */
    void getPosition(int* x, int* y);

    /**
     * @brief resizes the widget.
     * @param references to two integers.
     * @return void.
     */
    void resize(const int & w, const int & h);

    /**
     * @brief sets the w and h integers to current size.
     * @param pointers to two integers.
     * @return void.
     */
    void getSize(int* w, int* h);

    /**
     * @brief returns ID of the widget.
     * @param void.
     * @return widget's ID.
     */
    int getID();

    /**
     * @brief returns ID of the widget.
     * @param void.
     * @return widget's ID.
     */
    void setRenderer(SDL_Renderer *renderer);

private:
    SDL_Rect m_rect;
    SDL_Renderer *m_renderer;
    int m_id;
};
}

#endif // RWIDGET_H
