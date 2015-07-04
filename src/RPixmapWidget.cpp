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
#include "RPixmapWidget.h"

namespace Realio {
RPixmapWidget::RPixmapWidget(
        const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0)
    : RWidget(x,y,w,h)
{
    imgLoaded = false;
}

RPixmapWidget::~RPixmapWidget()
{

}

bool RPixmapWidget::loadFile(const char *file)
{
    // Add support for loading images
    imgLoaded = true;

    return imgLoaded;
}

void RPixmapWidget::showPixmap()
{
    // Add support for rendering images
}
}
