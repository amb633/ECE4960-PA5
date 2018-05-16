#pragma once
#include "utility_functions.hpp"

#define FORWARD_EULER 0
#define HEUN_ONE 1
#define RK34 2

namespace ode_solvers
{
void ODE_SOLVER( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* new_values , int method , bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 );

void forward_euler ( void (*function)( double, vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope );

void heun_oneStep ( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope );

void rk34 ( void (*function)( double , vector<double>* , vector<double>* , vector<double>* ) , 
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , bool adaptive , double e_rel , double e_abs );

void rk34_error( vector<double> k1 , vector<double> k2 , vector<double> k3 , vector<double> k4 , double march , double& error );

void rk34_new_march ( vector<double>* input , double error , double e_rel , double e_abs , double& march );
}