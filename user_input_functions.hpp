//
//  user_input_functions.hpp
//  
//
//  Created by Ariana Bruno on 5/16/18.
//

#ifndef user_input_functions_hpp
#define user_input_functions_hpp

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "celestial_body_functions.hpp"


void parseInput( string* path, vector<body>* input_bodies);
void getSolverInput( int& ODE_Solver_method, double& end_time, double& time_step );

#endif /* user_input_functions_hpp */
