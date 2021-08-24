#ifndef ELEMENTFIGURE_H
#define ELEMENTFIGURE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32

#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include <math.h>
#include <iostream>
#include <cstdlib>
//#include <random>
#include <ctime>

using namespace std;
#define MM 50
#define NN 50       // how many slices will be drawn
#define MAXCARN 100 //maximum af numbers of vehicle
#define TYPEN 4
//#define M_PI 3.1415926
#define PI 3.1415926
// #include "head.h"

//define a vector
class vector
{
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    vector(float x, float y, float z) : x(x), y(y), z(z) {}
    vector() {}
    void set(float x1, float y1, float z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }
};


//draw a cone
void drawCone(float radius, float axislength,float x,float y,float z) {
    float r, h;

    for (h = 0; h < axislength; h += 0.01) {
        r = h * radius / axislength;

        for (int j = 0; j < 360; j++) {
            glVertex3f(r * cos(2 * M_PI * j / 360)+x, h+y, r * sin(2 * M_PI * j / 360)+z);
        }
    }
}


//draw a cuboid
void drawCuboid(float width, float height, float length)
{
    int w[26] = {0, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1};
    int h[26] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1};
    int l[26] = {0, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1};
    float f1[5] = {0, 0.0f, 1.0f, 1.0f, 0.0f};
    float f2[5] = {0, 0.0f, 1.0f, 1.0f, 1.0f};
    int facet = 6;
    int vertex = 4;
    for (int i = 1; i <= facet; i++)
    {
        for (int j = 1; j <= vertex; j++)
        {
            glTexCoord2f(f1[j], f2[j]);
            glVertex3f(w[(i - 1) * 4 + j] * width / 2, h[(i - 1) * 4 + j] * height,
                       l[(i - 1) * 4 + j] * length / 2);
        }
    }
}


//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
//draw a ellipsoid
void drawEllipsoid(float xx, float yy, float zz, float radiusX, float radiusZ, float radiusY, float M, float N)
{
    float step_z = PI / M;      //z方向每次步进的角度
    float step_xy = 2 * PI / N; //x,y平面每次步进的角度
    float x[4], y[4], z[4];       //用来存坐标

    float angle_z = 0.0; //起始角度
    float angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for (i = 0; i < M; i++)
    {
        angle_z = i * step_z; //每次步进step_z
        for (j = 0; j < N; j++)
        {
            glColor3f(0.5f, 0.5f, 0.8f);
            angle_xy = j * step_xy; //每次步进step_xy
            //整个的过程可以想象3D打印机，一层一层的画出来
            x[0] = radiusX * sin(angle_z) * cos(angle_xy); //第一个小平面的第一个顶点坐标
            y[0] = radiusY * sin(angle_z) * sin(angle_xy);
            z[0] = radiusZ * cos(angle_z);

            x[1] = radiusX * sin(angle_z + step_z) * cos(angle_xy); //第一个小平面的第二个顶点坐标，下面类似
            y[1] = radiusY * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radiusZ * cos(angle_z + step_z);

            x[2] = radiusX * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = radiusY * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = radiusZ * cos(angle_z + step_z);

            x[3] = radiusX * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radiusY * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radiusZ * cos(angle_z);
            //至此得到一个平面的4个顶点
            for (int k = 0; k < 4; k++)
            {
                glVertex3f(xx + x[k], yy + y[k], zz + z[k]); //画出这个平面
            }
        } //循环画出这一层的平面，组成一个环
    }     //z轴++，画出剩余层
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd(); //OK
}

//draw a half ellipsoid
void drawHalfEllipsoid(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radiusX, GLfloat radiusY, GLfloat radiusZ, GLfloat M, GLfloat N)
{
    float step_y = PI / M;      //y方向每次步进的角度
    float step_xz = 2 * PI / N; //x,z平面每次步进的角度
    float x[4], y[4], z[4];       //用来存坐标

    float angle_y = 0.0; //起始角度
    float angle_xz = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for (i = 0; i < M; i++)
    {
        angle_y = i * step_y; //每次步进step_z

        for (j = 0; j < N / 2; j++)
        {
            angle_xz = j * step_xz;                        //每次步进step_xy
                                                           //整个的过程可以想象3D打印机，一层一层的画出来
            x[0] = radiusX * sin(angle_y) * cos(angle_xz); //第一个小平面的第一个顶点坐标
            y[0] = radiusZ * sin(angle_y) * sin(angle_xz);
            z[0] = radiusY * cos(angle_y);

            x[1] = radiusX * sin(angle_y + step_y) * cos(angle_xz); //第一个小平面的第二个顶点坐标，下面类似
            y[1] = radiusZ * sin(angle_y + step_y) * sin(angle_xz);
            z[1] = radiusY * cos(angle_y + step_y);

            x[2] = radiusX * sin(angle_y + step_y) * cos(angle_xz + step_xz);
            y[2] = radiusZ * sin(angle_y + step_y) * sin(angle_xz + step_xz);
            z[2] = radiusY * cos(angle_y + step_y);

            x[3] = radiusX * sin(angle_y) * cos(angle_xz + step_xz);
            y[3] = radiusZ * sin(angle_y) * sin(angle_xz + step_xz);
            z[3] = radiusY * cos(angle_y);
            //至此得到一个平面的4个顶点
            for (int k = 0; k < 4; k++)
            {
                glVertex3f(xx + x[k], yy + y[k], zz + z[k]); //画出这个平面
            }
        } //循环画出这一层的平面，组成一个环

    }        //z轴++，画出剩余层
    glEnd(); //OK
}

//draw a cylinder
void drawCylinder(float radius, float axislength,vector axis,float x,float y,float z)
{
    if (axis.x != 0)
    {
        //glBegin(GL_QUADS);
        for (float j = 0; j < axislength; j += axislength / NN)
        {
            for (int i = 0; i < 360; i++)
            {
                glVertex3f(j+x, radius * cos(2 * M_PI * i / 360)+y, radius * sin(2 * M_PI * i / 360)+z);
            }
        }
        //glEnd();
    }
    if (axis.y != 0)
    {
        //glBegin(GL_QUADS);
        for (float j = 0; j < axislength; j += axislength / NN)
        {
            for (int i = 0; i < 360; i++)
            {
                glVertex3f(radius * cos(2 * M_PI * i / 360)+x, j+y, radius * sin(2 * M_PI * i / 360)+z);
            }
        }
        //glEnd();
    }
}



#endif /* ELEMENTFIGURE_H */
