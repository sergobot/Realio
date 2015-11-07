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
#include "R3DObject.h"
#include "RCamera.h"
// C++
#include <iostream>
#include <sstream>
// STB
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace Realio {
R3DObject::R3DObject()
    : m_shader(nullptr)
{
    m_shader = createShaders();
}

R3DObject::~R3DObject()
{
    if(m_shader)
    {
        m_shader->deleteProgram();
        delete m_shader;
    }
}
void R3DObject::translate(const glm::vec3 vec)
{
    m_modelMatrix = glm::translate(m_modelMatrix, vec);
}

void R3DObject::rotate(const glm::vec3 axis, const float angle)
{
    m_modelMatrix = glm::rotate(m_modelMatrix, angle, axis);
}

void R3DObject::scale(const glm::vec3 ratio)
{
    m_modelMatrix = glm::scale(m_modelMatrix, ratio);
}

void R3DObject::scale(const float ratio)
{
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(ratio, ratio, ratio));
}

void R3DObject::loadModel(const char *file)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Could not load " << file << " to R3DObject: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Retrieve the directory path of the filepath
    std::string path(file);
    m_directory = path.substr(0, path.find_last_of('/'));

    // Process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void R3DObject::processNode(const aiNode *node, const aiScene *scene)
{
    for(unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
        setupMesh(&m_meshes.back());
    }

    for(unsigned i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

R3DObject::Mesh R3DObject::processMesh(const aiMesh *mesh, const aiScene *scene)
{
    // Data to fill
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture*> textures;

    for(unsigned i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        glm::vec3 vec;

        // Positions
        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.position = vec;

        // Normals
        vec.x = mesh->mNormals[i].x;
        vec.y = mesh->mNormals[i].y;
        vec.z = mesh->mNormals[i].z;
        vertex.normal = vec;

        // Texture coordinates
        if(mesh->mTextureCoords[i])
        {
            glm::vec2 vector;
            vector.x = mesh->mTextureCoords[0][i].x;
            vector.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vector;
        }
        else
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        if(mesh->mTangents != nullptr)
        {
            // Tangent
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
            vertex.tangent = vec;
        }
        if(mesh->mBitangents != nullptr)
        {
            // Bitangent
            vec.x = mesh->mBitangents[i].x;
            vec.y = mesh->mBitangents[i].y;
            vec.z = mesh->mBitangents[i].z;
            vertex.bitangent = vec;
        }

        vertices.push_back(vertex);
    }

    for(unsigned i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];

        // Copy indices of the mesh to our indices vector
        for(unsigned j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    if(mesh->mMaterialIndex > 0 || mesh->mMaterialIndex == 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse textures
        std::vector<Texture*> diffuseTextures = loadMaterialTextures(mat, R3DOBJECT_DIFFUSE_TEXTURE);
        textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());
        // Specular textures
        std::vector<Texture*> specularTextures = loadMaterialTextures(mat, R3DOBJECT_SPECULAR_TEXTURE);
        textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());
        // Normal textures
        std::vector<Texture*> normalTextures = loadMaterialTextures(mat, R3DOBJECT_NORMAL_TEXTURE);
        textures.insert(textures.end(), normalTextures.begin(), normalTextures.end());
    }

    Mesh pMesh;
    pMesh.vertices = vertices;
    pMesh.indices = indices;
    pMesh.textures = textures;

    pMesh.shader = createShaders();

    return pMesh;
}

void R3DObject::setupMesh(Mesh *mesh)
{
    // Vertex shader
    mesh->shader->addInputVariable("normal", RSHADER_VEC3_VARIABLE, RSHADER_VERTEX_SHADER);
    mesh->shader->addInputVariable("texCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER);
    mesh->shader->addOutputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER);
    mesh->shader->addAction("TexCoord = texCoord;\n", RSHADER_VERTEX_SHADER);
    // Fragment shader
    mesh->shader->addInputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_FRAGMENT_SHADER);

    // Setup mesh
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), &mesh->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), &mesh->indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));
    // Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);

    // Setup textures of the mesh
    unsigned diffuseTexturesCounter = 0;
    unsigned specularTexturesCounter = 0;
    unsigned normalTexturesCounter = 0;

    // We will add this line to the fragment shader
    std::string line = "color = ";

    float weight = 1.0f / mesh->textures.size();

    for(unsigned i = 0; i < mesh->textures.size(); ++i)
    {
        std::stringstream ss;

        R3DObjectTextureType type = mesh->textures[i]->type;

        if(type == R3DOBJECT_DIFFUSE_TEXTURE)
        {
            mesh->textures[i]->name = "diffuseTexture";
            ss << ++diffuseTexturesCounter;
        }
        else if(type == R3DOBJECT_SPECULAR_TEXTURE)
        {
            mesh->textures[i]->name = "specularTexture";
            ss << ++specularTexturesCounter;
        }
        else if(type == R3DOBJECT_NORMAL_TEXTURE)
        {
            mesh->textures[i]->name = "normalTexture";
            ss << ++normalTexturesCounter;
        }
        else
        {
            std::cerr << "Could not setup a mesh: Unknown texture type." << std::endl;
            break;
        }

        mesh->textures[i]->name.append(ss.str());

        mesh->shader->addUniform(mesh->textures[i]->name.c_str(), RSHADER_SAMPLER2D_VARIABLE, RSHADER_FRAGMENT_SHADER);
        line.append("texture(" + mesh->textures[i]->name + ", TexCoord) * " + std::to_string(weight) + " + ");
    }

    // Remove last two symbols ("+ ") and append ";"
    line.pop_back();
    line.pop_back();
    line.pop_back();
    line.append(";");

    mesh->shader->addAction(line.c_str(), RSHADER_FRAGMENT_SHADER);

    mesh->shader->compileShaders();
}

std::vector<R3DObject::Texture*> R3DObject::loadMaterialTextures(const aiMaterial *material, const R3DObjectTextureType type)
{
    std::vector<Texture*> textures;

    aiTextureType textureType;

    if(type == R3DOBJECT_DIFFUSE_TEXTURE)
        textureType = aiTextureType_DIFFUSE;
    else if(type == R3DOBJECT_SPECULAR_TEXTURE)
        textureType = aiTextureType_SPECULAR;
    else if(type == R3DOBJECT_NORMAL_TEXTURE)
        textureType = aiTextureType_HEIGHT;

    for(unsigned i = 0; i < material->GetTextureCount(textureType); ++i)
    {
        aiString str;
        material->GetTexture(textureType, i, &str);

        std::string path = m_directory + '/' + str.C_Str();
        bool loaded = false;

        for(unsigned j = 0; j < m_textures.size(); ++j)
        {
            if(m_textures[j]->path == path)
            {
                textures.push_back(m_textures[j]);
                loaded = true; // Texture with the same path is already loaded, skip it
                break;
            }
        }

        if(!loaded)
        {
            Texture *texture = new Texture;

            int width, height, comp;
            unsigned char* image = stbi_load(path.c_str(), &width, &height, &comp, STBI_rgb_alpha);

            glGenTextures(1, &texture->id);
            glBindTexture(GL_TEXTURE_2D, texture->id);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexImage2D(GL_TEXTURE_2D, 0, comp == 3 ? GL_RGB : GL_RGBA, width, height,
                         0, comp == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image);

            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // Set texture filtering
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(image);

            texture->path = path;
            texture->type = type;

            m_textures.push_back(texture);
            textures.push_back(m_textures.back());
        }
    }

    return textures;
}

glm::mat4 R3DObject::getModelMatrix()
{
    return m_modelMatrix;
}

void R3DObject::draw()
{
    for(unsigned i = 0; i < m_meshes.size(); ++i)
    {
        Mesh *mesh = &m_meshes[i];

        mesh->shader->use();

        for(unsigned j = 0; j < mesh->textures.size(); ++j)
        {
            glActiveTexture(GL_TEXTURE0 + j);
            glUniform1i(glGetUniformLocation(mesh->shader->getProgram(), mesh->textures[j]->name.c_str()), j);
            glBindTexture(GL_TEXTURE_2D, mesh->textures[j]->id);
        }

        glm::mat4 view = RCamera::global->getViewMatrix();
        glm::mat4 projection = glm::perspective(RCamera::global->getZoomRatio(), (float)1920/(float)1080, 0.1f, 100.0f); // DO NOT DO LIKE THIS!!!

        glm::vec4 vec(0.320384f, 14.057541f, 0.507779f, 1.0f);
        vec = projection * view * m_modelMatrix * vec;

        // Pass the matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(mesh->shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(mesh->shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(mesh->shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(mesh->VAO);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Unbind those textures
        for (unsigned j = 0; j < mesh->textures.size(); ++j)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

RShader* R3DObject::createShaders()
{
    RShader *shader = new RShader;
    // Configuring basic vertex shader
    shader->addInputVariable("position", RSHADER_VEC3_VARIABLE, RSHADER_VERTEX_SHADER, true);
    shader->addUniform("model", RSHADER_MAT4X4_VARIABLE, RSHADER_VERTEX_SHADER);
    shader->addUniform("view", RSHADER_MAT4X4_VARIABLE, RSHADER_VERTEX_SHADER);
    shader->addUniform("projection", RSHADER_MAT4X4_VARIABLE, RSHADER_VERTEX_SHADER);
    shader->addAction("gl_Position = projection * view * model * vec4(position, 1.0f);\n", RSHADER_VERTEX_SHADER);

    // Configuring basic fragment shader
    shader->addOutputVariable("color", RSHADER_VEC4_VARIABLE, RSHADER_FRAGMENT_SHADER, false);

    return shader;
}
}
