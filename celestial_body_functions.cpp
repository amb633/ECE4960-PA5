#include "celestial_body_functions.hpp"

void celestial_functions::printBody( body* which_body )
{
	cout << endl;
	cout << " mass of body : " << (*which_body).mass << endl;
	cout << " position of body : " ; printVector( &((*which_body).position) );
	cout << " velocity of body : " ; printVector( &((*which_body).velocity) );
	cout << endl;
}

void celestial_functions::find_acceleration( double time , int which_body , vector<body>* celestial_bodies , vector<double>* acceleration )
{
	double g_const = 6.67408e-11; //m3 kg-1 s-2

	int n_bodies = (*celestial_bodies).size();
	vector<double> current_body = (*celestial_bodies)[which_body].position;

	// create a 3x1 zero vector in acceleration
	zeroVector( 3 , acceleration );

	for ( int i = 0 ; i < n_bodies ; i++ )
	{
		if ( i == which_body ) continue;

		// find distance from current body to other bodies and cube it
		vector<double> other_body = (*celestial_bodies)[i].position;
		double distance;
		vectorNorm( &current_body , &other_body , distance );
		distance = pow( distance , 3.0 );
		cout << "euclidean distance cubed is = " << distance << endl;

		// find displacement of other body from current body
		vector<double> displacement;
		vectorDiff( &current_body , &other_body , &displacement );


		// multiply the displacement by the mass of the other body
		scaleVector( (*celestial_bodies)[i].mass , &displacement , &displacement );
		// divide by the euclidean distance cubed
		scaleVector( 1.0/distance , &displacement , &displacement );
		cout << "displacement is = " ; printVector ( &displacement );
		// cumulative sum in acceleration
		vectorSum( acceleration , &displacement , acceleration );
		cout << "acceleration is = "; printVector( acceleration );

	}

	// finally scale by the gravitational constant
	scaleVector( -g_const , acceleration , acceleration );
	// cout << "acceleration is = "; printVector( acceleration );

	return;
}