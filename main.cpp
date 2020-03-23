#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "try_spots.h"
#include "obstacle.h"
#include "conversion_post.h"
#include "ball_rack.h"

const int window_height = 900, window_width = 900;
float angle = 0.0;
const float camera_dist = -15000.0;

void display();
void reshape(int , int);
void update(int);
void init();
void reset_coordinate();
void draw_ground();

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
    reset_coordinate();

    // draw_try_spots();
    // draw_obstacle('B');
    // draw_conversion_post();
    // draw_ball_rack();
    draw_ground();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 40000.0);                                                // Setting view frustum
    glMatrixMode(GL_MODELVIEW);
}

void update(int a) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, update, 0);

    angle += 0.2;
    if (angle > 360.0)
        angle -= 360.0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void reset_coordinate() {
    glLoadIdentity();
    glTranslatef(-6650.0, -5000.0, camera_dist);                                        // To translate model in view frustum
    glRotatef(angle, 1.0, 1.0, 1.0);                                                    // View angle for camera
}

void draw_ground() {

    // drawing fence
    glPushMatrix();
    glTranslatef(0.0, 0.0, thick);
    draw_cube(13300+100, 50, 100, 145, 113, 90);                                        // Brown
    glTranslatef(0.0, 10000+50, 0.0);
    draw_cube(13300+100, 50, 100, 145, 113, 90);                                        // Brown
    glTranslatef(0.0, -10000, 0.0);
    draw_cube(50, 10000, 100, 145, 113, 90);                                            // Brown
    glTranslatef(13300+50, 0.0, 0.0);
    draw_cube(50, 10000, 100, 145, 113, 90);                                            // Brown
    glPopMatrix();


    //Lower vertical fences
    glPushMatrix();
    glTranslatef(50.0, 0.0, thick);
    glTranslatef(4075.0, 50.0, 0.0);
    draw_cube(50, 2983, 100, 145, 113, 90);                                             // Brown
    glTranslatef(5100.0, 0.0, 0.0);
    draw_cube(50, 2983, 100, 145, 113, 90);                                             // Brown
    glPopMatrix();


    // Upper vertical fences
    glPushMatrix();
    glTranslatef(50.0, 0.0, thick);
    glTranslatef(4075.0, 8567.0, 0.0);
    draw_cube(50, 1483, 100, 145, 113, 90);                                             // Brown
    glTranslatef(5100.0, 0.0, 0.0);
    draw_cube(50, 1483, 100, 145, 113, 90);                                             // Brown
    glPopMatrix();


    //Receiving Zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glPushMatrix();
    draw_cube(1575, 9000, 10, 97, 157, 71);                                             // Dark green
    glTranslatef(11725.0, 0.0, 0.0);
    draw_cube(1575, 9000, 10, 97, 157, 71);                                             // Dark green
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1000.0, 9000.0, 0.0);
    draw_cube(575, 1000, 10, 97, 157, 71);                                              // Dark green
    glTranslatef(10725.0, 0.0, 0.0);
    draw_cube(575, 1000, 10, 97, 157, 71);                                              // Dark green
    glPopMatrix();
    glPopMatrix();


    // Start Zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(0.0, 9000.0, 0.0);
    // Red Start Zone
    draw_cube(1000, 1000, 10, 176, 49, 53);                                             // Red
    // Blue Start Zone
    glTranslatef(12300.0, 0.0, 0.0);
    draw_cube(1000, 1000, 10, 0, 107, 172);                                             // Blue
    glPopMatrix();


    // Kicking Zone - Red kicking zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(1575.0, 0.0, 0.0);
    draw_cube(2500, 2500, 10, 176, 49, 53);                                             // Kicking Zone 3 - Dark Red
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 2500, 10, 190, 76, 62);                                             // Kicking Zone 2 - Medium Red
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 5000, 10, 233, 110, 108);                                           // Kicking Zone 1 - Light Red
    glPopMatrix();
    

    // Kicking Zone - Blue kicking zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(9225.0, 0.0, 0.0);
    draw_cube(2500, 2500, 10, 0, 107, 172);                                             // Kicking Zone 3 - Dark Blue
    glTranslatef(0.0, 2500.0, 0.0);             
    draw_cube(2500, 2500, 10, 76, 173, 223);                                            // Kicking Zone 2 - Medium Blue
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 5000, 10, 136, 202, 233);                                           // Kicking Zone 1 - Light Blue
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(4075.0, 0.0, 0.0);
    draw_cube(1000, 1000, 10, 176, 49, 53);                                             // Red
    glTranslatef(4150.0, 0.0, 0.0);
    draw_cube(1000, 1000, 10, 0, 107, 172);                                             // Blue
    glPopMatrix();


    // Passing zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(4075.0, 1000.0, 0.0);
    draw_cube(1000, 9000, 10, 126, 195, 79);                                            // Green
    glTranslatef(4150.0, 0.0, 0.0);
    draw_cube(1000, 9000, 10, 126, 195, 79);                                            // Green
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(5075.0, 0.0, 0.0);
    draw_cube(1075, 10000, 10, 126, 195, 79);                                           // Green
    glTranslatef(2075.0, 0.0, 0.0);
    draw_cube(1075, 10000, 10, 126, 195, 79);                                           // Green
    glPopMatrix(); 


    // Try spots
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(7150.0, 1500.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    draw_try_spots();
    glPopMatrix();


    // Below try spots
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(6150.0, 1500.0, 0.0);
    draw_cube(1000, 8500, 10, 97, 157, 71);
    glPopMatrix();


    // Ball rack
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(5900.0, 1500.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    draw_ball_rack();
    glPopMatrix();


    // Conversion Post
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(5940.0, 10050.0, 0.0);
    draw_conversion_post();
    glPopMatrix();


    // Obstacles - Blue
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(2560.0, 4420.0, 0.0);
    draw_obstacle('B');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('B');
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(4100.0, 3090.0, 0.0);
    draw_obstacle('B');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('B');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('B');
    glPopMatrix();


    // Obstacles - Red
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(10740.0, 4420.0, 0.0);
    draw_obstacle('R');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('R');
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(9200.0, 3090.0, 0.0);
    draw_obstacle('R');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('R');
    glTranslatef(0.0, 2660.0, 0.0);
    draw_obstacle('R');
    glPopMatrix();


    // Guidelines

    // Extreme left and right vertical guidelines
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(485.0, 0.0, 0.0);
    draw_cube(30, 10000, 5, 255, 255, 255);
    glTranslatef(12300.0, 0.0, 0.0);
    draw_cube(30, 10000, 5, 255, 255, 255);
    glPopMatrix();

    // Guidelines in start zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(0.0, 9485.0, 0.0);
    draw_cube(1000, 30, 5, 255, 255, 255);
    glTranslatef(12300.0, 0.0, 0.0);
    draw_cube(1000, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Left side horizontal guideline 
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(485.0, 7737.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1995.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1995.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Right side horizontal guidelines
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(9968.0, 7737.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1995.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1995.0, 0.0);
    draw_cube(2847, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Left side vertical guideline
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(3302.0, 3747.0, 0.0);
    draw_cube(30, 4020, 5, 255, 255, 255);
    glPopMatrix();

    // Right side vertical guideline
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(9968.0, 3747.0, 0.0);
    draw_cube(30, 4020, 5, 255, 255, 255);
    glPopMatrix();

    // Left side horizontal guidelines - 2
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(3332.0, 7064.0, 0.0);
    draw_cube(2363, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -2660.0, 0.0);
    draw_cube(2363, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Right side horizontal guidelines - 2
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(7635.0, 7064.0, 0.0);
    draw_cube(2363, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -2660.0, 0.0);
    draw_cube(2363, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Left side vertical guideline
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(5665.0, 0.0, 0.0);
    draw_cube(30, 10000, 5, 255, 255, 255);
    glPopMatrix();

    // Right side vertical guideline
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(7605.0, 0.0, 0.0);
    draw_cube(30, 10000, 5, 255, 255, 255);
    glPopMatrix();

    // Horizontal guidelines in passing zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(4125.0, 485.0, 0.0);
    draw_cube(1540, 30, 5, 255, 255, 255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(7635.0, 485.0, 0.0);
    draw_cube(1540, 30, 5, 255, 255, 255);
    glPopMatrix();

    // Vertical lines in passing zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(4560.0, 0.0, 0.0);
    draw_cube(30, 1000, 5, 255, 255, 255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(8710.0, 0.0, 0.0);
    draw_cube(30, 1000, 5, 255, 255, 255);
    glPopMatrix();

    // Horizontal dashes
    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(5500.0, 8395.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 50.0, thick);
    glTranslatef(7500.0, 8395.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glTranslatef(0.0, -1330.0, 0.0);
    draw_cube(300, 30, 5, 255, 255, 255);
    glPopMatrix();
}