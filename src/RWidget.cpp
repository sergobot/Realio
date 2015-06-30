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
#include "RWidget.h"
#include "RWidget_global.h"

namespace Realio {
RWidget::RWidget(const int x = 0, const int y = 0, const int w = 0, const int h = 0)
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;

    m_id = generateID();
}

RWidget::~RWidget()
{

}

void RWidget::moveTo(const int & x, const int & y)
{
    m_rect.x = x;
    m_rect.y = y;
}

void RWidget::getPosition(int *x, int *y)
{
    *x = m_rect.x;
    *y = m_rect.y;
}

void RWidget::resize(const int & w, const int & h)
{
    m_rect.w = w;
    m_rect.h = h;
}

void RWidget::getSize(int *w, int *h)
{
    *w = m_rect.w;
    *h = m_rect.h;
}

int RWidget::getID()
{
    return m_id;
}
}
