#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"

int main ( void )
{
	cout << endl;
	cout << " --------------- Testing Celestial Body Functions --------------- " << endl;

	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { 0.0 , 0.0 , 0.0 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 0.0 , 0.0 , 0.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B , planet_C};

	space_system space;

	create_system ( &bodies , &space );

	printVector( &(space.n_mass) );
	cout << endl << endl << " n_state of space :" << endl;
	printMatrix( &(space.n_state) );
	cout << endl << endl << " n_state_dot of space :" << endl;
	printMatrix( &(space.n_state_dot) );
	cout << endl << endl;

	vector<body> bodies_resolved;

	resolve_system( &space , &bodies_resolved );
	for ( int i = 0 ; i < bodies_resolved.size() ; i++ ){
		print_body( &bodies_resolved[i] );
	}

	cout << endl;
	return 0;
}