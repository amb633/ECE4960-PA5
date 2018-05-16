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
		vector<double> current_position;
		current_position.push_back( (*space).n_state[i][0] );
		current_position.push_back( (*space).n_state[i][1] );
		current_position.push_back( (*space).n_state[i][2] );
		current_body.position = current_position;

		vector<double> current_velocity;
		current_velocity.push_back( (*space).n_state[i][3] );
		current_velocity.push_back( (*space).n_state[i][4] );
		current_velocity.push_back( (*space).n_state[i][5] );
		current_body.position = current_velocity;

		vector<double> current_acceleration;
		current_acceleration.push_back( (*space).n_state_dot[i][3] );
		current_acceleration.push_back( (*space).n_state_dot[i][4] );
		current_acceleration.push_back( (*space).n_state_dot[i][5] );

		current_body.position = current_position;
		current_body.velocity = current_velocity;
		current_body.acceleration = current_acceleration;

		(*bodies).push_back( current_body );
	}
	return;
}