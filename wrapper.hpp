#pragma once

#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"

void simulate_system( space_system* space , double time , double& march , int method , 
	bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 );