
#include "head.h"


//draw a Rocket
void drawRocket(float length,float width,float height)
{

    //glColor3f(red, green, blue);


    //下标为0的数组元素不考虑，从[1]开始考虑
    glColor3f(121.0/255.0f,121.0/255.0f,121.0/255.0f);
    Cylinder cy0(length/2,height*0.75,0,0,0,0,1,0);
    cy0.draw();


    glColor3f(238.0/255.0f,44.0/255.0f,44.0/255.0f);
    Cone co1(length/2,height*0.25,0,0,height*0.75);
    co1.draw();

    glColor3f(30.0/255.0f,144.0/255.0f,255.0/255.0f);
    Cylinder c[4];
    Cylinder c1(length/5,height*0.15,length/2,0,0,0,1,0);c[0]=c1;
    Cylinder c2(length/5,height*0.15,-length/2,0,0,0,1,0);c[1]=c2;
    Cylinder c3(length/5,height*0.15,0,0,length/2,0,1,0);c[2]=c3;
    Cylinder c4(length/5,height*0.15,0,0,-length/2,0,1,0);c[3]=c4;
    for(int i=0;i<4;i++){
        c[i].draw();}
}



//draw a UFO
void UFO::drawUFO(float length, float width, float height)
{
    //class ElemFigure;

    //float ox=position.x,oy=position.y,oz=position.z;
    float ox = 0, oy = 0, oz = 0;
    Ellipsoid elpsd(length, width, 0.3 * height, ox, oy, oz);
    elpsd.draw();
    glColor3f(0.0f, 0.3f, 0.9f);

    HalfEllipsoid hfelpsd(0.5 * length, height, 0.5 * width, ox, oy, oz);
    hfelpsd.draw();

    HalfEllipsoid hf[11];
    for (int i = 0; i <= 10; i++)
    {
        glColor3f(0.0f, 0.0f, 0.8f);
        float xt = ox + 0.7 * length * cos(2 * M_PI / 10 * i);
        float zt = oz + 0.7 * width * sin(2 * M_PI / 10 * i);
        HalfEllipsoid ht(0.2 * length, 0.4 * height, 0.2 * width, xt, oy, zt);
        hf[i] = ht;
        hf[i].draw();
    }
}
