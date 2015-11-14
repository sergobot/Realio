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

#ifndef R3DSCENE_H
#define R3DSCENE_H

// Realio
#include "R3DObject.h"

namespace Realio {
class R3DScene
{
public:
    R3DScene();

    /**
     * @brief adds R3DObject to the scene.
     * @param pointer to a R3DObject object.
     * @return void.
     */
    void addObject(R3DObject *obj);

    /**
     * @brief removes a R3DObject object from the scene.
     * @param pointer to a R3DObject.
     * @return True, if the object is successfully deleted, else returns False.
     */
    bool removeObject(R3DObject *obj);

    /**
     * @brief draws all the R3DObject objects using R3DObject::draw().
     * @param void.
     * @return void.
     */
    void draw();

private:
    std::vector<R3DObject*> m_objects;
};
}

#endif // R3DSCENE_H
