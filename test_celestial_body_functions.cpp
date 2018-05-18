#include "test_functions.hpp"

/* function to test if transform form body specific format to system specific format is working */
bool test_space_transform()
{
	bool flag = true;

	// create three planets and stack them into a vector
	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { -1.0 , 0.5 , 0.25 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 5.0 , 3.0 , 1.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B , planet_C};

	// transform the bodies to a space system
	space_system space;
	create_system ( &bodies , &space );

	// true values for checking correctness
    vector<double> true_state = { 2.0 , 5.0 , 8.0 , -1.0 , 0.5 , 0.25 , 
							3.0 , 7.5 , 10.0 , 5.0 , 3.0 , 1.0 , 
							5.0 , 3.0 , -4.0 , 0.0 , 0.0 , 0.0 };

	vector<double> two_planet_states = { -1.0 , 0.5 , 0.25 , 0.0 , 0.0 , 0.0 , 
								5.0 , 3.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
								0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 };

    // test for correctness
	if ( space.n_mass[0] != 10.0 || space.n_mass[1] != 8.0 || space.n_mass[2] != 50.0 )
		flag = false;

	if ( space.n_state !=  true_state )
		flag = false;

	if ( space.n_state_dot !=  two_planet_states )
		flag = false;

	return flag ;
}

/* function to test if transform form system specific format to body specific format is working */
bool test_reverse_space_transform()
{
	bool flag = true;

	// create three planets and stack them into a vector
	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { -1.0 , 0.5 , 0.25 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 5.0 , 3.0 , 1.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B , planet_C};

	// transform the bodies to a space system
	space_system space;
	create_system ( &bodies , &space );

	// transform from space system back to body system
	vector<body> bodies_resolved;
	resolve_system( &space , &bodies_resolved );

	// check if the resolved bodies are identical to the original bodies
    for ( int i = 0 ; i < bodies_resolved.size() ; i++ ){
        // print_body( &bodies_resolved[i] );
        if ( bodies_resolved[i].mass != bodies[i].mass )
        	flag = false;
        if ( bodies_resolved[i].position != bodies[i].position )
        	flag = false;
        if ( bodies_resolved[i].velocity != bodies[i].velocity )
        	flag = false;
        if ( bodies_resolved[i].acceleration != bodies[i].acceleration )
        	flag = false;
    }
    return flag;
}

/* function to test the find_state_dot() function */
bool test_acceleration_calculation()
{
	bool flag = true;

	// create three planets and stack them into a vector
	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { -1.0 , 0.5 , 0.25 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 5.0 , 3.0 , 1.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B};

	// transform the bodies to a space system
	space_system space;
	create_system ( &bodies , &space );

	// first test a two body system
	vector<double> two_planet_derivative;
	find_state_dot( 0.0 , &space.n_mass , &space.n_state , &two_planet_derivative );

	// true values from hand calculation
	vector<double> two_planet_states = { -1.0 , 0.5 , 0.25 , 1.41499e-011  , 3.53747e-011  , 2.82998e-011 , 
										5.0 , 3.0 ,  1.0  , -1.76873e-011  , -4.42184e-011  , -3.53747e-011};
	
	// check if the values are within a small error bound
	vectorDiff( &two_planet_states , &two_planet_derivative , &two_planet_derivative );
	
	for ( int i = 0 ; i < two_planet_derivative.size() ; i++ ){
		if ( abs(two_planet_derivative[i]) > 1.0e-16 ) flag = false;
	}

	// now test a three body system
	bodies.push_back( planet_C );
	create_system( &bodies , &space );

	vector<double> three_planet_derivative;
	find_state_dot( 0.0 , &space.n_mass , &space.n_state , &three_planet_derivative );

	// true values from hand calculation
	vector<double> three_planet_states = { -1.0 , 0.5 , 0.25 , 1.92389e-11 , 3.1982e-11 , 7.94372e-12 ,
											5.0 , 3.0 , 1.0 , -1.56455e-11 , -4.88125e-11 , -4.96674e-11 ,
											0.0 , 0.0 , 0.0 , -1.34449e-12 , 1.41359e-12 , 6.35805e-12 };

	// check if the values are within a small error bound
	vectorDiff( &three_planet_states , &three_planet_derivative , &three_planet_derivative );

	for ( int i = 0 ; i < three_planet_derivative.size() ; i++ ){
		if ( abs(three_planet_derivative[i] ) > 1.0e-16 ) flag = false;
	}
	return flag;
}