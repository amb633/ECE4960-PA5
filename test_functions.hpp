#pragma once
#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"

bool test_space_transform();
bool test_reverse_space_transform();
bool test_acceleration_calculation();

bool test_forward_euler();
bool test_heun_one();
bool test_non_adaptive_rk34();
bool test_adaptive_rk34();

void ode_exponential_function ( double time , vector<double>* parameters , 
	vector<double>* input , vector<double>* output );