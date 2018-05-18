//
//  user_input_functions.cpp
//  
//
//  Created by Ariana Bruno on 5/16/18.
//

#include "user_input_functions.hpp"

//function used for reading in the file for planet data
void parseInput( vector<body>* input_bodies){
    
    //requests the user for the input data file path
    string path;
    cout << "Enter file path for planetary system's data: " << endl;
    cin >> path;

    //reads data in from the file
    ifstream myfile( path );
    if (myfile.is_open()){
        myfile.ignore(2048 , '\n');
        while( !myfile.eof() ){
            string name; //parses the name of the planet being input
            double mass , x, y, z, vx, vy, vz; //parses the values for planets initial states
            vector<double> position, velocity;
            myfile >> name >> mass >> x >> y >> z >> vx >> vy >> vz; //push the data from file into correct variables
            position = {x,y,z}; // formats variables for storing in the body struct
            velocity = {vx,vy,vz};
            body planet_n( name, mass, position, velocity ); //constructs the body struct from input data
            input_bodies->push_back(planet_n); //creates a vector of body structs that exist in the input data file
        }
        myfile.close();
        
        //printed to screen if reading the file is successful
        cout << "Successfully parsed input data " << endl;
    }
    
    //printed to screen when file is unavailable or not found and cannot be opened
    else cout << "Unable to open file " << endl;
}


//used to collect additional ODE solver information to run simulation
void getSolverInput( int& ODE_Solver_method, double& end_time, double& time_step ){
    
    //asks the user which solver method to use for the simulation
    string ODE_Solver_method_name;
    cout << "Available ODE Solvers are as follows: " << endl;
    cout << "   FORWARD_EULER, HEUN_ONE, HEUN_ITR, RK34, RK34A  " << endl;
    cout << "Enter which ODE Solver to use: " << endl;
    cin >> ODE_Solver_method_name;
    
    //saftey check, prints out the parse solver back to the user to confirm it is correct
    //if the string input is not an available method, the two else states should print to console.
    if(ODE_Solver_method_name == "FORWARD_EULER"){ ODE_Solver_method = 0; }
    else if(ODE_Solver_method_name == "HEUN_ONE"){ ODE_Solver_method = 1; }
    else if(ODE_Solver_method_name == "HEUN_ITR"){ ODE_Solver_method = 2; }
    else if(ODE_Solver_method_name == "RK34"){ ODE_Solver_method = 3; }
    else if(ODE_Solver_method_name == "RK34A"){ ODE_Solver_method = 4; }
    else{
        cout << "   ** did not choose a valid ODE solver method, using default: RK34 **" << endl;
        ODE_Solver_method = 3;
    }
    cout << "You chose method: ";
    if( ODE_Solver_method == 0 ){ ODE_Solver_method_name = "FORWARD_EULER"; }
    else if( ODE_Solver_method == 1 ){ ODE_Solver_method_name = "HEUN_ONE"; }
    else if( ODE_Solver_method == 2){ ODE_Solver_method_name = "HEUN_ITR"; }
    else if( ODE_Solver_method == 3 ){ ODE_Solver_method_name = "RK34"; }
    else if(ODE_Solver_method == 4){ ODE_Solver_method_name = "RK34A"; }
    else{
        ODE_Solver_method_name = "error";
    }
    cout << ODE_Solver_method_name << endl;

    //collect the total time duration to run the simulation for
    cout << "Enter the time duration to run your system (in terms of days): " << endl;
    cin >> end_time;
    cout << "Time duration: " << end_time << " days" << endl;

    //collects the time step to run the simulation for
    cout << "Enter the time step to solve your system (in terms of days): " << endl;
    cin >> time_step;
    cout << "Time step: " << time_step << " days" << endl;
}

void saveOutput( vector<vector<double>>* system_states, vector<string>* names, vector<double>* time_log){
    
    //takes a user input to the output file path to save the data to
    cout << "Enter the output file name: " << endl;
    string output_file;
    cin >> output_file;
    
    //opens the provided file given by the path
    ofstream full_log;
    full_log.open( output_file );
    
    //logs the headers for the file, including time and then the state of its position, in the
    // x, y, and z, dimensions
    full_log << "time    ";
    for( int n = 0; n < names->size(); n++){
        full_log << (*names)[n] << "_pos_x  " << (*names)[n] << "_pos_y  " << (*names)[n] << "_pos_z    ";

    }
    full_log << endl;
    
    //console logs the time and states using scientific logging formatting
    for( int i = 0; i< time_log->size(); i++){
        full_log << scientific;

        full_log << (*time_log)[i] << "    "; //logging each time step
        
        //the n_states need to be parsed for only the position state data for each planet
        for( int n = 0; n < names->size(); n++){
            //n_body's start vector position for its position state
            vector<double>::iterator position_start = (*system_states)[i].begin() + 6*n;
            //n_body's end vector position for its position state
            vector<double>::iterator position_end = position_start + 3;
            //collect the positions for n_body in n_body_pos vector
            vector<double> n_body_pos(position_start, position_end);
            
            //log n_body's position states (x,y,z) in the output file
            for( int p = 0; p<n_body_pos.size(); p++){
                full_log << n_body_pos[p] << "  ";
            }
            full_log << "  ";

        }
        full_log << endl;

    }
    
    //confirms to the user when the data has been saved completely and its provided file path destination
    cout << "Data has been saved to file: " << output_file <<endl;
}
