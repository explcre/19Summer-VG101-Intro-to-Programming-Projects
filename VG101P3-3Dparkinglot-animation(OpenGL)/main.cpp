
#include "head.h"
#include "p3.h"
#include "ElementFigure.h"
#include "Analysis.h"
#include "Control.h"
#include "ComplexFigure.h"


int main(int argc, char **argv)
{
    srand(time(NULL));

    //get the carport number
    cout<<"Please enter the number of carport:";
    cin>>game->n;
    cout<<"There is "<<game->n/2<<" vehicles in the parking lot."<<endl;
    game->getParkdata(game->n);
    // init GLUT and create window
    ParkData park(game->n/2);
    //input the car type that enter the parkinglot
    //output the arrival and departure time
    //output the parking fee of each car





    printf("Do you want to control the car ,or see it automatically perks?(1:auto,2:manual)");

    scanf("%d",&(game->ifauto));

    glutInit(&argc, argv);
    //initialize the window
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Test");
    //initialize the park data and shape.
    game->camera.init();
    game->init_wall();
    game->init_Park();
    game->assignPark();
    game->init_car();
    game->init_Door();
    game->init_flag();
    game->decideWhere2Park();

    //OpenGL control function
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL display
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // enter GLUT event processing cycle


    glutMainLoop();

    return 1;
}