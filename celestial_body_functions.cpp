#include "celestial_body_functions.hpp"

/* function to print all the information of a body in easy to read format */
void print_body( body* which_body )
{
	cout << endl;
    cout << " name of body : " << (*which_body).name << endl;
	cout << " mass of body : " << (*which_body).mass << endl;
	cout << " position of body : " ; printVector( &((*which_body).position) );
	cout << " velocity of body : " ; printVector( &((*which_body).velocity) );
	cout << " acceleration of body : " ; printVector( &((*which_body).acceleration) );
	cout << endl;
	return;
}

/* function to erase all the bodies in a system */
void clear_system( space_system* space )
{
    (*space).n_name.erase( (*space).n_name.begin(), (*space).n_name.end());
	(*space).n_mass.erase( (*space).n_mass.begin(), (*space).n_mass.end());
	(*space).n_state.erase( (*space).n_state.begin(), (*space).n_state.end());
	(*space).n_state_dot.erase( (*space).n_state_dot.begin(), (*space).n_state_dot.end());
	return;
}

/* function to convert from body specific format to system specific format 
 * takes in a vector of bodies that can be created by using push_back( body )
 */
void create_system ( vector<body>* bodies , space_system* space )
{
    vector<string> name;
	vector<double> mass;
	vector<double> state;       // p = [ x y z xdot ydot zdot ]
	vector<double> state_dot;	// pdot = [ xdot ydot zdot xdotdot ydotdot zdotdot ]

    // find the number of bodies and loop over each body
	int n_bodies = (*bodies).size(); 
	for ( int i = 0 ; i < n_bodies ; i++ ){
		
        // extract the name and mass of body
        name.push_back( (*bodies)[i].name );
		mass.push_back( (*bodies)[i].mass );
		
        // extract the position , velocity , and acceleration of body
		vector<double> current_position = (*bodies)[i].position;
		vector<double> current_velocity = (*bodies)[i].velocity;
		vector<double> current_acceleration = (*bodies)[i].acceleration;

		// concatenate the position and the velocity to the end of the full state vector
		state.insert(state.end(), current_position.begin(), current_position.end());
        state.insert( state.end() , current_velocity.begin() , current_velocity.end() );

		// concatenate the velocity and the acceleration to the end of the full state_dot vector
        state_dot.insert( state_dot.end() , current_velocity.begin() , current_velocity.end() );
        state_dot.insert(state_dot.end(), current_acceleration.begin(), current_acceleration.end());
	}

    // clear the existing information in the system, and put in the new information
	clear_system( space );
    (*space).n_name = name;
	(*space).n_mass = mass;
	(*space).n_state = state;
	(*space).n_state_dot = state_dot;
	return;
}

/* function to convert from system specific format to body specific format 
 * returns of vector of bodies that can be indexed easily 
 */
void resolve_system( space_system* space , vector<body>* bodies )
{
    // erase any existing information in the vector
	(*bodies).erase( (*bodies).begin(), (*bodies).end());

    // find the number of bodies and loop over each body
	int n_bodies = (*space).n_mass.size();
	for ( int i = 0 ; i < n_bodies ; i++ ){

        // create a temporary body variable
		body current_body;

        // extract the current body's name and mass
        current_body.name = (*space).n_name[i];
		current_body.mass = (*space).n_mass[i];
        
        // for indexing since the system format is a flat vector
        int id = i*6;

		// cout << "x position of planet : " << (*space).n_state[i][0] << endl;
        // extract the position information
		current_body.position[0] = ( (*space).n_state[id+0] );
		current_body.position[1] = ( (*space).n_state[id+1] );
		current_body.position[2] = ( (*space).n_state[id+2] );

        // extract the velocity information
		current_body.velocity[0] = ( (*space).n_state[id+3] );
		current_body.velocity[1] = ( (*space).n_state[id+4] );
		current_body.velocity[2] = ( (*space).n_state[id+5] );

        // extract the acceleration information
		current_body.acceleration[0] = ( (*space).n_state_dot[id+3] );
		current_body.acceleration[1] = ( (*space).n_state_dot[id+4] );
		current_body.acceleration[2] = ( (*space).n_state_dot[id+5] );

        // push the current body into the vector to be returned
		(*bodies).push_back( current_body );
	}
	return;
}

/* ODE function to find n_state_dot ( acceleration ) given n_state ( body_positions ) and n_parameters( body_masses ) 
 * feed this function to the ode solvers
 */
void find_state_dot( double time , vector<double>* body_masses , 
	vector<double>* body_states , vector<double>* state_dot )
{
    // gravitational constant
    double g_const = 6.67408e-11; //m3 kg-1 s-2

    // find the number of bodies in the system
    int n_bodies = (*body_masses).size();

    // clear any memory in state_dot and initialize with zeros
    zeroVector( (*body_states).size() , state_dot );
    
    // loop over every body in the system
    for( int which_body = 0; which_body < n_bodies; which_body++ ){
        
        int which_body_id = which_body*6;
        vector<double>::iterator body_begin = body_states->begin() + which_body_id;
        vector<double>::iterator body_end = body_begin + 6;
        // extract the position of the body of interest
            // remember the state is : state = [ x , y , z , xdot , ydot , zdot ]
            // so need to erase the last three elements to ensure vector only has the positions
            // but we need the velocity for the first three elements of state_dot
        vector<double> current_body(body_begin, body_end);
        // extract the velocity information 
        (*state_dot)[which_body_id] = current_body[3];
        (*state_dot)[which_body_id+1] = current_body[4];
        (*state_dot)[which_body_id+2] = current_body[5];
        // then erase the velocity information
        current_body.erase( current_body.end() - 3 , current_body.end() );

        // create a 3x1 zero vector for acceleration
        vector<double> acceleration;
        zeroVector( 3 , &acceleration );

        for ( int i = 0 ; i < n_bodies ; i++ ){
            // skip self
            if ( i == which_body ) continue;

            int other_body_id = i*6;
            vector<double>::iterator other_body_begin = body_states->begin() + other_body_id;
            vector<double>::iterator other_body_end = other_body_begin + 6;
            
            // extract position of other body;
            vector<double> other_body(other_body_begin, other_body_end);
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

        // store the infotmaiton in the state_dot vector
        (*state_dot)[which_body_id+3] = acceleration[0];
        (*state_dot)[which_body_id+4] = acceleration[1];
        (*state_dot)[which_body_id+5] = acceleration[2];
    }

    return;

}
