#include "ode_solver.hpp"

void ode_solvers::forward_euler( void (*function)(double , int , vector<body>* , body* ),
	double time , double march , vector<body>* bodies_input , vector<body>* bodies_slope )
{
	// find the number of bodies in the system
	int n_bodies = (*bodies_input).size();

	// make sure the slope vector is empty
	(*bodies_slope).erase( (*bodies_slope).begin(), (*bodies_slope).end());
	
	// for each body , find the pdot vector
	for ( int i = 0 ; i < n_bodies ; i++ ){
		// create a copy of the current body
		body copy_body( &((*bodies_input)[i]) );
		// find the forces/ acceleration acting on current body
			// after this step, copy_body will have the updated acceleration
			// but positions and velocities are not updated
		function( time , i , bodies_input , &copy_body );		

		// now push_back the acceleration into the slope vector
		(*bodies_slope).push_back(copy_body);
	}
	return;
}

// void ode_solvers::update_states( double march , vector<body>* bodies_slope , vector<body>* bodies_output )
// {
// 	int n_bodies = (*bodies_slope).size();
// 	(*bodies_output).erase( (*bodies_output).begin(), (*bodies_output).end());

// 	for ( int i = 0 ; i < n_bodies ; i++ ){
// 		body copy_body( (*bodies_slope)[i]);
// 		vector<double> pos_update , vel_update;
// 		scaleVector( march , &(copy_body.velocity) , &pos_update );
// 		scaleVector( march , &(copy_body.acceleration) , &vel_update );
// 		vectorSum( &pos_update , &(copy_body.position) , &(copy_body.position) );
// 		vectorSum( &vel_update , &(copy_body.velocity) , &(copy_body.velocity) );
// 		(*bodies_output).push_back(copy_body);
// 	}
// 	return;
// }

void ode_solvers::ODE_SOLVER( void (*function)(double , int , vector<body>* , body* ) , 
		double time , double march , vector<body>* bodies_input , vector<body>* bodies_output , int method )
{
		
}