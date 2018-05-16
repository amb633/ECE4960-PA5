#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"
#include "wrapper.hpp"
#include "test_functions.hpp"
#include "user_input_functions.hpp"


int main ( void )
{
    
    cout << " --------------- Testing User Interface --------------- " << endl << endl;
    string file_path;
    cout << "Enter file path for planetary system's data: " << endl;
//    cin >> file_path;
//    file_path = "/Users/arianabruno/Desktop/ECE4960/ProgrammingAssignments/ECE4960-PA5/user_input/test1.txt";
    file_path = "user_input/test1.txt";
    vector<body> bodies_user_input_file;
    
    parseInput( &file_path, &bodies_user_input_file);
    for ( int i = 0 ; i < bodies_user_input_file.size() ; i++ ) {
        print_body( &bodies_user_input_file[i] );
    }
    
    cout << endl;
    int ODE_Solver_method;
    double end_time_input, time_step_input;
    getSolverInput( ODE_Solver_method, end_time_input, time_step_input );
    
    
	cout << endl << boolalpha;
	cout << " --------------- Testing Celestial Body Functions --------------- " << endl << endl;

	cout << "...testing if space transformation is correct... : " << test_space_transform() << endl << endl;	

    cout << "...testing if reverse transformation is correct... : " << test_reverse_space_transform() << endl << endl;	

    cout << "...testing if acceleration function is correct... : " << test_acceleration_calculation() << endl << endl;

	cout << " --------------- Testing ODE Solver Functions --------------- " << endl << endl;
	
	cout << "...testing forward euler... : " << test_forward_euler() << endl << endl;
	
	cout << "...testing heun one step... : " << test_heun_one() << endl << endl;

	cout << "...testing heun one iterative... : " << test_heun_iterative() << endl << endl;

	cout << "...testing non adaptive rk34... " << test_non_adaptive_rk34() << endl << endl;

	cout << "...testing adaptive rk34... " << test_adaptive_rk34() << endl << endl;


	cout << " --------------- Creating the Inner Solar System --------------- " << endl << endl;
	body sun	( "sun" , 2.0e30 	, { 0.0 , 0.0 , 0.0 } 	 , { 0.0 , 0.0 , 0.0 });
	body mercury( "mercury" , 3.285e23 	, { 0.0 , 5.7e10 , 0.0 } , { 47000 , 0.0 , 0.0 });
	body venus 	( "venus" , 4.8e24 	, { 0.0 , 1.1e11 , 0.0 } , { 35000 , 0.0 , 0.0 });
	body earth 	( "earth" , 6.0e24 	, { 0.0 , 1.5e11 , 0.0 } , { 30000 , 0.0 , 0.0 });
	body mars 	( "mars" , 2.4e24 	, { 0.0 , 2.2e11 , 0.0 } , { 24000 , 0.0 , 0.0 });

	vector<body> bodies = { sun , mercury , venus , earth , mars };

	// for ( int i = 0 ; i < bodies.size() ; i++ ) {
	// 	print_body( &bodies[i] );
	// }

	space_system solar_system;
	create_system( &bodies , &solar_system );

	vector<space_system> system_states;
	system_states.push_back( solar_system );
	double march = 24.0*60.0*60.0; // march should be in seconds
	double time = 0.0;

	for ( size_t i = 0 ; i < 10 ; i++ ){
		time = i*march;
		simulate_system( &solar_system , time , march , FORWARD_EULER );
		system_states.push_back( solar_system );
		vector<body> bodies_resolved;
		resolve_system( &solar_system , &bodies_resolved );

		for ( int i = 0 ; i < bodies_resolved.size() ; i++ ) {
			print_body( &bodies_resolved[i] );
		}
	}

	// simulate_system( &solar_system , 0.0 , march , FORWARD_EULER );
	// system_states.push_back( solar_system );

	// vector<body> bodies_resolved;
	// resolve_system( &solar_system , &bodies_resolved );

	// for ( int i = 0 ; i < bodies_resolved.size() ; i++ ) {
	// 	print_body( &bodies_resolved[i] );
	// }

	cout << endl;

	return 0;
}
