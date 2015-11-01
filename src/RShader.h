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

//C++
#include <string>
#include <vector>
#include <map>
//GLEW
#include <GL/glew.h>

namespace Realio {
enum RShaderShaderType {
    RSHADER_VERTEX_SHADER,   //Vertex shader
    RSHADER_GEOMETRY_SHADER, //Geometry shader
    RSHADER_FRAGMENT_SHADER  //Fragment shader
};

enum RShaderVariableType {
    //Basic scalar types
    RSHADER_BOOL_VARIABLE,
    RSHADER_INT_VARIABLE,
    RSHADER_UINT_VARIABLE,
    RSHADER_FLOAT_VARIABLE,
    //Boolean vector
    RSHADER_BVEC2_VARIABLE,
    RSHADER_BVEC3_VARIABLE,
    RSHADER_BVEC4_VARIABLE,
    //Integer vector
    RSHADER_IVEC2_VARIABLE,
    RSHADER_IVEC3_VARIABLE,
    RSHADER_IVEC4_VARIABLE,
    //Unsigned integer vector
    RSHADER_UVEC2_VARIABLE,
    RSHADER_UVEC3_VARIABLE,
    RSHADER_UVEC4_VARIABLE,
    //Floating point vector
    RSHADER_VEC2_VARIABLE,
    RSHADER_VEC3_VARIABLE,
    RSHADER_VEC4_VARIABLE,
    //Floating point matrix with 2 columns
    RSHADER_MAT2X2_VARIABLE,
    RSHADER_MAT2X3_VARIABLE,
    RSHADER_MAT2X4_VARIABLE,
    //Floating point matrix with 3 columns
    RSHADER_MAT3X2_VARIABLE,
    RSHADER_MAT3X3_VARIABLE,
    RSHADER_MAT3X4_VARIABLE,
    //Floating point matrix with 4 columns
    RSHADER_MAT4X2_VARIABLE,
    RSHADER_MAT4X3_VARIABLE,
    RSHADER_MAT4X4_VARIABLE,
    //Sapmlers
    RSHADER_SAMPLER1D_VARIABLE,
    RSHADER_SAMPLER2D_VARIABLE,
    RSHADER_SAMPLER3D_VARIABLE,
};

class RShader
{
public:
    RShader(const char *vShader, const char *fShader, const char *gShader = nullptr);
    RShader();

    /**
     * @brief uses shader program.
     * @param void.
     * @return void.
     */
    void use();

    /**
     * @brief compiles shader program form sources.
     * @param vertex and fragment shaders' sources.
     * @return void.
     */
    void compileShaders(const char *vShader, const char *fShader, const char *gShader = nullptr);

    /**
     * @brief concatenates data in m_***Shaders to shaders, compiles and links them to a shader program using function above.
     * @param void.
     * @return void.
     */
    void compileShaders();

    /**
     * @brief adds a uniform variable to the shader.
     * @param name of the variable, its type and shader's type, to which the variable is added.
     * @return void.
     */
    void addUniform(const char* name, RShaderVariableType variableType, RShaderShaderType shaderType);

    /**
     * @brief adds an input variable to the shader.
     * @param name of the variable, its type and shader's type, to which the variable is added and location trigger.
     * @return if shader is vertex and located = true returns location, else returns -1.
     */
    int addInputVariable(const char* name, RShaderVariableType variableType, RShaderShaderType shaderType, bool located = true);

    /**
     * @brief adds an output variable to the shader.
     * @param name of the variable, its type and shader's type, to which the variable is added and location trigger.
     * @return if shader is fragment and located = true returns location, else returns -1.
     */
    int addOutputVariable(const char* name, RShaderVariableType variableType, RShaderShaderType shaderType, bool located = true);
    
    /**
     * @brief adds a line to the main function of the shader.
     * @param line to be executed in the main function of the shader and shader's type, to which the line is added.
     * @return void.
     */
    void addAction(const char* line, RShaderShaderType shaderType);

    /**
     * @brief returns the program.
     * @param void.
     * @return current shader program, placed in GLuint.
     */
    GLuint getProgram();

    /**
     * @brief returns the program.
     * @param void.
     * @return void.
     */
    void deleteProgram();

private:
    struct Shader {
        std::string shader;
        std::string uniforms;
        std::string inputVariables;
        std::string outputVariables;
        std::string mainFunction;
        unsigned location = 0;
        bool used = true;
    };

    Shader m_vertexShader;
    Shader m_geometryShader;
    Shader m_fragmentShader;

    std::map<RShaderVariableType, std::string> m_variableTypes;

    GLuint m_program;

    /**
     * @brief fills m_variableTypes.
     * @param void.
     * @return void.
     */
    void initVariableTypes();
};
}

#endif // RSHADER_H
