#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"

int main ( void )
{
	cout << endl;
	cout << " --------------- Testing Celestial Body Functions --------------- " << endl;

	// create three planets and stack them into a vector
	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { -1.0 , 0.5 , 0.25 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 5.0 , 3.0 , 1.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B , planet_C};

	// transform the bodies to a space system
	space_system space;
	create_system ( &bodies , &space );

	// check if the transformation is correct
	cout << "...testing if transformation is correct... " << endl;
	cout << endl << "planet masses are : " << endl;
	printVector( &(space.n_mass) );
	cout << endl << endl << "n_state of space :" << endl;
	printMatrix( &(space.n_state) );
	cout << endl << endl << "n_state_dot of space :" << endl;
	printMatrix( &(space.n_state_dot) );
	cout << endl << endl;

	// transform from space system back to body system
	cout << "...testing if reverse transformation is correct... " << endl;
	vector<body> bodies_resolved;
	resolve_system( &space , &bodies_resolved );
	for ( int i = 0 ; i < bodies_resolved.size() ; i++ ){
		print_body( &bodies_resolved[i] );
	}

	cout << "...testing if acceleration function is correct... " << endl;
	bodies.pop_back();
	vector<double> acceleration_a;
	space_system space_two;
	create_system( &bodies , &space_two );
	find_state_dot( 0.0 , 0 , &space_two.n_mass, &space_two.n_state , &acceleration_a );
	cout << " acceleration of A in 02 body system : ";
	printVector( &acceleration_a );
	
	find_state_dot( 0.0 , 0 , &space.n_mass, &space.n_state , &acceleration_a );
	cout << " acceleration of A in 03 body system : ";
	printVector( &acceleration_a );

	cout << endl << endl;

	cout << " --------------- Testing ODE Solver Functions --------------- " << endl;


	cout << endl;
	return 0;
}
