#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

const int PI = 4*atan(1);                                                               // Value of pi

void draw_cylinder(float radius, float height, int R, int G, int B) {

    float x = 0.0, y = 0.0, angle = 0.0, angle_stepsize = 0.1;
    glColor3f(R/255.0, G/255.0, B/255.0);

    // Draw the tube 
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    // Draw the circle on top of cylinder 
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

    // Draw the circle on bottom of cylinder 
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

void draw_open_cylinder(float radius, float height, int R, int G, int B) {
    float x = 0.0, y = 0.0, angle = 0.0, angle_stepsize = 0.1;

    glColor3f(R/255.0, G/255.0, B/255.0);
    
    // Draw the tube 
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
}

void draw_circle(float cx, float cy, float radius) {
    float x, y;
    float angle = 0.0, angle_stepsize=0.1;

    glBegin(GL_POLYGON);
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(cx + x, cy + y , 0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(cx + radius, cy + 0.0, 0.0);
    glEnd();
}