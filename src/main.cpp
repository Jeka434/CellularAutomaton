#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <iostream>
#include <unistd.h>

#include "CellularAutomaton.hpp"

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

GLint FPS = 60;
GLint window_width = 900;
GLint window_height = 900;
GLfloat left = 0.0;
GLfloat right = 1.0;
GLfloat bottom = 0.0;
GLfloat top = 1.0;
//Automaton sizes
GLint world_width = 300;
GLint world_height = 300;

CellularAutomaton *automaton;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    GLfloat xSize = (right - left) / world_width;
    GLfloat ySize = (top - bottom) / world_height;
    
    glBegin(GL_QUADS);
    for (GLint x = 0; x < world_width; ++x) {
        for (GLint y = 0; y < world_height; ++y) {

            float color = automaton->get_color(x, y);
            glColor3f(1.0*color, 1.0*color*color*color*color, 0.1*color);

            glVertex2f(    x*xSize+left,    y*ySize+bottom);
            glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
            glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
            glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
        }
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    window_width = w;
    window_height = h;

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void update(int value) {

    automaton->iterate();

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, update, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cellular Automaton");
    glClearColor(1, 1, 1, 1);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    automaton = new CellularAutomaton(world_width, world_height);

    update(0);
    glutMainLoop();

    return 0;
}