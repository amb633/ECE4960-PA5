clc , clear , close all;

g_const = 6.67408e-11;

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
accelerations = zeros( size(positions,1) , size(positions,2) );    

%% calculate the accelerations of each body

for id = 1:length( mass )
    current_mass = mass(id);
    current_pos = positions(id , :);
    current_vel = velocities(id, :);
    acc = zeros(3,1);

    for i = 1:length(mass)
        if i == id 
            continue;
        end
        other_pos = positions( i , : );
        den = (norm(current_pos - other_pos))^3.0;
        num = (mass(i))*(current_pos - other_pos);
        acc = acc + (num/den)';
    end
    acc = -g_const*acc;
    accelerations(id , : ) = acc;
end

%% calculate position update
march = 1.0;
positions = positions + velocities * march;

%% calculate the velocity update
velocities = velocities + accelerations * march;