
#include "head.h"


//camera control through mouse button
void mouseButton(int button, int state, int x, int y)
{

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {

        // when the button is released
        if (state == GLUT_UP)
        {
            game->camera.angle1 += game->camera.deltaAngle1;
            game->camera.angle2 += game->camera.deltaAngle2;
            game->mouse.xOrigin = -1;
            game->mouse.yOrigin = -1;
        }
        else
        { 
            game->mouse.xOrigin = x;
            game->mouse.yOrigin = y;
        }
    }

}

//camera control through mouse move
void mouseMove(int x, int y)
{
    // this will only be true when the left button is down
    if (game->mouse.xOrigin >= 0)
    {
        // update car.deltaAngle
        game->camera.deltaAngle1 = (x - game->mouse.xOrigin) * 0.001f;
        // update game->camera's direction
    }
    if (game->mouse.yOrigin >= 0)
    {
        // update car.deltaAngle
        game->camera.deltaAngle2 = (y - game->mouse.yOrigin) * 0.001f;
        // update game->camera's direction
    }
    if (game->mouse.yOrigin >= 0 || game->mouse.yOrigin >= 0)
    {
        game->camera.position.z = cos(game->camera.angle1 + game->camera.deltaAngle1) * cos(game->camera.angle2 + game->camera.deltaAngle2) * game->camera.distance;
        game->camera.position.x = -sin(game->camera.angle1 + game->camera.deltaAngle1) * cos(game->camera.angle2 + game->camera.deltaAngle2) * game->camera.distance;
        game->camera.position.y = sin(game->camera.angle2 + game->camera.deltaAngle2) * game->camera.distance;
    }
}

//main the size of picture
void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the correct perspective.
    gluPerspective(60, ratio, 0.01, 100);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

//speed control through Keyboard
void pressKey(int key, int xx, int yy)
{

    switch (key)
    {
    case GLUT_KEY_LEFT:
        game->car.deltaAngle1 = -0.05f;
        break;
    case GLUT_KEY_RIGHT:
        game->car.deltaAngle1 = 0.05f;
        break;
    case GLUT_KEY_UP:
        game->car.v_acceleration = 0.01f;
        break;
    case GLUT_KEY_DOWN:
        game->car.v_acceleration = -0.01f;
        break;
    }
}
//speed control through Keyboard
void releaseKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        game->car.deltaAngle1 = -0.0f;
        break;
    case GLUT_KEY_RIGHT:
        game->car.deltaAngle1 = 0.0f;
        break;
    case GLUT_KEY_UP:
        game->car.v_acceleration = 0.0f;
        break;
    case GLUT_KEY_DOWN:
        game->car.v_acceleration = 0.0f;
        break;
    }
}
//speed control through Keyboard
void processNormalKeys(unsigned char key, int x, int y)
{

    if (key == 27)
        exit(0);
    if (key == 'y')
    {
        game->camera.init();
        glutPostRedisplay();
    }
}


