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

#ifndef RGAME_H
#define RGAME_H

//Realio
#include "RWindow.h"
//C++
#include <iostream>
#include <string>

namespace Realio {
class RGame
{
public:
    explicit RGame(const std::string & name);
    ~RGame();

    /**
     * @brief sets name for the game.
     * @param new name.
     * @return void.
     */
    void setName(const std::string & name);

    /**
     * @brief returns current name of the game.
     * @param void.
     * @return current name, placed in std::string.
     */
    std::string getName();

    /**
     * @brief returns pointer to window of the game.
     * @param void.
     * @return main window.
     */
    RWindow* getWindow();

private:
    std::string *m_name;
    RWindow *m_window;
};
}

#endif // RGAME_H
