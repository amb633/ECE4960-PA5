#pragma once

#include "utility_functions.hpp"

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

struct space_system
{
	vector<string> n_name;
	vector<double> n_mass;
	vector<double> n_state;
	vector<double> n_state_dot;
};

void print_body( body* which_body );

void clear_system( space_system* space );
void create_system ( vector<body>* bodies , space_system* space );
void resolve_system( space_system* space , vector<body>* bodies );
void find_state_dot( double time , vector<double>* body_masses , vector<double>* body_positions , vector<double>* acceleration );
