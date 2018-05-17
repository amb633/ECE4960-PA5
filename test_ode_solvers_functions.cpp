#include "test_functions.hpp"

void ode_exponential_function ( double time , vector<double>* parameters , 
	vector<double>* input , vector<double>* output )
{
	double a = (*parameters)[0];
	double b = (*parameters)[1];
	double c = (*parameters)[2];
	vector<double> temp;
	double exp_comp = a*exp( b*time );
	scaleVector( -0.5 , input , &temp );
	shiftVector( exp_comp , &temp , output );
	return;
}

bool test_forward_euler() 
{
	bool flag = true;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	vector<double> values;
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		values.push_back( old_values[0] );
		vector<double> slope , new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &slope , FORWARD_EULER );
		scaleVector( march , &slope , &new_values );
		vectorSum( &old_values , &new_values , &new_values );
		old_values.erase( old_values.begin(), old_values.end());
		old_values = new_values;
	}
	vector<double> expected_values = {2.0 , 5.0 , 11.4022 , 25.5132 , 56.8493};
	vectorDiff ( &expected_values , &values , &values );

	for ( int i = 0 ; i < values.size() ; i++ ){
		if ( abs( values[i] ) > 1e-4 ) flag = false;
	}
	return flag;
}

bool test_heun_one() 
{
	bool flag = true;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	vector<double> values;
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		values.push_back( old_values[0] );
		vector<double> slope , new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &slope , HEUN_ONE );
		scaleVector( march , &slope , &new_values );
		vectorSum( &old_values , &new_values , &new_values );
		old_values.erase( old_values.begin(), old_values.end());
		old_values = new_values;
	}
	vector<double> expected_values = {2.0 , 6.70108 , 16.3198 , 37.1992 , 83.3378 };
	vectorDiff ( &expected_values , &values , &values );

	for ( int i = 0 ; i < values.size() ; i++ ){
		if ( abs( values[i] ) > 1e-4 ) flag = false;
	}
	return flag;
}

bool test_heun_iterative() 
{
	bool flag = true;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	vector<double> values;
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		values.push_back( old_values[0] );
		vector<double> slope , new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &slope , HEUN_ITR );
		scaleVector( march , &slope , &new_values );
		vectorSum( &old_values , &new_values , &new_values );
		old_values.erase( old_values.begin(), old_values.end());
		old_values = new_values;
	}
	printVector( &values );
	vector<double> expected_values = {2.0 , 6.3609 , 15.302 , 34.743 , 77.735 };
	vectorDiff ( &expected_values , &values , &values );

	for ( int i = 0 ; i < values.size() ; i++ ){
		if ( abs( values[i] ) > 1e-4 ) flag = false;
	}
	return flag;
}

bool test_non_adaptive_rk34()
{
	bool flag = true;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	vector<double> values;
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		values.push_back( old_values[0] );
		vector<double> slope , new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &slope , RK34 );
		scaleVector( march , &slope , &new_values );
		vectorSum( &old_values , &new_values , &new_values );
		old_values.erase( old_values.begin(), old_values.end());
		old_values = new_values;
	}
	vector<double> expected_values = {2.0 , 6.1919 , 14.8259 , 33.6235 , 75.2075 };
	vectorDiff ( &expected_values , &values , &values );

	for ( int i = 0 ; i < values.size() ; i++ ){
		if ( abs( values[i] ) > 1e-4 ) flag = false;
	}
	return flag;
}

bool test_adaptive_rk34()
{
	bool flag = true;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	vector<double> values;
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		values.push_back( old_values[0] );
		vector<double> slope , new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &slope , RK34A );
		scaleVector( march , &slope , &new_values );
		vectorSum( &old_values , &new_values , &new_values );
		old_values.erase( old_values.begin(), old_values.end());
		old_values = new_values;
	}
	vector<double> expected_values = {2.0 , 2.81239 , 3.85093 , 5.18517 , 6.92587 , 9.9197 , 12.1684 };
	vectorDiff ( &expected_values , &values , &values );
	for ( int i = 0 ; i < 5 ; i++ ){
		if ( abs( values[i] ) > 1e-4 ) flag = false;
	}
	return flag;
}