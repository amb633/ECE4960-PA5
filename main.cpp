#include "utility_functions.hpp"
#include "celestial_body_functions.hpp"
#include "ode_solvers.hpp"
#include "wrapper.hpp"
#include "test_functions.hpp"
#include <sstream>

int main ( void )
{
    int n_planets;
    cout << "Enter the number of planets: " << endl;
    cin >> n_planets;
    
    vector<body> bodies_user_input;
    
    for(int planet = 0; planet< n_planets; planet++){
        
        double planet_mass = 0;
        double position;
        vector<double> planet_position;
        cout << "Enter planet #" << planet << " mass: " << endl;
        cin >> planet_mass;
        cout << "Enter planet position x, y, z : " << endl;
        string line;
        getline( cin, line);
        istringstream stream(line);
        while (stream >> position)
            planet_position.push_back(position);
        body planet_n( planet_mass, planet_position, planet_position );
        bodies_user_input.push_back(planet_n);
    }

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
	body sun	( 2.0e30 	, { 0.0 , 0.0 , 0.0 } 	 , { 0.0 , 0.0 , 0.0 });
	body mercury( 3.285e23 	, { 0.0 , 5.7e10 , 0.0 } , { 47000 , 0.0 , 0.0 });
	body venus 	( 4.8e24 	, { 0.0 , 1.1e11 , 0.0 } , { 35000 , 0.0 , 0.0 });
	body earth 	( 6.0e24 	, { 0.0 , 1.5e11 , 0.0 } , { 30000 , 0.0 , 0.0 });
	body mars 	( 2.4e24 	, { 0.0 , 2.2e11 , 0.0 } , { 24000 , 0.0 , 0.0 });

	vector<body> bodies = { sun , mercury , venus , earth , mars };

	space_system solar_system;
	create_system( &bodies , &solar_system );

	cout << endl;

	return 0;
}
