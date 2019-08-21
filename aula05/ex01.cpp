/*
  Name:         triangle_anim.cpp
  Copyright:    Version 0.1
  Author:       Rodrigo Luis de Souza da Silva
  Last Update:  29/11/2018 (Animation based on FPS)
  Release:      28/10/2004
  Description:  Animação de triângulo usando função idle.
                Update: visualização e escolhe do FPS desejado
*/

#include <iostream>
#include <GL/glut.h>
#include <glcFPSViewer.h>

using namespace std;

float desiredFPS = 60;
float varX[] = {50.0f, 100.0f, 1.0f, 40.0f, 40.0f, 1.0f};
float varY[] = {1.0f, 50.0f, 100.0f, 1.0f, 70.0f, 70.0f};
float dirX[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float dirY[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float stepX[] = {75.0f, 75.0f, 75.0f, 75.0f, 75.0f, 75.0f};
float stepY[] = {75.0f, 75.0f, 75.0f, 75.0f, 75.0f, 75.0f};

glcFPSViewer *fpsViewer = new glcFPSViewer((char*) "Triangle Animation. ", (char*) " - Press ESC to Exit");

void display(void);
void init (void);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

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
    for (int i = 0; i < 6; ++i)
    {
        if(varX[i] <= -0.001 || varX[i] >= 100.0)
        {
            dirX[i] *= -1.0;
            varX[i] += dirX[i];
            stepX[i] = 50.0 + (rand() % 500) / 10.0;
        }
        if(varY[i] <= -0.001 || varY[i] >= 100.0)
        {
            dirY[i] *= -1.0;
            varY[i] += dirY[i];
            stepY[i] = 50.0 + (rand() % 500) / 10.0;
        }

        varX[i]+= dirX[i]* (stepX[i] / desiredFPS);
        varY[i]+= dirY[i]* (stepY[i] / desiredFPS); // Variation computed considering the FPS
    }

    // Update tLast for next time, using static local variable
    tLast = t;

    glutPostRedisplay();

}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f (varX[0], varY[0]);
    glVertex2f (varX[1], varY[1]);
    glVertex2f (varX[2], varY[2]);
    glEnd();

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f (varX[3], varY[3]);
    glVertex2f (varX[4], varY[4]);
    glVertex2f (varX[5], varY[5]);
    glEnd();

    glutSwapBuffers ();

    // Print FPS
    fpsViewer->drawFPS();
}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            desiredFPS = 60;
            break;
        case '2':
            desiredFPS = 30;
            break;
        case '3':
            desiredFPS = 10;
            break;
        case 27:
            exit(0);
            break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    srand(13);

    cout << "Triangle Animation Example" << endl;
    cout << "--------------------------" << endl;
    cout << "Press 1 to change FPS to ~60" << endl;
    cout << "Press 2 to change FPS to ~30" << endl;
    cout << "Press 3 to change FPS to ~10" << endl;
    cout << "Press ESC to exit" << endl;
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutCreateWindow ("");
    glutKeyboardFunc(keyboard);
    glutIdleFunc( idle);
    init ();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
