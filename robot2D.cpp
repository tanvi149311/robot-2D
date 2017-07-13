//
//  main.cpp
//  Project2
//
//  Created by Tanvi Pawale on 10/4/16.
//  Copyright © 2016 Tanvi Pawale. All rights reserved.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
#include <time.h>       /* time */

using namespace std;
int win_width = 800, win_height = 800;
float canvas_width = 30.0f, canvas_height = 30.0f;

bool keyStates[256];
int buttonState, j;
float colors[3];

float curMouse[2];
float preMouse[2];

int BodyParts[16];
float color[16][3];
int Rotations[16];
float wid[16];
int cnt = 0;
void init(void)
{
    for(int i = 0; i<256; i++) {
        keyStates[i] = false;
    }
    
    for(int i = 0; i<16; i++)
    {
        color[i][0] = 0.0f; // red
        color[i][1] = 0.0f; // green
        color[i][2] = 0.0f; // blue
        Rotations[i] = 0.0f;
        wid[i] =3.0f;
    }

    buttonState = -1; // no mouse button
}

void drawHexa(float color[][3], int partindex, int* Rotations)
{
    colors[0] = color[partindex-1][0];
    colors[1] = color[partindex-1][1];
    colors[2] = color[partindex-1][2];
    glColor3fv(colors);
    glRotatef(Rotations[partindex-1], 0, 0, 1);
    glLineWidth(wid[partindex-1]);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.8, 0);
        glVertex2f(-1.6, 1);
        glVertex2f(-0.8, 2);
        glVertex2f(0.8, 2);
        glVertex2f(1.6, 1);
        glVertex2f(0.8, 0);
    glEnd();
    glLineWidth(1.0f);
}

void drawCircle(float cx, float cy, float r, int num_seg,float color[][3], int partIndex)
{
    colors[0] = color[partIndex-1][0];
    colors[1] = color[partIndex-1][1];
    colors[2] = color[partIndex-1][2];
    glColor3fv(colors);
    glLineWidth(wid[partIndex-1]);
    glBegin(GL_LINE_STRIP);
    for(int ii = 0; ii < num_seg-8; ii++)
    {
        float theta = 2.0f *3.1415926f * float(ii) / float(num_seg);
        float x = r *cosf(theta);
        float y = r *sinf(theta);
        
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
    
    glutPostRedisplay();
}

void drawQuad1(float left, float right, float top, float bottom, float color[][3], int partIndex, int* Rotations)
{
    colors[0] = color[partIndex-1][0];
    colors[1] = color[partIndex-1][1];
    colors[2] = color[partIndex-1][2];
    glColor3fv(colors);
    glRotatef(Rotations[partIndex-1], 0, 0, 1);
    glLineWidth(wid[partIndex-1]);
    glBegin(GL_LINE_STRIP);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);
    
    glEnd();
    glLineWidth(1.0f);
    
    
}

void drawQuad(float left, float right, float top, float bottom, float color[][3], int partIndex, int* Rotations)
{
    colors[0] = color[partIndex-1][0];
    colors[1] = color[partIndex-1][1];
    colors[2] = color[partIndex-1][2];
    glColor3fv(colors);
    glRotatef(Rotations[partIndex-1], 0, 0, 1);
    glLineWidth(wid[partIndex-1]);
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bottom);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glEnd();
    glLineWidth(1.0f);
}

void selection(void)
{
    if(cnt < 16 && cnt >= 0)
    {
        if(BodyParts[cnt] == cnt+1)
        {
            for(int j=0; j<16;j++)
            {
                color[j][0] = 0.0f;
                wid[j] = 3.0f;
            }
            wid[cnt] = 5.0f;
            color[cnt][0] = 1.0f;
        }
        else
        {
            
            //wid = 3.0f;
            color[cnt][0] = 0.0f;
        }
    }
    else
    {
        cnt = 0;
        color[cnt][0] = 1.0f;
    }
}



void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
  
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //draw hip
    BodyParts[0]=1;
    selection();
    drawQuad(-1.4, 1.4, 0, 2, color, 1, Rotations);
    glPushMatrix(); //push hip matrix
    glPushMatrix(); //push hip matrix

    glTranslatef(0, 2, 0);
    
    //chest
    BodyParts[1]=2;
    selection();
    drawQuad(-2, 2, 0, 2, color, 2, Rotations);//draw chest
    glTranslatef(0, 2, 0);
    
    glPushMatrix(); //push neck matrix
    glPushMatrix(); //push neck matrix
    
    //neck
    BodyParts[2]=3;
    selection();
    drawQuad(-0.5, 0.5, 0, 1.5, color, 3, Rotations); //draw neck
    glTranslatef(0, 1.5, 0);
    
    //face
    BodyParts[3]=4;
    selection();
    drawHexa(color, 4, Rotations); // draw face
    glTranslatef(0, 1, 0);
    
    glPopMatrix(); // pop neck matrix
    glTranslatef(-2, -0.5, 0);
    glRotatef(-180, -2, 0, 0);
    
    //right arm
    BodyParts[4]=5;
    selection();
    drawQuad(-2, 0, -0.5, 0.5, color, 5, Rotations); // draw right arm
    glTranslatef(-2, 0, 0);
    
    //right forearm
    BodyParts[5]=6;
    selection();
    drawQuad(-2, 0, -0.5, 0.5, color, 6, Rotations); // draw right forearm
    glTranslatef(-2, 0, 0);
    
    //right hand
    BodyParts[6]=7;
    selection();
    drawQuad1(-1, 0, -1, 1, color, 7, Rotations); // draw right hand
    glTranslatef(-1,0,0);
    glRotatef(80, 0, 0, 1);
    drawCircle(0.0,0.0,1.0,20, color, 7);

    
    glPopMatrix(); //pop neck matrix
    glTranslatef(2, -0.5, 0);
    glRotatef(-180, 2, 0, 0);
    
    //left arm
    BodyParts[7]=8;
    selection();
    drawQuad(2, 0, -0.5, 0.5, color, 8, Rotations); // draw left arm
    glTranslatef(2, 0, 0);
    
    //left forearm
    BodyParts[8]=9;
    selection();
    drawQuad(2, 0, -0.5, 0.5, color, 9, Rotations); // draw left forearm
    glTranslatef(2, 0, 0);
    
    //left hand
    BodyParts[9]=10;
    selection();
    drawQuad1(1, 0, -1, 1, color, 10, Rotations); // draw left hand
    glTranslatef(1,0,0);
    glRotatef(-100, 0, 0, 1);
    drawCircle(0.0,0.0,1.0,20, color, 10);
    
    glPopMatrix(); //pop hip matrix
    glTranslatef(-0.7, 0, 0);
    
    //right thigh
    BodyParts[10]=11;
    selection();
    drawQuad(-0.5, 0.5, 0, -2, color, 11, Rotations); // draw right thigh
    glTranslatef(0, -2, 0);
    
    //right leg
    BodyParts[11]=12;
    selection();
    drawQuad(-0.5, 0.5, 0, -2, color, 12, Rotations); // draw right leg
    glTranslatef(0, -2, 0);
    glRotatef(-180, 0, 0, 0);
    
    //right foot
    BodyParts[12]=13;
    selection();
    drawQuad(-1.5, 0.5, 1, 0, color, 13, Rotations); // draw right foot
    
    glPopMatrix(); // pop hip matrix
    glTranslatef(0.7, 0, 0);

    // left thigh
    BodyParts[13]=14;
    selection();
    drawQuad(-0.5, 0.5, 0, -2, color, 14, Rotations); // draw left thigh
    glTranslatef(0, -2, 0);
    
    //left leg
    BodyParts[14]=15;
    selection();
    drawQuad(-0.5, 0.5, 0, -2, color, 15, Rotations); // draw left leg
    glTranslatef(0, -2, 0);
    glRotatef(-180, 0, 0, 0);
    
    //left foot
    BodyParts[15]=16;
    selection();
    drawQuad(-0.5, 1.5, 1, 0, color, 16, Rotations); // draw left foot

    glutSwapBuffers();
    
}

void reshape(int w, int h)
{
    win_width =  w;
    win_height = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width/2, canvas_width/2, -canvas_height/2, canvas_height/2);
    glViewport(0, 0, (GLsizei) win_width, (GLsizei) win_height);
    
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
            case 97:
                Rotations[cnt] = (Rotations[cnt] + 5) % 360;
                glutPostRedisplay();
                break;
            case 100:
                Rotations[cnt] = (Rotations[cnt] - 5) % 360;
                glutPostRedisplay();
                break;
            case 115: // s key
                    if(cnt >0)
                        cnt--;
                    else
                        cnt = 15;
                    glutPostRedisplay();
                    break;
            case 119: // w key
                    cnt++;
                    glutPostRedisplay();
                    break;
            case 27:
                exit(0);
                break;
            default:
                break;
        }
    
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        buttonState = button;
        curMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        curMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
        preMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        preMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
    }
    else if (state == GLUT_UP)
        button = -1;
}

void motion(int x, int y)
{
    
    curMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
    curMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
    
    preMouse[0] = curMouse[0];
    preMouse[1] = curMouse[1];
    glutPostRedisplay();
    
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("Robot");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
    
}
