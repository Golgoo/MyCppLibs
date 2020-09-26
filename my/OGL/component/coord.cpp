#include <my/OGL/component/coord.hpp>

using namespace my::OGL::component;

Coord::Coord(int halfExtentedCoord, float coordStep):
_half_extent_coord(halfExtentedCoord), 
_coord_step(coordStep),
_total_point((halfExtentedCoord*2+1) * (halfExtentedCoord*2+1) * 6),
_vertices(new float[_total_point * 3])
{
    int coord_count = 0;
    for(float x = -halfExtentedCoord ; x <= halfExtentedCoord ; x += coordStep){
        for(float y = -halfExtentedCoord ; y <= halfExtentedCoord ; y += coordStep){
            _vertices[coord_count++] = x ;
            _vertices[coord_count++] = y ;
            _vertices[coord_count++] = -halfExtentedCoord ;
            
            _vertices[coord_count++] = x ;
            _vertices[coord_count++] = y ;
            _vertices[coord_count++] = halfExtentedCoord;
        }
    }
    for(float x = -halfExtentedCoord ; x <= halfExtentedCoord ; x += coordStep){
        for(float z = -halfExtentedCoord ; z <= halfExtentedCoord ; z += coordStep){
            _vertices[coord_count++] = x ;
            _vertices[coord_count++] = -halfExtentedCoord ;
            _vertices[coord_count++] = z ;
            
            _vertices[coord_count++] = x ;
            _vertices[coord_count++] = halfExtentedCoord;
            _vertices[coord_count++] = z ;
        }
    }
    for(float y = -halfExtentedCoord ; y <= halfExtentedCoord ; y += coordStep){
        for(float z = -halfExtentedCoord ; z <= halfExtentedCoord ; z += coordStep){
            _vertices[coord_count++] = -halfExtentedCoord ;
            _vertices[coord_count++] = y ;
            _vertices[coord_count++] = z ;
            
            _vertices[coord_count++] = halfExtentedCoord;
            _vertices[coord_count++] = y ;
            _vertices[coord_count++] = z ;
        }
    }
}

Coord::~Coord()
{
    glDeleteBuffers(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    delete _vertices;
}

void Coord::setUpOGL()
{
    glGenBuffers(1, &_VBO);
    glGenVertexArrays(1, &_VAO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * _total_point * sizeof(float), _vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 , (void*)0);
    glEnableVertexAttribArray(0);
}

void Coord::Draw(const Shader &shader)
{
    //Do Some stuff with shader
    glBindVertexArray(_VAO);
    glDrawArrays(GL_LINES, 0, _total_point*2);
}
