#ifndef __FinalProject1__mapping__
#define __FinalProject1__mapping__

#include <stdio.h>
#include <common.h>
#include "utils/lodepng.h"
#include "utils/SourcePath.h"
#include "common.h"


class Mapping {

    struct {

    } state;

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;

public:

    Mapping();

    void start();

};

#endif /* mapping_h */
