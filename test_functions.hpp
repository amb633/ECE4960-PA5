/* header file to define testing functions */
#pragma once
#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"
#include "wrapper.hpp"

// tests for the celestial body functions
bool test_space_transform();
bool test_reverse_space_transform();
bool test_acceleration_calculation();

// tests for the ode solver functions
bool test_forward_euler();
bool test_heun_one();
bool test_heun_iterative();
bool test_non_adaptive_rk34();
bool test_adaptive_rk34();

// arbitarty ode function to test for correctness
// based on exponential function from hacker practices
void ode_exponential_function ( double time , vector<double>* parameters , 
	vector<double>* input , vector<double>* output );

// test for the interface between celestial functions and ode functions
bool test_wrapper();

