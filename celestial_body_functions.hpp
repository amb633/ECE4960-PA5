#pragma once

#include "utility_functions.hpp"

namespace celestial_functions
{
	struct body 
	{
		double mass;
		vector<double> position;
		vector<double> velocity;
		//vector<double> acceleration;

		body( double m , vector<double> p , vector<double> v ) : 
			mass(m) , position(p) , velocity(v) {};
	};

	void printBody( body* which_body );

	void find_acceleration( double time , int which_body , vector<body>* celestial_bodies , vector<double>* acceleration );

}