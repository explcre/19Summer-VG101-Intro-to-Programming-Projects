VG101 2019 summer
project1

name:XuPengcheng
student_ID:518370910177



Input:
1.mode
'Y' is select modes, 'N' is set up by yourself
2.difficulty
 if you enter 'Y',there will be 4 modes:'EASY', 'MEDIUM', 'HARD', 'HELL'
The parameters except the plate number are all generated automatically
 
 if you enter'N', you will set up these following parameters:

3.road(1).dir_n=input('Please input the number of directions of the road(4 is normal):');
%the number of all directions of the road, you'd better enter an even number larger than 2

4.road(1).lane_n=input('Please input the number of lanes of the road(>=2 and is an even number):');
%the number of lanes of the road

5.road(1).width=input('Please input the width of the road(The unit is 1 unit length, 4 is normal):');
%variable rd_w  is width of the road

6.car_n=input('Please input the number of cars(an integer):');
%the number of the cars

7.p=input('Please input the probability the the cars do not stop at the red light:(number 0-1)'); 
%the number of the cars

8.light(1).tr=input('Please input the time of red light of up left side(seconds):');
(A little tips:you'd better set the time of the green lights longer than (road width/car velocity) to avoid crash)
9.light(1).tg=input('Please input the time of green light of up left side(seconds):');
(A little tips:you'd better set the time of the green lights longer than (road width/car velocity) to avoid crash)

10.car(1).velocity0=input('Please input the maxium velocity of the cars(0.6 is normal):');

11.car(1).plate_lib=input("Please input the elements of the car plate number(e.g. ['abcdef123456']):");

12.car(1).plate_n=input('Please input the number of the car plate:');



Output & Function explanation:
1.function road=draw_road(road)
%It will draw the road
2.function light=draw_lightini(road,light)
%Initialize the light

3.function light=draw_light(t,road,light)
%continguing updating the lights
%when a=1,the 1st and 3rd become red;when a=2,2nd and 4th become red

4. function car=car_go(car,b)

%plot the car when the car is going straight

5.function car=car_stat(car,b)
%plot the car when the car is static.

6.function car=car_right(t,car,b,road,light)
%plot the car when it turn right

7.function car=car_right_yixinghuanying(t,car,b,road,light)
%special skills of cars:yixinghuanying


8.function car=car_left(t,car,b,road,light)
%plot the car when it turn left

9.function car=car_plate_generate(car,i)
%generate the car plate.
i is the ith car plate

10.function car=car_adjust(car,b,road,light)
%function to adjust car's position when finish turning

11.function car=change_velocity(t,dt,car,b,v0,vt)%t0 is the instant of time start to change speed
                                                  %t is the current time
                                                  %dt is the time used to change speed
                                                  %v0 is the origin velocity
                                                  %vt is the velocity after dt
%function to change the velocityfunction another=anotherSide(car,b,road,light)%It judge whether the car reach another side of the crossing



12.function car=avoid_bump(t,car,road)
%function to avoid bumping(not finished)


13.function another=anotherSide(car,b,road,light)
%It judge whether the car reach another side of the crossing



Varibles explanation:
1.struct car
car=struct('length',{},'width',{},...
    'no',{},...
    'on_road',{},...
    'plate',{},...
    'plate_lib',{},...
    'plate_n',{},...
    'car_type',{},...
    'shape',zeros(2,5),...
    'shapet',{},...
    'crashbox',{},...
    'color',{},...
    'fill1',{},...
    'fill2',{},...
    'fills',{},...
    'fillcolor',{},...
    'velocity0',{},...
    'velocity',{},...
    'changingv',{},...
    'ox',{},'oy',{},...
    'dx',{},'dy',{},...
    'oox',{},'ooy',{},...
    'odirection',{},...
    'direction2',{},...
    'violation',{},...
    'state',{},...
    'area',{},...
    'No_in_area',{},...
    'lane',{},...
    't_g',{},...
    't0',{},...
    't1',{},...
    'boom',{});

%originally define a struct car,
%it's length is 2 ,width is 1,it's number
%plate is its plate number
%on_road is the number of cars on the road
%shape is its priginal shape
%shapet is its current shape(rotated)
%crashbox is used to judge whether it crash into other cars
%color is a char like 'r'
%fill is a 2*n matrix to describe the place to paint another color
%fillcolor is the color filled corresponding to "fill"
%velocity0 is the originally set
%velocity is the current velocity of each car which is randomly  set.
%changingv is a boolean 0 or values>0,if 0 it's not changingits speed
          %otherwise its value is its time start to change v
%ox,oy,is its center point's position, set up by ox and oy matrices
%oox,ooythe position change with respect to the light when reach crossing
%odirection is which way a car take originally,it's randomly generated in the range 1 to car_n 
%direction2 is which way a car NOW take(will be changed after turning)
%violation record whether the car will break traffic rules 1is violation,0 is not
%state is a varieble to express whether the car have crossed the road:
       %1: not crossed 2:stop when there're other cars before it stopped at the crossing 3:stop at the crossing 
       %4:at the crossing(straight) 5:turning right 6.turning left 7:have crossed
%area is to express where the cars are, there are road(1).dir_n  number of
       %road directions and 1 crossing
%No_in_area is the car No, in its area :an integer 
%t0 is the time the car starts to turn
%t1 is the time the car almost finishes turning
%boom is to express whether the car bump into each other,0 is no ,n>=1 is
%the number it bumps into.
%t_g: the time the car is generated


2.struct road
road=struct('width',{},'dir_n',{},'lane_n',{},'shape',{},...
            'size',{},'set',{},'midline',{},'midlines',{},'midlines_s',{},...
            'pic_l',{},'pic_w',{},'turningLight',{});
%define the road as a struct
%dir_n is the number of directions
%lane_n is the number of lanes
%shape is a matrix to show how the 1/n of the road is plotted
%size is the size of shape matrix
%set is the whole set of all parts of road
%midline is 1 middle line of road
%midlines is the set of  a quarter of all the lanes of middle line of road
%midlines_s is the set of all middle lines of road
%turningLight is whether the road has a turning light
road(1).turningLight=0;
road(1).pic_l=16;%picture length
road(1).pic_w=16;%picture width


3.light=struct('position',{},'no',{},'color',{},...
             'size',{},'set',{},'tr',{},'tg',{},'tt',{});
%define the light as a struct
%tr is time of red
%tg is time of green
%tt is time of turning lights :They will be blue!
light(1).tt=0;


Algorithm explanation:
1.The input
 You can select modes or set up parameters by yourself

2.Setting up data of road and light

3.Setting up rhe data of car

4.The main function:it's a loop
  i=1;
  while isAllOut(car,road)==0 && iscrash(1)==0
        i=i+1;
  end
  £¨i represents time£©

  So when there're still cars on the screen and there's no car crashed, the loop continuously.
  each step stands for an instant of time 
  everystep:1)Plotting road and light 
            2)The car's state is updated
            3)Plotting the car 


5.The critical function to change cars' state is the function
(function car_state_change())
  


car().state is a variable to express whether the car have crossed the road:
        1: not crossed 
        2:stop when there're other cars before it stopped at the crossing 
        3:stop at the crossing 
        4:at the crossing(straight) 
        5:turning right 
        6.turning left 
        7:have crossed


    1 ---if reach the crossing--- if red light && not break rule------------> 3
        |                    |
        |                     ---- if green light ||(red and break rule)----> reach_greenlight()---------------------------if the leftest lane---> 6
        |                                             (to randomly decide whether             |
        |                                            the car go straight or left or right)    -----random---------------->4
         ---if not reach crassing-----1)avoid_bump()  
                                        (to aviod bump into the car before it)                |                                                                    |
                                      2)car_go()                                              -----random---------------->5
                                        (continue going straight)


    2-------1)car_paint()-----if greenlight----->car_go()
           



    3-------1)set v=0   
            2)paint_car----if reach&&(green )--->car_reachgreenlight()



    4------change v to original(v0>0)--------if reach another side---->7


    5------1)change v to original(v0>0)
           2)turn right
           3)adjust position on another side----finish turning---->7

    6------1)change v to original(v0>0)
           2)turn left
           3)adjust position on another side----finish turning---->7

    7------car_go()
           


   

6.After we come out of the while loop
   1)we print all the cars which broke the laws 
   2) we display the ending image
      if all the cars are out of screen, we win.
      if crash happen,we lose.


Notes:
1. If you enter directions number>4, the car will only go straight
(because the turning function of 4 direction road can not be used in direction>4)
2.The crashbox is a l little bit smaller than the car is plotted(0.7 times)
so sometimes the cars do "touch", but maybe intersection is very small so we consider it as not crashed.
But obvious where car main body bump into each other will definitely be considered as "crashed".