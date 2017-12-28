//
//  main.cpp
//  CSCI368_Project4
//
//  Created by Madushani Lekam Wasam Liyanage on 12/3/17.
//  Copyright © 2017 Madushani Lekam Wasam Liyanage. All rights reserved.
//

/*
 This program demonstrates a rocket launch
 Press 'space bar' to pause/resume the rocket
 Press 'r' to reset the rocket launch
 Press left and right arrow keys to move the rocket left and right
 */

#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
using namespace std;

GLfloat pos[] = {-2,4,5,1},
amb[] = {0.3,0.3,0.3,1.0};
GLfloat front_amb_diff[] = {0.7,0.5,0.1,1.0};
GLfloat back_amb_diff[] = {0.4,0.7,0.1,1.0};
GLfloat front_red[] = {1, 0.05, 0};
GLfloat back_red[] = {0.62, 0, 0.06};
GLfloat front_gray[] = {0.4, 0.4, 0.4};
GLfloat back_gray[] = {0.1, 0.1, 0.1};
GLfloat yellow[] = {1.0, 1.0, 0.2};
GLfloat spe[] = {0.25,0.25,0.25,1.0};
GLfloat theta = 0, dt = 0.5, axes[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
int axis = 0;
float xOne=0,yOne=-1, zOne=0;
float angle = 0;
float laserAngle = 0.0;
#define ROCKET_SPEED .0025
#define ROCKET_MOVE .02
int flag = 0;

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;

// Set lighting intensity and color
GLfloat qaAmbientLight[]    = {0.1, 0.1, 0.1, 1.0};
GLfloat qaDiffuseLight[]    = {1, 1, 1, 1.0};
GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};
GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};
// Light source position
GLfloat qaLightPosition[]    = {0, 0, 0, 1};

void cone(void) {
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_red);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne,yOne,-5);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 1, 50, 50);
    glPopMatrix();
}

void cylinder(void) {
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_gray);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_gray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne, yOne, -5.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(quadratic,0.5,0.5,2.0,50,50);
    glPopMatrix();
}

void disk(void) {
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_gray);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_gray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne, yOne-2.0, -5.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(quadratic, 0, 0.5, 50, 50);
    glPopMatrix();
}

void rect1(void) {
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_red);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne-.65,yOne-1.95, -5.5);
    glRotatef(60.0, 0.0, 1.0, 0.0);
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    glScaled(.5, .1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void rect2(void) {
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_red);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne+.65,yOne-1.95, -5.5);
    glRotatef(120.0, 0.0, 1.0, 0.0);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glScaled(.5, .1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void rect3(void) {
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_red);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glTranslatef(xOne,yOne-1.75, -4.5);
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glScaled(.5, .1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void laser(void) {
    glPushMatrix();
    glLoadIdentity();
    if (flag == 1) {
        glColor3f(1.0, 1.0, 1.0);
    }
    else {
        gluPerspective(75, 1.0, 2, 8);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
        glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    }
    glTranslatef(xOne, -3, -5.0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glutSolidCone(0.75, 1+yOne, 50, 50);
    glPopMatrix();
}

void sphere() {
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 1.0, 2, 8);
    glPushMatrix();
    glRotatef(yRotated,0.0,1.0,0.0);
    glTranslatef(-2.0,0.0, -4.0);
    // Set the light position
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   // Make sphere glow (emissive)
    glutSolidSphere(radius/8,50,50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
    glPopMatrix();
}

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glTranslated(0, 0, -5);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glPushMatrix();
    sphere();
    cone();
    cylinder();
    disk();
    rect1();
    rect2();
    rect3();
    laser();
    glFlush();
    glutSwapBuffers();
}

void initLighting() {
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    
}

void keys(int key, int x, int y) {
    if(key == GLUT_KEY_RIGHT) {
        xOne+=ROCKET_MOVE;
    }
    if(key == GLUT_KEY_LEFT) {
        xOne-=ROCKET_MOVE;
    }
    display();
}

void keys(unsigned char key, int x, int y) {
    if(flag == 0 && key == ' ') {
        flag = 1;
    }
    else if (flag == 1 && key == ' ') {
        flag = 0;
    }
    else if (key == 'r') {
        yOne = -1;
        xOne = 0;
        flag = 0;
    }
}

void update(int value) {
    if (flag == 0) {
        yOne+=ROCKET_SPEED;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void idle(void) {
    if (zRotated > 360.0 ) {
        zRotated -= 360.0*floor(zRotated/360.0);   // Don't allow overflow
    }
    if ( yRotated > 360.0 ) {
        yRotated -= 360.0*floor(yRotated/360.0);   // Don't allow overflow
    }
    zRotated += 0.1;
    yRotated +=0.1;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("project4");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initLighting();
    xRotated = yRotated = zRotated = 0.0;
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(keys);
    glutKeyboardFunc(keys);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
