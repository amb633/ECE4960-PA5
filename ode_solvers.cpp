#include "ode_solvers.hpp"

// void ode_exponential_function( double time , int dummy_int , vector<double>* params , 
// 	vector<vector<double>>* inputs , vector<vector<double>>* outputs )
// {
// 	double a = (*params)[0];
// 	double b = (*params)[1];
// 	double c = (*params)[2];

		
// }

void ode_solvers::ODE_SOLVER( void (*function)(double, int , vector<double>* , vector<vector<double>>* , vector<double>* ),
	double time , double march , vector<double>* parameters /*masses*/ , vector<vector<double>>* inputs /*positions*/ , 
	vector<vector<double>>* slopes /*state_dots*/ , int method )
{

}

void ode_solvers::forward_euler ( void (*function)( double, int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* parameters , vector<vector<double>>* input , 
	vector<vector<double>>* slopes )
{
	for ( int i = 0 ; i < (*input).size() ; i++ ){
		vector<double> phi;
		function( time , i , parameters , input , &phi);
		(*slopes).push_back( phi );
	}
	return;
}

void ode_solvers::heun_oneStep ( void (*function) ( double , int , vector<double>* , vector<vector<double>>* , vector<double>* ) ,
	double time , double march , vector<double>* parameters , vector<vector<double>>* input , 
	vector<vector<double>>* slopes )
{

}