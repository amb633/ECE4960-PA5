function [ slope , march ] = forward_euler( time , march , parameters , input )
% Forward Euler method of calculating the slope of a function

slope = find_state_dot( time , parameters , input );

end

