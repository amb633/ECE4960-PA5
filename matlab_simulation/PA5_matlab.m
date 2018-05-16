clc , clear , close all;

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

for day = 1:10
    %% calculate the accelerations of each body
    accelerations = find_state_dot ( mass , positions );

    %% calculate position update
    march = 24*60*60;
    positions = positions + velocities * march;

    %% calculate the velocity update
    velocities = velocities + accelerations * march;
    
    %% display the information
    disp ( "day = " ); disp ( day );
    for i = 1:length(mass)
        disp( names(i) );
        %disp( mass(i) );
        disp( positions(i,:) );
        disp( velocities(i,:) );
        disp( accelerations(i,:) );
    end
end