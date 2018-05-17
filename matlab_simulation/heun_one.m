function [slope , march] = heun_one(time , march , parameters , input)
% One step heun method of calculating the slope of a function

[ update , march ] = forward_euler( time , march , parameters , input );
prediction = ( update*march) + input;

f1 = find_state_dot( time , parameters , input );
f2 = find_state_dot( time + march , parameters , prediction );

slope = 0.5*( f1 + f2 );

end

