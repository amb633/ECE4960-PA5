clc , clear , close all;

days = 10;

names = [ "sun" , "mercury" , "venus" , "earth" , "mars" ];

mass = [ 2e30 ; 3.285e23 ; 4.8e24 ; 6e24 ; 2.4e24 ];

positions = [ 0 , 0 , 0 ;
            0 , 5.7e10 , 0;
            0 , 1.1e11 , 0;
            0 , 1.5e11 , 0;
            0 , 2.2e11 , 0];
velocities = [ 0 , 0 , 0 ;
               47000 , 0 , 0;
               35000 , 0 , 0;
               30000 , 0 , 0;
               24000 , 0 , 0];

sun_position_log = zeros( days+1 , 3 );
mercury_position_log = zeros( days+1 , 3 );
venus_position_log = zeros( days+1 , 3 );
earth_position_log = zeros( days+1 , 3 );
mars_position_log = zeros( days+1 , 3 );

sun_position_log( 1 , : ) = positions( 1 , : );
mercury_position_log( 1 , : ) = positions( 2 , : );
venus_position_log( 1 , : ) = positions( 3 , : );
earth_position_log( 1 , : ) = positions( 4 , : );
mars_position_log( 1 , : ) = positions( 5 , : );

march = 24*60*60;

for day = 1:days
    %% calculate the accelerations of each body
    time = day * 24 * 60 * 60;
%     [ accelerations , march ] = forward_euler( time , march , mass , positions );
    [ accelerations , march ] = RK34( time , march , mass , positions , false , 1e-4 , 1e-7 );

    %% calculate position update
    
    positions = positions + velocities * march;

    %% calculate the velocity update
    velocities = velocities + accelerations * march;
    
    sun_position_log( day+1 , : ) = positions( 1 , : );
    mercury_position_log( day+1 , : ) = positions( 2 , : );
    venus_position_log( day+1 , : ) = positions( 3 , : );
    earth_position_log( day+1 , : ) = positions( 4 , : );
    mars_position_log( day+1 , : ) = positions( 5 , : );
    
end

figure(1); hold on;
plot3( sun_position_log(:,1) , sun_position_log(:,2) , sun_position_log(:,3) , ...
        'ro' , 'MarkerSize' , 14 , 'MarkerFaceColor' , 'r' );
plot3( mercury_position_log(:,1) , mercury_position_log(:,2) , mercury_position_log(:,3) );
plot3( venus_position_log(:,1) , venus_position_log(:,2) , venus_position_log(:,3) );
plot3( earth_position_log(:,1) , earth_position_log(:,2) , earth_position_log(:,3) );
plot3( mars_position_log(:,1) , mars_position_log(:,2) , mars_position_log(:,3) );