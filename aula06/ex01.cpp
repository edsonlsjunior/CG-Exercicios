/*
  Name:        3D View.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        14/11/2013
  Description: C�digo base para exerc�cios em 3D.
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
int width = 640, height = 480;
float x = 0.5, y = 4.5;

int distOrigem = 2;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_LIGHT0);                   // habilita luz 0
    glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (2.5, -3.0, distOrigem, 2.5, 3.0, 0.0, 0.0, 1.0, 0.0);


    glDisable(GL_LIGHTING);

    glColor3f (1.0f, 1.0f, 1.0f);
    for (int j = 0; j < 5; ++j)
        for (int i = 0; i < 5; ++i)
        {
            glBegin(GL_LINE_LOOP);
                glVertex3f(1.0f + i, 0.0f + j, 0.0);
                glVertex3f(0.0f+ i, 0.0 + j, 0.0);
                glVertex3f(0.0f + i, 1.0f + j, 0.0);
                glVertex3f(1.0f + i, 1.0f + j, 0.0);
            glEnd();
        }

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(x ,y , 0.5);
        glRotatef( rotationY, 0.0, 1.0, 0.0 );
        glRotatef( rotationX, 1.0, 0.0, 0.0 );
        glColor3f (1.0f, 0.0f, 0.0);
        //glutSolidTorus(5.0f, 10.0f, 40, 40);
        glutSolidCube(1.0f);
    glPopMatrix();

    glutSwapBuffers();
}

void idle ()
{
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x1, int y1)
{
    switch (tolower(key))
    {
        case '+' :
            distOrigem--;
            if(distOrigem<20) distOrigem=20;
            break;
        case '-' :
            distOrigem++;
            if(distOrigem>180) distOrigem=180;
            break;
        case 's':
            if(y > 0.5)
                y--;
            break;
        case 'w':
            if(y < 4.5)
                y++;
            break;
        case 'a':
            if(x > 0.5)
                x--;
            break;
        case 'd':
            if(x < 4.0)
                x++;
            break;

        case 27:
            exit(0);
            break;
    }
}

// Motion callback
void motion(int x, int y )
{
    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        last_x = x;
        last_y = y;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
