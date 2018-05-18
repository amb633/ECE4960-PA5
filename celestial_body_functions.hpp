#pragma once

#include "utility_functions.hpp"

/* struct to store user defined celestial bodies -> body specific format for easy reading
 * each body has 5 members : name , mass , position , velocity , and acceleration
 * position , velocity , and acceleration are defined in cartesian coordinates
 * 
 * four ways to initialize a body :
 *	i)	body() : without any input, will initialize and empty body with all values = 0.0
 *	ii)	body( m , pos_vector , vel_vector ) : will initialize a body with the mass = m , position = pos_vector , velocity = vel_vector , and acceleration = 0.0, but without a name
 *	iii)body( s , m , pos_vector , vel_vector ) : same as above , but with an identifying string variable for the name
 *	iv)	body( body* ) : with a pointer to another existing body, creates an identical copy of the body refered to by the pointer
 */
struct body
{
	string name;
	double mass;
	vector<double> position;
	vector<double> velocity;
	vector<double> acceleration;

	body() : mass(0.0) , position({0.0 , 0.0 , 0.0}) , velocity({0.0 , 0.0 , 0.0}) , acceleration({0.0 , 0.0 , 0.0}) {};

	body( double m , vector<double> p , vector<double> v ) : 
		mass(m) , position(p) , velocity(v) , acceleration( {0.0 , 0.0 , 0.0} ) {};

	body ( string s , double m , vector<double> p , vector<double> v ) :
		name(s) , mass(m) , position(p) , velocity(v) , acceleration( {0.0 , 0.0 , 0.0} ) {};

	body( body* b ) :
		name( (*b).name ) , mass( (*b).mass ) , position( (*b).position ) , velocity( (*b).velocity ) , acceleration( (*b).acceleration ) {};

};

/* struct to store the current state of the system in vector format -> system specific format for handling by ode solver functions
 * ode solver functions are written to handle ANY generic set of inputs in the form of vector<double>
 * therefore, need to convert from body specific format to generic format for ode sovers to handle
 * 
 * four members in struct :
 *	i)  n_name : to store the names of all the bodies in the system
 *	ii)	n_mass : to store the masses of all the bodies in the system
 *	iii)n_state: to store the current state of the system
 *	iv) n_state_dot : to store the current derivative of the system 
 *
 *	for each body, state = [ x_position , y_position , z_position , x_velocity , y_velocity , z_velocity ]
 *  and state_dot = [ x_velocity , y_velocity , z_velocity , x_acceleration , y_acceleration , z_acceleration ]
 *	n_state is a stack of all of the states : [ state_1 , state_2 , state_3 ... ]
 *	n_state_dot is a state of all the state_dots : [ state_dot_1 , state_dot_2 , state_dot_3 ... ]
 */
struct space_system
{
	vector<string> n_name;
	vector<double> n_mass;
	vector<double> n_state;
	vector<double> n_state_dot;
};

/* function to print all the information of a body in easy to read format */
void print_body( body* which_body );

/* function to erase all the bodies in a system */
void clear_system( space_system* space );

/* function to convert from body specific format to system specific format */
void create_system ( vector<body>* bodies , space_system* space );

/* function to convert from system specific format to body specific format */
void resolve_system( space_system* space , vector<body>* bodies );

/* ODE function to find n_state_dot ( acceleration ) given n_state ( body_positions ) and n_parameters( body_masses ) 
 * feed this function to the ode solvers
 */
void find_state_dot( double time , vector<double>* body_masses , vector<double>* body_positions , vector<double>* acceleration );
