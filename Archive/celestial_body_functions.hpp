#pragma once

#include "utility_functions.hpp"

// namespace celestial_functions
// {
	struct body 
	{
		double mass;
		vector<double> position;
		vector<double> velocity;
		vector<double> acceleration;

		body( double m , vector<double> p , vector<double> v ) : 
			mass(m) , position(p) , velocity(v) , acceleration( {0.0 , 0.0 , 0.0} ) {};
		body( body* b ) :
			mass( (*b).mass ) , position( (*b).position ) , velocity( (*b).velocity ) , acceleration( (*b).acceleration ) {};

	};

	void printBody( body* which_body );

	void find_acceleration( double time , int which_body , vector<body>* celestial_bodies , body* output );

// }