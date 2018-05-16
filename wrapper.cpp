#include "wrapper.hpp"

void simulate_system( space_system* space , double time , double& march , int method , 
	bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 )
{
	void (*space_function)( double , vector<double>* , vector<double>* , vector<double>* );
	ode_solvers::ODESOLVER( space_function , time , march , &((*space).n_mass) , &((*space).n_state) , &((*space).n_state_dot) , method );

	return;
}