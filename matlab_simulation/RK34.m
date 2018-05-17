function [slope , march] = RK34(time , march , parameters , input , ...
                                  adaptive , e_rel , e_abs )
% RK34 method of calculating the slope of a function

k1 = find_state_dot( time , parameters , input );
k2 = find_state_dot( time + 0.5*march , parameters , input + (0.5*march*k1) );
k3 = find_state_dot( time + 0.75*march , parameters , input + (0.75*march*k2) );
k4 = find_state_dot( time + march , parameters , input + march*k3 );

if ( adaptive ) 
    error = rk34_error( march , k1 , k2 , k3 , k4 );
    march = find_new_march( input , march , error , e_rel , e_abs );
end

sum_k = 7.0*k1 + 6.0*k2 + 8.0*k3 + 3.0*k4;
slope = sum_k / 24;

end

function error = rk34_error( march , k1 , k2 , k3 , k4 )
    k1 = -5.0*k1;
    k2 = 6.0*k2;
    k3 = 8.0*k3;
    k4 = -9.0*k4;
    
    k_sum = k1 + k2 + k3 + k4;
    error_vector = (march/72)*k_sum;
    error = norm( error_vector );
end

function march = find_new_march( input , march , error , e_rel , e_abs )
xn = norm( input );
temp = error / ( xn + e_abs );
temp = e_rel/temp;
march = march * ( temp ^ (1/3) );
end