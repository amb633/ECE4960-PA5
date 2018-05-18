//
//  user_input_functions.cpp
//  
//
//  Created by Ariana Bruno on 5/16/18.
//

#include "user_input_functions.hpp"

void parseInput( vector<body>* input_bodies){
    string path;
    cout << "Enter file path for planetary system's data: " << endl;
    cin >> path;
//    path = "/Users/arianabruno/Desktop/ECE4960/ProgrammingAssignments/ECE4960-PA5/user_input/test2.txt";
    ifstream myfile( path );
    if (myfile.is_open()){
        myfile.ignore(2048 , '\n');
        while( !myfile.eof() ){
            string name;
            double mass , x, y, z, vx, vy, vz;
            vector<double> position, velocity;
            myfile >> name >> mass >> x >> y >> z >> vx >> vy >> vz;
            position = {x,y,z};
            velocity = {vx,vy,vz};
            body planet_n( name, mass, position, velocity );
            input_bodies->push_back(planet_n);
        }
        myfile.close();
        
        cout << "Successfully parsed input data " << endl;
    }
    else cout << "Unable to open file " << endl;
}

void getSolverInput( int& ODE_Solver_method, double& end_time, double& time_step ){
    string ODE_Solver_method_name;
    cout << "Available ODE Solvers are as follows: " << endl;
    cout << "   FORWARD_EULER, HEUN_ONE, HEUN_ITR, RK34, RK34A  " << endl;
    cout << "Enter which ODE Solver to use: " << endl;
    cin >> ODE_Solver_method_name;
    cout << ODE_Solver_method_name << endl;
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

    cout << "Enter the time duration to run your system (in terms of days): " << endl;
    cin >> end_time;
    cout << "Time duration: " << end_time << " days" << endl;

    cout << "Enter the time step to solve your system (in terms of days): " << endl;
    cin >> time_step;
    cout << "Time step: " << time_step << " days" << endl;
}

void saveOutput( vector<vector<double>>* system_states, vector<string>* names, vector<double>* time_log){
    
    cout << "Enter the output file name: " << endl;
    string output_file;
    cin >> output_file;
    
    ofstream full_log;
    full_log.open( output_file );
    
    full_log << "time    ";
    for( int n = 0; n < names->size(); n++){
        full_log << (*names)[n] << "_pos_x  " << (*names)[n] << "_pos_y  " << (*names)[n] << "_pos_z    ";
        // cout << (*names)[n] << "_pos_x  " << (*names)[n] << "_pos_y  " << (*names)[n] << "_pos_z    ";

    }
    full_log << endl;
    
    for( int i = 0; i< time_log->size(); i++){
        full_log << scientific;
        // cout << scientific;

        full_log << (*time_log)[i] << "    ";
        // cout << (*time_log)[i] << "    ";
        
        for( int n = 0; n < names->size(); n++){
            vector<double>::iterator position_start = (*system_states)[i].begin() + 6*n;
            vector<double>::iterator position_end = position_start + 3;
            vector<double> n_body_pos(position_start, position_end);
            for( int p = 0; p<n_body_pos.size(); p++){
                full_log << n_body_pos[p] << "  ";
                // cout << n_body_pos[p] << "  ";
            }
            full_log << "  ";
            // cout << "  ";

        }
        full_log << endl;
        // cout << "  ";

    }
    
    cout << "Data has been saved to file: " << output_file <<endl;
}
