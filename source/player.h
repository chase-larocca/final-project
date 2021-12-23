#ifndef __FinalProject1__player__
#define __FinalProject1__player__
                     
#include <stdio.h>
#include <common.h>

#include <array>

#define _MAX_SPEED 5
#define _DAMPING -.0025
#define _ACC 0.1
#define _ROT 0

class Player {


    vec2 player_vert[18];
    vec3 player_color[18];

    std::array<vec2,18> other_player;


    struct {
        vec2 cur_location;   //Current position of the center
        float angle;         //Rotation angle
        vec2 pointing;       //Vector pointing to the front of the ship
        vec2 move;


        bool inside;
        int current_object;
        int num_obj;

        //std::vector < vec2* > objects;
        std::vector < unsigned int > num_points;

        //This function will be helpful to keep track of the direction the ship
        //is pointing

        bool hit;
        bool move_left;
        bool move_right;
        bool move_down;
        bool jump;

        int health;

        mat4 mv;

        
        //mat4 M1;

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
    
    Player();

    vec2 get_location() { return state.cur_location;  }

    inline void sub_Health() { state.health -= 1;  }

    int get_health() { return state.health;  }
    
    mat4 get_modelView() { return state.mv; }
    inline std::array<vec2, 18> get_verts(mat4 mv) {
        
        for (int i = 0; i <= 18; i++) {
            vec2 mvTransform = !(mv) * player_vert[i];

            other_player[i] = (mvTransform);
        
        }
        return other_player; 
    }

    bool get_hitstate() { return state.hit; }

    void change_color();

    // Player punch
    inline void start_hit(){state.hit = true; }
    inline void stop_hit(){state.hit = false;}
    
    // Player move down
    inline void move_down_start() { state.move_down = true; state.pointing.y = 1.0; }
    inline void move_down_stop() { state.move_down = false; state.pointing.y = 0.0; }

    // Player move left
    inline void move_left_start() { state.move_left = true; state.pointing.x = -1.0; }
    inline void move_left_stop() { state.move_left = false; state.pointing.x = 0.0; }

    // Player move right
    inline void move_right_start() { state.move_right = true; state.pointing.x = 1.0; }
    inline void move_right_stop() { state.move_right = false; state.pointing.x = 0.0; }

    // Player jump
    inline void jump_true() { state.jump = true; state.pointing.y = -1.0; }

    inline void jump_false() { state.jump = false; state.pointing.y = 1.0; }

    //void object_position_callback(GLFWwindow* window);
   

    bool inside_outside_test(GLFWwindow* window, Player p1, Player p2);

    void update_state(float width, float height, int player_number);

    void gl_init(int player_number);

    void draw(mat4 proj, int playerNumber);

};

#endif /* player_h */
