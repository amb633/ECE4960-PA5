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
