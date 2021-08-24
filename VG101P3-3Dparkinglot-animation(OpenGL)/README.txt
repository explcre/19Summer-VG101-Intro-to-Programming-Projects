README 
This file is attacked to project 3 of pgroup 24.

# Basic Setup
Instead of 2D plotting, we use 3D plotting for player's better experience.
Also, our game enables players to use press keys on the keyboard to manipulate motion of the car, use 'Y' on the keyboard to reset the camera and use mouse button to change camera angle(relative information contains in Control.h)

Our project deserves bonuses because:
1. Our flexible and powerful hierarchy diagram, we make good use of inheritance and polymorphism to draw complex figures.
2. We use 3D rather than 2D plotting, that's much more vivid, and definitely more challenging.
3. We have great interactive user interface, user could use keyboard button to manipulate motion of the car.
4. There's a flag at the top of the car which could move up and down when speed of car is nonzero.
5. We successfully combine part 1 and part 2.
6. There're 2 modes for players to choose: 1. auto and 2. manual

# Hierarchy Diagram

ElemFigure___Cuboid
   |____________Cone
   |____________Ellipsoid
   |____________HalfEllipsoid
   |____________Cylinder

shape________            _______Rocket
motion______-------- |_______Flag
                                 |_______UFO
                                 |_______Teleported

vector
motion_mouse

Wall
ParkData
Game

# Problems encounted
1. At first we have difficulty combining part 1 and part 2, but we struggle to cooperate them.
2. At first we use SYSTEMTIME in windows, however, after failed compilation in JOJ, we turn to <time.h> to count time (embodied in function arrival and departure)

#Important Notes to PLAY:
1. When running the code, after the "There is ... vehicles in the parking lot." you need to press any key button on the keyboard to proceed.
2. When "driving" the car into the slot, "collide" with walls of free space until the red floor turns green, that's a valid parking. Unless there's no departure ticket when the car goes out the door.
3. Every slot has its number, which is determined in advance. but in an auto mode, the parking slot is determined randomly.
--------------------------------------------------------------------------------------------------------------------------------------------------------
Detailed introduction to classes:  
-------------------------------------------------------------------------------------------------------------------------------------------------------
# about class vector ( in ElementFigure.h)
attributes: float x,y,z
methods: vector:: vector( )
                vector::vector(float x,float y,float z)
                void vector::set(float x1,float y1,float z1)
we define the vector class, thus lay the basis for motion and anchor position of figures.

#about class motion(in head.h)
attributes: float deltaAngle1,deltaAngle2, angle1,angle2, distance,velocity_2, v_acceleration
                 vector position,velocity
methods: void motion::init( )
                motion::~motion( )
we use vector position and vector velocity to describe motion of object
void init( ) initialize the position of object.
note: angle1 is the angle formed by z-axis and position, angle 2 is the angle formed by y-axis and position, distance is from the origin

#about class motion_mouse (in head.h)
attributes: int xOrigin=-1,yOrigin=-1
----------------------------------------------------------------------------------------------------------------------------------------------------------
#about class ElemFigure( in head.h)
attributes: float length,width,height,red,green,blue
                 vector position
methods:  virtual float getLength( );
                 virtual float getWidth( );
                 virtual float getHeight( );
                 virtual vector getPosition( );
                 virtual void setPosition(vector a);
                 virtual void move(vector dir);
                 virtual void rotate(float angle);
                 virtual void zoom(float k);
                 virtual ~ElemFigure();
#about class Cone (derived from ElemFigure)
attributes:  float radius, axislength;
    vector position;
    float red, green,blue
methods: Cone();
Cone(float radius, float axislength, float x1, float y1, float z1);
void draw();
void rotate(float angle);
virtual ~Cone( );

#about class Ellipsoid(derived from ElemFigure)
attributes: float length, width, height;
    vector position;
    float red, green,blue
methods: Ellipsoid( );
Ellipsoid(float length,float width,float height,float x,float y,float z)
void draw( );
void rotate(float angle);
virtual ~Ellipsoid( );

#about class HalfEllipsoid(derived from ElemFigure)
attributes: float length, width, height;
    vector position;
    float red, green,blue
methods: HalfEllipsoid( );
HalfEllipsoid(float length,float width,float height,float x,float y,float z)
void draw( );
void rotate(float angle);
virtual ~HalfEllipsoid( );

#about class Cuboid(derived from ElemFigure)
attributes: float length, width, height;
    vector position;
   float red, green,blue
methods: Cuboid( )
Cuboid(float length,float width,float height,float x,float y,float z)
void draw( );
void rotate(float angle);
virtual ~Cuboid( );

#about class Cylinder (derived from ElemFigure)
attributes:  float radius, axislength;
    vector position;
    float red, green,blue
methods: Cylinder();
Cylinder(float radius, float axislength, float x1, float y1, float z1);
void draw();
void rotate(float angle);
virtual ~Cylinder( );
---------------------------------------------------------------------------------------------------------------
#about class shape
attributes:
private: float width,length,height;
public: float red,green,blue;
methods:   
                 shape( );
                 float getLength( );
                 float getWidth( );
                 float getHeight( ); 
                 void changeL(float length_1);
                 void changeH(float height_1);
                 void changeW(float width_1);
note: class shape and class ElemFigure are very similar classes, because in complex figures (rocket and UFO), we need to "has a" derived class of ElemFigure, thus we use class shape to avoid confliction and add flexibility to change its size.

#about class Rocket(derived from class shape and class motion)
attributes:float scale, deltaAngle1, deltaAngle2, l, w,h
                vector position
methods: void drawZoomIO( ): to draw rocket and change its scale( zoom in and zoom out)as well.
                void changeROCKET(Rocket R): to change l, w,h and position according to Rocket R
                virtual ~Rocket( );

#about class Flag(derived from class shape and class motion)
attributes: float scale, deltaAngle1, deltaAngle2, l, w,h
                vector position
methods:  void draw(float x, float y, float z, float vx, float vz): to draw the flag and make it move in y direction when x-velocity and z-velocity isn't 0
                 virtual ~Flag( );

#about class Car(derived from class shape and class motion)
attributes: float scale, deltaAngle1, deltaAngle2, l, w,h
                vector position
methods:  void draw( ): to draw one car
                 void changeCAR(Car C): to change l,w,h and position of car
                 virtual ~Car( );

#about class UFO(derived from class shape and class motion)
attributes: float scale, deltaAngle1, deltaAngle2, l, w,h
                vector position
methods:  void draw( ): to draw one UFO
                 void drawRotate(int i);
                 void changeUFO(UFO U)
                 virtual ~UFO( );

#about class Teleported(derived from class shape and class motion)
attributes: float scale, l, w,h
                vector position
methods:  void draw( ): to draw one teleported and change color
                 void changeTeleported(Teleported T)
                 virtual ~Teleported( );
------------------------------------------------------------------------
#about class Wall
attributes:
vector wallposition;
    float length, width, height;
    float red,green,blue;
methods:
void set(vector wallposition1, float length1, float width1, float height1)
void drawDoor()// the door in the entrance of the parking lot, will change color if a car goes in
void drawPark()// the walls around, total number is generated by the number user enters


#about class ParkData
attributes:(protected)
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
    float unitPrice[5] = {0, 1, 2, 3, 4}; //for each type of car, price is different
    float price[MAXCARN];
    vector position[MAXCARN]; //position of carpark
    Wall walls[MAXCARN * 2];
methods:
    ParkData( );
    ParkData(int park_n): to initialize
    void setParkState(int i, int state_t)// for the ith slot, set the state according to type of cars
    void setParkState(int i, int state_t) 
    void setParkTimeIn(int i, int time_thour, int time_tmin, int time_tsecond)
    void setParkTimeOut(int i, int time_thour, int time_tmin, int time_tsecond) 
    int calculateseconds(int i) 
    float calculatePrice(int i) 
    void showParkTimeIn(int i) 
    void showParkTimeOut(int i) 
    void showParkTimeInterval(int i) 
    int showstate(int i) 
    int showprice(int i) 
    int showN()// show the parking slots in total
    virtual ~ParkData() {}

*note: the relation between unit parking fee of parking state and car type is:
1 for car, 2 for Rocket, 3 for UFO
thus the parking fee is: unit parking fee * time interval (departure time-arrival time)(unit second)
also, we use the system time to record time(SYSTEMTIME sys)

out of this class, we use class Parkdata to define 2 functions to perform the functions of the parking lot
void arrival(ParkData *p, int i): to determine which kind of car(car,UFO,Rocket) and print a ticket(record the arrival time and guidance of slot)
void departure(ParkData *p,int i): to record the leaving time and calculate the parking fee

*note: in these two functions, we use <time.h> to count time
       every slot has its number, which is determined in advance. but in an auto mode, the parking slot is determined randomly.
 we also have some forward declaration:
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
----------------------------------------------------------------------------------------

On these basis, we define class Game to contain all the data and control function of the project.
 
# class Game:
attributes: 
public:
    Car car;// cars already in the parking lot, generated randomly
    Car player;// car manipulated by the user
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
    motion camera;
    motion_mouse mouse;// related to the angle of user
    //initialize the parking lot

methods:

static Game *getInstance()
void getParkdata(int n)
void assignPark( )//intialize the park, draw UFO, rockets and teleported
void init_wall()//initialize the walls of the park
void init_Door()
void init_Park()

void drawUFO(float length, float width, float height);
void computeUFODir()//rotate the UFO

 int hit_check(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)// hit analysis
 void hit_analysis()
 void park_analysis() //analyze whether the car is in a carport
 void change_speed()// change speed
void change_speed_f()//change friction direction
 void computePos()// change car's position
void computeDir()// change car's speed
void init_car()//intialize the car
void init_flag( )//initialize the flag

static Game *game = Game::getInstance();
---------------------------------------------------------------------------------------------------------------------------------------------------
# about the interactive interface (information contained in Control.h)

void mouseButton(int button, int state, int x, int y)  //camera control through mouse button
void mouseMove(int x, int y)  //camera control through mouse move
void changeSize(int w, int h)  //main the size of picture
void pressKey(int key, int xx, int yy)  //speed control through Keyboard
void releaseKey(int key, int x, int y)  //speed control through Keyboard
void processNormalKeys(unsigned char key, int x, int y) //speed control through Keyboard, press 'Y' on the keyboard to change the view
