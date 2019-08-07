/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Last Update: 03/09/2014
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <stdio.h>
#include <GL/glut.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

char controle = 'z';

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

    // Desenhar um polígono branco (retângulo)
    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f (0.0, -1.0, 0.0);
        glVertex3f (0.0, 1.0, 0.0);
    glEnd();

        glBegin(GL_LINES);
        glVertex3f (-1.0, 0.0, 0.0);
        glVertex3f (1.0, 0.0, 0.0);
    glEnd();

    switch (controle)
    {
        case 'z':
            glBegin(GL_TRIANGLES);
             glColor3f (1.0, 0.0, 0.0);
                glVertex3f (0.0, 0.0, 0.0);
                glVertex3f (1.0, 0.0, 0.0);
                glVertex3f (0.5, 1.0, 0.0);
            glEnd();
            break;
        case 'x':
            glBegin(GL_LINE_LOOP);
             glColor3f (1.0, 0.0, 0.0);
                glVertex3f (0.0, 0.0, 0.0);
                glVertex3f (1.0, 0.0, 0.0);
                glVertex3f (0.5, 1.0, 0.0);
            glEnd();
            break;

        case 'c':
        {
            glBegin(GL_LINE_LOOP);
             glColor3f (1.0, 0.0, 0.0);
                glVertex3f (0.0, 0.0, 0.0);
                glVertex3f (1.0, 0.0, 0.0);
                glVertex3f (0.5, 1.0, 0.0);
            glEnd();
            glBegin(GL_TRIANGLES);
             glColor3f (1.0, 0.0, 0.0);
                glVertex3f (0.0, 0.0, 0.0);
                glVertex3f (-1.0, 0.0, 0.0);
                glVertex3f (-0.5, -1.0, 0.0);
            glEnd();
        } break;

        case 'v':
        {
            glBegin(GL_LINE_STRIP);
                glColor3f (0.0, 0.0, 0.0);
                glVertex3f (0.5, 0.5, 0.0);
                glVertex3f (1.0, 0.0, 0.0);
                glVertex3f (0.5, -0.5, 0.0);
                glVertex3f (-0.5, -0.5, 0.0);
                glVertex3f (-1.0, 0.0, 0.0);
                glVertex3f (-0.5, 0.5, 0.0);
            glEnd();
        } break;
    }

    glutSwapBuffers ();
}


void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (1.0, 1.0, 1.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
    controle = key;
    switch (key)
    {
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
