#include "ode_solvers.hpp"

/* parent ode function with swtich case to chose between methods 
 * takes in the following arguments :
 *	i)	function pointer to the ode function -> standard function signature of double , and three vector<double>*
 *		any ode function, with this standard signature can be solved using this function
 * 	ii) current time
 *	iii)current march
 *	iv)	vector of parameters for the ode function
 *	v)	vector of current states for the ode function
 *	vi)	vector in which the slope calculation will be stored
 *	vii) user-defined method of solving the ode
 *	viii) boolean variable to indicate time stepping adaptivity -> default is false
 *	ix)	relative error threshold -> default is 1e-4
 *	x)	absolute error threshold -> default is 1e-7
 *	
 * returns the slope of the system at the current time step
 */
void ode_solvers::ODE_SOLVER( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope , int method , bool adaptive , double e_rel , double e_abs )
{
	switch (method){
		case FORWARD_EULER:{
			forward_euler( function , time , march , parameters , input , slope );
			break;
		}
		case HEUN_ONE: {
			heun_oneStep( function , time , march , parameters , input , slope );
			break;
		}
		case HEUN_ITR: {
			heun_iterative( function , time , march , parameters , input , slope , e_abs );
			break;
		}
		case RK34: {
			rk34( function , time , march , parameters , input , slope , false , e_rel , e_abs );
			break;
		}
		case RK34A: {
			rk34( function , time , march , parameters , input , slope , true , e_rel , e_abs );
			break;
		}
	}
	return;
}

/* function to calculate slope using forward euler method */
void ode_solvers::forward_euler( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope )
{
	function( time , parameters , input , slope );
	return;
}

/* function to calculate slope using one step heun method */
void ode_solvers::heun_oneStep( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input ,
	vector<double>* slope )
{
	vector<double> f1 , f2 , predict , sum;

	// predict the slope
	function( time , parameters , input , &f1 );

	// calculate the predicted state update
	scaleVector( march , &f1 , &predict );
	vectorSum( input , &predict , &predict );

	// correct the slope using the predicted state
	function( time + march , parameters , &predict , &f2 );

	// return average of prediction and correction
	vectorSum( &f1 , &f2 , &sum );
	scaleVector( 0.5 , &sum , slope );
	return;
}

/* function to calculate the slope using the iterative heun method */
void ode_solvers::heun_iterative ( void (*function) ( double , vector<double>* , vector<double>* , vector<double>* ) ,
	double time , double& march , vector<double>* parameters , vector<double>* input , 
	vector<double>* slope , double err )
{
	double error = 1.0;
	vector<double> f1 , f2 , initial , prev_correction;
	function( time , parameters , input , &f1 );

	// first prediction 
	scaleVector( march , &f1 , &initial );
	vectorSum( input , &initial , &initial );

	// first correction
	function( time + march , parameters , &initial , &f2 );
	vectorSum( &f1 , &f2 , &f2 );
	scaleVector( 0.5*march , &f2 , &f2 );
	vectorSum( input , &f2 , &prev_correction );

	vector<double> new_slope;

	// repeat correction until within error tolerance
	while ( error > err ){
		vector<double> new_correction , new_update;
		function( time + march , parameters , &prev_correction , &new_slope );
		vectorSum( &f1 , &new_slope , &new_slope );
		scaleVector( 0.5 , &new_slope , &new_slope );
		scaleVector( march , &new_slope , &new_update );
		vectorSum( input , &new_update , &new_correction );

		double temp_1 , temp_2;
		vectorNorm( &new_correction , &prev_correction , temp_1 );
		vectorNorm( &new_correction , temp_2 );
		error = temp_1 / temp_2;

		prev_correction = new_correction;
	}

	// return the converged slope
	(*slope) = new_slope;
	return;
}

/* function to calculate the slope using the RK34 method 
 * if adaptive variable is set to true, adaptive time stepping is used
 */
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

	// calculate the update in march if required
	if ( adaptive ) {
		double error;
		rk34_error( k1 , k2 , k3 , k4 , march , error );
		rk34_new_march( input , error , e_rel , e_abs , march );
		// max the march at 5 days (?)
		march = min( march , 5*24.0*60.0*60.0 );
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

/* function to calculate error in rk34 */
void ode_solvers::rk34_error( vector<double> k1 , vector<double> k2 , vector<double> k3 , vector<double> k4 , double march , double& error ) 
{
	scaleVector( -5.0 , &k1 , &k1 );
	scaleVector( 6.0 , &k2 , &k2 );
	scaleVector( 8.0 , &k3 , &k3 );
	scaleVector( -9.0 , &k4 , &k4 );

	vector<double> ksum;

	vectorSum( &k1 , &k2 , &ksum );
	vectorSum( &ksum , &k3 , &ksum );
	vectorSum( &ksum , &k4 , &ksum );

	vector<double> error_vector;
	scaleVector( march/72.0 , &ksum , &error_vector );
	vectorNorm( &error_vector , error );
	return;
}

/* function to update the time step for rk34a */
void ode_solvers::rk34_new_march ( vector<double>* input , double error , double e_rel , double e_abs , double& march )
{
	double xn;
	vectorNorm( input , xn);
	double intermediate_value = error/ ( xn + e_abs );
	intermediate_value = e_rel / intermediate_value;
	double temp = pow(intermediate_value, (1.0/3.0) );
	if ( !isnan(temp) )
		march *= temp;
	return;
}