#ifndef HEAD_H
#define HEAD_H
#include "ElementFigure.h"
#include <time.h>

//define the coordinate motion of mouse
class motion_mouse
{
public:
    int xOrigin = -1;
    int yOrigin = -1;
};

//define the motion of objects
class motion
{
public:
    float deltaAngle1 = 0.0f;
    float deltaAngle2 = 0.0f;
    vector velocity;
    vector position;
    float velocity_2 = 0.0f;
    float distance = 10.0f;
    float v_acceleration = 0.0f;
    float angle1 = 0.0f;
    float angle2 = 0.0f;
    //initialize the camera
    void init()
    {
        angle1 = 0;
        angle2 = PI / 4;
        distance = 5.0f;
        position.z = cos(angle1) * cos(angle2) * distance;
        position.x = -sin(angle1) * cos(angle2) * distance;
        position.y = sin(angle2) * distance;
    }
    virtual ~motion() {}
};

//define a type that contains all element shapes
class ElemFigure
{
protected:
    float length, width, height;
    vector position;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    ElemFigure()
    {
        length = 1;
        width = 1;
        height = 1;
        vector p(0, 0, 0);
        position = p;
    }
    ElemFigure(float length, float width, float height, float x, float y, float z) : length(length), width(width), height(height)
    {
        vector p(x, y, z);
        position = p;
    }
    //return the length,width,height and position
    virtual float getLength() { return length; }
    virtual float getWidth() { return width; }
    virtual float getHeight() { return height; }
    virtual vector getPosition() { return position; }
    //change the position
    virtual void setPosition(vector a) { position = a; }
    //change the direction
    virtual void rotate(float angle) {}
    //change the size
    virtual void zoom(float k)
    {
        length *= k;
        width *= k;
        height *= k;
    }

    virtual ~ElemFigure() {}
};

//define a type that contains all complex figures
class shape
{
private:
    float width, length, height;

public:
    float red = 1.0f, green = 1.0f, blue = 1.0f;
    //return the length,width and height
    float getL() { return length; }
    float getW() { return width; }
    float getH() { return height; }
    //change the length,width and height
    void changeL(float length_1) { length = length_1; }
    void changeW(float width_1) { width = width_1; }
    void changeH(float height_1) { height = height_1; }
    //initialize function
    shape()
    {
        width = 1;
        length = 1;
        height = 1;
    }
};

//define an element figure cone
class Cone : public ElemFigure
{
protected:
    float radius, axislength;
    vector position;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    //initialize function
    Cone()
    {
        radius = 1.0;
        axislength = 1.0;
        vector p(0, 0, 0);
        position = p;
    }
    Cone(float radius, float axislength, float x1, float y1, float z1) : radius(radius), axislength(axislength)
    {
        vector p(x1, y1, z1);
        position = p;
    }
    //draw function
    void draw() { drawCone(radius, axislength, position.x, position.y, position.z); }
    void rotate(float angle){};
    virtual ~Cone(){};
};

//define an element figure Ellipsoid
class Ellipsoid : ElemFigure
{
protected:
    float length, width, height;
    vector position;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    //initialize function
    Ellipsoid()
    {
        length = 1;
        width = 1;
        height = 1;
        vector p(0, 0, 0);
        position = p;
    }

    Ellipsoid(float length, float width, float height, float x, float y, float z) : length(length), width(width), height(height)
    {
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void draw() { drawEllipsoid(position.x, position.y, position.z, length, width, height, MM, NN); }
    void rotate(float angle){};

    virtual ~Ellipsoid() {}
};
//define an element figure half Ellipsoid
class HalfEllipsoid : ElemFigure
{
protected:
    float length, width, height;
    vector position;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    //initialize function
    HalfEllipsoid()
    {
        length = 1;
        width = 1;
        height = 1;
        vector p(0, 0, 0);
        position = p;
    }
    HalfEllipsoid(float length, float width, float height, float x, float y, float z) : length(length), width(width), height(height)
    {
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void draw() { drawHalfEllipsoid(position.x, position.y, position.z, length, width, height, MM, NN); }
    void rotate(float angle){};

    virtual ~HalfEllipsoid() {}
};

//define an element figure Cuboid
class Cuboid : ElemFigure
{
protected:
    float length, width, height;
    vector position;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    //initialize function
    Cuboid()
    {
        length = 1;
        width = 1;
        height = 1;
        vector p(0, 0, 0);
        position = p;
    }
    Cuboid(float length, float width, float height, float x, float y, float z) : length(length), width(width), height(height)
    {
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void draw() { drawCuboid(width, height, length); }
    void rotate(float angle){};
    virtual ~Cuboid() {}
};

//define an element figure Cylinder
class Cylinder : public ElemFigure
{
protected:
    float radius, axislength;
    vector position, axis;
    float red = 1.0f, green = 1.0f, blue = 1.0f;

public:
    //initialize function
    Cylinder()
    {
        radius = 1.0;
        axislength = 1.0;
        vector p(0, 0, 0);
        position = p;
        vector a(1, 0, 0);
        axis = a;
    }
    Cylinder(float radius, float axislength, float x1, float y1, float z1, float x2, float y2, float z2) : radius(radius), axislength(axislength)
    {
        vector p(x1, y1, z1);
        position = p;
        vector a(x2, y2, z2);
        axis = a;
    }
    //draw function
    void draw()
    {
        drawCylinder(radius, axislength, axis, position.x, position.y, position.z);
    }
    void rotate(float angle){};
    virtual ~Cylinder(){};
};

//define a complex figure rocket
class Rocket : public motion, public shape
{
protected:
    float scale;

public:
    //initialize function
    Rocket()
    {
        scale = 1;
        deltaAngle1 = deltaAngle2 = 0.2f;
        changeL(1);
        changeW(1);
        changeH(1);
        vector p(0, 0, 0);
        position = p;
    }
    Rocket(float x, float y, float z, float l, float w, float h)
    {
        scale = 1;
        deltaAngle1 = deltaAngle2 = 0.2f;
        changeL(l);
        changeW(w);
        changeH(h);
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void drawZoomIO()
    {
        static float d = -0.01;
        static float dd = 1;
        dd += d;
        if (dd <= 0.1)
            d = 0.01;
        if (dd >= 1)
            d = -0.01;
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dd, dd, dd);
        glColor3f(red, green, blue);
        glRotated(90.0f, 1, 0, 0); //旋转坐标系，使得z轴为竖直轴
        glColor3f(238.0f / 255, 44.0f / 255, 44.0f / 255);
        glutSolidCone(0.1f, -0.4f, 20, 20); //圆锥，火箭头
        glTranslatef(0.0f, 0.0f, 0.7f);
        glColor3f(121.0f / 255, 121.0f / 255, 121.0f / 255);
        glutSolidCylinder(0.1f, -0.7f, 10, 10); //火箭体
        //配饰
        glColor3f(30.0f / 255, 144.0f / 255, 255.0f / 255);
        glTranslatef(0.0f, 0.15f, 0.0f); //横坐标（右+），竖坐标（下+），纵坐标（前+）
        glutSolidCylinder(0.05f, -0.2f, 10, 10);
        glTranslatef(0.0f, -0.3f, 0.0f); //横坐标（右+），竖坐标（下+），纵坐标（前+）
        glutSolidCylinder(0.05f, -0.2f, 10, 10);
        glTranslatef(0.15f, 0.15f, 0.0f); //横坐标（右+），竖坐标（下+），纵坐标（前+）
        glutSolidCylinder(0.05f, -0.2f, 10, 10);
        glTranslatef(-0.3f, 0.0f, 0.0f); //横坐标（右+），竖坐标（下+），纵坐标（前+）
        glutSolidCylinder(0.05f, -0.2f, 10, 10);
        glPopMatrix();
    }
    void changeROCKET(Rocket R)
    {
        deltaAngle1 = deltaAngle2 = 0.2f;
        velocity.y = 0.02f;
        changeL(R.getL());
        changeW(R.getW());
        changeH(R.getH());
        position = R.position;
    }
    virtual ~Rocket() {}
};

//define wall of carspark
class Wall
{
public:
    vector wallposition;
    float length, width, height;
    float red = 1.0f, green = 1.0f, blue = 1.0f;
    //initialize function
    Wall(vector wallposition, float length, float width, float height) : wallposition(wallposition), length(length), width(width), height(height) {} //组合类构造函数
    Wall() {}
    void set(vector wallposition1, float length1, float width1, float height1)
    {
        wallposition = wallposition1;
        length = length1;
        width = width1;
        height = height1;
    }

    //draw function
    void drawWall()
    {
        glPushMatrix();
        glTranslatef(wallposition.x, wallposition.y, wallposition.z);

        glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        drawCuboid(width, height, length);
        glEnd();
        glPopMatrix();
    }
    void drawDoor()
    {
        glPushMatrix();
        glTranslatef(wallposition.x, wallposition.y, wallposition.z);

        glBegin(GL_QUADS);
        glColor4f(red, green, blue, 0.4);
        drawCuboid(width, height, length);
        glEnd();
        glPopMatrix();
    }
    void drawPark()
    {
        glPushMatrix();
        glTranslatef(wallposition.x, wallposition.y, wallposition.z);
        glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        drawCuboid(width, 0.0f, length);

        glEnd();
        glPopMatrix();
    }
};

//define a complex figure flag
class Flag : public motion, public shape
{
protected:
    vector position;

public:
    float r, w, h;
    //initialize function
    Flag() {}
    Flag(float x, float y, float z, float radius, float w_, float h_)
    {

        deltaAngle1 = deltaAngle2 = 0.2f;
        vector p(x, y, z);
        position = p;
        r = radius;
        w = w_;
        h = h_;
    }
    //draw function
    void draw(float x, float y, float z, float vx, float vz)
    {
        static float dy = 0.02;
        static float yy = 0;
        if (vx != 0 || vz != 0)
            yy += dy;
        if (yy >= 0.2)
            dy = -0.02;
        if (yy <= -0.2)
            dy = 0.02;
        glPushMatrix();
        glTranslatef(x, y + yy-h, z);
        glRotatef(angle1 * 180 / M_PI, 0.0f, -1.0f, 0.0f);
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(90, 1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glutSolidCylinder(r / 10, h, 20, 20);
        glTranslatef(0, 0, w / 2);
        drawCuboid(0.2 * r, h, w / 2);
        glEnd();

        glPopMatrix();
    }
    virtual ~Flag() {}
};

//define a complex figure car
class Car : public motion, public shape
{
protected:
public:
    //initialize function
    Car()
    {

        changeH((rand() % 1) * 0.2f + 0.2f);
        changeW(getH() * 2);
        changeL(getW() * 2);
        vector p(0, 0, 0);
        position = p;
    }
    Car(float x, float y, float z, float l, float w, float h)
    {

        deltaAngle1 = deltaAngle2 = 0.2f;
        changeL(l);
        changeW(w);
        changeH(h);
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void draw()
    {
        glPushMatrix();
        glTranslatef(position.x, position.y + getH() / 2, position.z);
        glPushMatrix();
        glRotatef(angle1 * 180 / M_PI, 0.0f, -1.0f, 0.0f);
        glColor3f(red, green, blue);

        glBegin(GL_QUADS);
        drawCuboid(getW(), getH(), getL());
        glEnd();
        glTranslatef(0, getH() * 3 / 4, getL() / 4);
        glBegin(GL_QUADS);
        drawCuboid(getW(), getH() / 2, getL() / 2);
        glEnd();
        glPopMatrix();
        glTranslatef(getL() * sin(angle1) / 4, 0, -getL() * cos(angle1) / 4);
        glColor3f(red / 2, green / 3, blue / 4);
        glPushMatrix();
        glRotatef(angle1 * 180 / M_PI + 90, 0.0f, -1.0f, 0.0f);
        glutSolidCylinder(getH() / 2, getW() / 2 + 0.05, 20, 20);
        glutSolidCylinder(getH() / 2, -getW() / 2 - 0.05, 20, 20);
        glPopMatrix();
        glTranslatef(-getL() * sin(angle1) / 2, 0, getL() * cos(angle1) / 2);
        glRotatef(angle1 * 180 / M_PI + 90, 0.0f, -1.0f, 0.0f);
        glutSolidCylinder(getH() / 2, getW() / 2 + 0.05, 20, 20);
        glutSolidCylinder(getH() / 2, -getW() / 2 - 0.05, 20, 20);
        glPopMatrix();
    }
    //initialize car
    void changeCAR(Car C)
    {
        blue = 0;
        changeL(C.getL());
        changeW(C.getW());
        changeH(C.getH());
        position = C.position;
    }
    virtual ~Car() {}
};
//define a complex figure UFO
class UFO : public motion, public shape
{
protected:
public:
    //initialize function
    UFO()
    {
        deltaAngle1 = deltaAngle2 = 0.2f;
        velocity.y = 0.02f;
        changeL(1);
        changeW(1);
        changeH(1);
        vector p(0, 0, 0);
        position = p;
    }
    UFO(float x, float y, float z, float l, float w, float h)
    {
        deltaAngle1 = deltaAngle2 = 0.2f;
        velocity.y = 0.02f;
        changeL(l);
        changeW(w);
        changeH(h);
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void drawUFO(float length, float width, float height);
    void drawRotate(int i)
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(angle1 * 180 / M_PI, 0.14 * cos(i + 5), -1.0f, 0.14 * sin(i + 5));
        //glColor3f(red, green, blue);
        glBegin(GL_QUADS);
        //下标为0的数组元素不考虑，从[1]开始考虑
        drawUFO(getL(), getW(), getH());
        glEnd();
        glPopMatrix();
    }
    void draw() { drawUFO(getL(), getW(), getH()); }
    //initialize UFO
    void changeUFO(UFO U)
    {
        deltaAngle1 = deltaAngle2 = 0.2f;
        velocity.y = 0.02f;
        changeL(U.getL());
        changeW(U.getW());
        changeH(U.getH());
        position = U.position;
    }
    virtual ~UFO() {}
};
//define a complex figure Teleported
class Teleported : public motion, public shape
{
protected:
public:
    //initialize function
    Teleported()
    {
        changeL(1);
        changeW(1);
        changeH(1);
        vector p(0, 0, 0);
        position = p;
    }
    Teleported(float x, float y, float z, float l, float w, float h)
    {
        changeL(l);
        changeW(w);
        changeH(h);
        vector p(x, y, z);
        position = p;
    }
    //draw function
    void draw(int t)
    {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        //glRotatef(angle1 * 180 / M_PI, 0.14 * cos(i + 5), -1.0f, 0.14 * sin(i + 5));
        //glColor3f(red, green, blue);
        glBegin(GL_QUADS);
        //下标为0的数组元素不考虑，从[1]开始考虑
        float dred = (float)rand() / RAND_MAX + t / 10.0, dgreen = (float)rand() / RAND_MAX + t / 10.0, dblue = (float)rand() / RAND_MAX + t / 10.0;
        red += dred / 20.0;
        green += dgreen / 20.0;
        blue += dblue / 20.0;
        int w[26] = {0, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1};
        int h[26] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1};
        int l[26] = {0, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1};
        float f1[5] = {0, 0.0f, 1.0f, 1.0f, 0.0f};
        float f2[5] = {0, 0.0f, 1.0f, 1.0f, 1.0f};
        int facet = 6;
        int vertex = 4;

        if (red >= 1)
        {
            red = red - 1;
        }
        if (green >= 1)
        {
            green = green - 1;
        }
        if (blue >= 1)
        {
            blue = blue - 1;
        }
        glColor3f(red, green, blue);
        for (int i = 1; i <= facet; i++)
        {

            for (int j = 1; j <= vertex; j++)
            {
                glTexCoord2f(f1[j], f2[j]);
                glVertex3f(w[(i - 1) * 4 + j] * getW() / 2, h[(i - 1) * 4 + j] * getH(),
                           l[(i - 1) * 4 + j] * getL() / 2);
            }
        }

        glEnd();
        glPopMatrix();
    }
    //initialize Teleported
    void changeTeleported(Teleported T)
    {
        changeL(T.getL());
        changeW(T.getW());
        changeH(T.getH());
        position = T.position;
    }
    virtual ~Teleported() {}
};
//define a type that contains all complex shapes and walls
class ParkData
{
protected:
    int park_n;         //number of park
    int car_n;          //number of cars
    int state[MAXCARN]; //the type of vehicle
    float time_inhour[MAXCARN];
    float time_inmin[MAXCARN];
    float time_insecond[MAXCARN];
    float time_outhour[MAXCARN];
    float time_outmin[MAXCARN];
    float time_outsecond[MAXCARN];
    float unitPrice[5] = {0,0.00001,0.00002,0.00003,0.00004}; //for each type of car, price is different
    float price[MAXCARN];
    vector position[MAXCARN]; //position of carpark
    Wall walls[MAXCARN * 2];
    int statenow=0;

public:
    ParkData() {}
    ParkData(int park_n) : park_n(park_n)
    {
        for (int i = 1; i <= park_n; i++)
        {
            state[i] = 0;
            time_inhour[i] = 0;
            time_inmin[i] = 0;
            time_insecond[i] = 0;
            time_outhour[i] = 0;
            time_outmin[i] = 0;
            time_outsecond[i] = 0;
            price[i] = 0;
        }
    }
    void setstatenow(int statenow1){statenow=statenow1;}
    int showstatenow(){return statenow;}
    void setParkState(int i, int state_t) { state[i] = state_t; }
    void setParkTimeIn(int i, int time_thour, int time_tmin, int time_tsecond) { time_inhour[i] = time_thour, time_inmin[i] = time_tmin, time_insecond[i] = time_tsecond; }
    void setParkTimeOut(int i, int time_thour, int time_tmin, int time_tsecond) { time_outhour[i] = time_thour, time_outmin[i] = time_tmin, time_outsecond[i] = time_tsecond; }
    int calculateseconds(int i) { return (time_outhour[i] * 3600 + time_outmin[i] * 60 + time_outsecond[i] - time_inhour[i] * 3600 - time_inmin[i] * 60 - time_insecond[i]); }
    float calculatePrice(int i) { return  unitPrice[statenow] * calculateseconds(i); }
    void showParkTimeIn(int i) { cout << "Time of arrical: " << time_inhour[i] << ":" << time_inmin[i] << ":" << time_insecond[i] << endl; }
    void showParkTimeOut(int i) { cout << "Time of departure: " << time_outhour[i] << ":" << time_outmin[i] << ":" << time_outsecond[i] << endl; }
    void showParkTimeInterval(int i) { cout << "Time spent in the parking lot: " << calculateseconds(i) / 3600 << " hours " << (calculateseconds(i) - calculateseconds(i) / 3600) / 60 << " minutes " << calculateseconds(i) % 60 << " seconds" << endl; }
    int showstate(int i) { return state[i]; }
    int showprice(int i) { return price[i]; }
    int showN() { return park_n; }

    virtual ~ParkData() {}
};

void arrival(ParkData* p,int i,int n){
    int statenow1;
    time_t time_seconds=time(0);
    struct tm* now_time=localtime(&time_seconds);
    p->setParkTimeIn(i,now_time->tm_hour,now_time->tm_min,now_time->tm_sec);//get the arrival time

    cout<<"Please enter the type of the vehecle(1:Car 2:Rocket 3:UFO)";
    cin>>statenow1;//record the type of the vehicle
    //p->setParkState(i,state);
    p->setstatenow(statenow1);
    cout<<"---------------Arrival ticket---------------"<<endl;
    p->showParkTimeIn(i);
    cout<<"Type of the vehicle: ";
    switch(statenow1){
        case 1:
            cout<<"Car"<<endl;
            break;
        case 2:
            cout<<"Rocket"<<endl;
            break;
        case 3:
            cout<<"UFO"<<endl;
            break;
    }
    cout<<"The available parking place: ";
    for(int ii=1;ii<n+1;ii++){
        if(p->showstate(ii)==0)
            cout<<ii<<",";
    }
    cout<<endl;
}

void departure(ParkData* p,int i){
    time_t time_seconds=time(0);
    struct tm* now_time=localtime(&time_seconds);
    p->setParkTimeOut(i,now_time->tm_hour,now_time->tm_min,now_time->tm_sec);//get the departure time
    cout<<"---------------Departure ticket---------------"<<endl;
    p->showParkTimeOut(i);
    p->showParkTimeInterval(i);
    cout<<"Type of the vehicle: ";
    switch(p->showstatenow()){
        case 1:
            cout<<"Car"<<endl;
            break;
        case 2:
            cout<<"Rocket"<<endl;
            break;
        case 3:
            cout<<"UFO"<<endl;
            break;
    }
    cout<<"The total price: "<<p->calculatePrice(i)<<"$"<<endl;
}
//forward declaration
void changeSize(int w, int h);
void pressKey(int key, int xx, int yy);
void releaseKey(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
void renderScene();
float min(float x, float y);
float max(float x, float y);
float mult(float x1, float y1, float x2, float y2, float xx, float yy);
float cross(float x1, float y1, float x2, float y2, float xx, float yy);

//define a class that contains all the data and control function of the project
class Game
{
private:
    Game(){};
    ~Game(){};

public:
    static Game *getInstance()
    {
        static Game *s = NULL;
        if (s == NULL)
            s = new Game();
        return s;
    }
    //define all the shapes that required
    Car car;
    Car player;
    Flag flag;
    Wall wall[100], teleport[MAXCARN];
    Wall door;
    vector wallposition[100];
    int n;
    UFO Us[20];
    Rocket RS[20];
    Teleported TS[20];
    Car c[20];
    ParkData pk;
    int empty2Park;
    int ifauto;//=1 auto,=0 not auto
    motion camera;
    motion_mouse mouse;
    int enter=0;//decide whether or not to print arrival ticket.If enter=0,print.
    int parkingplace=0;//record the available parking place, the user should park the car in this place
    int enterorleave=0;//record whether the car has entered the parking lot and parked already. If enterorleave=0,the car hasn't, or it has.
    int leave=0;//decide whether or not to print departure ticket. If leave=0,print.
    //initialize the parking lot
    void getParkdata(int n)
    {
        pk = ParkData(n);
    }


    //forward declaration
    void drawUFO(float length, float width, float height);

    //hit analysis
    int hit_check(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
    {
        if (min(x1, x2) <= max(x3, x4) &&
            min(y1, y2) <= max(y3, y4) &&
            min(x3, x4) <= max(x1, x2) &&
            min(y3, y4) <= max(y1, y2))
            return 1;
        return 0;
    }
    //hit analysis
    void hit_analysis()
    {

        vector t;
        t = car.position;
        float x[5], z[5], wx[5], wz[5];
        t.x += car.velocity.x;
        t.z += car.velocity.z;
        x[0] = -player.getW() / 2 * cos(car.angle1) + player.getL() / 2 * sin(car.angle1) + t.x;
        z[0] = -player.getW() / 2 * sin(car.angle1) - player.getL() / 2 * cos(car.angle1) + t.z;
        x[1] = player.getW() / 2 * cos(car.angle1) + player.getL() / 2 * sin(car.angle1) + t.x;
        z[1] = player.getW() / 2 * sin(car.angle1) - player.getL() / 2 * cos(car.angle1) + t.z;
        x[2] = player.getW() / 2 * cos(car.angle1) - player.getL() / 2 * sin(car.angle1) + t.x;
        z[2] = player.getW() / 2 * sin(car.angle1) + player.getL() / 2 * cos(car.angle1) + t.z;
        x[3] = -player.getW() / 2 * cos(car.angle1) - player.getL() / 2 * sin(car.angle1) + t.x;
        z[3] = -player.getW() / 2 * sin(car.angle1) + player.getL() / 2 * cos(car.angle1) + t.z;
        x[4] = x[0];
        z[4] = z[0];

        wx[0] = -door.width / 2 + door.wallposition.x;
        wx[1] = door.width / 2 + door.wallposition.x;
        wx[2] = door.width / 2 + door.wallposition.x;
        wx[3] = -door.width / 2 + door.wallposition.x;
        wx[4] = wx[0];
        wz[0] = -door.length / 2 + door.wallposition.z;
        wz[1] = -door.length / 2 + door.wallposition.z;
        wz[2] = door.length / 2 + door.wallposition.z;
        wz[3] = door.length / 2 + door.wallposition.z;
        wz[4] = wz[0];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if (hit_check(x[i], z[i], x[i + 1], z[i + 1], wx[j], wz[j], wx[j + 1], wz[j + 1]) &&
                    mult(x[i], z[i], wx[j + 1], wz[j + 1], wx[j], wz[j]) * mult(wx[j + 1], wz[j + 1], x[i + 1], z[i + 1], wx[j], wz[j]) > 0 &&
                    mult(wx[j], wz[j], x[i], z[i], x[i + 1], z[i + 1]) * mult(x[i], z[i], wx[j + 1], wz[j + 1], x[i + 1], z[i + 1]) > 0)
                {
                    // car.velocity.x = -car.velocity.x;
                    // car.velocity.z = -car.velocity.z;
                    door.green = 0;
                    door.red = 1;
                    //decide which available parking place to park
                    for(int k=0;k<n;k++){
                        if(pk.showstate(k)==0){
                            parkingplace=k;break;
                        }
                    }

                    //change the parameter enter to 1 so that it won't print the ticket again and agian
                    if(enter==0) {
                        arrival(&pk, parkingplace,n);
                        enter=1;
                    }
                    //change the parameter leave to 1 so that it won't print the ticket again and agian
                    if(enterorleave==1&&leave==0){
                        departure(&pk,parkingplace);
                        leave=1;
                    }
                    break;
                }
                else
                {
                    door.red = 0;
                    door.green = 1;
                }
            }


        for (int k = 1; k <= n + 5; k++)
        {
            wx[0] = -wall[k].width / 2 + wall[k].wallposition.x;
            wx[1] = wall[k].width / 2 + wall[k].wallposition.x;
            wx[2] = wall[k].width / 2 + wall[k].wallposition.x;
            wx[3] = -wall[k].width / 2 + wall[k].wallposition.x;
            wx[4] = wx[0];
            wz[0] = -wall[k].length / 2 + wall[k].wallposition.z;
            wz[1] = -wall[k].length / 2 + wall[k].wallposition.z;
            wz[2] = wall[k].length / 2 + wall[k].wallposition.z;
            wz[3] = wall[k].length / 2 + wall[k].wallposition.z;
            wz[4] = wz[0];
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    if (hit_check(x[i], z[i], x[i + 1], z[i + 1], wx[j], wz[j], wx[j + 1], wz[j + 1]) &&
                        mult(x[i], z[i], wx[j + 1], wz[j + 1], wx[j], wz[j]) * mult(wx[j + 1], wz[j + 1], x[i + 1], z[i + 1], wx[j], wz[j]) > 0 &&
                        mult(wx[j], wz[j], x[i], z[i], x[i + 1], z[i + 1]) * mult(x[i], z[i], wx[j + 1], wz[j + 1], x[i + 1], z[i + 1]) > 0)
                    {
                        // car.velocity.x = -car.velocity.x;
                        // car.velocity.z = -car.velocity.z;
                        car.velocity_2 = -car.velocity_2;
                        return;
                    }
                }
        }
    }
    //analyze whether the car is in a carport
    void park_analysis()
    {
        int p = 0;
        vector t;
        t = car.position;
        float x[4], z[4], wx[4], wz[4];
        x[0] = -player.getW() / 2 * cos(car.angle1) + player.getL() / 2 * sin(car.angle1) + t.x;
        z[0] = -player.getW() / 2 * sin(car.angle1) - player.getL() / 2 * cos(car.angle1) + t.z;
        x[1] = player.getW() / 2 * cos(car.angle1) + player.getL() / 2 * sin(car.angle1) + t.x;
        z[1] = player.getW() / 2 * sin(car.angle1) - player.getL() / 2 * cos(car.angle1) + t.z;
        x[2] = player.getW() / 2 * cos(car.angle1) - player.getL() / 2 * sin(car.angle1) + t.x;
        z[2] = player.getW() / 2 * sin(car.angle1) + player.getL() / 2 * cos(car.angle1) + t.z;
        x[3] = -player.getW() / 2 * cos(car.angle1) - player.getL() / 2 * sin(car.angle1) + t.x;
        z[3] = -player.getW() / 2 * sin(car.angle1) + player.getL() / 2 * cos(car.angle1) + t.z;
        for (int i = n + 6; i < 2 * n + 6; i++)
        {
            p = 1;
            wx[0] = -wall[i].width / 2 + wall[i].wallposition.x;
            wx[1] = wall[i].width / 2 + wall[i].wallposition.x;
            wx[2] = wall[i].width / 2 + wall[i].wallposition.x;
            wx[3] = -wall[i].width / 2 + wall[i].wallposition.x;
            wz[0] = -wall[i].length / 2 + wall[i].wallposition.z;
            wz[1] = -wall[i].length / 2 + wall[i].wallposition.z;
            wz[2] = wall[i].length / 2 + wall[i].wallposition.z;
            wz[3] = wall[i].length / 2 + wall[i].wallposition.z;
            for (int j = 0; j < 4; j++)
            {
                if (cross(wx[0], wz[0], wx[1], wz[1], x[j], z[j]) * cross(wx[2], wz[2], wx[3], wz[3], x[j], z[j]) < 0 ||
                    cross(wx[1], wz[1], wx[2], wz[2], x[j], z[j]) * cross(wx[3], wz[3], wx[0], wz[0], x[j], z[j]) < 0 ||
                    pk.showstate(i - n - 5) != 0)
                {
                    wall[i].red = 1;
                    wall[i].blue = 0;
                    wall[i].green = 0;
                    p = 0;
                    break;
                }
            }
            if (p)
            {
                wall[i].red = 0;
                wall[i].green = 1;
                enterorleave=1;//to record that it has parked
                return;
            }
        }
    }
    //change speed
    void change_speed()
    {
        if (car.velocity.x * car.velocity.x + car.velocity.z * car.velocity.z < 1)
        {
            car.velocity.x += car.v_acceleration * sin(car.angle1);
            car.velocity.z += -car.v_acceleration * cos(car.angle1);
            car.velocity_2 += +car.v_acceleration;
        }
    }
    //change friction direction
    void change_speed_f()
    {
        float sinn = car.velocity.x / sqrtf(car.velocity.x * car.velocity.x + car.velocity.z * car.velocity.z);
        float cosn = car.velocity.z / sqrtf(car.velocity.x * car.velocity.x + car.velocity.z * car.velocity.z);
        if ((car.velocity.x) * (car.velocity.x) < (0.01f * sinn / 2) * (0.01f * sinn / 2))
            car.velocity.x = 0.0f;
        if ((car.velocity.z) * (car.velocity.z) < (-0.01f * cosn / 2) * (-0.01f * cosn / 2))
            car.velocity.z = 0.0f;
        if ((car.velocity_2) * (car.velocity_2) < (-0.01f) * (-0.01f))
            car.velocity_2 = 0.0f;
        if (car.velocity.x != 0)
            car.velocity.x += (-0.01f / 2) * sinn;
        if (car.velocity.z != 0)
            car.velocity.z += (-0.01f / 2) * cosn;

        if (car.velocity_2 > 0)
            car.velocity_2 -= 0.01f / 2;
        else if (car.velocity_2 < 0)
            car.velocity_2 += 0.01f / 2;
    }
    //change car's position
    void computePos()
    {

        car.position.x += car.velocity.x;
        car.position.z += car.velocity.z;
    }
    //change car's speed
    void computeDir()
    {
        car.angle1 += car.deltaAngle1;
        car.velocity.x = car.velocity_2 * sin(car.angle1);
        car.velocity.z = -car.velocity_2 * cos(car.angle1);
    }
    //initialize the park
    void assignPark()
    {
        //initialize UFO
        for (int o = 1; o <= n / 6; o++)
        {
            int k = 0;
            int t = (rand() % n) + 1;

            while (pk.showstate(t) != 0)
            {
                k++;
                t = (rand() % n) + 1;
            }
            pk.setParkState(t, 2);
            t = t + n + 5;
            UFO U(wallposition[t].x, wallposition[t].y + 0.4 * Us[0].getH(), wallposition[t].z, 0.4, 0.4, 0.2);
            Us[o].changeUFO(U);
        }
        //initialize rocket
        for (int o = 1; o <= n / 6; o++)
        {
            int k = 0;
            int t = (rand() % n) + 1;

            while (pk.showstate(t) != 0)
            {
                k++;
                t = (rand() % n) + 1;
            }
            pk.setParkState(t, 1);
            t = t + n + 5;
            Rocket R(wallposition[t].x, wallposition[t].y + 1, wallposition[t].z, 0.4, 0.4, 0.2);
            RS[o].changeROCKET(R);
        }
        //initialize car
        for (int o = 1; o <= n / 6; o++)
        {
            int k = 0;
            int t = (rand() % n) + 1;

            while (pk.showstate(t) != 0)
            {
                k++;
                t = (rand() % n) + 1;
            }
            pk.setParkState(t, 3);
            t = t + n + 5;
            float H = ((rand() % 1) * 0.2f + 0.2f);
            float W = H * 2;
            float L = W * 2;
            Car C(wallposition[t].x, wallposition[t].y, wallposition[t].z, L, W, H);
            c[o].changeCAR(C);
        }
        //initialize Teleported
        for (int o = 1; o <= n / 6; o++)
        {
            int k = 0;
            int t = (rand() % n) + 1;

            while (pk.showstate(t) != 0)
            {
                k++;
                t = (rand() % n) + 1;
            }
            pk.setParkState(t, 4);
            t = t + n + 5;
            Teleported T(wallposition[t].x, wallposition[t].y + 0.0 * TS[0].getH(), wallposition[t].z, 0.2, 0.8, 1.3);
            TS[o].changeTeleported(T);
        }
    }

    //initialize the park wall
    void init_wall()
    {

        for (int i = 1; i < n / 2 + 1; i++)
        {
            wallposition[i].set(-1.9 + (i - 1) * 1, 0.0f, 2.2f);
        }
        for (int j = 1; j < n / 2 + 1; j++)
        {
            wallposition[n / 2 + j].set(-1.9 + (j - 1) * 1, 0.0f, -2.2f);
        }
        wallposition[n + 1].set(-4.0f, 0.0f, 0.0f);
        wallposition[n + 2].set(n / 2 - 1.75, 0.0f, 0.0f);
        wallposition[n + 3].set((n / 2 - 5.75) / 2, 0.0f, -3.25f);
        wallposition[n + 4].set(n / 4 - 2, 0.0f, 3.25f);
        wallposition[n + 5].set((n / 2 - 5.9) / 2, 0.0f, 0.0f);

        wall[n + 1].set(wallposition[n + 1], 7.0f, 0.5f, 1.0f);          //left
        wall[n + 2].set(wallposition[n + 2], 6.0f, 0.5f, 1.0f);          //right
        wall[n + 3].set(wallposition[n + 3], 0.5f, n / 2 + 2.75f, 1.0f); //back
        wall[n + 4].set(wallposition[n + 4], 0.5f, n / 2 + 1.0, 1.0f);   //front
        //wall[n + 5].set(wallposition[n + 5], 1.0f, n / 2 - 1.9f, 1.0f);//back
        for (int k = 1; k < n + 1; k++)
        {
            wall[k].set(wallposition[k], 1.6f, 0.2f, 1.0f);
        }
    }
    //initialize the car
    void init_car()
    {
        car.position.x = -3.2;
        car.position.z = 4;
    }
    //initialize the flag
    void init_flag()
    {
        flag.r = 0.2;
        flag.w = 0.5;
        flag.h = 0.5;
    }
    //initialize the door
    void init_Door()
    {
        door.wallposition.x = -3.2;
        door.wallposition.z = 3.25;
        door.height = 1;
        door.length = 0.25;
        door.width = 1.4;
        door.red = 0;
        door.blue = 0;
        door.green = 1;
    }
    //initialize the carport
    void init_Park()
    {

        for (int i = n + 6; i < n + 5 + n / 2 + 1; i++)
        {
            wallposition[i].set(-1.4 + (i - n - 6) * 1, 0.1f, 2.2f);
        }
        for (int j = n + 5 + n / 2 + 1; j < 2 * n + 5 + 1; j++)
        {
            wallposition[j].set(-1.4 + (j - (n + 5 + n / 2 + 1)) * 1, 0.1f, -2.2f);
        }

        for (int k = n + 6; k < 2 * n + 6; k++)
        {
            wall[k].set(wallposition[k], 1.6f, 0.8f, 0.0f);
        }
    }
    //rotate UFO
    void computeUFODir()
    {
        for (int i = 1; i <= n / 6; i++)
        {
            Us[i].angle1 += Us[i].deltaAngle1;
            Us[i].position.y += Us[i].velocity.y;
            if (Us[i].position.y + 0.4 * Us[i].getH() + Us[i].velocity.y >= wall[1].height)
            {
                Us[i].velocity.y = -0.02f;
            }
            if (Us[i].position.y - 0.5 * Us[i].getH() + Us[i].velocity.y <= 0)
            {
                Us[i].velocity.y = 0.02f;
            }
        }
    }

    void decideWhere2Park(){

        empty2Park=(int)(rand() %n)+1;
        while(pk.showstate(empty2Park)!=0){empty2Park=(int)(rand() %n+1);}
        printf("we park %d\n",empty2Park);
    }
void autoMode(){

        if(car.position.z>=wallposition[1].z-0.9 && car.position.x<=wallposition[1].x-0.5f){
            car.velocity.z=-0.05;
            car.position.z += car.velocity.z;
        }



        if(car.position.z<=wallposition[1].z-0.9 &&car.position.z>=wallposition[n/2+1].z+2.0&& car.angle1<=PI/2 && car.position.x<=wallposition[1].x-0.5f){
            /*car.deltaAngle1=-0.06f;
            car.angle1+=car.deltaAngle1;
car.position.x= (car.position.x - (wallposition[empty2Park].x-0.5))*cos(car.angle1)- (car.position.z - (wallposition[empty2Park].z-0.5))*sin(car.angle1) + (wallposition[empty2Park].x-0.5) ;

car.position.z= (car.position.x - (wallposition[empty2Park].x-0.5))*sin(car.angle1) + (car.position.z - (wallposition[empty2Park].z-0.5)) *cos(car.angle1)+(wallposition[empty2Park].z-0.5) ;
*/          car.deltaAngle1=PI/10;
            car.angle1+=car.deltaAngle1;
            //car.velocity.x= 0.05f*sin(car.angle1);
            //car.velocity.z=-0.05f*cos(car.angle1);
            car.velocity.z=0;
            car.position.x += 0.05f*sin(car.angle1);//car.velocity.x;
            car.position.z += -0.05f*cos(car.angle1);//car.velocity.z;


        }


        if(car.position.z<=wallposition[1].z-0.9 && car.position.x<=wallposition[n+2].x) {

            if (empty2Park <= n / 2) {
                if ( car.position.x <= wallposition[empty2Park].x+0.25f  &&car.angle1<=PI) {
                    car.deltaAngle1 = 0.0;
                    car.velocity.x = 0.06f;
                    car.position.x += car.velocity.x;
                } else if ( car.position.x >= wallposition[empty2Park].x +0.25f&& car.angle1<=PI)  {
                    car.deltaAngle1 = PI/15;

                    car.angle1 += car.deltaAngle1;
                    car.velocity.x = 0.01f *10* sin(car.angle1);
                    car.velocity.z = -0.01f*10* cos(car.angle1);
                    car.position.x += car.velocity.x;
                    car.position.z += car.velocity.z;

                }


            } else if (empty2Park > n / 2) {

                if( car.position.z>=wallposition[n/2+1].z+2.5&&car.position.x<=wallposition[n+2].x-1.5){
                    car.deltaAngle1 = 0.0;
                    car.velocity.x = 0.06f;
                    car.position.x += car.velocity.x;
                }

                if( empty2Park<n && car.position.z>=wallposition[n/2+1].z+0.5 &&car.position.x>=wallposition[n+2].x-1.5 && car.angle1>=-PI/2){
                    car.deltaAngle1 = -PI/20;

                    car.angle1 += car.deltaAngle1;
                    car.velocity.x =  0.05f *5* sin(car.angle1);
                    car.velocity.z = - 0.05f*5* cos(car.angle1);
                    car.position.x += car.velocity.x;
                    car.position.z += car.velocity.z;
                }
                if( empty2Park==n && car.position.z>=wallposition[n/2+1].z+0.5 &&car.position.x>=wallposition[n+2].x-1.5 && car.angle1>=0){
                    car.deltaAngle1 = -PI/20;

                    car.angle1 += car.deltaAngle1;
                    car.velocity.x =  0.05f *5* sin(car.angle1);
                    car.velocity.z = - 0.05f*5* cos(car.angle1);
                    car.position.x += car.velocity.x;
                    car.position.z += car.velocity.z;
                }
                if( empty2Park==n && car.position.z>=wallposition[n/2+1].z+0.5 &&car.position.x>=wallposition[n+2].x-1.5 && car.angle1<=0){
                    car.deltaAngle1=0;
                    car.velocity.z = - 0.05f*5* cos(car.angle1);
                    car.position.z += car.velocity.z;
                }



            }


            if(empty2Park>n/2&&empty2Park<n&&car.position.z<=wallposition[n/2+1].z+2  &&  car.position.x>=wallposition[empty2Park].x+0.7 && car.angle1<=-PI/2){

                car.deltaAngle1 = 0.0;
                car.velocity.x = -0.1f;
                car.position.x += car.velocity.x;
            }


        }

        if ( empty2Park<=n/2 && car.position.x >= wallposition[empty2Park].x-0.1 &&car.position.z <= wallposition[empty2Park].z+0.2&& car.angle1>=PI)  {
            car.deltaAngle1=0;
            car.velocity.z = -0.01f*20* cos(car.angle1);
            car.position.z += car.velocity.z;

        }


        if ( empty2Park>n/2&&empty2Park<n && car.position.z<=wallposition[n/2+1].z+3.6 &&car.position.x <= wallposition[empty2Park].x +0.7f&& car.angle1<=0)  {
            car.deltaAngle1 = PI/15;

            car.angle1 += car.deltaAngle1;
            car.velocity.x = 0.01f *10* sin(car.angle1);
            car.velocity.z = -0.01f*10* cos(car.angle1);
            car.position.x += car.velocity.x;
            car.position.z += car.velocity.z;

        }

        if ( empty2Park>n/2 &&empty2Park<n&& car.position.z<=wallposition[n/2+1].z+2.6&& car.position.x <= wallposition[empty2Park].x+0.7 &&car.position.z >= wallposition[empty2Park].z&& car.angle1>=0)  {
            car.deltaAngle1=0;
            car.velocity.z = -0.01f*20* cos(car.angle1);
            car.position.z += car.velocity.z;

        }



        }




};

static Game *game = Game::getInstance();
#endif /* HEAD_H */
