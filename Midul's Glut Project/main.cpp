#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>  // For sinf and cosf
#include <cstdlib>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // for music


bool musicPlaying = false;
bool buttonMusicPlaying = false;

// Coordinates for all used points
const GLfloat E_x = 0.0186881f, E_y = -0.4492912f;
const GLfloat F_x = -0.1607379f, F_y = -0.4500557f;
const GLfloat D_x = -0.1616933f, D_y = 0.6555639f;
const GLfloat C_x = 0.0194138f, C_y = 0.5921187f;

const GLfloat H_x = -0.2668681f, H_y = -0.4494837f;
const GLfloat O_x = -0.2661725f, O_y = 0.1617017f;
const GLfloat G_x = -0.262312f, G_y = 0.617227f;

const GLfloat T_x = 0.0210854f, T_y = -0.1143654f;
const GLfloat U_x = 0.2576044f, U_y = -0.0981337f;
const GLfloat V_x = 0.2645608f, V_y = -0.4575499f;

const GLfloat Z_x = 0.5219492f, Z_y = -0.4552311f;
const GLfloat W_x = 0.5335433f, W_y = -0.1352348f;

const GLfloat A1_x = 0.3689075f, A1_y = -0.1839299f;
const GLfloat B1_x = 0.4732541f, B1_y = -0.1978427f;
const GLfloat C1_x = 0.4778917f, C1_y = -0.4413182f;
const GLfloat D1_x = 0.3781827f, D1_y = -0.4413182f;

const GLfloat F1_x = 0.7213672f, F1_y = -0.4853757f;
const GLfloat E1_x = 0.7329613f, E1_y = -0.0587139f;
const GLfloat G1_x = 0.8326703f, G1_y = -0.4946509f;
const GLfloat H1_x = 0.8303515f, H1_y = -0.0842208f;
const GLfloat I1_x = 0.9926684f, I1_y = -0.070308f;
const GLfloat J1_x = 0.9949873f, J1_y = -0.0308881f;
const GLfloat K1_x = 0.9602051f, K1_y = -0.1213219f;
const GLfloat L1_x = 0.9578862f, L1_y = -0.4853757f;
const GLfloat M1_x = 1.0f, M1_y = -0.12f;

// New point N1
const GLfloat N1_x = 0.725f, N1_y = -0.296f;


const GLfloat circle_center_x = -0.20998f;  // O_x
const GLfloat circle_center_y =  0.304f;        // roughly halfway in polygon 2
const GLfloat radius = 0.05f;                 // adjust size as needed

float _move_cloud_1 = 0.00f;
float _move_cloud_2 = 0.00f;

float angle = 0.0f; // for tree
float airplaneX = -6.0f;  // Start from outside the left boundary

// Global variables to control car position and movement
float carPosX = -1.9f;
bool moveCar = false;
float moveSpeed = 0.01f;  // Speed of the car movement
bool movingRight = true;  // Direction of movement


void DrawTextBox() {
    // Box parameters
    float boxX = -0.9f, boxY = 0.8f, boxWidth = 0.45f, boxHeight = 0.15f;

    // Draw the rectangle box (black border with white fill)
    glColor3f(1.0f, 1.0f, 1.0f); // White fill
    glBegin(GL_QUADS);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY - boxHeight);
    glVertex2f(boxX, boxY - boxHeight);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black border
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(boxX, boxY);
    glVertex2f(boxX + boxWidth, boxY);
    glVertex2f(boxX + boxWidth, boxY - boxHeight);
    glVertex2f(boxX, boxY - boxHeight);
    glEnd();

    // Draw text inside box
    const char* message = "Press C for car";
    glColor3f(0.0f, 0.0f, 0.0f); // Black text

    // Position text slightly inside the box
    float textX = boxX + 0.05f;
    float textY = boxY - 0.07f;

    glRasterPos2f(textX, textY);

    // Render each character using GLUT bitmap font
    for (const char* c = message; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}


void drawAirplane() {
    glPushMatrix();

    // Scale down to fit in frame
     // Make airplane 0.5× smaller than before
    glScalef(0.2f, 0.2f, 1.0f);
     glTranslatef(airplaneX, 4.3f, 0.0f);  // Animate along x-axis and fix y

    glBegin(GL_QUADS);  // MAIN
    glColor3f(0.9f, 0.7f, 0.8f);
    glVertex3f(-0.90f, -0.50f, 0.0f);
    glVertex3f(0.40f, -0.50f, 0.0f);
    glVertex3f(0.20f, -0.20f, 0.0f);
    glVertex3f(-0.90f, -0.20f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // MAIN2
    glColor3f(0.7f, 0.7f, 0.9f);
    glVertex3f(-0.90f, -0.35f, 0.0f);
    glVertex3f(0.30f, -0.35f, 0.0f);
    glVertex3f(0.20f, -0.20f, 0.0f);
    glVertex3f(-0.90f, -0.20f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // wing1
    glColor3f(0.99f, 0.8f, 0.99f);
    glVertex3f(-0.15f, -0.20f, 0.0f);
    glVertex3f(0.00f, -0.20f, 0.0f);
    glVertex3f(-0.25f, 0.30f, 0.0f);
    glVertex3f(-0.25f, 0.10f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // wing2
    glColor3f(0.9f, 0.8f, 0.9f);
    glVertex3f(-0.35f, -0.90f, 0.0f);
    glVertex3f(-0.30f, -0.90f, 0.0f);
    glVertex3f(0.00f, -0.43f, 0.0f);
    glVertex3f(-0.20f, -0.43f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // bottom band
    glColor3f(0.9f, 0.8f, 0.8f);
    glVertex3f(-0.90f, -0.50f, 0.0f);
    glVertex3f(0.40f, -0.50f, 0.0f);
    glVertex3f(0.35f, -0.43f, 0.0f);
    glVertex3f(-0.90f, -0.43f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // tail
    glColor3f(0.7f, 0.9f, 0.9f);
    glVertex3f(-0.88f, -0.20f, 0.0f);
    glVertex3f(-0.65f, -0.20f, 0.0f);
    glVertex3f(-0.88f, 0.30f, 0.0f);
    glEnd();

    glPopMatrix();
}
void updatePlane(int value) {
    airplaneX += 0.01f;  // Speed of airplane

    if (airplaneX > 6.0f)  // Reset if it goes outside right boundary
        airplaneX = -6.0f;

    glutPostRedisplay();              // Request redisplay
    glutTimerFunc(10, updatePlane, 0); // Call again after ~60 FPS
}




// Draw tree with only the crown swaying
void drawTree(float x, float y, float scale, int layers) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);      // Position the tree
    glScalef(scale, scale, 1.0f);  // Scale the tree

    // Draw trunk (fixed, no rotation)
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, -1.0f);
    glVertex2f(0.05f, -1.0f);
    glVertex2f(0.035f, -0.5f);
    glVertex2f(-0.035f, -0.5f);
    glEnd();

    // Swaying crown (rotated above the trunk)
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);           // Move pivot to top of trunk
    glRotatef(sinf(angle) * 5, 0.0f, 0.0f, 1.0f); // Sway left & right
    glTranslatef(0.0f, 0.5f, 0.0f);            // Move back

    glColor3f(0.0f, 0.5f, 0.0f);
    float baseY = -0.5f;
    float topY = baseY + 0.2f;
    float width = 0.45f;

    for (int i = 0; i < layers; ++i) {
        glBegin(GL_TRIANGLES);
        glVertex2f(-width, baseY + i * 0.1f);
        glVertex2f(width, baseY + i * 0.1f);
        glVertex2f(0.0f, topY + i * 0.1f);
        glEnd();
        width -= 0.05f;
    }

    glPopMatrix(); // End swaying crown
    glPopMatrix(); // End whole tree
}
// Timer update
// Timer function (renamed to updateTree)
void updateTree(int value) {
    angle += 0.04f;
    if (angle > 2 * M_PI) angle = 0;
    glutPostRedisplay();
    glutTimerFunc(30, updateTree, 0);
}

void drawStar(float x, float y, float size) {
    glColor3f(1.0f, 1.0f, 1.0f); // white color for stars
    glBegin(GL_LINES);
        glVertex2f(x - size, y);
        glVertex2f(x + size, y);
        glVertex2f(x, y - size);
        glVertex2f(x, y + size);
    glEnd();
}
void drawMultipleStars() {
 float starPositions[][2] = {
    {-0.95f, 0.90f}, {-0.80f, 0.85f}, {-0.60f, 0.95f}, {-0.40f, 0.80f}, {-0.20f, 0.88f},
    { 0.00f, 0.93f}, { 0.20f, 0.87f}, { 0.40f, 0.92f}, { 0.60f, 0.85f}, { 0.80f, 0.89f},
    { 0.95f, 0.94f}, { 0.70f, 0.78f}, { 0.30f, 0.82f}, {-0.10f, 0.79f}, {-0.50f, 0.83f},
    {-0.70f, 0.91f}, {-0.92f, 0.96f}, {-0.74f, 0.88f}, {-0.58f, 0.91f}, {-0.33f, 0.85f},
    {-0.12f, 0.90f}, { 0.11f, 0.94f}, { 0.27f, 0.88f}, { 0.47f, 0.93f}, { 0.63f, 0.90f},
    { 0.78f, 0.95f}, { 0.91f, 0.86f}, { 0.67f, 0.84f}, { 0.45f, 0.80f}, { 0.15f, 0.79f},

    // Middle layer stars
    {-0.85f, 0.50f}, {-0.60f, 0.45f}, {-0.35f, 0.52f}, {-0.10f, 0.48f}, { 0.20f, 0.51f},
    { 0.40f, 0.43f}, { 0.65f, 0.49f}, { 0.85f, 0.54f}, { 0.98f, 0.42f}, {-0.98f, 0.46f},

    // Lower layer stars
    {-0.80f, 0.20f}, {-0.55f, 0.15f},  { 0.00f, 0.12f},
    { 0.55f, 0.22f}, { 0.75f, 0.19f}, { 0.95f, 0.15f}, {-0.95f, 0.10f}, { 0.88f, 0.08f}
};


    for (int i = 0; i < sizeof(starPositions) / sizeof(starPositions[0]); i++) {
        drawStar(starPositions[i][0], starPositions[i][1], 0.008f);
    }
}



void update_cloud_1(int value) {
    _move_cloud_1 += 0.0025f;
    if(_move_cloud_1-1.3 > 1.0)
    {
        _move_cloud_1 = -1.0;
    }
	glutPostRedisplay(); //Notify GLUT that the display has changed

	glutTimerFunc(20, update_cloud_1, 0); //Notify GLUT to call update again in 20 milliseconds
}
void update_cloud_2(int value){
    _move_cloud_2 -= 0.0025f;
    if(_move_cloud_2+1.3 < -1.0)
    {
        _move_cloud_2 = 1.0;
    }
	glutPostRedisplay(); //Notify GLUT that the display has changed

	glutTimerFunc(20, update_cloud_2, 0);
}
void cloud_left(){
    //Cloud on the left
    glLoadIdentity(); //Reset the drawing perspective
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.78,0.82,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.74,0.87,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.70,0.91,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.65,0.88,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.07;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.61,0.80,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.68,0.77,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_1, 0.0f, 0.0f);
        glTranslatef(-0.75,0.78,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();
}
void cloud_right(){
    //Cloud on the right
    glLoadIdentity(); //Reset the drawing perspective
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.78,0.70,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.74,0.75,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.70,0.79,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.65,0.76,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.07;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.61,0.76,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.68,0.65,0);
        glScalef(0.6,1,1);
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.63,0.66,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.075;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();

    glPushMatrix();
    glTranslatef(_move_cloud_2, 0.0f, 0.0f);
        glTranslatef(0.75,0.66,0);
        glScalef(0.6,1,1);
       glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.06;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
        glEnd();
        glPopMatrix();
}



void drawCircle(GLfloat cx, GLfloat cy, GLfloat rx, GLfloat ry, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
void drawPersonWithPolygons(float x, float y, float scale) {
    // Head (circle)
    glColor3f(1.0f, 0.8f, 0.6f); // skin tone
    drawCircle(x, y + 0.065f * scale, 0.02f * scale, 0.025f * scale, 30);

    // Neck connector (small rectangle)
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.005f * scale, y + 0.045f * scale);
        glVertex2f(x + 0.005f * scale, y + 0.045f * scale);
        glVertex2f(x + 0.005f * scale, y + 0.04f * scale);
        glVertex2f(x - 0.005f * scale, y + 0.04f * scale);
    glEnd();

    // Body (rectangle)
    glColor3f(0.2f, 0.2f, 0.8f); // shirt
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.015f * scale, y + 0.04f * scale);
        glVertex2f(x + 0.015f * scale, y + 0.04f * scale);
        glVertex2f(x + 0.015f * scale, y - 0.015f * scale);
        glVertex2f(x - 0.015f * scale, y - 0.015f * scale);
    glEnd();

    // Legs (two rectangles)
    glColor3f(0.0f, 0.0f, 0.0f); // pants
    // Left leg
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.015f * scale, y - 0.015f * scale);
        glVertex2f(x - 0.002f * scale, y - 0.015f * scale);
        glVertex2f(x - 0.002f * scale, y - 0.055f * scale);
        glVertex2f(x - 0.015f * scale, y - 0.055f * scale);
    glEnd();

    // Right leg
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.015f * scale, y - 0.015f * scale);
        glVertex2f(x + 0.002f * scale, y - 0.015f * scale);
        glVertex2f(x + 0.002f * scale, y - 0.055f * scale);
        glVertex2f(x + 0.015f * scale, y - 0.055f * scale);
    glEnd();

    // Left arm
    glColor3f(0.2f, 0.2f, 0.8f); // same shirt color
    glBegin(GL_POLYGON);
        glVertex2f(x - 0.015f * scale, y + 0.04f * scale);
        glVertex2f(x - 0.03f * scale, y + 0.01f * scale);
        glVertex2f(x - 0.025f * scale, y + 0.005f * scale);
        glVertex2f(x - 0.01f * scale, y + 0.03f * scale);
    glEnd();

    // Right arm
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.015f * scale, y + 0.04f * scale);
        glVertex2f(x + 0.03f * scale, y + 0.01f * scale);
        glVertex2f(x + 0.025f * scale, y + 0.005f * scale);
        glVertex2f(x + 0.01f * scale, y + 0.03f * scale);
    glEnd();
}






// railing for protecting the polygons
void drawRailing(
    GLfloat startX,
    GLfloat endX,
    GLfloat baseY,
    GLfloat railingHeight,
    GLfloat thickness,
    GLfloat postWidth,
    GLfloat postSpacing
) {
    // Color (steel gray)
    glColor3f(0.3f, 0.3f, 0.3f);

    // Horizontal base bar
    glBegin(GL_QUADS);
        glVertex2f(startX, baseY);
        glVertex2f(endX, baseY);
        glVertex2f(endX, baseY + thickness);
        glVertex2f(startX, baseY + thickness);
    glEnd();

    // Vertical posts
    GLfloat postX = startX;
    while (postX <= endX) {
        glBegin(GL_QUADS);
            glVertex2f(postX, baseY);
            glVertex2f(postX + postWidth, baseY);
            glVertex2f(postX + postWidth, baseY + railingHeight);
            glVertex2f(postX, baseY + railingHeight);
        glEnd();
        postX += postSpacing;
    }

    // Diagonal cross bars (optional)
    postX = startX;
    while (postX + postSpacing <= endX) {
        // Bottom-left to top-right
        glBegin(GL_LINES);
            glVertex2f(postX, baseY);
            glVertex2f(postX + postSpacing, baseY + railingHeight);
        glEnd();

        // Top-left to bottom-right
        glBegin(GL_LINES);
            glVertex2f(postX, baseY + railingHeight);
            glVertex2f(postX + postSpacing, baseY);
        glEnd();

        postX += postSpacing;
    }
}
// Function to draw wheels
void DrawWheels(float cx, float cy, float r, int segments = 100) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}
// Function to draw the car
void DrawCar() {
    // Car body
    glColor3f(0.0f, 0.0f, 1.0f); // Blue body
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(0.6f, -0.2f);
    glVertex2f(0.6f, 0.1f);
    glVertex2f(-0.6f, 0.1f);
    glEnd();

    // Car top
    glColor3f(0.0f, 0.0f, 0.8f); // Darker blue top
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(-0.25f, 0.3f);
    glEnd();

    // Left glass window
    glColor3f(0.7f, 0.9f, 1.0f); // Light blue
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, 0.1f);
    glVertex2f(-0.02f, 0.1f);
    glVertex2f(-0.02f, 0.25f);
    glVertex2f(-0.2f, 0.25f);
    glEnd();

    // Right glass window
    glBegin(GL_POLYGON);
    glVertex2f(0.02f, 0.1f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(0.2f, 0.25f);
    glVertex2f(0.02f, 0.25f);
    glEnd();

    // Door line
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.0f, 0.1f);
    glEnd();

    // Wheels - outer black
    glColor3f(0.0f, 0.0f, 0.0f);
    DrawWheels(-0.4f, -0.25f, 0.1f); // Left
    DrawWheels(0.4f, -0.25f, 0.1f);  // Right

    // Wheels - inner gray
    glColor3f(0.6f, 0.6f, 0.6f);
    DrawWheels(-0.4f, -0.25f, 0.05f);
    DrawWheels(0.4f, -0.25f, 0.05f);
}
void CarTimer(int value) {
    if (moveCar) {
        if (carPosX < 1.6f) {
            carPosX += moveSpeed;
        } else {
            carPosX = -2.0f; // Reset position to start when it passes right boundary
        }
        glutPostRedisplay();
    }
    glutTimerFunc(16, CarTimer, 0);
}


// Keyboard handler: toggle movement on 'C' key
/*
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        moveCar = !moveCar;
    }
}*/
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        moveCar = !moveCar;

        if (!musicPlaying) {
            // Open and play MP3
          mciSendString("open \"C:\\Users\\User\\Desktop\\Bangladesh Flag\\car_music.mp3\" type mpegvideo alias mymusic", NULL, 0, NULL);
           //                  "C:\Users\User\Desktop\Bangladesh Flag\car_music.mp3"
            mciSendString("play mymusic repeat", NULL, 0, NULL); // repeat = loop
            musicPlaying = true;
        } else {
            // Stop and close MP3
            mciSendString("stop mymusic", NULL, 0, NULL);
            mciSendString("close mymusic", NULL, 0, NULL);
            musicPlaying = false;
        }
    }
}

void Blocks()
{
    // Light Brown Ground between road and building
glColor3f(0.85f, 0.6f, 0.4f); // Light brown color
glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.4f);  // Top-left
    glVertex2f(1.0f, -0.4f);   // Top-right
    glVertex2f(1.0f, -0.6f);    // Bottom-right (road top edge)
    glVertex2f(-1.0f, -0.6f);   // Bottom-left (road top edge)
glEnd();


    // Polygon 1: Green
    glColor3f(0.396f, 0.263f, 0.129f);
    glBegin(GL_POLYGON);
        glVertex2f(E_x, E_y);
        glVertex2f(F_x, F_y);
        glVertex2f(D_x, D_y);
        glVertex2f(C_x, C_y);
    glEnd();

    // Polygon 2: Red
  glColor3f(0.710f, 0.396f, 0.114f);
    glBegin(GL_POLYGON);
        glVertex2f(F_x, F_y);
        glVertex2f(H_x, H_y);
        glVertex2f(O_x, O_y);
        glVertex2f(G_x, G_y);
        glVertex2f(D_x, D_y);
    glEnd();

// Black Polygon on Red Tower (like a window or platform)
glColor3f(0.0f, 0.0f, 0.0f); // Black color
glBegin(GL_POLYGON);
    glVertex3f(0.75f, -0.15f, 0.0f);  // Bottom Left
    glVertex3f(0.81f, -0.15f, 0.0f);  // Bottom Right
    glVertex3f(0.81f, -0.08f, 0.0f);  // Top Right
    glVertex3f(0.75f, -0.08f, 0.0f);  // Top Left
glEnd();


    // Polygon 3: under tree
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(E_x, E_y);
        glVertex2f(T_x, T_y);
        glVertex2f(U_x, U_y);
        glVertex2f(V_x, V_y);
    glEnd();

    // Polygon 4: Cyan
    glColor3f(0.7f, 0.3f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(U_x, U_y);
        glVertex2f(V_x, V_y);
        glVertex2f(Z_x, Z_y);
        glVertex2f(W_x, W_y);
    glEnd();

    // Polygon 5: Magenta
    glColor3f(1.0f, 0.8f, 0.4f);
    glBegin(GL_POLYGON);
        glVertex2f(A1_x, A1_y);
        glVertex2f(B1_x, B1_y);
        glVertex2f(C1_x, C1_y);
        glVertex2f(D1_x, D1_y);
    glEnd();

    // Polygon 6: Brown
    glColor3f(0.6f, 0.3f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(H1_x, H1_y);
        glVertex2f(G1_x, G1_y);
        glVertex2f(F1_x, F1_y);
        glVertex2f(E1_x, E1_y);
        glVertex2f(J1_x, J1_y);
        glVertex2f(I1_x, I1_y);
        glVertex2f(H1_x, H1_y);
    glEnd();

    // Polygon 7: Dark Brown
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(G1_x, G1_y);
        glVertex2f(H1_x, H1_y);
        glVertex2f(K1_x, K1_y);
        glVertex2f(L1_x, L1_y);
    glEnd();

    // Polygon 8: Dark Brown
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(K1_x, K1_y);
        glVertex2f(H1_x, H1_y);
        glVertex2f(I1_x, I1_y);
        glVertex2f(M1_x, M1_y);
    glEnd();

    // Polygon 9: Dark Brown (New - F1 → Z → W → N1)
    glColor3f(0.35f, 0.15f, 0.0f); // Distinct dark brown
    glBegin(GL_POLYGON);
        glVertex2f(F1_x, F1_y);
        glVertex2f(Z_x, Z_y);
        glVertex2f(W_x, W_y);
        glVertex2f(N1_x, N1_y);
    glEnd();

    // Polygon 10: Very Dark Brown (J → L → M)
// Polygon: Very Dark Brown (J → L → M)
glColor3f(0.2f, 0.1f, 0.0f); // Very dark brown
glBegin(GL_POLYGON);
    glVertex2f(-0.4564737246107f, 0.0679740811046f); // J
    glVertex2f(-0.5310094308302f, 0.0837739823952f); // L
    glVertex2f(-0.5300225736584f, -0.1977849234605f); // M
glEnd();

// Polygon: Light Brown (H → O → N → J → M → O1) right curve one
glColor3f(0.7f, 0.4f, 0.2f); // Light brown
glBegin(GL_POLYGON);
    glVertex2f(-0.2668680587518f, -0.4494837111891f); // H
    glVertex2f(-0.2661724680421f,  0.1617016757903f); // O
    glVertex2f(-0.4194677411011f,  0.1928894052941f); // N
    glVertex2f(-0.4564737246107f,  0.0679740811046f); // J
    glVertex2f(-0.5300225736584f, -0.1977849234605f); // M
    glVertex2f(-0.5764f,          -0.4438f);          // O1
glEnd();


// Polygon: Custom shape using K → P → Q → R → S → P1 left one curve
glColor3f(0.5f, 0.25f, 0.1f); // Medium brown
glBegin(GL_POLYGON);
    glVertex2f(-0.8218032601375f, -0.4439130575857f); // K
    glVertex2f(-0.7224803124402f, -0.1950666738383f); // P
    glVertex2f(-0.6772920301856f, -0.0135510191358f); // Q
    glVertex2f(-0.8955076026927f,  0.0135378105547f); // R
    glVertex2f(-0.9991928325331f, -0.2627695327730f); // S
    glVertex2f(-0.9999f,          -0.426f);           // P1
glEnd();

// Polygon: Complex shape using K → P → Q → I → L → J → M → O1 middle one
glColor3f(0.35f, 0.2f, 0.1f); // Dark reddish brown
glBegin(GL_POLYGON);
    glVertex2f(-0.8218032601375f, -0.4439130575857f); // K
    glVertex2f(-0.7224803124402f, -0.1950666738383f); // P
    glVertex2f(-0.6772920301856f, -0.0135510191358f); // Q
    glVertex2f(-0.6427393521498f,  0.1018405588390f); // I
    glVertex2f(-0.5310094308302f,  0.0837739823952f); // L
    glVertex2f(-0.4564737246107f,  0.0679740811046f); // J
    glVertex2f(-0.5300225736584f, -0.1977849234605f); // M
    glVertex2f(-0.5764f,          -0.4438f);          // O1
glEnd();



    // Road: Dark gray rectangle at the bottom
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);   // Bottom-left corner
        glVertex2f(1.0f, -1.0f);    // Bottom-right corner
        glVertex2f(1.0f, -0.55f);   // Top-right corner (adjust height as needed)
        glVertex2f(-1.0f, -0.55f);  // Top-left corner
    glEnd();
    // Road center dashed line: Yellow
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    float x_start = -0.95f;
    float dash_width = 0.1f;
    float gap = 0.1f;
    float y_middle = -0.78f;

    while (x_start + dash_width <= 1.0f) {
        glBegin(GL_POLYGON);
            glVertex2f(x_start, y_middle + 0.01f);
            glVertex2f(x_start + dash_width, y_middle + 0.01f);
            glVertex2f(x_start + dash_width, y_middle - 0.01f);
            glVertex2f(x_start, y_middle - 0.01f);
        glEnd();
        x_start += dash_width + gap;
    }

 // Yellow vertical ellipse inside the second polygon
glColor3f(1.0f, 1.0f, 0.0f); // Yellow
glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.20998f, 0.304f); // Center of the ellipse
    int num_segments = 100;
    float radius_x = 0.035f; // Horizontal radius (narrower)
    float radius_y = 0.06f;  // Vertical radius (taller)
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * 3.1415926f * i / num_segments;
        float x = radius_x * cosf(angle);
        float y = radius_y * sinf(angle);
        glVertex2f(-0.20998f + x, 0.304f + y);
    }
glEnd();

}

void drawMouseButton() {
    glPushMatrix();

    // Smaller button: 0.2 wide, 0.1 tall
    glColor3f(0.2f, 0.6f, 0.8f); // Blue button
    glBegin(GL_QUADS);
    glVertex2f(0.75f, 0.9f);  // Bottom-left
    glVertex2f(1.0f, 0.9f);  // Bottom-right
    glVertex2f(1.0f, 1.0f);  // Top-right
    glVertex2f(0.75f, 1.0f);  // Top-left
    glEnd();

    // Draw text inside the small button
    glColor3f(1, 1, 1); // White text
    glRasterPos2f(0.78f, 0.94f); // Adjust text position for smaller space

    const char* text = "Play Music";
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]); // Smaller font
    }

    glPopMatrix();
}
// Mouse click handler
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float glX = 2.0f * x / width - 1.0f;
        float glY = 1.0f - 2.0f * y / height;

        // Button area: x=[0.8,1.0], y=[0.9,1.0]
        if (glX >= 0.8f && glX <= 1.0f && glY >= 0.9f && glY <= 1.0f) {
            if (!buttonMusicPlaying) {
                mciSendString("open \"C:\\Users\\User\\Desktop\\Bangladesh Flag\\play_music.mp3\" type mpegvideo alias buttonmusic", NULL, 0, NULL);
                mciSendString("play buttonmusic repeat", NULL, 0, NULL);
                buttonMusicPlaying = true;
            } else {
                mciSendString("stop buttonmusic", NULL, 0, NULL);
                mciSendString("close buttonmusic", NULL, 0, NULL);
                buttonMusicPlaying = false;
            }
        }
    }
}
void UniversityName() {
    glColor3f(1.0f, 1.0f, 1.0f); // White text

    const char* text = "COMILLA UNIVERSITY";

    float textX = -0.1f;    // Horizontal position inside polygon
    float startY = 0.5f;   // Starting near top inside polygon (adjust this!)

    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        glRasterPos2f(textX, startY - i * 0.05f); // Subtract to go downward
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);



    drawMultipleStars();

  cloud_left();
    cloud_right();

    // Draw 3 trees behind yellow and blue polygons
///drawTree(0.15f, -0.12f);   // Tree 1
///drawTree(0.33f, -0.12f); // Tree 2
///drawTree(0.51f, -0.14f);     // Tree 3
drawTree(0.15f, 0.120f, 0.40f, 8);  // Centered, normal size, 8 layers
drawTree(0.38f, 0.08f, 0.30f, 10);
drawTree(0.58f, 0.05f, 0.40f, 8);
// Draw 3 clouds in the night sky
///drawCloud(-0.6f, 0.75f); // Cloud 1
///drawCloud(0.0f, 0.85f);  // Cloud 2
///drawCloud(0.5f, 0.7f);   // Cloud 3




Blocks();
UniversityName();


// Draw 5 people inside railing
// People standing inside railing
drawPersonWithPolygons(-0.38f, -0.41f, 1.1f);
drawPersonWithPolygons(-0.43f, -0.41f, 1.0f);
drawPersonWithPolygons(-0.42f, -0.41f, 0.99f);
drawPersonWithPolygons(-0.48f, -0.42f, 1.06f);
drawPersonWithPolygons( -0.56f, -0.415f, 0.97f);




// draw railing
drawRailing(-1.0f, 1.0f, -0.5f, 0.1f, 0.02f, 0.01f, 0.08f);




drawAirplane();

glPushMatrix();        // Save current transformation matrix
    glTranslatef(carPosX + 0.2f, -0.65f, 0.0f); // Translate (including your 0.2 offset and lower y)
    glScalef(0.8f, 0.8f, 1.0f);        // Scale to half size (x and y)
    DrawCar();             // Draw the car at new position
    glPopMatrix();

glPushMatrix();
    glTranslatef(-0.2f, -0.1f, 0.0f); // Translate (including your 0.2 offset and lower y)
    glScalef(0.8f, 0.8f, 1.0f);
    DrawTextBox();
glPopMatrix();


drawMouseButton();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Multiple Colored Polygons");

glClearColor(0.05f, 0.05f, 0.2f, 1.0f); // Dark night sky
    glutDisplayFunc(display);
       glutTimerFunc(20, update_cloud_1, 0);
    glutTimerFunc(20, update_cloud_2, 0);
     glutTimerFunc(0, updateTree, 0);     // Call renamed timer
     glutTimerFunc(0, updatePlane, 0); // Start the animation
     glutKeyboardFunc(keyboard);
      glutMouseFunc(mouse);
    glutTimerFunc(0, CarTimer, 0);
    glutMainLoop();
    return 0;
}
/// change 779 number line for the different path for car sound
