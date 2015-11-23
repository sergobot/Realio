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

#ifndef RANIMATEDPIXMAP_H
#define RANIMATEDPIXMAP_H

// Realio
#include "RPixmap.h"
// C++
#include <vector>

namespace Realio {
class RAnimatedPixmap : public RPixmap
{
public:
    RAnimatedPixmap(const int x, const int y, const int w, const int h);
    RAnimatedPixmap(const int x, const int y);
    RAnimatedPixmap();
    ~RAnimatedPixmap();

    /**
     * @brief loads the image into the widget.
     * @param const char array.
     * @return True, if file is successfully loaded. False, if not.
     */
    bool loadFile(const char *file);

    /**
     * @brief shows the next image to the screen.
     * @param void.
     * @return void.
     */
    void nextFrame();

    /**
     * @brief shows up the pixmap to the widget.
     * @param void.
     * @return void.
     */
    virtual void show();

    /**
     * @brief sets the widget's width and height to the image's ones.
     * @param void.
     * @return void.
     */
    void fitByImage();


private:
    struct Image {
        unsigned char *image;
        int w, h, comp;
        int index;
        GLuint id;
    };
    std::vector<Image*> m_images;

    unsigned currentFrame;
};
}

#endif // RANIMATEDPIXMAP_H
