#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void draw_cube(float l, float b, float h, int R, int G, int B) {
    glBegin(GL_QUADS);
    glColor3f(R/255.0, G/255.0, B/255.0);
    glNormal3d(0, 0, -1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, b, 0);
    glVertex3f(l, b, 0);
    glVertex3f(l, 0, 0);

    glNormal3d(0, 0, 1);
    glVertex3f(0, 0, h);
    glVertex3f(l, 0, h);
    glVertex3f(l, b, h);
    glVertex3f(0, b, h);

    glNormal3d(-1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, h);
    glVertex3f(0, b, h);
    glVertex3f(0, b, 0);

    glNormal3d(1, 0, 0);
    glVertex3f(l, 0, 0);
    glVertex3f(l, b, 0);
    glVertex3f(l, b, h);
    glVertex3f(l, 0, h);

    glNormal3d(0, -1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(l, 0, 0);
    glVertex3f(l, 0, h);
    glVertex3f(0, 0, h);

    glNormal3d(0, 1, 0);
    glVertex3f(0, b, 0);
    glVertex3f(0, b, h);
    glVertex3f(l, b, h);
    glVertex3f(l, b, 0);

    glEnd();
};