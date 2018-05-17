function [accelerations] = find_state_dot( ~ , mass, positions)
%Function to calculate the acceleration of each body
    %given the whole systems mass and position
    
g_const = 6.67408e-11;
accelerations = zeros( size(positions,1) , size(positions,2) );    

for id = 1:length( mass )
    current_pos = positions( id , : );
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
end

