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

// Realio
#include "RWidget.h"
#include "RWidget_global.h"

namespace Realio {
RWidget::RWidget(
        const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0)
    : m_xPos(x)
    , m_yPos(y)
    , m_width(w)
    , m_height(h)
    , m_moved(false)
    , m_resized(false)
{
    m_id = generateID();
}

/*virtual*/ RWidget::~RWidget()
{

}

void RWidget::move(const int x, const int y)
{
    float xTrans = float(2 * (x - m_xPos)) / float(m_winWidth);
    float yTrans = float(2 * (m_yPos - y)) / float(m_winHeight);

    translate(glm::vec3(xTrans, yTrans, 0));

    m_xPos = x;
    m_yPos = y;
    m_moved = true;
}

int RWidget::getXPos()
{
    return m_xPos;
}

int RWidget::getYPos()
{
    return m_yPos;
}

void RWidget::resize(const int w, const int h)
{
    m_width = w;
    m_height = h;
    m_resized = true;
}

void RWidget::scale(const float ratio)
{
    R3DObject::scale(ratio);
}

int RWidget::getWidth()
{
    return m_width;
}

int RWidget::getHeight()
{
    return m_height;
}

int RWidget::getID()
{
    return m_id;
}

/*virtual*/ void RWidget::update()
{

}

/*virtual*/ void RWidget::show()
{

}

void RWidget::setWindowSize(const int w, const int h)
{
    m_winWidth = w;
    m_winHeight = h;

    int x = m_xPos;
    int y = m_yPos;
    m_xPos = 0;
    m_yPos = 0;

    move(x, y);
}
}
