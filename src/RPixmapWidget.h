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

#ifndef RPIXMAPWIDGET_H
#define RPIXMAPWIDGET_H

//SDL2
#include <SDL2/SDL.h>
//Realio
#include "RWidget.h"

namespace Realio {
class RPixmapWidget : public RWidget
{
public:
    RPixmapWidget(const int x, const int y, const int w, const int h);
    ~RPixmapWidget();

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
    void showPixmap();

private:
    bool imgLoaded;
};
}

#endif // RPIXMAPWIDGET_H
