#pragma once
#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"

#define FORWARD_EULER 0;
#define HEUN_ONE 1;
#define HEUN_ITR 2;
#define RK34 3;
#define RK34A 4;

namespace ode_solvers
{
	void ODE_SOLVER( void (*function)(double , int , vector<body>* , body* ) , 
		double time , double march , vector<body>* bodies_input , vector<body>* bodies_output , int method );

	void forward_euler( void (*function)(double , int , vector<body>* , body* ),
			double time , double march , vector<body>* bodies_input , vector<body>* bodies_slope );

	void heun_oneStep( void (*function)(double , int , vector<body>* , body* ),
			double time , double march , vector<body>* bodies_input , vector<body>* bodies_slope );

	void rk34 ( void (*function)(double , int , vector<body>* , body* ),
			double time , double march , vector<body>* bodies_input , vector<body>* bodies_slope );

	void update_states( double time , double march , vector<body>* bodies_input , 
		vector<body>* bodies_slope , vector<body>* bodies_output );
}