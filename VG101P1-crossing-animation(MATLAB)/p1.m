[car,road,light]=declareStructs();
%The followings are the main functions
[car,road,light]=read_input(car,road,light);
car=initiateCar(car,road);
[road,light]=initiateRoadLight(road,light);
road=draw_road(road);
light=draw_lightini(road,light);
[car,road,light]=mainloop(car,road,light);
ending(car,road);



function [car,road,light]=declareStructs()
%we first declare 3 structs :road ,car,light
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


light=struct('position',{},'no',{},'color',{},...
             'size',{},'set',{},'tr',{},'tg',{},'tt',{});
%define the light as a struct
%tr is time of red
%tg is time of green
%tt is time of turning lights :They will be blue!





car=struct('n',{},...
    'p',{},...
    'length',{},'width',{},...
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
%odirection is which way a car take originally,it's randomly generated in the range 1 to car(1).n
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

end

function [car,road,light]=read_input(car,road,light)




    mode=input("Do you want to select a difficulty level or set up parameters by yourself?('Y' is select modes, 'N' is set up by yourself):");
    switch mode 
        case 'Y'
            difficulty=input("Please select: 'EASY', 'MEDIUM', 'HARD', 'HELL'");
            switch difficulty
                case 'EASY'
                    road(1).dir_n=4;
                    road(1).lane_n=2;
                    road(1).width=6;
                    car(1).n=5;
                    car(1).p=0;
                    light(1).tr=6;
                    light(1).tg=6;
                    car(1).velocity0=0.5;
                case 'MEDIUM'
                    road(1).dir_n=4;
                    road(1).lane_n=4;
                    road(1).width=10;
                    car(1).n=12;
                    car(1).p=0.1;
                    light(1).tr=2;
                    light(1).tg=2;
                    car(1).velocity0=0.6;
                case 'HARD'
                    road(1).dir_n=6;
                    road(1).lane_n=6;
                    road(1).width=8;
                    car(1).n=25;
                    car(1).p=0.3;
                    light(1).tr=4;
                    light(1).tg=4;
                    car(1).velocity0=0.8;
                case 'HELL'
                    road(1).dir_n=8;
                    road(1).lane_n=8;
                    road(1).width=10;
                    car(1).n=50;
                    car(1).p=0.5;
                    light(1).tr=10;
                    light(1).tg=10;
                    car(1).velocity0=0.8;
            end
        case 'N'
                road(1).dir_n=input('Please input the number of directions of the road(an even number>2)(4 is normal):');%the number of all directions of the road
                while road(1).dir_n<0 || mod(road(1).dir_n,2)==1
                    road(1).dir_n=input('ERROR!!!Please input the number of directions of the road AGAIN!!!(4 is normal)(an even number>2):');
                end

                road(1).lane_n=input('Please input the number of lanes of the road(>=2 and is an even number):');%the number of lanes of the road
                while(mod(road(1).lane_n,2)==1) || road(1).lane_n < 2
                    road(1).lane_n=input('ERROR!!Please input the number of lanes of the road AGAIN!!!(>=2 and is an even number)!!!:');%the number of lanes of the road
                end
                road(1).width=input('Please input the width of the road(The unit is 1 unit length, road_width/road_lane_n=2.5 is normal):');%variable rd_w  is width of the road
                while road(1).width<0
                    road(1).width=input('ERROR!!!Please input the width of the road AGAIN!!!(The unit is 1 unit length, road_width/road_lane_n=2.5 is normal)(w>0):');
                end
                car(1).n=input('Please input the number of cars(an integer>1):');%the number of the cars
                while car(1).n<0 || floor(car(1).n)~=car(1).n %be integer>0,otherwise input again
                    car(1).n=input('ERROR!!!Please input the number of cars(an integer) AGAIN!!!(n>0):');
                end
                p=input('Please input the probability the the cars do not stop at the red light:(number 0-1)'); %the number of the cars

                while p<0 || p>1
                    p=input('ERROR!!Please input the probability the the cars do not stop at the red light AGAIN!!:(number 0-1)!!!:');
                end

                car(1).velocity0=input('Please input the maxium velocity of the cars(0.6 is normal):');
                while car(1).velocity0<0
                    car(1).velocity0=input('ERROR!!!Please input the maxium velocity of the cars AGAIN!!!(0.6 is normal)(v>0)::');
                end


                light(1).tr=input("Please input the time of red light of up left side(seconds)(A little tips:you'd better set the time of the green lights longer than (road width/car velocity)):");
                while light(1).tr<0
                    light(1).tr=input('ERROR!!!Please input the time of red light of up left side AGAIN!!!(seconds)(t>0):');
                end
                light(1).tg=input('Please input the time of green light of up left side(seconds):');
                while light(1).tg<0
                    light(1).tg=input('ERROR!!!Please input the time of green light of up left side AGAIN!!!(seconds)(t>0):');
                end
                if road(1).turningLight==1
                    light(1).tt=input('Please input the time of turning light of up left side(seconds):');
                while light(1).tt<0
                    light(1).tt=input('ERROR!!!Please input the time of turning light of up left side AGAIN!!!(seconds)(t>0):');
                end
    end

    end

    car(1).plate_lib=input("Please input the elements of the car plate number(e.g. ['abcdef123456']):");
    car(1).plate_n=input('Please input the length of the car plate:');
    while car(1).plate_n<0
        car(1).plate_n=input('ERROR!!!Please input the number of the car plate AGAIN!!!(n>0)::');
    end

    
    
road(1).turningLight=0;
road(1).pic_l=16;%picture length
road(1).pic_w=16;%picture width

light(1).tt=0;
end



function car=initiateCar(car,road)
    for i=1:car(1).n
            car(i).no=i;

            low=road.width/road.lane_n*0.4;
            high=road.width/road.lane_n*0.75;
            car(i).width=unifrnd(low,high);
            %randomly generate the width of car(shorter than a given value)
            car(i).length=car(i).width*(1.4+1.2*rand(1));

            car(i).velocity0=car(1).velocity0*(1-(i-1)/car(1).n*0.15*rand(1));
            car(i).velocity=car(i).velocity0;
        %according to the maximium velocity, every car newly generated will be
        %gradually a bit smaller and smaller(to avoid potential accidents)
      while i>1 && car(i).velocity0>car(i-1).velocity0
          car(i).velocity0=car(1).velocity0*(1-(i-1)/car(1).n*0.15*rand(1));
      end

            car(i).odirection=round(unifrnd(1,road.dir_n));
            %randomly generate the direction of cars, 1 - the number of direction
            car(i).direction2=car(i).odirection;
             %the original position of car according to direction
            car(i).lane=round(unifrnd(1,road(1).lane_n/2));

            while i>1 && car(i).odirection(1)==car(i-1).odirection(1) && car(i).lane(1)==car(i-1).lane(1)
                car(i).odirection=round(unifrnd(1,road.dir_n));
                %randomly generate the direction of cars, 1 - the number of direction
                car(i).direction2=car(i).odirection;
                 %the original position of car according to direction
                car(i).lane=round(unifrnd(1,road(1).lane_n/2));
            end

        theta=(car(i).odirection-1)/road(1).dir_n*360+90;
        la=(road(1).pic_l+car(i).length/2);
        lb=(0.5*(road(1).width/road(1).lane_n)*(1+2*(car(i).lane-1)));
        l=sqrt(la^2+lb^2);
        car(i).ox=l*cosd(theta+atand(lb/la));%center of car(x axis)
        car(i).oy=l*sind(theta+atand(lb/la));%center of car(y axis)
        lc=road(1).width/2-lb;
        car(i).dx=zeros(1,road(1).dir_n);
        car(i).dy=zeros(1,road(1).dir_n);
        car(i).oox=zeros(1,road(1).dir_n);
        car(i).ooy=zeros(1,road(1).dir_n);
        for j=1:road(1).dir_n
            car(1).dx(j)=-cosd((j-1)/road(1).dir_n*360+90);%the location change of 4 directions of cars on x axis
            car(1).dy(j)=-sind((j-1)/road(1).dir_n*360+90);%the location change of 4 directions of cars on y axis
            car(i).oox(j)=-lc*cosd(j/road(1).dir_n*360+90);%the position change with respect to the light when reach crossing
            car(i).ooy(j)=-lc*sind(j/road(1).dir_n*360+90);
        end  


        beetles_shape=[-0.5,  -0.5,    -0.43,  -0.33, -0.46, -0.44,   -0.33, -0.208,   -0.208, -0.167,-0.167, -0.205,                0.292, 0.5,  0.5,   0.292,     -0.205, -0.167, -0.167, -0.208, -0.208, -0.33, -0.44, -0.46, -0.33, -0.43, -0.5, -0.5;
                       0,      0.25,    0.38,    0.38,   0.1,  0.33,    0.38,   0.38,   0.483,   0.5,   0.40,   0.38,                0.38,  0.33,-0.33, -0.38,      -0.38,  -0.4,   -0.5,   -0.483, -0.38,  -0.38, -0.33, -0.1,  -0.38, -0.38,  -0.25,  0];
        beetles_shape(1,:)=beetles_shape(1,:).*car(i).length;
        beetles_shape(2,:)=beetles_shape(2,:).*car(i).width;
        newshape=rotate(theta)*beetles_shape;            
        car(i).shape=[car(i).shape;newshape];
        car(i).shapet=[car(i).shapet;newshape];


        crashbox=0.7*[-1/2*car(i).length,  1/2*car(i).length,    1/2*car(i).length,     -1/2*car(i).length,   -1/2*car(i).length;...
                       1/2*car(i).width,   1/2*car(i).width,     -1/2*car(i).width,     -1/2*car(i).width,    1/2*car(i).width];
        newcrashbox=rotate(theta)*crashbox;
        car(i).crashbox=newcrashbox;

        car(i).color=unifrnd(0,1,1,3);

        newfill=[  -0.042,  -0.042, -0.208,  -0.25, -0.25, -0.208,-0.042,  ;
                    0.23,    -0.23, -0.33,   -0.27, 0.27,   0.33,   0.23,      ];
        newfill(1,:)=newfill(1,:).*car(i).length;
        newfill(2,:)=newfill(2,:).*car(i).width;
        newfill=rotate(theta)*newfill; 
        car(i).fill1=[car(i).fill1, newfill];
        car(i).fills=[car(i).fill1; newfill];

        car(i).fillcolor=[car(i).fillcolor;0 0.5 1];

        newfill=[0.233,  0.33, 0.375,  0.375,   0.33, 0.233, 0.233;
                 0.23,  0.33,  0.27,  -0.27,  -0.33, -0.23,  0.23 ];
        newfill(1,:)=newfill(1,:).*car(i).length;
        newfill(2,:)=newfill(2,:).*car(i).width;
        newfill=rotate(theta)*newfill; 
        car(i).fill2=[car(i).fill2, newfill];
        car(i).fills=[car(i).fill1; newfill];

        car(i).fillcolor=[car(i).fillcolor;0 0.5 1];


        %the following steps will generate the car property about whether break
        %the rule according to the p input.
        random=rand(1);
        if random<=car(1).p 
            car(i).violation=1;
        else
            car(i).violation=0;
        end
        if car(i).lane==1% the left side of the lane will not break the rule
            car(i).violation=0;
        end


        car(i).state=1;
        car(i).t0=0;
        car(i).boom=0;

        car(i).changingv=0;

        car=car_plate_generate(car,i);

    end
end



function [road,light]=initiateRoadLight(road,light)

    r=road(1).width/2/cosd(0.5*(180-360/road(1).dir_n));
    theta0=180-(180-(360/road(1).dir_n))/2;
    theta=1/road(1).dir_n*360;

    road(1).shape=[  r*cosd(theta0),            r*cosd(theta0)    ;...
                     road(1).pic_l+10,                 r*sind(theta0);   ]; 

    x0=road(1).shape(1,1);
    y0=road(1).shape(2,1);
    x=road(1).shape(1,2);
    y=road(1).shape(2,2);
    [xx,yy]=rotatexy(theta,x0,y0,x,y);
    newroadshape=[xx;yy];
    road(1).shape=[road(1).shape,newroadshape];



    road(1).size=size(road(1).shape);
    %The size of a quarter of ROAD matrix
    road(1).set=[road(1).set road(1).shape];
    %store first quarter into ROADS


    light(1).position=[r*cosd(theta0)  ;...
                       r*sind(theta0) ];
    light(1).set=[light(1).set light(1).position];

    road(1).midline=[0                  0;...
                     r*sind(theta0)       road(1).pic_l+10];
    road(1).midlines=road(1).midline;            
    for i=1:round(road(1).lane_n/2)-1
       d=[-road(1).width/road(1).lane_n; 0];
       newmidline=road(1).midline+d.*i;
       road(1).midlines=[road(1).midlines, newmidline];

       newmidline=road(1).midline-d.*i;
       road(1).midlines=[road(1).midlines, newmidline];   
    end


    road(1).midlines_s=road(1).midlines;


    theta=1/road(1).dir_n*360;
    % x0=road(1).shape(1,1);
    % y0=road(1).shape(2,1);
    % x=road(1).shape(1,2);
    % y=road(1).shape(2,2);
    % road(1).shape=[road(1).shape(:,1), rotatexy(theta,x0,y0,x,y)*road(1).shape];

    %following lines will  store all parts into road,light and midline by rotation
      for i=2:road(1).dir_n

          road(i).shape=rotate(theta)*road(i-1).shape;%ROAD itself rotated by 90 degrees
          road(1).set=[road(1).set,road(i).shape];

          light(i).position=rotate(theta)*light(i-1).position;%light itself rotated by 90 degrees
          light(1).set=[light(1).set,light(i).position];

          road(i).midlines=rotate(theta)*road(i-1).midlines;
          road(1).midlines_s=[road(1).midlines_s,road(i).midlines];
      end
end

function [car,road,light]=mainloop(car,road,light)
    axis ([-road(1).pic_l,   road(1).pic_l  -road(1).pic_w    road(1).pic_w]);
    i=1;
    car(1).t_g=1;
    car(1).on_road=1;
    iscrash=zeros(1,3);
    while isAllOut(car,road)==0 && iscrash(1)==0
           clf;
                   road=draw_road(road);
                   light=draw_light(i/10,road,light);

                for b=1:car(1).on_road
                    if  i/car(1).on_road/(1+3*rand(1)) > car(1).length/car(1).velocity0 && car(1).on_road<car(1).n
                        car(1).on_road=car(1).on_road+1; %only when two car interval is long enough, a new car will be generated
                        car(car(1).on_road).t_g=i;
                    end


                    axis ([-road(1).pic_l,   road(1).pic_l  -road(1).pic_w    road(1).pic_w]);

                    car=car_state_change(i,car,b,road,light);    

                end
                drawnow;

          %axis ([-pic_l pic_l  -pic_w  pic_w]);  
          %hold on;
          i=i+1;

          iscrash=isCrash(car);
    end
end



function rot_mat=rotate(theta)
    rot_mat=[cosd(theta) -sind(theta) ;sind(theta) cosd(theta)];%the matrix which can rotate90 degrees when multiplied by a position matrix
    
end

% function TAT=rotatexym(theta,x0,y0,x,y)%it's a function to make point(x0,y0) to rotate theta degrees around x,y
%     T=[1,0,x-x0;...
%        0,1,y-y0;...
%        0,0,1;]*[x0;y0;1;];
%     A=[cosd(theta), -sind(theta),0;...
%        sind(theta),  cosd(theta),0;...
%        0,             0         ,1;]*[x0;y0;1;];
%     
%     TAT=T*A*inv(T);
%     
% %     rot_mat=[cosd(theta) -sind(theta) ;sind(theta) cosd(theta)];%the matrix which can rotate90 degrees when multiplied by a position matrix
% %     x = (x- light(dir).position(1))*cosd(angle) - (car(b).oy-light(dir).position(2))*sind(angle) + light(dir).position(1);		
% %     y = (car(b).oy- light(dir).position(2))*cosd(angle) + (car(b).ox-light(dir).position(1))*sind(angle) + light(dir).position(2);
% end

function [xx,yy]=rotatexy(theta,x0,y0,x,y)%it's a function to make point(x0,y0) to rotate theta degrees around (x,y)
     xx = (x0-x)*cosd(theta) - (y0-y)*sind(theta) + x;		
     yy = (x0-x)*sind(theta) + (y0-y)*cosd(theta) + y;
end

    %plot the roads  and midlines
function road=draw_road(road)
              fill(road(1).set(1,:),road(1).set(2,:),[0.8,0.8,0.8]);
          for i=1:road(1).dir_n
              line(road(i).shape(1,:),road(i).shape(2,:),'Color',[0.9,0.9,0.9],'linewidth',4/2.5*road(1).width/road(1).lane_n);
              hold on;
              for j=1:road(1).lane_n-1
                  line(road(i).midlines(1,j*2-1:j*2),road(i).midlines(2,j*2-1:j*2),'Color','y','linestyle','--','linewidth',3/2.5*road(1).width/road(1).lane_n);
                  hold on;
              end
          end
          
end
    
    %plot the lights
 function light=draw_lightini(road,light)
          for i=1:road(1).dir_n
              if mod(i,2)==1
                  line(light(i).position(1,:),light(i).position(2,:),'color','red','marker','.','markersize',40/2.5*road(1).width/road(1).lane_n);
                  %the function light1 will make lights in 1st and 3rd quadrant become red
                  hold on;
                  light(i).color='r';
              elseif mod(i,2)==0
                  line(light(i).position(1,:),light(i).position(2,:),'color','green','marker','.','markersize',40/2.5*road(1).width/road(1).lane_n);
                  hold on;
                  %the function light1 will make lights in 2nd and 4th quadrant become green
                  light(i).color='g';
              end
          end
 end
 
  function light=draw_light(t,road,light)%when a=1,the 1st and 3rd become red;when a=2,2nd and 4th become red
           if mod(t,(light(1).tr+light(1).tg+light(1).tt))<=light(1).tr
               a=1;
           elseif mod(t,(light(1).tr+light(1).tg+light(1).tt))<=light(1).tr+light(1).tg
               a=2;
           else
               a=3;
           end
          for i=1:road(1).dir_n
              if mod(i,2)==mod(a,2)
                  line(light(i).position(1,:),light(i).position(2,:),'color','red','marker','.','markersize',40/2.5*road(1).width/road(1).lane_n);
                  %the function light1 will make lights in 1st and 3rd quadrant become red

                  light(i).color='r';
              elseif mod(i,2)~=mod(a,2)
                  line(light(i).position(1,:),light(i).position(2,:),'color','green','marker','.','markersize',40/2.5*road(1).width/road(1).lane_n);

                  %the function light1 will make lights in 2nd and 4th quadrant become green
                  light(i).color='g';
              else
                  line(light(i).position(1,:),light(i).position(2,:),'color','blue','marker','.','markersize',40/2.5*road(1).width/road(1).lane_n);

                  %the function light1 will make lights in 2nd and 4th quadrant become green
                  light(i).color='b';
              end
          end
  end
  
  
  function car=car_state_change(t,car,b,road,light)
             reach=reachLight(car,b,light);
             
%              if t>= (road(1).width/road(1).lane_n)/car(b).velocity
                        switch car(b).state%state is a varieble to express whether the car have crossed the road:
                            case 1%1: not crossed 
                                if reach
                                        car=car_paint(car,b,0);
                                        if (light(car(b).odirection).color =='g')|| ( (light(car(b).odirection).color =='r')&& car(b).violation==1 )
                                           car=car_reach_greenlight(t,car,b,road,light);
                                        elseif (light(car(b).odirection).color =='b')
                                            car=car_reach_greenlight(t,car,b,road,light);
                                        elseif (light(car(b).odirection).color =='r')&& car(b).violation==0
                                            car(b).state=3;
                                        end
                                else
                                    car(b).velocity=car(b).velocity0;
                                    car=avoid_bump(car,b);
                                    car=car_go(car,b);
                                end 
                            case 2% stop when there're cars before this car stopped at the crossing
                                car_paint(car,b,0);
                                 if (light(car(b).odirection).color =='g')
                                     car(b).state=1;
                                 end
                            case 3%3:stop at the crossing 
                                car=change_velocity(t,1,car,b,car(b).velocity,0,0);
                                car=car_paint(car,b,0);
                                %car=change_velocity(t,2,car,b,car(b).velocity,0);
                                if reach && ((light(car(b).odirection).color =='g')||(light(car(b).odirection).color =='b'))
                                            car=car_reach_greenlight(t,car,b,road,light);  
                                            
                                end
                            case 4%4:go at the crossing(straight)
                                %car=avoid_bump(t,car,road);
                                car=change_velocity(t,1,car,b,car(b).velocity,car(1).velocity0,0);
                                car=car_go(car,b);
                                
                                if  anotherSide(car,b,road,light)
                                   car(b).state=7;
                                end
                            case 5% 5:turning right 5.turning left 6:have crossed 
                                car=change_velocity(t,1,car,b,car(b).velocity,car(b).velocity0,0);
                                car=car_right(t,car,b,road,light);
                                car=car_adjust(t,car,b,road,light);
                                if car(b).state==7
                                    car=car_paint(car,b,0);
                                end
                            case 6%6.turning left 
                                car=change_velocity(t,1,car,b,car(b).velocity,car(b).velocity0,0);
                                car=car_left(t,car,b,road,light);  
                                car=car_adjust(t,car,b,road,light);
                                 if car(b).state==7
                                    car=car_paint(car,b,0);
                                end
                            case 7%7:have crossed
                                car=car_go(car,b);
                                
                        end                       
             %end
  end 
  
  
  
  
  function car=car_reach_greenlight(t,car,b,road,light)
  if (t-car(b).t_g)*10>=(road(1).pic_l-road(1).width/2)/car(1).velocity0
      
                                            if car(b).lane==1 && road(1).lane_n > 2 &&road(1).dir_n==4 && (light(car(b).odirection).color =='b')% 1st lane is the lane to turn left
                                                car(b).t0=t;
                                                car(b).state=6;
                                            elseif car(b).lane==1 && road(1).lane_n > 2 &&road(1).dir_n==4 && (light(car(b).odirection).color =='g')    
                                                car(b).t0=t;
                                                car(b).state=6;
                                            elseif car(b).lane==(road(1).lane_n/2) && road(1).dir_n==4
                                                
                                                    ran=1*rand(1);%use an algorithm to adjust the possibility to turn or go straight
                                                    if ran<=0.01
                                                        car(b).state=4;
                                                        %return;
                                                    elseif ran<=1
                                                        car(b).t0=t;
                                                        car(b).state=5;
                                                        
                                                        %return;
                                                    end
                                            elseif( car(b).lane < road(1).lane_n && car(b).lane > 1  )|| road(1).dir_n~=4
                                                car(b).state=4;
                                                %return;
                                            end
  else
      car(b).state=4;
  end
 return;
  end
  
  
  
  function car=car_go(car,b)
                
                dir=car(b).direction2;
   
                    car(b).ox=car(b).ox+car(b).velocity*car(1).dx(dir);
                    car(b).oy=car(b).oy+car(b).velocity*car(1).dy(dir);
                    car=car_paint(car,b,0);
end
  


function car=car_right(t,car,b,road,light)
 
                dir=car(b).direction2;
                %dirl=mod(car(b).direction2-2,road(1).dir_n)+1;
                
                 dt=3;
                if t-car(b).t0<=1 %set up of the turning
                    car(b).state=5;
                    car(b).ox=car(b).oox(dir)+light(dir).position(1)+0.15*car(1).dx(dir)*car(b).length;
                    car(b).oy=car(b).ooy(dir)+light(dir).position(2)+0.15*car(1).dy(dir)*car(b).length;
                    car=car_paint(car,b,-5);
                elseif t-car(b).t0< dt+car(b).length/car(b).velocity/10%during turning
                
                i=t-car(b).t0;
                 %for i=1:dt
                    %int angle = 45 * i;//逆时针	
                    x=light(dir).position(1)*(1-0);%the rotation center
                    y=light(dir).position(2)*(1-0);
                        angle = -80/50* i* 4/road(1).dir_n/dt*10;%colckwise to turn right		
                        car(b).ox = (car(b).ox- x)*cosd(angle) - (car(b).oy-y)*sind(angle) +x;		
                        car(b).oy = (car(b).oy- y)*cosd(angle) + (car(b).ox-x)*sind(angle) +y;	
                        car=car_paint(car,b,angle);
                elseif t-car(b).t0>=dt+car(b).length/car(b).velocity/10 %finish turning
                    car(b).state=7;
                    car(b).direction2=mod(car(b).direction2-2,road(1).dir_n)+1;
                end
end


function car=car_right_yixinghuanying(t,car,b,road,light)%如果把car_right()函数换成这个，你的车将使出移形换影特技
                
                dir=car(b).direction2;
               
                
                if car(b).state==1
                    car(b).t0=t;
                    car(b).state=5;
                    
                end
                dt=10;
                %i=t-car(b).t0;
                for i=1:dt
                    %int angle = 45 * i;//逆时针	
                    t=t+1;
                        angle = -80/50* i* 4/road(1).dir_n;%colckwise to turn right		
                        car(b).ox = (car(b).ox- light(dir).position(1))*cosd(angle) - (car(b).oy-light(dir).position(2))*sind(angle) + light(dir).position(1);		
                        car(b).oy = (car(b).oy- light(dir).position(2))*cosd(angle) + (car(b).ox-light(dir).position(1))*sind(angle) + light(dir).position(2);		

                        car(b).shapet=rotate(angle)*car(b).shapet;
                        car(b).crashbox=rotate(angle)*car(b).crashbox;
                        x=car(b).shapet(1,:)+car(b).ox;
                        y=car(b).shapet(2,:)+car(b).oy;
                
                        
                        fill(x,y,car(b).color);
                        set(line,'xdata',x,'ydata',y,'Color','k');
                        
                        car(b).fill=rotate(angle)*car(b).fill;
                        x=car(b).fill(1,:)+car(b).ox;
                        y=car(b).fill(2,:)+car(b).oy;
                        fill(x,y,car(b).fillcolor(1));
                end
                 if t-car(b).t0>=dt+car(b).length*car(b).velocity0/5
                    car(b).state=6;
                     car(b).direction2=mod(car(b).direction2-2,road(1).dir_n)+1;
                %The car moves to another direction on its right so the parameter+1;
                 end
end

function car=car_left(t,car,b,road,light)
                
                dir=car(b).direction2;
                dirl=mod(car(b).direction2-2,road(1).dir_n)+1;
                
                dt=10;
                if t-car(b).t0<=1
                    car(b).state=6;
                    car(b).ox=car(b).oox(dir)+light(dir).position(1)+0.2*car(1).dx(dir)*car(b).length;
                    car(b).oy=car(b).ooy(dir)+light(dir).position(2)+0.2*car(1).dy(dir)*car(b).length;
                    car=car_paint(car,b,5);
                elseif t-car(b).t0< dt+car(b).length/car(b).velocity/10
                
                i=t-car(b).t0;
                 %for i=1:dt
                    %int angle = 45 * i;//逆时针	
                    x=light(dirl).position(1)*(1)+1*car(1).dx(dir);%the rotation center
                    y=light(dirl).position(2)*(1)+1*car(1).dy(dir);
                        angle = 80/50* i* 4/road(1).dir_n/dt*10;%colckwise to turn right		
                        car(b).ox = (car(b).ox- x)*cosd(angle) - (car(b).oy-y)*sind(angle) +x;		
                        car(b).oy = (car(b).oy- y)*cosd(angle) + (car(b).ox-x)*sind(angle) +y;		
                       car=car_paint(car,b,angle);
                elseif t-car(b).t0>=dt+car(b).length/car(b).velocity/10
                    car(b).state=7;
                    car(b).direction2=mod(car(b).direction2,road(1).dir_n)+1;
                end
end

  

function car=car_adjust(t,car,b,road,light)%function to adjust car's position when finish turning
         dir=car(b).direction2;
         dirl=mod(dir,road(1).dir_n)+1;
         if car(b).state~=7
             car(b).t1=t;%t1 is the time the car almost finish turning
         elseif car(b).state==7 %&& t-car(b).t1>=car(b).length/car(b).velocity0 % use this judgement to make the car wait a little time to go into the another lane to avoid bumping
                    car(b).ox=car(b).oox(dir)+light(dirl).position(1)+0.4*car(1).dx(dir)*car(b).velocity0;
                    car(b).oy=car(b).ooy(dir)+light(dirl).position(2)+0.4*car(1).dy(dir)*car(b).velocity0;

                    theta=(car(b).direction2-car(b).odirection)/road(1).dir_n*360;
                    car(b).shapet=rotate(theta)*car(b).shape;
                    car(b).crashbox=rotate(theta)*car(b).crashbox;

                    car(b).fill1=rotate(theta)*car(b).fills(1:2,:);
                    car(b).fill2=rotate(theta)*car(b).fills(3:4,:);
         end
end



function car=car_plate_generate(car,i)
    car(i).plate = car(1).plate_lib(round(unifrnd(1,length(car(1).plate_lib),1,car(1).plate_n)));

    if i>size(car,2)
         return;
    end
    
    if i>1
        for j=1:i-1
            if car(j).plate==car(i).plate
                car_plate_generate(car,i);
                return;
            end
        end
    end
    return;
end


function car=change_velocity(t,dt,car,b,v0,vt,flag)%t0 is the instant of time start to change speed
                                                  %t is the current time
                                                  %dt is the time used to change speed
                                                  %v0 is the origin velocity
                                                  %vt is the velocity after dt
                                                  %flag is whether paint the car
if car(b).changingv==0
    car(b).changingv=t;
end

t0=car(b).changingv;
car(b).velocity=v0+(t-t0)*(vt-v0)/dt;


if flag
    car=car_paint(car,b,0);
end

if t-car(b).changingv>=dt
    car(b).changingv=0;
    return;
end
                 
end






function car=avoid_bump(car,b)
dir=car(b).direction2; 
if (dir==1 || dir==3)
    for i=1:car(1).on_road
        if i~=b  && car(i).odirection==car(b).odirection && car(i).lane==car(b).lane && abs(car(i).oy-car(b).oy)<=2.2*car(b).length
            car(b).state=2;
        end
    end
elseif (dir==2 || dir==4)
    for i=1:car(1).on_road
        if i~=b  && car(i).odirection==car(b).odirection && car(i).lane==car(b).lane && abs(car(i).ox-car(b).ox)<=2.2*car(b).length
            car(b).state=2;
        end
    end
end
end


function another=anotherSide(car,b,road,light)%It judge whether the car reach another side of the crossing
dirl=mod(car(b).odirection,road(1).dir_n)+1;
    if ((mod(car(b).odirection,2)==1 )&& (light(dirl).position(2)-car(b).oy-0.25*car(b).length)<=0.0001 )...
     ||((mod(car(b).odirection,2)==0) && (light(dirl).position(1)-car(b).ox-0.25*car(b).length)<=0.0001 )
        another=1;
    else
        another=0;
    end
return
end



function reach=reachLight(car,b,light)%It judge whether the car reach the traffic light
dir=car(b).odirection;
    if ((dir==1 ||dir==3) && abs(light(dir).position(2)-(car(b).oy+car(b).dy(dir)*0.5*car(b).length))<=2*car(1).velocity0)...
     ||((dir==2 ||dir==4) && abs(light(dir).position(1)-(car(b).ox+car(b).dx(dir)*0.5*car(b).length))<=2*car(1).velocity0)
        reach=1;
    else
        reach=0;
    end
return;
end


function cross=GetCross(p1x,p1y, p2x,p2y, px,py) %get |p1 p2| X |p1 p|
cross=(p2x - p1x) * (py - p1y) - (px - p1x) * (p2y - p1y);
return
end
% 
function isPointIn=IsPointInMatrix(p1x,p1y, p2x,p2y,p3x,p3y,p4x,p4y, px,py)
isPointIn = GetCross(p1x,p1y,p2x,p2y,px,py) * GetCross(p3x,p3y, p4x,p4y, px,py) >= 0 ...
    && GetCross(p2x,p2y, p3x,p3y, px,py) * GetCross(p4x,p4y, p1x,p1y, px,py) >= 0;
return
end

function [iscrash,i,j]=isCrash(car)
iscrash=0;
for a=1:car(1).on_road
    for b=1:car(1).on_road
        for k=1:4
            p1x=car(a).ox+car(a).crashbox(1,1);
            p1y=car(a).oy+car(a).crashbox(2,1);
            p2x=car(a).ox+car(a).crashbox(1,2);
            p2y=car(a).oy+car(a).crashbox(2,2);
            p3x=car(a).ox+car(a).crashbox(1,3);
            p3y=car(a).oy+car(a).crashbox(2,3);
            p4x=car(a).ox+car(a).crashbox(1,4);
            p4y=car(a).oy+car(a).crashbox(2,4);
            px=car(b).ox+car(b).crashbox(1,k);
            py=car(b).oy+car(b).crashbox(2,k);
                if a~=b && IsPointInMatrix(p1x,p1y, p2x,p2y,p3x,p3y,p4x,p4y, px,py)
                    iscrash=1;
                    i=a;
                    j=b;
                    return;
                end
                
        end
    end
end
end


function car=car_paint(car,b,angle)
               car(b).shapet=rotate(angle)*car(b).shapet;
               car(b).crashbox=rotate(angle)*car(b).crashbox;
               x=car(b).shapet(1,:)+car(b).ox;
               y=car(b).shapet(2,:)+car(b).oy;
                
               fill(x,y,car(b).color);
               line('xdata',x,'ydata',y,'Color','k');
               car(b).fill1=rotate(angle)*car(b).fill1;
               x=car(b).fill1(1,:)+car(b).ox;
               y=car(b).fill1(2,:)+car(b).oy;
               fill(x,y,car(b).fillcolor(1));
               
               car(b).fill2=rotate(angle)*car(b).fill2;
               x=car(b).fill2(1,:)+car(b).ox;               
               y=car(b).fill2(2,:)+car(b).oy;
               fill(x,y,car(b).fillcolor(2));

end



function isO=isOut(car,b,road)
if car(b).ox>=road(1).pic_l || car(b).oy>=road(1).pic_l...
    || car(b).ox<=-road(1).pic_l || car(b).oy<=-road(1).pic_l
    isO=1;
else
    isO=0;
end
end

function isAO=isAllOut(car,road)
flag=1;
for i=1:size(car,2)
    if  car(i).state~=7
        flag=0;
    end
    if isOut(car,i,road)==0
        flag=0;
    end
end
isAO=flag;
end

function print_violation(car)
disp('the following are the plates of cars which break the traffic rule:');
for i=1:size(car,2)
    if car(i).violation==1
        disp(car(i).plate);
    end
end
end

function ending(car,road)
    print_violation(car);
    iscrash=isCrash(car);
    if isAllOut(car,road)==1
        clf;
        x=imread('win.jpg');
        imshow(x);
    elseif iscrash(1)==1
        clf;
        x=imread('lose.jpg');
        imshow(x);
    end
end