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

#ifndef RSHADER_H
#define RSHADER_H

//GLEW
#include <GL/glew.h>

namespace Realio {
class RShader
{
public:
    RShader(const char *vShader, const char *fShader);
    RShader();

    /**
     * @brief uses the shader.
     * @param void.
     * @return void.
     */
    void use();

    /**
     * @brief compiles shader program form sources.
     * @param vertex and fragment shaders' sources.
     * @return void.
     */
    void compileShaders(const char *vShader, const char *fShader);

    /**
     * @brief returns the program.
     * @param void.
     * @return current shader program, placed in GLuint.
     */
    GLuint getProgram();

    /**
     * @brief returns the program.
     * @param void.
     * @return current shader program, placed in GLuint.
     */
    void deleteProgram();

private:
    GLuint m_program;
};
}

#endif // RSHADER_H
