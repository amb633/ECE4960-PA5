#include "ode_solvers.hpp"

void ode_solvers::ODE_SOLVER( void (*function)(double, int , vector<double>* , vector<vector<double>>* , vector<double>* ),
	double time , double march , vector<double>* input , vector<double>* slope , int method )
{

}

void ode_solvers::forward_euler ( void (*function)( double, int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* input , vector<double>* slope )
{

}

void ode_solvers::heun_oneStep ( void (*function) ( double , int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* input , vector<double>* slope )
{
	
}