#include "test_functions.hpp"

bool test_wrapper() 
{
	cout << endl << "...creating the inner solar system..."<< endl;
	// create the five inner bodies with name , mass , initial positions and initial velocities
	body sun	( "sun" , 2.0e30 	, { 0.0 , 0.0 , 0.0 } 	 , { 0.0 , 0.0 , 0.0 });
	body mercury( "mercury" , 3.285e23 	, { 0.0 , 5.7e10 , 0.0 } , { 47000 , 0.0 , 0.0 });
	body venus 	( "venus" , 4.8e24 	, { 0.0 , 1.1e11 , 0.0 } , { 35000 , 0.0 , 0.0 });
	body earth 	( "earth" , 6.0e24 	, { 0.0 , 1.5e11 , 0.0 } , { 30000 , 0.0 , 0.0 });
	body mars 	( "mars" , 2.4e24 	, { 0.0 , 2.2e11 , 0.0 } , { 24000 , 0.0 , 0.0 });

	// create a vector of the bodies
	vector<body> bodies = { sun , mercury , venus , earth , mars };

	// create information to store the true values for 10th day
	body sun_10	 	( "sun" , 2.0e30 	, { 1364.66 , 18083.8 , 0.0 } , { 0.0058695 , 0.0460192 , 0.0 });
	body mercury_10	( "mercury" , 3.285e23 	, { 3.80845e+010 , 4.37595e+010 , 0.0 } , { 36.2881e+003 , -32.4228e+003 , 0.0});
	body venus_10 	( "venus" , 4.8e24 	, {29.9702e+009 , 106.3188e+009 , 0.0000e+000} , {33.8340e+003 , -9.3951e+003 , 0.0});
	body earth_10 	( "earth" , 6.0e24 	, {25.8284e+009 , 148.0123e+009 , 0.0000e+000} , {29.6032e+003 , -5.0968e+003 , 0.0});
	body mars_10	( "mars" ,  2.4e24  , {20.7127e+009 , 219.0742e+009 , 0.0000e+000} , {23.8990e+003 , -2.3792e+003 , 0.0});

	vector<body> bodies_10 = { sun_10 , mercury_10 , venus_10 , earth_10 , mars_10 };

	cout << "...running the inner solar system with forward euler..." << endl;

	// transform to a flattened structure
	space_system solar_system;
	create_system( &bodies , &solar_system );

	// create a vector to store checkpoints at each time-step
	vector<vector<double>> system_states;
	system_states.push_back( solar_system.n_state ); // push in the initial positions
	double march = 24.0*60.0*60.0; // march should be in seconds
	double time = 0.0;	//starting time

	// run the system for 10 days
	for ( size_t i = 0 ; i < 10 ; i++ ){
		time = i*march; // calculate the current time in seconds
		// simulate_system() updates the solar_system variable dynamically, a new variable is NOT created
		simulate_system( &solar_system , time , march , FORWARD_EULER );
		// push in the current checkpoint of the system
		system_states.push_back( solar_system.n_state );
	}

	// reverse the system back to body specific information
	vector<body> bodies_resolved;
	resolve_system( &solar_system , &bodies_resolved );

	// compare information for each body
	bool flag = true;
	for ( int i = 0 ; i < 5 ; i++ ){
		// print_body( &bodies_resolved[i] );
		vector<double> pos_diff , vel_diff;
		vectorDiff( &bodies_resolved[i].position , &bodies_10[i].position , &pos_diff );
		for ( int p = 0 ; p < pos_diff.size() ; p++ ) {
			if ( abs(pos_diff[p]) > 1e5 ) flag = false;
		}
		vectorDiff( &bodies_resolved[i].velocity , &bodies_10[i].velocity , &vel_diff );
		for ( int v = 0 ; v < vel_diff.size() ; v++ ){
			if ( abs(vel_diff[v]) > 1e5 ) flag = false;
		}
	}
	return flag;
}