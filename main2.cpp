#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "try_spots.h"
#include "obstacle.h"
#include "conversion_post.h"
#include "ball_rack.h"


// Necessary constant declarations ...
const int window_height = 900, window_width = 900;
float angle = 0.0, roboMoveAngle = 0.0f, viewAngle = 0.0f;
float camera_dist = 5000.0, deltaAngle = 0.0f, deltaMove = 0.0f;
bool state = true;
float lx=0.0f,ly=-1.0f;                                                                 // camera's direction vector
float x=0.0f, y=5.0f;                                                                   // XY position of the camera


// Function declarations ...
void display();
void reshape(int, int);
void update(int);
void init();
void reset_camera();
void draw_ground();
void set_lighting();
void special_key(int, int, int);
void keyboard(unsigned char, int, int);
void draw_robot(float, float);
void release_key(int, int, int);
void get_pos(float);
void get_dir(float);


int main(int argc, char **argv) {
    // INIT GLUT AND CREATE WINDOW
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);           
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(window_width, window_height);                                    // Sets window height and width ...
    glutCreateWindow("Model");

    init();                                                                             // Initializes lighting ...

    // REGISTER CALLBACKS
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);                                                           // Reshapes view window after window resize ...
    glutIdleFunc(display);
    glutTimerFunc(0, update, 0);                                                        // Setting up the frame every time ...
    
    // KEY BINDINGS
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_key);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(release_key);

    glutMainLoop();
    return 0;
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    set_lighting();
}


void get_pos(float deltaMove) {
    int new_x = x + deltaMove*lx;
    int new_y = y + deltaMove*ly;
    if (new_x > 0 && new_x < 13400) x = new_x;
    if (new_y > -150 && new_y < 10850) {
        if (new_y > 10100) { if (x > 5990 && x < 7410) y = new_y; }
        else if (new_y < 0) { if (x > 5990 && x < 7410) y = new_y; }
        else y = new_y;
    }
}


void get_dir(float deltaAngle) {
    viewAngle += deltaAngle;
    lx = sin(viewAngle);
    ly = -cos(viewAngle);
}


void display() {
    if (deltaAngle) get_dir(deltaAngle);
    if (deltaMove) get_pos(deltaMove);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    reset_camera();
    draw_ground();
    draw_robot(x, y); // rendering red robot

    if (deltaMove) { // SHOW HANDS/LEGS MOVEMENT
        if (state) {
            if (roboMoveAngle < 30) roboMoveAngle+=1.5f;
            else state=false;
        } else {
            if (roboMoveAngle > -30) roboMoveAngle-=1.5f;
            else state=true;
        }
    } else roboMoveAngle = 0.0f;
    cout << "x-" << x << ", y-" << y << endl;

    glutSwapBuffers();
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio =  w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);                                                             // Setting up the viewport ...
    gluPerspective(60, ratio, 2.0, 40000.0);                                                // Setting view frustum ...
    glMatrixMode(GL_MODELVIEW);
}


void update(int a) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, update, 0);                                                  // 60 FPS frame rate ...
}

void reset_camera() {
    glLoadIdentity();
    gluLookAt(  x-lx*500  ,     y-ly*500 , 650.0f,
                x+500*lx  ,     y+500*ly , 650.0f,
                0.0f, 0.0f,  1.0f);
}


void set_lighting() {
    float light_pos[] = { 6650, 5000, 5000, 1};

    // Setting light properties
    float ambient_light[] = { 0, 0, 0, 1};
    float diffuse_light[] = {1, 1, 1, 1};
    float specular_light[] = {1, 1, 1, 1};
    float specular_material[] = {1, 1, 1, 1};
    float emission_material[] = {0, 0, 0, 1};
    float shininess[] = {50};
    float global_ambient[] = {0.2, 0.2, 0.2, 1};                                        // default ...
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    glLightModelfv(GL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Setting material properties
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}


void special_key(int key, int x, int y) {
    float move = 10.0f, ang = 0.01f;

    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = ang; break;
        case GLUT_KEY_RIGHT : deltaAngle = -ang; break;
        case GLUT_KEY_UP : deltaMove = move; break;
        case GLUT_KEY_DOWN : deltaMove = -move; break;
    }
}


void release_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}


void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        // PRESS ESCAPE TO EXIT
        case 27:
            exit(0);
        default:
            break;
    }
}


void drawCube(float x, float y, float z, string str) {
    if (str == "brown") {
        draw_cube(x, y, z, 145, 113, 90);
    } else if (str == "darkGreen") {
        draw_cube(x, y, z, 97, 157, 71);
    } else if (str == "green") {
        draw_cube(x, y, z, 126, 195, 79);
    } else if (str == "red") {
        draw_cube(x, y, z, 176, 49, 53);
    } else if (str == "blue") {
        draw_cube(x, y, z, 0, 107, 172);
    }
}


void draw_robot(float X, float Y) {
    glPushMatrix();
    glTranslatef(X, Y, 0);
    glRotatef(viewAngle*60, 0.0f, 0.0f, 1.0f);

    // HEAD
    glPushMatrix();
    glTranslatef(30, 0, 543);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    draw_cube(60, 60, 60, 255, 255, 100);
    glPopMatrix();

    // UPPER BODY
    glPushMatrix();
    glTranslatef(-75, 0, 360);
    drawCube(150, 60, 180, "red");
    glPopMatrix();

    // LEFT LEG
    glPushMatrix();
    glTranslatef(-75, 0, 330);
    glRotatef(roboMoveAngle, 1.0f, 0.0f, 0.0f);
    drawCube(60, 60, -270, "darkGreen");
    glPopMatrix();

    // RIGHT LEG
    glPushMatrix();
    glTranslatef(15, 0, 330);
    glRotatef(-roboMoveAngle, 1.0f, 0.0f, 0.0f);
    drawCube(60, 60, -270, "darkGreen");
    glPopMatrix();

    // LEFT HAND
    glPushMatrix();
    glTranslatef(-105, 0, 525);
    glRotatef(-roboMoveAngle, 1.0f, 0.0f, 0.0f);
    draw_cube(30, 60, -210, 0, 100, 100);
    glPopMatrix();

    // RIGHT HAND
    glPushMatrix();
    glTranslatef(75, 0, 525);
    glRotatef(roboMoveAngle, 1.0f, 0.0f, 0.0f);
    draw_cube(30, 60, -210, 0, 100, 100);
    glPopMatrix();
    glPopMatrix();
}


void draw_ground() {

    // drawing fence
    glPushMatrix();
    glTranslatef(0.0, 0.0, thick);
    drawCube(13300+100, 50, 100, "brown");
    glTranslatef(0.0, 10000+50, 0.0);
    drawCube(13300+100, 50, 100, "brown");
    glTranslatef(0.0, -10000, 0.0);
    drawCube(50, 10000, 100, "brown");
    glTranslatef(13300+50, 0.0, 0.0);
    drawCube(50, 10000, 100, "brown");
    glPopMatrix();


    //Lower vertical fences
    glPushMatrix();
    glTranslatef(50.0, 0.0, thick);
    glTranslatef(4075.0, 50.0, 0.0);
    drawCube(50, 2983, 100, "brown");
    glTranslatef(5100.0, 0.0, 0.0);
    drawCube(50, 2983, 100, "brown");
    glPopMatrix();


    // Upper vertical fences
    glPushMatrix();
    glTranslatef(50.0, 0.0, thick);
    glTranslatef(4075.0, 8567.0, 0.0);
    drawCube(50, 1483, 100, "brown");
    glTranslatef(5100.0, 0.0, 0.0);
    drawCube(50, 1483, 100, "brown");
    glPopMatrix();


    //Receiving Zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glPushMatrix();
    drawCube(1575, 9000, 10, "darkGreen");
    glTranslatef(11725.0, 0.0, 0.0);
    drawCube(1575, 9000, 10, "darkGreen");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1000.0, 9000.0, 0.0);
    drawCube(575, 1000, 10, "darkGreen");
    glTranslatef(10725.0, 0.0, 0.0);
    drawCube(575, 1000, 10, "darkGreen");
    glPopMatrix();
    glPopMatrix();


    // Start Zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(0.0, 9000.0, 0.0);
    // Red Start Zone
    drawCube(1000, 1000, 10, "red");
    // Blue Start Zone
    glTranslatef(12300.0, 0.0, 0.0);
    drawCube(1000, 1000, 10, "blue");
    glPopMatrix();


    // Kicking Zone - Red kicking zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(1575.0, 0.0, 0.0);
    draw_cube(2500, 2500, 10, 176, 49, 53);                                             // Kicking Zone 3 - Dark Red ...
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 2500, 10, 190, 76, 62);                                             // Kicking Zone 2 - Medium Red ...
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 5000, 10, 233, 110, 108);                                           // Kicking Zone 1 - Light Red ...
    glPopMatrix();
    

    // Kicking Zone - Blue kicking zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(9225.0, 0.0, 0.0);
    draw_cube(2500, 2500, 10, 0, 107, 172);                                             // Kicking Zone 3 - Dark Blue ...
    glTranslatef(0.0, 2500.0, 0.0);             
    draw_cube(2500, 2500, 10, 76, 173, 223);                                            // Kicking Zone 2 - Medium Blue ...
    glTranslatef(0.0, 2500.0, 0.0);
    draw_cube(2500, 5000, 10, 136, 202, 233);                                           // Kicking Zone 1 - Light Blue ...
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(4075.0, 0.0, 0.0);
    // draw_cube(1000, 1000, 10, 176, 49, 53);                                             // Red ...
    drawCube(1000, 1000, 10, "red");
    glTranslatef(4150.0, 0.0, 0.0);
    // draw_cube(1000, 1000, 10, 0, 107, 172);                                             // Blue ...
    drawCube(1000, 1000, 10, "blue");
    glPopMatrix();


    // Passing zone
    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(4075.0, 1000.0, 0.0);
    drawCube(1000, 9000, 10, "green");
    glTranslatef(4150.0, 0.0, 0.0);
    drawCube(1000, 9000, 10, "green");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 50.0, 0.0);
    glTranslatef(5075.0, 0.0, 0.0);
    drawCube(1075, 10000, 10, "green");
    glTranslatef(2075.0, 0.0, 0.0);
    drawCube(1075, 10000, 10, "green");
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
