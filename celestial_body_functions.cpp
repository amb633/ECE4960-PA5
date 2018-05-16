#include "celestial_body_functions.hpp"

void print_body( body* which_body )
{
	cout << endl;
	cout << " mass of body : " << (*which_body).mass << endl;
	cout << " position of body : " ; printVector( &((*which_body).position) );
	cout << " velocity of body : " ; printVector( &((*which_body).velocity) );
	cout << " acceleration of body : " ; printVector( &((*which_body).acceleration) );
	cout << endl;
	return;
}

void clear_system( space_system* space )
{
	(*space).n_mass.erase( (*space).n_mass.begin(), (*space).n_mass.end());
	(*space).n_state.erase( (*space).n_state.begin(), (*space).n_state.end());
	(*space).n_state_dot.erase( (*space).n_state_dot.begin(), (*space).n_state_dot.end());
	return;
}

void create_system ( vector<body>* bodies , space_system* space )
{
	vector<double> mass;
	vector<vector<double>> state; // p = [ x y z xdot ydot zdot ]
	vector<vector<double>> state_dot;	// pdot = [ xdot ydot zdot xdotdot ydotdot zdotdot ]

	int n_bodies = (*bodies).size();
	for ( int i = 0 ; i < n_bodies ; i++ ){
		
		mass.push_back( (*bodies)[i].mass );
		
		vector<double> current_position = (*bodies)[i].position;
		vector<double> current_velocity = (*bodies)[i].velocity;
		vector<double> current_acceleration = (*bodies)[i].acceleration;

		// concatenate the position and the velocity
		current_position.insert( current_position.end() , current_velocity.begin() , current_velocity.end() );
		state.push_back( current_position );

		// concatenate the velocity and the acceleration
		current_velocity.insert( current_velocity.end() , current_acceleration.begin(), current_acceleration.end() );
		state_dot.push_back( current_velocity );
	}

	clear_system( space );
	(*space).n_mass = mass;
	(*space).n_state = state;
	(*space).n_state_dot = state_dot;
	return;
}

void resolve_system( space_system* space , vector<body>* bodies )
{
	(*bodies).erase( (*bodies).begin(), (*bodies).end());

	int n_bodies = (*space).n_mass.size();
	for ( int i = 0 ; i < n_bodies ; i++ ){
		body current_body;
		current_body.mass = (*space).n_mass[i];

		// cout << "x position of planet : " << (*space).n_state[i][0] << endl;
		current_body.position[0] = ( (*space).n_state[i][0] );
		current_body.position[1] = ( (*space).n_state[i][1] );
		current_body.position[2] = ( (*space).n_state[i][2] );

		current_body.velocity[0] = ( (*space).n_state[i][3] );
		current_body.velocity[1] = ( (*space).n_state[i][4] );
		current_body.velocity[2] = ( (*space).n_state[i][5] );

		current_body.acceleration[0] = ( (*space).n_state_dot[i][3] );
		current_body.acceleration[1] = ( (*space).n_state_dot[i][4] );
		current_body.acceleration[2] = ( (*space).n_state_dot[i][5] );


		(*bodies).push_back( current_body );
	}
	return;
}

void find_state_dot( double time , int which_body , vector<double>* body_masses , 
	vector<vector<double>>* body_states , vector<double>* state_dot )
{
	// gravitational constant
	double g_const = 6.67408e-11; //m3 kg-1 s-2

	// find the number of bodies in the system
	int n_bodies = (*body_masses).size();

	// clear any memory in state_dot and initialize with zeros
	zeroVector( 6 , state_dot );
	// extract the position of the body of interest
		// remember the state is : state = [ x , y , z , xdot , ydot , zdot ]
		// so need to erase the last three elements to ensure vector only has the positions
		// but we need the velocity for the first three elements of state_dot
	vector<double> current_body = (*body_states)[which_body];
	(*state_dot)[0] = current_body[3];
	(*state_dot)[1] = current_body[4];
	(*state_dot)[2] = current_body[5];
	current_body.erase( current_body.end() - 3 , current_body.end() );

	// create a 3x1 zero vector for acceleration
	vector<double> acceleration;
	zeroVector( 3 , &acceleration );

	for ( int i = 0 ; i < n_bodies ; i++ ){
		if ( i == which_body ) continue;

		// extract position of other body;
		vector<double> other_body = (*body_states)[i];
		other_body.erase( other_body.end() - 3 , other_body.end() );

		// find the euclidean distance between the two bodies and cube it
		double distance;
		vectorNorm( &current_body , &other_body , distance );
		distance = pow( distance , 3.0 );

		// find displacement of other body from current body
		vector<double> displacement;
		vectorDiff( &current_body , &other_body , &displacement );

		// multiply the displacement by the mass of the other body
		scaleVector( (*body_masses)[i] , &displacement , &displacement );
		// divide by the euclidean distance cubed
		scaleVector( 1.0/distance , &displacement , &displacement );
		// cout << "displacement is = " ; printVector ( &displacement );
		// cumulative sum in acceleration
		vectorSum( &acceleration , &displacement , &acceleration );
		// cout << "acceleration is = "; printVector( acceleration );
	}

	// finally scale by the gravitational constant
	scaleVector( -g_const , &acceleration , &acceleration );
	// cout << "acceleration is = "; printVector( acceleration );

	(*state_dot)[3] = acceleration[0];
	(*state_dot)[4] = acceleration[1];
	(*state_dot)[5] = acceleration[2];

	return;

}