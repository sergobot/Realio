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
#include "R3DScene.h"
// C++
#include <iostream>

namespace Realio {
R3DScene::R3DScene()
{

}

void R3DScene::addObject(R3DObject *obj)
{
    m_objects.push_back(obj);
}

bool R3DScene::removeObject(R3DObject *obj)
{
    if(obj == nullptr)
    {
        std::cerr << "Could not remove R3DObject from R3DScene: no object given" << std::endl;
        return false;
    }

    for(unsigned i = 0; i < m_objects.size(); ++i)
    {
        if(m_objects[i] == obj)
            m_objects.erase(m_objects.begin() + i); // If object is added multiple times, remove all pointers to it
        else
        {
            std::cerr << "Could not delete R3DObject(" << obj << ") from R3DScene: No such object" << std::endl;
            return false;
        }
    }

    return true;
}

void R3DScene::draw()
{
    for(unsigned i = 0; i < m_objects.size(); ++i)
        m_objects[i]->draw();
}
}
