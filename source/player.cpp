#include "player.h"

#include <string>
#include <string>

using namespace std;

//Player constructor
Player::Player() {

    state.current_object = 0;
    state.mv;

    state.health = 50;

    state.cur_location = vec2(0.0, 0.0);
    state.pointing = vec2(0.0, 0.0);
    state.move = vec2(0.0, 0.0);
    state.angle = 0.0;
};

//mat2 RotateZ2D(const GLfloat theta) {
//    GLfloat angle = DegreesToRadians * theta;
//    mat2 c;
//    c[0][0] = c[1][1] = cos(angle);
//    c[1][0] = sin(angle);
//    c[0][1] = -c[1][0];
//    return c;
//}


//Called everytime an animation tick happens
void Player::update_state(float width, float height, int player_number) {
    if (state.jump == true || state.move_right == true || state.move_left == true || state.move_down == true) {
        state.move += _ACC * state.pointing;
        if (sqrt(state.move.x * state.move.x + state.move.y * state.move.y) > _MAX_SPEED) {
            state.move /= sqrt(state.move.x * state.move.x + state.move.y * state.move.y);
            state.move *= _MAX_SPEED;
        }
    }


    state.move *= 0.25;
    state.cur_location += state.move;
    
    if (player_number == 1) {
        
        if (state.cur_location.x < -.5) { //-width / 2 height / 2
            state.cur_location.x = -.5;
        }
        
        if (state.cur_location.x > 1.25) {
            state.cur_location.x = 1.25;
        }
        
        if (state.cur_location.y > .75) {  //-height / 2 height / 2
            state.cur_location.y = .75;
        }
        if (state.cur_location.y < -1.0) {
            state.cur_location.y = -1.0;
        }
    }
    
    if (player_number == 2) {
        if (state.cur_location.x < -1.25) { //-width / 2 height / 2
            state.cur_location.x = -1.25;
        }
        
        if (state.cur_location.x > .5) {
            state.cur_location.x = .5;
        }
        
        if (state.cur_location.y > .75) {  //-height / 2 height / 2
            state.cur_location.y = .75;
        }
        if (state.cur_location.y < -1.0) {
            state.cur_location.y = -1.0;
        }
    }
}




bool Player::inside_outside_test(GLFWwindow* window, Player player, Player player2) {

    //vec2 point = player2.get_location();
    // vec2 point2 = player2.player_vert[12];


    //if (point == point2) {
    //    glfwSetWindowShouldClose(window, GLFW_TRUE);

    //    std::cout << "Close Window";

    //    return true;
    //
    //}
    int strips = 0; 

    //state.inside = true;


    state.inside = false;


    for (int i = 12; i <= 17; i++) {
        //vec2 p1 = player.player_vert[i] + player.get_location();
        //vec2 p2 = player.player_vert[i + 1] + player.get_location();

        vec2 p1 = player.player_vert[i] + player.get_location();

        vec2 center = player2.get_location();

        if (p1.x > center.x - 0.125) {
            if (p1.x < center.x + 0.125) {
                if (p1.y > center.y - 0.125) {
                    if (p1.y < center.y + 0.125) {
                        state.inside = true;
                        return true;
                    }
                }
            }
        }

        else {
        
            state.inside = false;
        }



        return true;
    }


}

void Player::change_color() {

    if (state.health == 100) {
        for (int i = 0; i <= 17; i++) {
            player_color[i].y += .25;
            player_color[i].z += .25;
        }
    }

    if (state.health == 74) {
        for (int i = 0; i <= 17; i++) {
            player_color[i].y += .25;
            player_color[i].z += .25;
        }
    }

    if (state.health == 49) {
        for (int i = 0; i <= 17; i++) {
            player_color[i].y += .25;
            player_color[i].z += .25;
        }
    }

    if (state.health == 24) {
        for (int i = 0; i <= 17; i++) {
            player_color[i].y += .25;
            player_color[i].z += .25;
        }
    }


    


}


//Initialize the gl state and variables
void Player::gl_init(int player_number) {

    //Player
    //vec2* player = new vec2[18];
    //vec3* player_colors = new vec3[18];
    //player_vert[0] = vec2(-0.5, 0.25); player_color[0] = vec3(1.0, 0.0, 0.0);
    //player_vert[1] = vec2(-0.25, 0.25); player_color[1] = vec3(1.0, 0.0, 0.0);
    //player_vert[2] = vec2(-0.25, 0.0); player_color[2] = vec3(1.0, 0.0, 0.0);
    //player_vert[3] = vec2(-0.5, 0.25); player_color[3] = vec3(1.0, 0.0, 0.0);
    //player_vert[4] = vec2(-0.25, 0.0); player_color[4] = vec3(1.0, 0.0, 0.0);
    //player_vert[5] = vec2(-0.5, 0.0); player_color[5] = vec3(1.0, 0.0, 0.0);
    //player_vert[6] = vec2(-0.5, 0.25); player_color[6] = vec3(1.0, 0.0, 0.0);
    //player_vert[7] = vec2(0.0, 0.25); player_color[7] = vec3(1.0, 0.0, 0.0);
    //player_vert[8] = vec2(-0.25, 0.25); player_color[8] = vec3(1.0, 0.0, 0.0);
    //player_vert[9] = vec2(-0.25, 0.25); player_color[9] = vec3(1.0, 0.0, 0.0);
    //player_vert[10] = vec2(0.0, 0.25); player_color[10] = vec3(1.0, 0.0, 0.0);
    //player_vert[11] = vec2(-0.5, 0.25); player_color[11] = vec3(1.0, 0.0, 0.0);
    //// Fist
    //player_vert[12] = vec2(-0.25, 0.1); player_color[12] = vec3(1.0, 0.0, 0.0);
    //player_vert[13] = vec2(-0.1, 0.1); player_color[13] = vec3(1.0, 0.0, 0.0);
    //player_vert[14] = vec2(-0.1, 0.05); player_color[14] = vec3(1.0, 0.0, 0.0);
    //player_vert[15] = vec2(-0.25, 0.1); player_color[15] = vec3(1.0, 0.0, 0.0);
    //player_vert[16] = vec2(-0.1, 0.05); player_color[16] = vec3(1.0, 1.0, 0.0);
    //player_vert[17] = vec2(-0.25, 0.05); player_color[17] = vec3(1.0, 1.0, 0.0);
    //size_t player_vert_bytes = 18 * sizeof(vec2);
    //size_t player_color_bytes = 18 * sizeof(vec3);


    if (player_number == 1) {
    
        
        // Body

        player_vert[0] = vec2(-0.5, 0.25);  player_color[0] = vec3(1.0, 0.0, 0.0);
        player_vert[1] = vec2(-0.25, 0.25);  player_color[1] = vec3(1.0, 0.0, 0.0);
        player_vert[2] = vec2(-0.25, 0.0);  player_color[2] = vec3(1.0, 0.0, 0.0);
        player_vert[3] = vec2(-0.5, 0.25);  player_color[3] = vec3(1.0, 0.0, 0.0);
        player_vert[4] = vec2(-0.25, 0.0);  player_color[4] = vec3(1.0, 0.0, 0.0);
        player_vert[5] = vec2(-0.5, 0.0);  player_color[5] = vec3(1.0, 0.0, 0.0);

        player_vert[6] = vec2(-0.5, 0.25);  player_color[6] = vec3(1.0, 0.0, 0.0);
        player_vert[7] = vec2(0.0, 0.25);  player_color[7] = vec3(1.0, 0.0, 0.0);
        player_vert[8] = vec2(-0.25, 0.25);  player_color[8] = vec3(1.0, 0.0, 0.0);
        player_vert[9] = vec2(-0.25, 0.25);  player_color[9] = vec3(1.0, 0.0, 0.0);
        player_vert[10] = vec2(0.0, 0.25);  player_color[10] = vec3(1.0, 0.0, 0.0);
        player_vert[11] = vec2(-0.5, 0.25);  player_color[11] = vec3(1.0, 0.0, 0.0);

        // Fist

         player_vert[12] = vec2(-0.25, 0.1);  player_color[12] = vec3(1.0, 0.0, 0.0);
         player_vert[13] = vec2(-0.1, 0.1);  player_color[13] = vec3(1.0, 0.0, 0.0);
         player_vert[14] = vec2(-0.1, 0.05);  player_color[14] = vec3(1.0, 0.0, 0.0);
         player_vert[15] = vec2(-0.25, 0.1);  player_color[15] = vec3(1.0, 0.0, 0.0);
         player_vert[16] = vec2(-0.1, 0.05);  player_color[16] = vec3(1.0, 0.0, 0.0);
         player_vert[17] = vec2(-0.25, 0.05);  player_color[17] = vec3(1.0, 0.0, 0.0);

    }

    else {

        vec2* player = new vec2[18];

        vec3* player_colors = new vec3[18];

        // Body

        player_vert[0] = vec2(-0.5, 0.25); player_color[0] = vec3(1.0, 1.0, 0.0);
        player_vert[1] = vec2(-0.25, 0.25); player_color[1] = vec3(1.0, 1.0, 0.0);
        player_vert[2] = vec2(-0.25, 0.0); player_color[2] = vec3(1.0, 1.0, 0.0);
        player_vert[3] = vec2(-0.5, 0.25); player_color[3] = vec3(1.0, 1.0, 0.0);
        player_vert[4] = vec2(-0.25, 0.0); player_color[4] = vec3(1.0, 1.0, 0.0);
        player_vert[5] = vec2(-0.5, 0.0); player_color[5] = vec3(1.0, 1.0, 0.0);

        player_vert[6] = vec2(-0.5, 0.25); player_color[6] = vec3(1.0, 1.0, 0.0);
        player_vert[7] = vec2(0.0, 0.25); player_color[7] = vec3(1.0, 1.0, 0.0);
        player_vert[8] = vec2(-0.25, 0.25); player_color[8] = vec3(1.0, 1.0, 0.0);
        player_vert[9] = vec2(-0.25, 0.25); player_color[9] = vec3(1.0, 1.0, 0.0);
        player_vert[10] = vec2(0.0, 0.25); player_color[10] = vec3(1.0, 1.0, 0.0);
        player_vert[11] = vec2(-0.5, 0.25); player_color[11] = vec3(1.0, 1.0, 0.0);

        // Fist

        player_vert[12] = vec2(-0.25, 0.1); player_color[12] = vec3(1.0, 1.0, 0.0);
        player_vert[13] = vec2(-0.1, 0.1); player_color[13] = vec3(1.0, 1.0, 0.0);
        player_vert[14] = vec2(-0.1, 0.05); player_color[14] = vec3(1.0, 1.0, 0.0);
        player_vert[15] = vec2(-0.25, 0.1); player_color[15] = vec3(1.0, 1.0, 0.0);
        player_vert[16] = vec2(-0.1, 0.05); player_color[16] = vec3(1.0, 1.0, 0.0);
        player_vert[17] = vec2(-0.25, 0.05); player_color[17] = vec3(1.0, 1.0, 0.0);

    }
   
    size_t player_vert_bytes = 18 * sizeof(vec2);

    size_t player_color_bytes = 18 * sizeof(vec3);

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


//Draw a ship
void Player::draw(mat4 proj,int playerNumber) {

    glUseProgram(GLvars.program);
    glBindVertexArray(GLvars.vao);

    //If you have a modelview matrix, pass it with proj
    //if (state.pointing.x == 1.0) {
    //    mat4 mv = Angel::Translate(state.cur_location.x, state.cur_location.y, 1.0);
    //    glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj * mv);
    //}
    //else {
    //    
    //    
    //}

    if (playerNumber == 1) { 
        
        state.mv = Angel::Translate(state.cur_location.x, state.cur_location.y, 1.0);
        glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj * state.mv);
    }
    if (playerNumber == 2) {
       

        mat4  mv = Angel::Translate(state.cur_location.x, state.cur_location.y, 1.0) * Angel::RotateY(180);
        glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj * mv);
    }
   
    //Draw something

    /*glBindVertexArray(GLvars.vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);*/

    

    //Draw
    std::cout<<state.hit;
    if(state.hit){
        
        //Maybe draw something different if the thruster is on
        glBindVertexArray( GLvars.vao);
        glDrawArrays(GL_TRIANGLES, 12, 17);
        
      //  glBindVertexArray(0);
    }

    glDrawArrays(GL_TRIANGLES, 0, 12);

    glBindVertexArray(0);
    glUseProgram(0);

}
