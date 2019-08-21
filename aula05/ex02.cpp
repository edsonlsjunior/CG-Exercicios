/*
  Name:        animationBase.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update:	23/08/2016
  Date:        23/08/2016
  Description: Arquivo base para o exercício da auila de animação
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"
#include <iostream>

class Sphere
{
public:
    float coord[3];
    float speed[3];
    Sphere() {};
    Sphere(float x, float y)
    {
        this->coord[0] = x;
        this->coord[1] = y;
        this->coord[2] = 0;
        setSpeed(250, 0.0);
    };
    void setSpeed(float velX, float velY)
    {
        this->speed[0] = velX;
        this->speed[1] = velY;
    }
};

// Globals
float desiredFPS = 60.0;
int width  = 1000;
int height = 500;
Sphere s(20.0, 3 * height/4.0);

void idle()
{
    float t, desiredFrameTime, frameTime;
    static float tLast = 0.0;

    // Get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    t /= 1000.0;

    // Calculate frame time
    frameTime = t - tLast;
    // Calculate desired frame time
    desiredFrameTime = 1.0 / (float) (desiredFPS);

    // Check if the desired frame time was achieved. If not, skip animation.
    if( frameTime <= desiredFrameTime)
        return;
    // **  UPDATE ANIMATION VARIABLES ** //

    //CONTROLE DO EIXO X
    if (s.coord[0] < 20.0)
    {
        s.speed[0] *= -1.0;
        s.coord[0] = 20.0;
    }
    if (s.coord[0] > width - 20.0)
    {
        s.speed[0] *= -1.0;
        s.coord[0] = width - 20.0;
    }
    //CONTROLE DO EIXO Y
    if (s.coord[1] < 20.0)
    {
        s.speed[1] *= -0.8;
        s.coord[1] = 20.0;
    }

    //aplicando gravidade em Y
    s.speed[1] = s.speed[1] - 20.0;
    //atualizando posicoes das coordenadas
    for (int i = 0; i < 2; ++i)
    {
        s.coord[i] += (s.speed[i] / desiredFPS);
    }

    glutPostRedisplay();
}

void init(void)
{
    glClearColor (0.5, 0.5, 0.5, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    initLight(width, height);
}

void display(void)
{
    float sphereSize = 30.0;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0.0, width, 0.0, height, -sphereSize, sphereSize);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();

    setMaterial();

    glTranslatef(s.coord[0], s.coord[1], 0.0); // Posicionamento inicial da esfera
    glutSolidSphere(20.0, 100, 100);

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y)
{
    if(tolower(key) == 27) exit(0);
    if(tolower(key) == ' ') s.speed[1] = 800;
}

// Motion callback
void motion(int x, int y )
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Animation Base");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc( motion );
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
