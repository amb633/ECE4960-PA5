#include "ode_solvers.hpp"

void ode_solvers::ODE_SOLVER( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* new_values , int method , bool adaptive , double e_rel , double e_abs )
{
	vector<double> phi , update;

	switch (method){
		case FORWARD_EULER:{
			forward_euler( function , time , march , parameters , input , &phi );
			break;
		}
		case HEUN_ONE: {
			heun_oneStep( function , time , march , parameters , input , &phi );
			break;
		}
		case HEUN_ITR: {
			heun_iterative( function , time , march , parameters , input , &phi , e_rel );
			break;
		}
		case RK34: {
			rk34( function , time , march , parameters , input , &phi , false , e_rel , e_abs );
			break;
		}
		case RK34A: {
			rk34( function , time , march , parameters , input , &phi , true , e_rel , e_abs );
			break;
		}
	}
	scaleVector( march , &phi , &update );
	vectorSum( input , &update , new_values );
	return;
}

void ode_solvers::forward_euler( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope )
{
	function( time , parameters , input , slope );
	return;
}

void ode_solvers::heun_oneStep( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope )
{
	vector<double> f1 , f2 , eu , predict , sum;

	// predict using the forward_euler method
	forward_euler( function , time , march , parameters , input , &eu );
	scaleVector( march , &eu , &eu );
	vectorSum( input , &eu , &predict );

	function( time , parameters , input , &f1 );
	function( time + march , parameters , &predict , &f2 );

	vectorSum( &f1 , &f2 , &sum );
	scaleVector( 0.5 , &sum , slope );
	return;
}

void ode_solvers::heun_iterative ( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , double e_rel )
{
	double error = 1.0;
	vector<double> current_update , current_prediction;
	current_update = (*input);
	while ( error > e_rel ){
		heun_oneStep( function , time , march , parameters , &current_update , &current_prediction );
		double temp_1 , temp_2;
		vectorNorm( &current_prediction , &current_update , temp_1 );
		vectorNorm( &current_prediction , temp_2 );
		error = temp_1/ temp_2;
		current_update = current_prediction;
	}
	(*slope) = current_prediction;
	return;
}


void ode_solvers::rk34 ( void (*function)( double , vector<double>* , vector<double>* , vector<double>* ) , 
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , bool adaptive , double e_rel , double e_abs )
{
	vector<double> k1 , k1h , k2 , k2h , k3 , k3h , k4 , ksum;
	
	function ( time , parameters , input , &k1 );
	
	scaleVector( 0.5*march , &k1 , &k1h );
	vectorSum( input , &k1h , &k1h );
	function( (time + 0.5*march) , parameters , &k1h , &k2 );

	scaleVector( 0.75*march , &k2 , &k2h );
	vectorSum( input , &k2h , &k2h );
	function( (time + 0.75*march) , parameters , &k2h , &k3 );

	scaleVector( march , &k3 , &k3h );
	vectorSum( input , &k3h , &k3h );
	function( (time + march) , parameters , &k3h , &k4 );

	if ( adaptive ) {
		double error;
		rk34_error( k1 , k2 , k3 , k4 , march , error );
		rk34_new_march( input , error , e_rel , e_abs , march );
	}

	scaleVector( 7.0 , &k1 , &k1 );
	scaleVector( 6.0 , &k2 , &k2 );
	scaleVector( 8.0 , &k3 , &k3 );
	scaleVector( 3.0 , &k4 , &k4 );

	vectorSum( &k1 , &k2 , &ksum );
	vectorSum( &k3 , &ksum , &ksum );
	vectorSum( &k4 , &ksum , &ksum );

	scaleVector( (1.0/24.0) , &ksum , slope );
	return;
}

void ode_solvers::rk34_error( vector<double> k1 , vector<double> k2 , vector<double> k3 , vector<double> k4 , double march , double& error ) 
{
	scaleVector( -5.0 , &k1 , &k1 );
	scaleVector( 6.0 , &k2 , &k2 );
	scaleVector( 8.0 , &k3 , &k3 );
	scaleVector( -9.0 , &k4 , &k4 );

	vectorSum( &k1 , &k2 , &k2 );
	vectorSum( &k2 , &k3 , &k3 );
	vectorSum( &k3 , &k4 , &k4 );

	vector<double> error_vector;
	scaleVector( march/72.0 , &k4 , &error_vector );
	vectorNorm( &error_vector , error );
	return;
}

void ode_solvers::rk34_new_march ( vector<double>* input , double error , double e_rel , double e_abs , double& march )
{
	double xn;
	vectorNorm( input , xn);
	double intermediate_value = error/ ( xn + e_abs );
	intermediate_value = e_rel / intermediate_value;
	march *= cbrt( intermediate_value );
	return;
}