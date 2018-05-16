//
//  user_input_functions.cpp
//  
//
//  Created by Ariana Bruno on 5/16/18.
//

#include "user_input_functions.hpp"

void parseInput( string* path, vector<body>* input_bodies){
    ifstream myfile( *path );
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
    if(ODE_Solver_method_name == "FORWARD_EULER"){ ODE_Solver_method = 0; }
    else if(ODE_Solver_method_name == "HEUN_ONE"){ ODE_Solver_method = 1; }
    else if(ODE_Solver_method_name == "HEUN_ITR"){ ODE_Solver_method = 2; }
    else if(ODE_Solver_method_name == "RK34"){ ODE_Solver_method = 3; }
    else if(ODE_Solver_method_name == "RK34A"){ ODE_Solver_method = 4; }
    else{
        cout << "   ** did not choose a valid ODE solver method, using default: RK34 **" << endl;
        ODE_Solver_method = 3;
    }

    cout << "Enter the time duration to run your system (in terms of days): " << endl;
    cin >> end_time;

    cout << "Enter the time step to solve your system (in terms of days): " << endl;
    cin >> time_step;
}
