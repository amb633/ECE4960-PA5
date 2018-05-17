#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"
#include "wrapper.hpp"
#include "test_functions.hpp"
#include "user_input_functions.hpp"


int main ( void )
{
	cout << endl << boolalpha;
	cout << " --------------- Testing Celestial Body Functions --------------- " << endl << endl;

	cout << "...testing if space transformation is correct... : " << test_space_transform() << endl << endl;	

    cout << "...testing if reverse transformation is correct... : " << test_reverse_space_transform() << endl << endl;	

    cout << "...testing if acceleration function is correct... : " << test_acceleration_calculation() << endl << endl;

	cout << " --------------- Testing ODE Solver Functions --------------- " << endl << endl;
	
	cout << "...testing forward euler... : " << test_forward_euler() << endl << endl;
	
	cout << "...testing heun one step... : " << test_heun_one() << endl << endl;

	cout << "...testing heun iterative... : " << test_heun_iterative() << endl << endl;

	cout << "...testing non adaptive rk34... : " << test_non_adaptive_rk34() << endl << endl;

	cout << "...testing adaptive rk34... : " << test_adaptive_rk34() << endl << endl;

	cout << " --------------- Testing Wrapper Functions --------------- " << endl;

	if ( test_wrapper() ) 
		cout << "...wrapper function was successful..."  << endl << endl;
	else cout << "..wrapper function failed... " << endl << endl;


    cout << " --------------- Using User Interface to Create Solar System --------------- " << endl << endl;
    string file_path;
    cout << "Enter file path for planetary system's data: " << endl;
    //    cin >> file_path;
    file_path = "/Users/arianabruno/Desktop/ECE4960/ProgrammingAssignments/ECE4960-PA5/user_input/test1.txt";
//    file_path = "user_input/test1.txt";
    vector<body> bodies_user_input_file;

    parseInput( &file_path, &bodies_user_input_file);
//    for ( int i = 0 ; i < bodies_user_input_file.size() ; i++ ) {
//        print_body( &bodies_user_input_file[i] );
//    }

    cout << " --------------- Using User Interface to collect Solver Information --------------- " << endl << endl;
    cout << endl;
    int ODE_Solver_method;
    double end_time_input, time_step_input;
    getSolverInput( ODE_Solver_method, end_time_input, time_step_input );

    cout << " --------------- Running User's System Simulation --------------- " << endl << endl;
    space_system user_solar_system;
    create_system( &bodies_user_input_file , &user_solar_system );


    vector<vector<double>> user_system_states;
    user_system_states.push_back( user_solar_system.n_state );
    vector<double> sim_time_log;
    double uer_march = time_step_input*24.0*60.0*60.0; // march should be in seconds
    double sim_time = 0.0;
    sim_time_log.push_back(sim_time);

    for ( size_t i = 0 ; i <= end_time_input ; i++ ){
        sim_time = i*uer_march;
        sim_time_log.push_back(sim_time);
        simulate_system( &user_solar_system , sim_time , uer_march , ODE_Solver_method );
        user_system_states.push_back( user_solar_system.n_state );
        vector<body> user_bodies_resolved;
        resolve_system( &user_solar_system , &user_bodies_resolved );

        for ( int i = 0 ; i < user_bodies_resolved.size() ; i++ ) {
            print_body( &user_bodies_resolved[i] );
        }
    }

    cout << endl;
    
//    string output_path = "ForwardEuler_Results.txt";
    
    cout << "Enter the output file name: " << endl;
    string output_path;
    cin >> output_path;
    
    saveOutput( &user_system_states, &user_solar_system.n_name, &sim_time_log, output_path);
    

	return 0;
}
