#ifndef __FinalProject1__health__
#define __FinalProject1__health__

#include <stdio.h>
#include <common.h>

#include <array>

class  Health {


    vec2 player_vert[4];
    vec3 player_color[4];

    struct {

        mat4 mv;

    } state;

    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;

    //mat2 RotateZ(const GLfloat theta);

public:

    Health();

    void update_state(float width, float height);

    void gl_init(int player_number);

    void draw(mat4 proj, int playerNumber, int health);

};

#endif /* health_h */

