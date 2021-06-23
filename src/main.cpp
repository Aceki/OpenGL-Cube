#include <iostream>

#include <glm/glm.hpp>
#include <gl/freeglut.h>
#include <gl/GLU.h>

constexpr int windowWidth = 480;
constexpr int windowHeight = 480;

void drawCube()
{
    static GLfloat vertices[] = {
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
         0.5, -0.5,  0.5,
        -0.5, -0.5,  0.5,

        -0.5,  0.5, -0.5,
         0.5,  0.5, -0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
    };

    static GLuint indices[] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        0, 3, 7, 4,
        1, 2, 6, 5,
        0, 1, 5, 4,
        3, 2, 6, 7
    };

    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);

    glPopClientAttrib();
}

void polarView(GLdouble distance, GLdouble twist, GLdouble elevation, GLdouble azimuth)
{
    glTranslated(0.0, 0.0, -distance);
    glRotated(-twist, 0.0, 0.0, 1.0);
    glRotated(-elevation, 1.0, 0.0, 0.0);
    glRotated(azimuth, 0.0, 0.0, 1.0);
}

void pilotView(GLdouble planex, GLdouble planey, GLdouble planez, GLdouble roll, GLdouble pitch, GLdouble heading)
{
    glRotated(roll,0.0,0.0,1.0);
    glRotated(pitch,0.0,1.0,0.0);
    glRotated(heading,1.0,0.0,0.0);
    glTranslated(-planex,-planey,-planez);
}

void reshape(int, int)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90, double(windowWidth) / windowHeight, 1, 20);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutReshapeWindow(windowWidth, windowHeight);
}

void draw()
{
    static float angle = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5);

    glLoadIdentity();

    polarView(2, 0, -angle, angle);

    drawCube();

    glFlush();

    if ((angle += 0.05) >= 360)
        angle = 0;
}

void display()
{
    draw();

    glutSwapBuffers();

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);

    glutCreateWindow("Cube");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS;
}
