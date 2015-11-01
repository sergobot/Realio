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
#include "RShader.h"
//C++
#include <iostream>

namespace Realio {
RShader::RShader()
{
    initVariableTypes();
}

RShader::RShader(const char *vShader, const char *fShader, const char *gShader)
{
    compileShaders(vShader, fShader, gShader);
}

void RShader::initVariableTypes()
{
    m_variableTypes = {
        {RSHADER_BOOL_VARIABLE,         "bool"},
        {RSHADER_INT_VARIABLE,          "int"},
        {RSHADER_UINT_VARIABLE,         "uint"},
        {RSHADER_FLOAT_VARIABLE,        "float"},

        {RSHADER_BVEC2_VARIABLE,        "bvec2"},
        {RSHADER_BVEC3_VARIABLE,        "bvec3"},
        {RSHADER_BVEC4_VARIABLE,        "bvec4"},

        {RSHADER_IVEC2_VARIABLE,        "ivec2"},
        {RSHADER_IVEC3_VARIABLE,        "ivec3"},
        {RSHADER_IVEC4_VARIABLE,        "ivec4"},

        {RSHADER_UVEC2_VARIABLE,        "uvec2"},
        {RSHADER_UVEC3_VARIABLE,        "uvec3"},
        {RSHADER_UVEC4_VARIABLE,        "uvec4"},

        {RSHADER_VEC2_VARIABLE,         "vec2"},
        {RSHADER_VEC3_VARIABLE,         "vec3"},
        {RSHADER_VEC4_VARIABLE,         "vec4"},

        {RSHADER_MAT2X2_VARIABLE,       "mat2x2"},
        {RSHADER_MAT2X3_VARIABLE,       "mat2x3"},
        {RSHADER_MAT2X4_VARIABLE,       "mat2x4"},

        {RSHADER_MAT3X2_VARIABLE,       "mat3x2"},
        {RSHADER_MAT3X3_VARIABLE,       "mat3x3"},
        {RSHADER_MAT3X4_VARIABLE,       "mat3x4"},

        {RSHADER_MAT4X2_VARIABLE,       "mat4x2"},
        {RSHADER_MAT4X3_VARIABLE,       "mat4x3"},
        {RSHADER_MAT4X4_VARIABLE,       "mat4x4"},

        {RSHADER_SAMPLER1D_VARIABLE,    "Sampler1D"},
        {RSHADER_SAMPLER2D_VARIABLE,    "Sampler2D"},
        {RSHADER_SAMPLER3D_VARIABLE,    "Sampler3D"}
    };
}

void RShader::use()
{
    glUseProgram(m_program);
}

void RShader::compileShaders(const char *vShader, const char *fShader, const char *gShader)
{
    // Compile shaders
    GLuint vertex, fragment, geometry;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "Could not compile vertex shader: " << infoLog << std::endl;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShader, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "Could not compile fragment shader: " << infoLog << std::endl;
    }

    // Shader Program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);

    //Geometry Shader
    if(gShader != nullptr)
    {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShader, NULL);
        glCompileShader(geometry);
        // Print compile errors if any
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            std::cerr << "Could not compile geometry shader: " << infoLog << std::endl;
        }

        glAttachShader(m_program, geometry);
    }

    glLinkProgram(m_program);
    // Print linking errors if any
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cerr << "Could not link shaders into a program: " << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(gShader != nullptr)
        glDeleteShader(geometry);
}

void RShader::compileShaders()
{
    //Concatenate data to the vertex shader
    m_vertexShader.shader = "#version 330 core\n";
    m_vertexShader.shader.append(m_vertexShader.inputVariables);
    m_vertexShader.shader.append(m_vertexShader.outputVariables);
    m_vertexShader.shader.append(m_vertexShader.uniforms);
    m_vertexShader.shader.append("void main() {\n");
    m_vertexShader.shader.append(m_vertexShader.mainFunction + "}");

    //Concatenate data to the fragment shader
    m_fragmentShader.shader = "#version 330 core\n";
    m_fragmentShader.shader.append(m_fragmentShader.inputVariables);
    m_fragmentShader.shader.append(m_fragmentShader.outputVariables);
    m_fragmentShader.shader.append(m_fragmentShader.uniforms);
    m_fragmentShader.shader.append("void main() {\n");
    m_fragmentShader.shader.append(m_fragmentShader.mainFunction + "}");

    //Concatenate data to the geometry shader
    m_geometryShader.shader = "#version 330 core\n";
    m_geometryShader.shader.append(m_geometryShader.inputVariables);
    m_geometryShader.shader.append(m_geometryShader.outputVariables);
    m_geometryShader.shader.append(m_geometryShader.uniforms);
    m_geometryShader.shader.append("void main() {\n");
    m_geometryShader.shader.append(m_geometryShader.mainFunction + "}");

    compileShaders(m_vertexShader.shader.c_str(), m_fragmentShader.shader.c_str(), m_geometryShader.shader.c_str());
}

void RShader::addUniform(const char *name, RShaderVariableType variableType, RShaderShaderType shaderType)
{
    if(shaderType == RSHADER_VERTEX_SHADER)
        m_vertexShader.uniforms.append("uniform " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_GEOMETRY_SHADER)
        m_geometryShader.uniforms.append("uniform " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_FRAGMENT_SHADER)
        m_fragmentShader.uniforms.append("uniform " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else
        std::cerr << "Could not add uniform variable '" << name << "' to any shader: Wrong shader type.\n";
}

int RShader::addInputVariable(const char *name, RShaderVariableType variableType, RShaderShaderType shaderType, bool located)
{
    if(shaderType == RSHADER_VERTEX_SHADER)
        if(located) 
        {
            std::string variable(name);
            std::size_t i = variable.find('[');
            unsigned loc = m_vertexShader.location;
            if(i != std::string::npos)
            {
                m_vertexShader.inputVariables.append("layout (location = " + std::to_string(loc) + ") in " +
                                                 m_variableTypes.at(variableType) +
                                                 " " + name + ";\n");
                m_vertexShader.location += std::stoi(std::string(variable.begin() + i + 1, variable.begin() + variable.find(']') - 1));
            }
            else
                m_vertexShader.location += 1;
            
            return loc;
        }
        else
            m_vertexShader.inputVariables.append("in " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_GEOMETRY_SHADER)
        m_geometryShader.inputVariables.append("in " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_FRAGMENT_SHADER)
        m_fragmentShader.inputVariables.append("in " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else
        std::cerr << "Could not add input variable '" << name << "' to any shader: Wrong shader type.\n";
    
    return -1;
}

int RShader::addOutputVariable(const char *name, RShaderVariableType variableType, RShaderShaderType shaderType, bool located)
{
    if(shaderType == RSHADER_VERTEX_SHADER)
        m_vertexShader.outputVariables.append("out " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_GEOMETRY_SHADER)
        m_geometryShader.outputVariables.append("out " + m_variableTypes.at(variableType) + " " + name + ";\n");
    else if(shaderType == RSHADER_FRAGMENT_SHADER)
    {
        if(located) 
        {
            std::string variable(name);
            std::size_t i = variable.find('[');
            unsigned loc = m_fragmentShader.location;
            if(i != std::string::npos)
            {
                m_fragmentShader.outputVariables.append("layout (location = " + std::to_string(loc) + ") out " +
                                                 m_variableTypes.at(variableType) +
                                                 " " + name + ";\n");
                m_fragmentShader.location += std::stoi(std::string(variable.begin() + i + 1, variable.begin() + variable.find(']') - 1));
            }
            else
                m_fragmentShader.location += 1;
            
            return loc;
        }
        else
            m_fragmentShader.outputVariables.append("out " + m_variableTypes.at(variableType) + " " + name + ";\n");
    }
    else
        std::cerr << "Could not add output variable '" << name << "' to any shader: Wrong shader type.\n";
    
    return -1;
}

void RShader::addAction(const char *line, RShaderShaderType shaderType)
{
    if(shaderType == RSHADER_VERTEX_SHADER)
        m_vertexShader.mainFunction.append(line);
    else if(shaderType == RSHADER_GEOMETRY_SHADER)
        m_geometryShader.mainFunction.append(line);
    else if(shaderType == RSHADER_FRAGMENT_SHADER)
        m_fragmentShader.mainFunction.append(line);
    else
        std::cerr << "Could not add line '"<< line << "' to any shader: Wrong shader type.\n";
}

GLuint RShader::getProgram()
{
    return m_program;
}

void RShader::deleteProgram()
{
    glDeleteProgram(m_program);
}
}
