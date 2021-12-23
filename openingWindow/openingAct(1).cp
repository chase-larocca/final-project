#define GL_SILENCE_DEPRECATION
 #include <iostream>
 #include <vector>
 #include "polygon.h"
 #include "stdio.h"
 #include "string.h"
 #include "stdlib.h"
 
 #ifdef __APPLE__
 #include <GLUT/glut.h>
 #else
 #include <GL/glut.h>
 #endif
 
 
 void display4()
 {
 
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0, 0, 0);
 glRasterPos3f(-1,1,0);
 
 char msg1[] = "FIGHT!!!!";
 for (int i = 0; i<strlen(msg1);i++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
 
 glPushMatrix();
 
 glFlush();
 glutSwapBuffers();
 
 }
 
 
 void display3()
 {
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0, 0, 0);
 glRasterPos3f(0,1,0);
 
 char msg1[] = "3";
 for (int i = 0; i<strlen(msg1);i++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
 
 glFlush();
 glutSwapBuffers();
 }
 
 
 void display2()
 {
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0, 0, 0);
 glRasterPos3f(0,1,2);
 
 char msg1[] = "2";
 for (int i = 0; i<strlen(msg1);i++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
 
 
 
 glFlush();
 glutSwapBuffers();
 }
 
 void display1()
 {
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0, 0, 0);
 glRasterPos3f(0,1,2);
 
 char msg1[] = "1";
 for (int i = 0; i<strlen(msg1);i++)
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
 
 
 glFlush();
 glutSwapBuffers();
 }
 
 
 
 void welcomeDisplay() {
 
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0, 0, 0);
 glRasterPos3f(-2,0,2);
 
 
 char msg2[] = "press x to start the game";
 for (int i = 0; i<strlen(msg2);i++)
 glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
 
 glutSwapBuffers();
 
 }
 
 
 void keys(unsigned char key, int x, int y){
 if (key == 'x'){
 glutDisplayFunc(display3);
 }
 
 if (key == 'c'){
 glutDisplayFunc(display2);
 }
 
 if (key == 'v'){
 glutDisplayFunc(display1);
 }
 
 if (key == 'b'){
 glutDisplayFunc(display4);
 }
 
 if (key == 'n'){
 exit(0);
 
 }   // exit out of window
 
 
 
 // add one more key press to start actual game
 
 
 glutPostRedisplay();
 
 }
 
 int main(int argc, char **argv)
 
 {
 
 glutInit(&argc, argv);
 
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(1024, 768);
 
 glutCreateWindow("Street Fighter");
 
 glOrtho(-10, 10, -10, 10, -10, 10);
 
 glutDisplayFunc(welcomeDisplay);
 glutKeyboardFunc(keys);
 
 
 glutMainLoop();
 
 
 return 0;
 
 
 }
 
 
 

