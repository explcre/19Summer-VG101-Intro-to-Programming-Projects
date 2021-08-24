
#include "head.h"
using namespace std;





void renderScene()
{

    if(game->ifauto==1){game->autoMode();}
    if (game->car.velocity.x != 0 || game->car.velocity.z != 0)
        game->computeDir();
    game->computePos();
    game->change_speed();
    game->change_speed_f();
    game->hit_analysis();
    game->park_analysis();




    game->computeUFODir();

    // Clear Color and Depth Buffers
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(
        0.01f + game->camera.position.x + game->car.position.x, 0.01f + game->camera.position.y + game->car.position.y, 0.01f + game->camera.position.z + game->car.position.z,
        //   x,1.0f,z-5,
        // x+0.01f, 15.0f, z+0.01f,
        game->car.position.x, game->car.position.y, game->car.position.z,
        // x,1.0f,z,
        0.0f, 1.0f, 0.0f);

    // Draw ground
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    for (int i = 1; i < game->n + 6; i++)
        game->wall[i].drawWall();
    for (int i = game->n + 6; i < 2 * game->n + 6; i++)
        game->wall[i].drawPark();

    game->car.draw();
    game->flag.draw(game->car.position.x,game->car.position.y+1.5,game->car.position.z,game->car.velocity.x,game->car.velocity.z);
    game->door.drawDoor();
    // int o = 1;
    // while (o <= n /*Us[o].getExist()!=0*/)
    // {
    //     if (pk.showstate(o) == 2)
    //         Us[o].drawRotate(o);
    //     o++;
    // }
    for (int i = 1; i <= game->n / 6; i++)
    {
        game->Us[i].drawRotate(i);
    }
    for (int i = 1; i <= game->n / 6; i++)
    {
        game->RS[i].drawZoomIO();
    }
    for (int i = 1; i <= game->n / 6; i++)
    {
        game->c[i].draw();
    }
    for (int i = 1; i <= game->n / 6; i++)
    {
        game->TS[i].draw(i);
    }

    glutSwapBuffers();
}




