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

#ifndef RPIXMAP_H
#define RPIXMAP_H

//SDL2
#include <SDL2/SDL.h>
//Realio
#include "RWidget.h"
#include "RShader.h"

namespace Realio {
class RPixmap : public RWidget
{
public:
    RPixmap(const int x, const int y, const int w, const int h);
    RPixmap(const int x, const int y);
    RPixmap();
    ~RPixmap();

    /**
     * @brief loads the image into the widget.
     * @param const char array.
     * @return True, if file is successfully loaded. False, if not.
     */
    bool loadFile(const char *file);

    /**
     * @brief shows up the pixmap to the widget.
     * @param void.
     * @return void.
     */
    virtual void show();

    /**
     * @brief updates the widget's content.
     * @param void.
     * @return void.
     */
    virtual void update();

    /**
     * @brief sets the widget's width and height to the image's ones.
     * @param void.
     * @return void.
     */
    void fitByImage();

private:
    bool imgLoaded;
    unsigned char *m_image;
    int img_height, img_width, comp;
    GLuint m_texture;
    GLuint VBO, VAO, EBO;

    RShader *m_shader;

    /**
     * @brief updates the widget's size and position.
     * @param void.
     * @return void.
     */
    void updateSize();

    /**
     * @brief creates shaders. Call it only once!
     * @param void.
     * @return void.
     */
    void createShaders();
};
}

#endif // RPIXMAP_H
