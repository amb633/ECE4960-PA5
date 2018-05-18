#pragma once

#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"

/* wrapper to interface between the ode solvers and the celestial body functions
 * takes in 4 arguments :
 *	i) current space system
 *	ii) current time
 *	iii) current time step
 *	iv) solver method 
 *
 * and 3 optional arguments
 *	i) adaptivity for time stepping -> default is false
 *	ii) relative error threshold -> default is 1e-4
 *  iii) absolute error threshold -> default is 1e07
 *
 * returns the state of the system in the next time step
 */

void simulate_system( space_system* space , double time , double& march , int method , 
	bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 );