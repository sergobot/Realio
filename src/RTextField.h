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

#ifndef RTEXTFIELD_H
#define RTEXTFIELD_H

//Realio
#include "RPixmap.h"
//C++
#include "string"

namespace Realio {
class RTextField : public RPixmap
{
public:
    RTextField(const int x, const int y, const int w, const int h);
    RTextField(const int x, const int y);
    RTextField();

    /**
     * @brief returns current text.
     * @param void.
     * @return current text.
     */
    std::string getText();

    /**
     * @brief sets text content of the widget.
     * @param new text.
     * @return void.
     */
    void setText(const std::string & text);

    /**
     * @brief updates the widget's content.
     * @param void.
     * @return void.
     */
    virtual void update();

private:
    std::string m_text;
};
}

#endif // RTEXTFIELD_H
