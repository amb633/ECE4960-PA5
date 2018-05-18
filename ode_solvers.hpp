#pragma once
#include "utility_functions.hpp"

/* ode solver functions 
 * imported from programming assignment 4 , with slight modification 
 * testing done with the exponential ode function from hacker practices
 */

/* constant definitions for solver methods */
#define FORWARD_EULER 0
#define HEUN_ONE 1
#define HEUN_ITR 2
#define RK34 3
#define RK34A 4

namespace ode_solvers
{

/* parent ode function with swtich case to chose between methods */
void ODE_SOLVER( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope , int method , bool adaptive = false , double e_rel = 1e-4 , double e_abs = 1e-7 );

/* main method functions */
void forward_euler ( void (*function)( double, vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope );

void heun_oneStep ( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope );

void heun_iterative ( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , double e_rel );

void rk34 ( void (*function)( double , vector<double>* , vector<double>* , vector<double>* ) , 
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , bool adaptive , double e_rel , double e_abs );

/* helper functions for adaptive time stepping */
void rk34_error( vector<double> k1 , vector<double> k2 , vector<double> k3 , vector<double> k4 , double march , double& error );

void rk34_new_march ( vector<double>* input , double error , double e_rel , double e_abs , double& march );
}