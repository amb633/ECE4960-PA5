#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"

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


int main ( void )
{
	cout << endl;
	cout << " --------------- Testing Celestial Body Functions --------------- " << endl;

	// create three planets and stack them into a vector
	body planet_A( 10.0 , { 2.0 , 5.0 , 8.0 } , { -1.0 , 0.5 , 0.25 } );
	body planet_B( 8.0 , {3.0 , 7.5 , 10.0 } , { 5.0 , 3.0 , 1.0 } );
	body planet_C( 50.0 , { 5.0 , 3.0 , -4.0 } , { 0.0 , 0.0 , 0.0 } );

	vector<body> bodies = {planet_A , planet_B , planet_C};

	// transform the bodies to a space system
	space_system space;
	create_system ( &bodies , &space );

    // check if the transformation is correct
    cout << "...testing if transformation is correct... " << endl;
    cout << endl << "planet masses are : " << endl;
    printVector( &(space.n_mass) );
    cout << endl << endl << "n_state of space :" << endl;
    printVector( &(space.n_state) );
    cout << endl << endl << "n_state_dot of space :" << endl;
    printVector( &(space.n_state_dot) );
    cout << endl << endl;

    // transform from space system back to body system
    cout << "...testing if reverse transformation is correct... " << endl;
    vector<body> bodies_resolved;
    resolve_system( &space , &bodies_resolved );
    for ( int i = 0 ; i < bodies_resolved.size() ; i++ ){
        print_body( &bodies_resolved[i] );
    }

    cout << "...testing if acceleration function is correct... " << endl;
    bodies.pop_back();
    vector<double> acceleration_a;
    space_system space_two;
    create_system( &bodies , &space_two );
    find_state_dot( 0.0 , &space_two.n_mass, &space_two.n_state , &acceleration_a );
    cout << " acceleration of A in 02 body system : ";
    printVector( &acceleration_a );

    find_state_dot( 0.0 , &space.n_mass, &space.n_state , &acceleration_a );
    cout << " acceleration of A in 03 body system : ";
    printVector( &acceleration_a );

    cout << endl << endl;

	cout << " --------------- Testing ODE Solver Functions --------------- " << endl;
	cout << "...testing forward euler... " << endl;
	void (*ode_exp_fcn)( double , vector<double>* , vector<double>* , vector<double>* ) = ode_exponential_function;
	double march = 1.0;
	vector<double> parameters = { 4.0 , 0.8 , -0.5 };
	vector<double> old_values = {2.0};
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		vector<double> new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &new_values , FORWARD_EULER );
		printVector( &new_values );
		old_values.erase( old_values.begin() , old_values.end() );
		old_values = new_values;
	}

	cout << "...testing heun one step... " << endl;
	old_values = {2.0};
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		vector<double> new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &new_values , HEUN_ONE );
		printVector( &new_values );
		old_values.erase( old_values.begin() , old_values.end() );
		old_values = new_values;
	}

	cout << "...testing non adaptive rk34... " << endl;
	old_values = {2.0};
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		vector<double> new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &new_values , RK34 );
		printVector( &new_values );
		old_values.erase( old_values.begin() , old_values.end() );
		old_values = new_values;
	}

	cout << "...testing adaptive rk34... " << endl;
	old_values = {2.0};
	for ( double time = 0.0 ; time < 5.0 ; time += march ){
		vector<double> new_values;
		ode_solvers::ODE_SOLVER( ode_exp_fcn , time , march , &parameters , &old_values , &new_values , RK34 , true );
		printVector( &new_values );
		old_values.erase( old_values.begin() , old_values.end() );
		old_values = new_values;
	}


	cout << endl;
	return 0;
}