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
//GLEW
#include <GL/glew.h>

namespace Realio {
class RWidget
{
public:
    RWidget(const int x, const int y, const int w, const int h);
    ~RWidget();

    /**
     * @brief sets widget's position on a window to x and y.
     * @param two integers.
     * @return void.
     */
    void move(const int x, const int y);

    /**
     * @brief returns widget's X position.
     * @param void.
     * @return widget's X position.
     */
    int getXPos();

    /**
     * @brief returns widget's Y position.
     * @param void.
     * @return widget's Y position.
     */
    int getYPos();

    /**
     * @brief resizes the widget.
     * @param two integers.
     * @return void.
     */
    void resize(const int w, const int h);

    /**
     * @brief scales the widget.
     * @param scaling ratio in float.
     * @return void.
     */
    void scale(float ratio);

    /**
     * @brief returns widget's width.
     * @param void.
     * @return widget's width.
     */
    int getWidth();

    /**
     * @brief returns widget's height.
     * @param void.
     * @return widget's height.
     */
    int getHeight();

    /**
     * @brief returns ID of the widget.
     * @param void.
     * @return widget's ID.
     */
    int getID();

    /**
     * @brief sets window's height and width
     * @param window's width and height
     * @return void
     */
    void setWindowSize(int w, int h);

    /**
     * @brief updates the widget's content.
     * @param void.
     * @return void.
     */
    virtual void update();

protected:
    int m_id;
    int m_xPos; // Top left angle positions
    int m_yPos;
    int m_width;
    int m_height;
    int m_winWidth;
    int m_winHeight;
    bool m_moved;
    bool m_resized;
};
}

#endif // RWIDGET_H
