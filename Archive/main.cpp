#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solver.hpp"

int main ( void )
{
	cout << endl;

	cout << " --------------- Testing Celestial Body Functions --------------- " << endl;

	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { 0.0 , 0.0 , 0.0 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 0.0 , 0.0 , 0.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> celestial_bodies;
	celestial_bodies.push_back( planet_A );
	celestial_bodies.push_back( planet_B );

	printBody ( &planet_A );

	body acceleration_A( &planet_A );
	find_acceleration( 0.0 , 0 , &celestial_bodies , &acceleration_A );
	printBody( &acceleration_A );

	celestial_bodies.push_back( planet_C );
	find_acceleration( 0.0 , 0 , &celestial_bodies , &acceleration_A );
	printBody( &acceleration_A );

	cout << endl << endl;
	return 0;
}