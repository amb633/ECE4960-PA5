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
    
    //sends an input vector to hold the planetary bodies read in
    //from a user input file path
    vector<body> bodies_user_input_file;
    //function parses the data from the file provided by the file path given by the user
    parseInput (&bodies_user_input_file);


    cout << " --------------- Using User Interface to collect Solver Information --------------- " << endl << endl;
    cout << endl;
    int ODE_Solver_method;
    double end_time_input, time_step_input;
    //gathers input information from the user including the ODE solver method to use
    //the time duration to run the simulation for and the time step to calculate the results
    getSolverInput( ODE_Solver_method, end_time_input, time_step_input );

    cout << " --------------- Running User's System Simulation --------------- " << endl << endl;
    
    //this creates a space system for the user's input data file of planet bodies
    
    space_system user_solar_system;
    create_system( &bodies_user_input_file , &user_solar_system );

    //the user-defined systems inital states from input file are collected and stored
    // in a matrix of system states which will be updates as the ODE solver steps through the duration
    vector<vector<double>> user_system_states;
    user_system_states.push_back( user_solar_system.n_state );
    
    //vector to log the time for each step in the ODE solver
    vector<double> sim_time_log;
    double user_march = time_step_input*24.0*60.0*60.0; // march converted to seconds
    double sim_time = 0.0; //initializes the start time
    sim_time_log.push_back(sim_time);

    //iterates through the time duration calculating the simulate system at each time step
    for ( size_t i = 0 ; i <= end_time_input ; i++ ){
        
        //calculates the current time step and logs it
        sim_time = i*user_march;
        sim_time_log.push_back(sim_time);
        
        //runs the time step iteration for the ODE solver
        simulate_system( &user_solar_system , sim_time , user_march , ODE_Solver_method );
        //logs the current time step's system planet states (positions and velocities)
        user_system_states.push_back( user_solar_system.n_state );
        
        //resolves the output of the updated planetary states into the system structure
        vector<body> user_bodies_resolved;
        resolve_system( &user_solar_system , &user_bodies_resolved );
    }

    cout << endl;
    
    saveOutput( &user_system_states, &user_solar_system.n_name, &sim_time_log);
    

	return 0;
}
