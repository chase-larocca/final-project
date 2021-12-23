// FinalProject1.cpp : Defines the entry point for the application.
//

#include "common.h"

#include "FinalProject1.h"
#include "utils/lodepng.h"
#include "mapping.h"
#include "player.h"
#include "health.h"



using namespace Angel;

Player player1;

Player player2;

Health healthbar;

Mapping map;



using namespace std;

int width, height;

int current_object = 0;
int num_obj = 4;

int who_hit;

std::vector < vec2* > objects;
std::vector < unsigned int > num_points;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

  // PLAYER 1 KEY CALLBACKS
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_LEFT ) // && (action == GLFW_PRESS || action == GLFW_REPEAT))
        if (action == GLFW_PRESS) {
            player1.move_left_start();
        }
        if (action == GLFW_RELEASE) {
            player1.move_left_stop();
        }
    if (key == GLFW_KEY_RIGHT) //&& (action == GLFW_PRESS || action == GLFW_REPEAT))

        if (action == GLFW_PRESS) {
            player1.move_right_start();
        }
        if (action == GLFW_RELEASE) {
            player1.move_right_stop();
        }
        if (key == GLFW_KEY_UP) {
            if (action == GLFW_PRESS) {
                player1.jump_true();
            }
            if (action == GLFW_RELEASE) {
                player1.jump_false();

            }
        }
     if (key == GLFW_KEY_C) {
            if (action == GLFW_PRESS) {
               player1.start_hit();
            }
            if (action == GLFW_RELEASE) {
               player1.stop_hit();
            }
        }
    
    if (key == GLFW_KEY_DOWN) {
        if (action == GLFW_PRESS) {
            player1.move_down_start();
        }
        if (action == GLFW_RELEASE) {
            player1.move_down_stop();
        }
    }
    

     // PLAYER 2 KEY CALLBACKS

     if (key == GLFW_KEY_A) // && (action == GLFW_PRESS || action == GLFW_REPEAT))
            if (action == GLFW_PRESS) {
                player2.move_left_start();
            }
            if (action == GLFW_RELEASE) {
                player2.move_left_stop();
         }
     if (key == GLFW_KEY_D) //&& (action == GLFW_PRESS || action == GLFW_REPEAT))
            if (action == GLFW_PRESS) {
                player2.move_right_start();
            }
            if (action == GLFW_RELEASE) {
                player2.move_right_stop();
            }
     if (key == GLFW_KEY_W) {
            if (action == GLFW_PRESS) {
                player2.jump_true();
            }
            if (action == GLFW_RELEASE) {
                player2.jump_false();

            }
        }
     if (key == GLFW_KEY_Q) {
            if (action == GLFW_PRESS) {
                player2.start_hit();
            }
            if (action == GLFW_RELEASE) {
                player2.stop_hit();
            }
        }
    
    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            player2.move_down_start();
        }
        if (action == GLFW_RELEASE) {
            player2.move_down_stop();
        }
    }

}


//void object_position_callback(GLFWwindow* window)
//{
//    //Assuming the default frustrum with extents from -1 to 1, this converts
//    //the screen cursor position to world coordinates
//    int width, height;
//
//    glfwGetFramebufferSize(window, &width, &height);
//    
//    player1.inside_outside_test(window, player2.get_verts());
//    player2.inside_outside_test(window, player1.get_verts());
//}


void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    player1.gl_init(1);
    player2.gl_init(2);
    healthbar.gl_init(1);

   // map.start();
}


//Call update function 30 times a second
void animate(GLFWwindow* window) {
    if (glfwGetTime() > 0.033) {
        glfwSetTime(0.0);

        player1.update_state(width, height, 1);
        player2.update_state(width, height, 2);

        if (player1.get_hitstate() == true) {
            
            if (player1.inside_outside_test(window, player1, player2) == true) {
                player2.sub_Health();
                player2.change_color();

            }

            
        }

        if (player2.get_hitstate() == true) {
            if (player2.inside_outside_test(window, player1, player2) == true) {
                player1.sub_Health();
                player1.change_color();
            }

            
        }


        
    }




}

int main(void)
{
    GLFWwindow* window;

   // glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 10);


    window = glfwCreateWindow(1024, 768, "Street Fighter", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

   // glClearColor( 0.8, 0.8, 1.0, 1.0 );

    init();

    while (!glfwWindowShouldClose(window)) {

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        //Pick a coordinate system that makes the most sense to you
        //(left, right, top, bottom)
        mat4 proj = Ortho2D(-1.0, 1.0, 1.0, -1.0);

        //mat4 proj = Ortho2D(-width / 2, width / 2, -height / 2, height / 2);

        animate(window);

        glClear(GL_COLOR_BUFFER_BIT);

        if (player1.get_health() > 0) {
            player1.draw(proj, 1);
        }

        if (player2.get_health() > 0) {
            player2.draw(proj, 2);
        }

        healthbar.draw(proj, 1, player1.get_health());


        

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
