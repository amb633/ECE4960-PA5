#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"

int main ( void )
{
	cout << endl;

	celestial_functions::body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { 0.0 , 0.0 , 0.0 } );
	celestial_functions::body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 0.0 , 0.0 , 0.0 } );
	celestial_functions::body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<celestial_functions::body> celestial_bodies;
	celestial_bodies.push_back( planet_A );
	celestial_bodies.push_back( planet_B );
	celestial_bodies.push_back( planet_C );

	vector<double> acceleration_A;
	celestial_functions::find_acceleration( 0.0 , 0 , &celestial_bodies , &acceleration_A );

	printVector( &acceleration_A );
	celestial_functions::printBody ( &planet_A );
	return 0;
}