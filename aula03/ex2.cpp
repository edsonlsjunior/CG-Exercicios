/*
  Name:        quad_transform.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        16/09/2004
  Last Update: 07/08/2019
  Description: Transformations using of OpenGL commands
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

void display(void);
void init (void);
void desenhaEixos();
void showMenu();
void mouse(int button, int state, int x, int y);

void specialKeysPress(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if (ytrans < 5)
                ytrans += 1.0;
            break;
        case GLUT_KEY_DOWN:
            if (ytrans > 0)
                ytrans -= 1.0;
            break;
        case GLUT_KEY_RIGHT:
            if (xtrans < 5)
                xtrans += 1.0;
            break;
        case GLUT_KEY_LEFT:
            if (xtrans > 0)
                xtrans -= 1.0;
            break;
        default:
            printf("\nPressionou outra tecla especial não mapeada!");
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (300, 300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    printf("Posicione as janelas e clique na janela do OpenGL para habilitar o menu.\n");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        enableMenu = 1;
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Inicializa com matriz identidade

    //desenhaEixos();

    glColor3f (1.0, 1.0, 1.0);

        //glRotatef(angle, 0.0, 0.0, 1.0);
        //glScalef(scale, scale, scale);

        for (int k = 0; k < 3; ++k)
        {
            for (double i = -3.5; i <= 2.5; i += 2.0)
            {
                glPushMatrix();
                glTranslatef(i, 2.5 - 2*k, 0.0);
                glutSolidCube(1);
                glPopMatrix();
            }

            for (double i = -2.5; i <= 2.5; i += 2.0)
            {
                glPushMatrix();
                glTranslatef(i, 1.5 - 2*k, 0.0);
                glutSolidCube(1);
                glPopMatrix();
            }
        }

    glColor3f (1.0, 0.0, 0.0);

    glTranslatef(-2.5 + xtrans, -2.5 + ytrans, 0.0);
    glutSolidSphere(0.5, 20, 20);

    glutSwapBuffers ();
    glutPostRedisplay();
}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glutSpecialFunc( specialKeysPress );
}
