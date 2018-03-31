#include "mesh.hpp"

Mesh::Mesh() : indices(0)
{
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &indexBuffer);
}

void Mesh::load(
        const GLfloat *vertexArray,
        const GLfloat *normalArray,
        const GLfloat *texCoordArray,
        const GLuint *indexArray,
        GLsizei v_count,
        GLsizei i_count)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, vertexArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 3, normalArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 2, texCoordArray, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, i_count * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

    indices = i_count;
}

void Mesh::load(const aiMesh *mesh)
{
    GLfloat *positionArray = new GLfloat[mesh->mNumVertices * 3];
    GLfloat *normalArray = new GLfloat[mesh->mNumVertices * 3];
    GLfloat *textureCoordArray = new GLfloat[mesh->mNumVertices * 2];
    GLuint *indexArray = new GLuint[mesh->mNumFaces * 3];


    for(unsigned int j = 0; j < mesh->mNumVertices; j++)
    {
        const aiVector3D *vertex = mesh->mVertices + j;
        const aiVector3D *normal = mesh->mNormals + j;

        positionArray[j * 3 + 0] = vertex->x;
        positionArray[j * 3 + 1] = vertex->y;
        positionArray[j * 3 + 2] = vertex->z;

        normalArray[j * 3 + 0] = normal->x;
        normalArray[j * 3 + 1] = normal->y;
        normalArray[j * 3 + 2] = normal->z;

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

    load(positionArray, normalArray, textureCoordArray, indexArray, mesh->mNumVertices, mesh->mNumFaces * 3);

    delete[] positionArray;
    delete[] normalArray;
    delete[] textureCoordArray;
    delete[] indexArray;
}