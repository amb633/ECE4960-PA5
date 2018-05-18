#include "wrapper.hpp"

/* wrapper to interface between the ode solvers and the celestial body functions 
 * finds the slope of the system in the current time step
 * returns the state of the system in the next time step
 */

void simulate_system( space_system* space , double time , double& march , int method , 
	bool adaptive , double e_rel , double e_abs )
{
	vector<double> update;
	void (*space_function)( double , vector<double>* , vector<double>* , vector<double>* ) = find_state_dot;
	ode_solvers::ODE_SOLVER( space_function , time , march , &((*space).n_mass) , &((*space).n_state) , &((*space).n_state_dot) , method );
	scaleVector( march , &((*space).n_state_dot) , &update );
	vectorSum( &((*space).n_state) , &update , &((*space).n_state) );

	return;
}
