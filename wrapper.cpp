#include "wrapper.hpp"

void simulate_system( space_system* space , double time , double& march , int method , 
	bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 )
{
	vector<double> update;
	void (*space_function)( double , vector<double>* , vector<double>* , vector<double>* ) = find_state_dot;
	ode_solvers::ODE_SOLVER( space_function , time , march , &((*space).n_mass) , &((*space).n_state) , &((*space).n_state_dot) , method );
	scaleVector( march , &((*space).n_state_dot) , &update );
	vectorSum( &((*space).n_state) , &update , &((*space).n_state) );

	return;
}
