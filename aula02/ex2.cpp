/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

#define PI 3.14159265359

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

int partesVet [] = {6, 12, 180};
int indice = 2;
int partes = partesVet[indice];

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quad Test");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("Pressione ESC para fechar.\n");
    glutMainLoop();

    return 0;
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f (-10.0, 0.0, 0.0);
        glVertex3f (390.0, 0.0, 0.0);
    glEnd();

        glBegin(GL_LINES);
        glVertex3f (0.0, -2.0, 0.0);
        glVertex3f (0.0, 2.0, 0.0);
    glEnd();

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);

        std::cout << indice << std::endl;
        partes = partesVet[indice];
        float coordX;
        float rad;
        for (int i = 0; i < partes + 1; ++i)
        {
            coordX = i * 360.0/ partes;
            rad = (coordX * PI) / 180;

            glVertex3f(coordX, sin(rad), 0.0);
        }
    glEnd();

    glutSwapBuffers ();
}


void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case (char)GLUT_KEY_LEFT: case 'x':
            indice = (indice - 1 + 3) % 3;
            break;
        case (char)GLUT_KEY_RIGHT: case 'z':
            indice = (indice+1) % 3;
            break;
    }
    glutPostRedisplay();
}
