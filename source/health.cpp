#include "health.h"


Health::Health() {


};


void Health::gl_init(int player_number) {

    vec2* player = new vec2[4];

    vec3* player_colors = new vec3[4];


    if (player_number == 1) {


        // Body

        player_vert[0] = vec2(-0.25, 0.5); player_color[0] = vec3(1.0, 1.0, 0.0);
        player_vert[1] = vec2(-0.5, 0.5); player_color[1] = vec3(1.0, 1.0, 0.0);
        player_vert[2] = vec2(-0.5, 0.25); player_color[2] = vec3(1.0, 1.0, 0.0);
        player_vert[3] = vec2(-0.5, 0.7); player_color[3] = vec3(1.0, 1.0, 0.0);


        //player_vert[0] = vec2(-0.5, 0.25);  player_color[0] = vec3(1.0, 0.0, 0.0);
        //player_vert[1] = vec2(-0.25, 0.25);  player_color[1] = vec3(1.0, 0.0, 0.0);
        //player_vert[2] = vec2(-0.25, 0.0);  player_color[2] = vec3(1.0, 0.0, 0.0);
        //player_vert[3] = vec2(-0.5, 0.25);  player_color[3] = vec3(1.0, 0.0, 0.0);
        //player_vert[4] = vec2(-0.25, 0.0);  player_color[4] = vec3(1.0, 0.0, 0.0);
        //player_vert[5] = vec2(-0.5, 0.0);  player_color[5] = vec3(1.0, 0.0, 0.0);

        //player_vert[6] = vec2(-0.5, 0.25);  player_color[6] = vec3(1.0, 0.0, 0.0);
        //player_vert[7] = vec2(0.0, 0.25);  player_color[7] = vec3(1.0, 0.0, 0.0);
        //player_vert[8] = vec2(-0.25, 0.25);  player_color[8] = vec3(1.0, 0.0, 0.0);
        //player_vert[9] = vec2(-0.25, 0.25);  player_color[9] = vec3(1.0, 0.0, 0.0);
        //player_vert[10] = vec2(0.0, 0.25);  player_color[10] = vec3(1.0, 0.0, 0.0);
        //player_vert[11] = vec2(-0.5, 0.25);  player_color[11] = vec3(1.0, 0.0, 0.0);

        //// Fist

        //player_vert[12] = vec2(-0.25, 0.1);  player_color[12] = vec3(1.0, 0.0, 0.0);
        //player_vert[13] = vec2(-0.1, 0.1);  player_color[13] = vec3(1.0, 0.0, 0.0);
        //player_vert[14] = vec2(-0.1, 0.05);  player_color[14] = vec3(1.0, 0.0, 0.0);
        //player_vert[15] = vec2(-0.25, 0.1);  player_color[15] = vec3(1.0, 0.0, 0.0);
        //player_vert[16] = vec2(-0.1, 0.05);  player_color[16] = vec3(1.0, 0.0, 0.0);
        //player_vert[17] = vec2(-0.25, 0.05);  player_color[17] = vec3(1.0, 0.0, 0.0);

    }

    else {

        
        // Body
        
        player_vert[0] = vec2(-0.25, 0.5); player_color[0] = vec3(1.0, 1.0, 0.0);
        player_vert[1] = vec2(-0.5, 0.5); player_color[1] = vec3(1.0, 1.0, 0.0);
        player_vert[2] = vec2(-0.5, 0.25); player_color[2] = vec3(1.0, 1.0, 0.0);

        //player_vert[3] = vec2(-0.5, 0.25); player_color[3] = vec3(1.0, 1.0, 0.0);
        //player_vert[4] = vec2(-0.25, 0.0); player_color[4] = vec3(1.0, 1.0, 0.0);
        //player_vert[5] = vec2(-0.5, 0.0); player_color[5] = vec3(1.0, 1.0, 0.0);

        //player_vert[6] = vec2(-0.5, 0.25); player_color[6] = vec3(1.0, 1.0, 0.0);
        //player_vert[7] = vec2(0.0, 0.25); player_color[7] = vec3(1.0, 1.0, 0.0);
        //player_vert[8] = vec2(-0.25, 0.25); player_color[8] = vec3(1.0, 1.0, 0.0);
        //player_vert[9] = vec2(-0.25, 0.25); player_color[9] = vec3(1.0, 1.0, 0.0);
        //player_vert[10] = vec2(0.0, 0.25); player_color[10] = vec3(1.0, 1.0, 0.0);
        //player_vert[11] = vec2(-0.5, 0.25); player_color[11] = vec3(1.0, 1.0, 0.0);

        //// Fist

        //player_vert[12] = vec2(-0.25, 0.1); player_color[12] = vec3(1.0, 1.0, 0.0);
        //player_vert[13] = vec2(-0.1, 0.1); player_color[13] = vec3(1.0, 1.0, 0.0);
        //player_vert[14] = vec2(-0.1, 0.05); player_color[14] = vec3(1.0, 1.0, 0.0);
        //player_vert[15] = vec2(-0.25, 0.1); player_color[15] = vec3(1.0, 1.0, 0.0);
        //player_vert[16] = vec2(-0.1, 0.05); player_color[16] = vec3(1.0, 1.0, 0.0);
        //player_vert[17] = vec2(-0.25, 0.05); player_color[17] = vec3(1.0, 1.0, 0.0);

    }

    size_t player_vert_bytes = 4 * sizeof(vec2);

    size_t player_color_bytes = 4 * sizeof(vec3);

    std::string vshader = shader_path + "vshader_Ship.glsl";
    std::string fshader = shader_path + "fshader_Ship.glsl";

    GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
    GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

    GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GLvars.vertex_shader, 1, (const GLchar**)&vertex_shader_source, NULL);
    glCompileShader(GLvars.vertex_shader);
    check_shader_compilation(vshader, GLvars.vertex_shader);

    GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(GLvars.fragment_shader, 1, (const GLchar**)&fragment_shader_source, NULL);
    glCompileShader(GLvars.fragment_shader);
    check_shader_compilation(fshader, GLvars.fragment_shader);

    GLvars.program = glCreateProgram();
    glAttachShader(GLvars.program, GLvars.vertex_shader);
    glAttachShader(GLvars.program, GLvars.fragment_shader);

    glLinkProgram(GLvars.program);
    check_program_link(GLvars.program);

    glBindFragDataLocation(GLvars.program, 0, "fragColor");

    GLvars.vpos_location = glGetAttribLocation(GLvars.program, "vPos");
    GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor");
    GLvars.M_location = glGetUniformLocation(GLvars.program, "M");

    // Create a vertex array object
    glGenVertexArrays(1, &GLvars.vao);
    //Set GL state to use vertex array object
    glBindVertexArray(GLvars.vao);

    //Generate buffer to hold our vertex data
    glGenBuffers(1, &GLvars.buffer);
    //Set GL state to use this buffer
    glBindBuffer(GL_ARRAY_BUFFER, GLvars.buffer);

    //Create GPU buffer to hold vertices and color
    glBufferData(GL_ARRAY_BUFFER, sizeof(player_vert) + sizeof(player_color), NULL, GL_STATIC_DRAW);
    //First part of array holds vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(player_vert), player_vert);
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(player_vert), sizeof(player_color), player_color);

    glEnableVertexAttribArray(GLvars.vpos_location);
    glEnableVertexAttribArray(GLvars.vcolor_location);

    glVertexAttribPointer(GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(player_vert)));

    glBindVertexArray(0);

}


void Health::draw(mat4 proj, int playerNumber, int health) {

    glUseProgram(GLvars.program);
    
    //Draw something


    glBindVertexArray(GLvars.vao);
    glDrawArrays(GL_TRIANGLES, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);

}