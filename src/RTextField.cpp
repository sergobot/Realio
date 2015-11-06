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
#include "RTextField.h"

namespace Realio {
RTextField::RTextField(const int x, const int y, const int w, const int h)
    : RPixmap(x,y,w,h)
{
    m_text = "";
}

RTextField::RTextField(const int x, const int y)
    : RPixmap(x,y)
{
    m_text = "";
}

RTextField::RTextField()
    : RPixmap()
{
    m_text = "";
}

std::string RTextField::getText()
{
    return m_text;
}

void RTextField::setText(const std::string & text)
{
    m_text = text;
}

/*virtual*/ void RTextField::update()
{

}
}
