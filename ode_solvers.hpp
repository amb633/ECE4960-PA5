#pragma once
#include "utility_functions.hpp"

#define FORWARD_EULER 0
#define HEUN_ONE 1
#define RK34 2
#define RK34A 3

namespace ode_solvers
{
void ODE_SOLVER( void (*function)(double, int , vector<double>* , vector<vector<double>>* , vector<double>* ),
	double time , double march , vector<double>* parameters /*masses*/ , vector<vector<double>>* inputs /*positions*/ , 
	vector<vector<double>>* slopes /*state_dots*/ , int method );

void forward_euler ( void (*function)( double, int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* parameters , vector<vector<double>>* input , 
	vector<vector<double>>* slopes );

void heun_oneStep ( void (*function) ( double , int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* parameters , vector<vector<double>>* input , 
	vector<vector<double>>* slopes );
}