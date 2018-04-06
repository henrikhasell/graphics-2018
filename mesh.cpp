#include "mesh.hpp"

Mesh::Mesh() : indices(0)
{
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &tangentBuffer);
    glGenBuffers(1, &bitangentBuffer);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &tangentBuffer);
    glDeleteBuffers(1, &bitangentBuffer);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

void Mesh::load(
        const GLfloat *vertexArray,
        const GLfloat *normalArray,
        const GLfloat *tangentArray,
        const GLfloat *bitangentArray,
        const GLfloat *texCoordArray,
        const GLuint *indexArray,
        GLsizei v_count,
        GLsizei i_count)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, vertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, normalArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, tangentArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, bitangentArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 2, texCoordArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, i_count * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

    indices = i_count;
}

void Mesh::load(const aiMesh *mesh)
{
    auto *positionArray = new GLfloat[mesh->mNumVertices * 3];
    auto *normalArray = new GLfloat[mesh->mNumVertices * 3];
    auto *tangentArray = new GLfloat[mesh->mNumVertices * 3];
    auto *bitangentArray = new GLfloat[mesh->mNumVertices * 3];
    auto *textureCoordArray = new GLfloat[mesh->mNumVertices * 2];
    auto *indexArray = new GLuint[mesh->mNumFaces * 3];


    for(unsigned int j = 0; j < mesh->mNumVertices; j++)
    {
        const aiVector3D *vertex = mesh->mVertices + j;
        const aiVector3D *normal = mesh->mNormals + j;
        const aiVector3D *tangent = mesh->mTangents + j;
        const aiVector3D *bitangent = mesh->mBitangents + j;

        positionArray[j * 3 + 0] = vertex->x;
        positionArray[j * 3 + 1] = vertex->y;
        positionArray[j * 3 + 2] = vertex->z;

        normalArray[j * 3 + 0] = normal->x;
        normalArray[j * 3 + 1] = normal->y;
        normalArray[j * 3 + 2] = normal->z;

        tangentArray[j * 3 + 0] = tangent->x;
        tangentArray[j * 3 + 1] = tangent->y;
        tangentArray[j * 3 + 2] = tangent->z;

        bitangentArray[j * 3 + 0] = bitangent->x;
        bitangentArray[j * 3 + 1] = bitangent->y;
        bitangentArray[j * 3 + 2] = bitangent->z;

        if(*mesh->mTextureCoords)
        {
            const aiVector3D *textureCoord = *mesh->mTextureCoords + j;

            textureCoordArray[j * 2 + 0] = textureCoord->x;
            textureCoordArray[j * 2 + 1] = textureCoord->y;
        }
        else
        {
            textureCoordArray[j * 2 + 0] = 0.0f;
            textureCoordArray[j * 2 + 1] = 0.0f;
        }
    }

    for(unsigned int j = 0; j < mesh->mNumFaces; j++)
    {
        aiFace *face = mesh->mFaces + j; // Assume triangular faces.

        for(unsigned int k = 0; k < face->mNumIndices; k++)
        {
            indexArray[j * 3 + k] = face->mIndices[k];
        }
    }

    load(
        positionArray,
        normalArray,
        tangentArray,
        bitangentArray,
        textureCoordArray,
        indexArray,
        mesh->mNumVertices,
        mesh->mNumFaces * 3);

    delete[] positionArray;
    delete[] normalArray;
    delete[] tangentArray;
    delete[] bitangentArray;
    delete[] textureCoordArray;
    delete[] indexArray;
}