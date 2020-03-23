#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "cuboid.h"
using namespace std;


const int window_height = 500, window_width = 500;
float angle = 0.0;
const float camera_dist = -500.0;
const float lightpos[] = {50, 50, 100, 1};
void display();
void reshape(int , int);
void update(int);
void init();
void reset_coordinate();
void draw_try_spots();
void draw_obstacle(char);
void draw_conversion_post();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Model");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    

    glTranslatef(0.0, 0.0, camera_dist);                   // Translates object alog z-axis
    glRotatef(angle, 1.0, 1.0, 1.0);
    // GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
    // GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    // GLfloat shininess[] = {50};
    // glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    // glBegin(GL_POLYGON);
    // glColor3f(0.0, 0.0, 1.0);
    // glVertex3i(0, 0, 0);
    // glVertex3i(0, 100, 0);
    // glVertex3i(100, 100, 0);
    // glVertex3i(100, 0, 0);
    // glEnd();
    draw_cube(100, 100, 100, 0, 0, 255);

    glBegin(GL_POLYGON);
    glVertex3f(lightpos[0], lightpos[1], lightpos[2]);
    glVertex3f(lightpos[0]+2, lightpos[1]+2, lightpos[2]);
    glVertex3f(lightpos[0], lightpos[1]+2, lightpos[2]);
    glEnd();
    
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 20000.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int a) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, update, 0);
    angle += 0.8;

    if (angle > 360.0)
        angle -= 360.0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    // GLfloat lightpos[] = {300, 300, 300, 1};
    GLfloat ambient_color[] = {0, 0, 0, 1};
    GLfloat diffuse_color[] = {1, 1, 1, 1};
    GLfloat specular_color[] = {1, 1, 1, 1};
    GLfloat global_ambient[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_color);
    GLfloat shine[] = {100};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ambient_color);
}

