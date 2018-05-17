//
//  main.cpp
//  hackerPractNote6
//
//  Created by Ariana Bruno on 4/12/18.
//  Copyright © 2018 Ariana Bruno. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

//double function_f(double x){
//
//    return 1.0;
//}
//
//double f_prime(double h1, double h2, double x){
//    double term1 = (h1/(h2*(h1-h2)))*function_f(x+h2);
//    double term2 = -1.0*((h1+h2)/(h1*h2))*function_f(x);
//    double term3 = -1.0*(h2/(h1*(h1-h2)))*function_f(x+h1);
//    return term1+term2+term3;
//}

double h61_GT(double t){
    return exp(-t);
}

double h61_backEuler(double t, double dt){
    if( t == 0.0 ){
        return 1.0;
    }else{
        return (1/(1+dt))*h61_GT(t-dt);
    }
}

double h61_trapEuler(double t, double dt){
    if( t == 0.0 ){
        return 1.0;
    }else{
        return ((2-dt)/(2+dt))*h61_GT(t-dt);
    }
}

void h61(){
    char separator    = ' ';
    int table_width = 17;
    cout <<  left << setw(8) << setfill(separator) << "t";
    cout <<  left << setw(table_width) << setfill(separator) << "Ground Truth";
    cout <<  left << setw(table_width) << setfill(separator) << "Backward Euler";
    cout <<  left << setw(table_width) << setfill(separator) << "||BE - GT||";
    cout <<  left << setw(table_width) << setfill(separator) << "Trapezoid Euler";
    cout <<  left << setw(table_width) << setfill(separator) << "||TE - GT||"<< endl;
    double t = 0.0;
    double delta_t = 0.5;
    while( t <= 20.0 ){
        double result_GT = h61_GT(t);
        double result_backEuler = h61_backEuler(t, delta_t);
        double result_trapEuler = h61_trapEuler(t, delta_t);
        
        cout <<  left << setw(8) << setfill(separator) << t;
        cout <<  left << setw(table_width) << setfill(separator) << result_GT;
        cout <<  left << setw(table_width) << setfill(separator) << result_backEuler;
        cout <<  left << setw(table_width) << setfill(separator) << (result_GT - result_backEuler);
        cout <<  left << setw(table_width) << setfill(separator) << result_trapEuler;
        cout <<  left << setw(table_width) << setfill(separator) << (result_GT - result_trapEuler)<< endl;
        t += 0.5;
    }
}

double h62_exact( double t ){
    return (((4/1.3)*(exp(0.8*t) - exp(-0.5*t))) + 2*exp(-0.5*t));
}

double h62_dx_dt( double x, double t ){
    return (4*exp(0.8*t)) - 0.5*x;
}

double h62_forwardEuler(double x_prev, double t, double h){
    if ( t == 0.0 ){
        return 2.0;
    } else {
        return x_prev + h*h62_dx_dt(x_prev, t-h);
    }
}

double h62_Huen(double x_prev, double t, double h){
    if ( t == 0.0 ){
        return 2.0;
    } else {
        double x_j_0 = x_prev + h62_dx_dt(x_prev, t-h);
        return (x_prev + (((h62_dx_dt(x_prev, t-h)) + h62_dx_dt(x_j_0, t))/2.0)*h);
    }
}

double h62_Huen_corrector( double x_prev, double h, double t, double x_j){
    return x_prev + ((h62_dx_dt(x_prev, t-h) + h62_dx_dt(x_j, t))/2.0);
}

double h62_Huen_itr( double x_prev, double t, double h, double x_j = -0.0){
    if ( t == 0.0 ){
        return 2.0;
    }
    double iter_critera, x_j2;
    if( x_j == -0.0 ){
        x_j = h62_Huen(x_prev, t-h, h);
    }
    
    x_j2 = h62_Huen_corrector(x_prev, h, t, x_j);
    iter_critera = abs(x_j2-x_j)/x_j2;
    
        double result;
        
    if (iter_critera < 1e-7){
        result =  x_j2;
    } else{
        result = h62_Huen_itr(x_prev, t, h, x_j2);
    }
    return result;
}

void h62(){
    char separator    = ' ';
    int table_width = 15;
    cout <<  left << setw(8) << setfill(separator) << "t";
    cout <<  left << setw(table_width) << setfill(separator) << "x true";
    cout <<  left << setw(table_width) << setfill(separator) << "x forward";
    cout <<  left << setw(table_width) << setfill(separator) << "|e_forward|";
    cout <<  left << setw(table_width) << setfill(separator) << "Huen";
    cout <<  left << setw(table_width) << setfill(separator) << "|e_huen|";
    cout <<  left << setw(table_width) << setfill(separator) << "Huen iter";
    cout <<  left << setw(table_width) << setfill(separator) << "|e_huen_iter|"<< endl;
    double h = 1.0;
    double t = 0.0;
    double x = 2.0;
    double x_t = x;
    double x1 = x;
    double x2 = x;
    double x3 = x;
    while ( t <= 4 ){
        cout <<  left << setw(8) << setfill(separator) << t;
        x_t = h62_exact(t);
        cout <<  left << setw(table_width) << setfill(separator) << x_t;
        x1 = h62_forwardEuler(x1, t, h);
        cout <<  left << setw(table_width) << setfill(separator) <<  x1;
        cout <<  left << setw(table_width) << setfill(separator) <<  (abs(x1-x_t)/x_t)*100;
        x2 = h62_Huen(x2, t, h);
        cout <<  left << setw(table_width) << setfill(separator) <<  x2;
        cout <<  left << setw(table_width) << setfill(separator) <<  (abs(x2-x_t)/x_t)*100;
        x3 = h62_Huen_itr(x3, t, h);
        cout <<  left << setw(table_width) << setfill(separator) <<  x3;
        cout <<  left << setw(table_width) << setfill(separator) <<  (abs(x3-x_t)/x_t)*100 << endl;
        t += h;
    }
}

double h63_k1(double x, double t, double h){
    return h62_dx_dt(x, t);
}

double h63_k2(double x, double t, double h, double k1){
    return h62_dx_dt(x + (k1*h/2.0), t + (h/2.0));
}

double h63_k3(double x, double t, double h, double k2){
    return h62_dx_dt(x + (k2*h/2.0), t + (h/2.0));
}

double h63_k4(double x, double t, double h, double k3){
    return h62_dx_dt(x + (k3*h), t + h);
}

double h63_RK4(double x_prev, double k1, double k2, double k3, double k4, double h){
    return x_prev + ((1.0/6.0)*(k1 + (2.0*k2) + (2.0*k3) + k4)*h);
}

void h63(){
    char separator    = ' ';
    int table_width = 15;
    cout <<  left << setw(8) << setfill(separator) << "t";
    cout <<  left << setw(table_width) << setfill(separator) << "x true";
    cout <<  left << setw(table_width) << setfill(separator) << "k1";
    cout <<  left << setw(table_width) << setfill(separator) << "k2";
    cout <<  left << setw(table_width) << setfill(separator) << "k3";
    cout <<  left << setw(table_width) << setfill(separator) << "k4";
    cout <<  left << setw(table_width) << setfill(separator) << "x_RK4";
    cout <<  left << setw(table_width) << setfill(separator) << "|e_xRK4|"<< endl;
    double h = 1.0;
    double t = 0.0;
    double x = 2.0;
    double x_t = x;
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double x_RK4 = x;
    while ( t <= 4 ){
        if (t == 0 ){
            cout <<  left << setw(8) << setfill(separator) << t;
            x_t = h62_exact(t);
            cout <<  left << setw(table_width) << setfill(separator) << x_t << endl;
        } else {
            cout <<  left << setw(8) << setfill(separator) << t;
            x_t = h62_exact(t);
            cout <<  left << setw(table_width) << setfill(separator) << x_t;
            k1 = h63_k1(x, t - h, h);
            cout <<  left << setw(table_width) << setfill(separator) <<  k1;
            k2 = h63_k2(x, t - h, h, k1);
            cout <<  left << setw(table_width) << setfill(separator) <<  k2;
            k3 = h63_k3(x, t - h, h, k2);
            cout <<  left << setw(table_width) << setfill(separator) <<  k3;
            k4 = h63_k4(x, t - h, h, k3);
            cout <<  left << setw(table_width) << setfill(separator) <<  k4;
            x = h63_RK4(x, k1, k2, k3, k4, h);
            cout <<  left << setw(table_width) << setfill(separator) <<  x;
            cout <<  left << setw(table_width) << setfill(separator) <<  (abs(x-x_t)/x_t)*100 << endl;
        }
        t += h;
    }
    
}

double h64_k1(double x_prev, double t){
    return h62_dx_dt(x_prev, t);
}

double h64_k2(double x_prev, double t, double h, double k1){
    return h62_dx_dt(x_prev + (k1*h/2.0), t + (h/2.0));
}

double h64_k3(double x_prev, double t, double h, double k2){
    return h62_dx_dt(x_prev + (3.0*k2*h/4.0), t + (3.0*h/4.0));
}

double h64_k4(double x_prev, double t, double h, double k3){
    return h62_dx_dt(x_prev + k3*h, t + h);
}

double h64_RK4(double x_prev, double k1, double k2, double k3, double k4, double h){
    return x_prev + ((1.0/24.0)*((7.0*k1) + (6.0*k2) + (8.0*k3) + (3.0*k4))*h);
}

double h64_error31(double k1, double k2, double k3, double k4, double h){
    return ((1/72.0)*(-5.0*k1 + 6.0*k2 + 8.0*k3 -9*k4)*h);
}

void h64(){
    char separator    = ' ';
    int table_width = 15;
    cout <<  left << setw(8) << setfill(separator) << "t";
    cout <<  left << setw(table_width) << setfill(separator) << "x true";
    cout <<  left << setw(table_width) << setfill(separator) << "x_RK4";
    cout <<  left << setw(table_width) << setfill(separator) << "|e_xRK4|";
    cout <<  left << setw(table_width) << setfill(separator) << "error eqn(31)";
    cout <<  left << setw(table_width) << setfill(separator) << "time step eqn(33)" << endl;
    double h = 1.0;
    double t = 0.0;
    double x = 2.0;
    double x_t = x;
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double e_R = 0;
    double err31 = 0;
    double step33 = 0;
    //    double x_RK4 = x;
    while ( t <= 4 ){
        if (t == 0 ){
            cout <<  left << setw(8) << setfill(separator) << t;
            x_t = h62_exact(t);
            cout <<  left << setw(table_width) << setfill(separator) << x_t << endl;
        } else {
            cout <<  left << setw(8) << setfill(separator) << t;
            x_t = h62_exact(t);
            cout <<  left << setw(table_width) << setfill(separator) << x_t;
            k1 = h64_k1(x, t - h); k2 = h64_k2(x, t - h, h, k1); k3 = h64_k3(x, t - h, h, k2); k4 = h64_k4(x, t - h, h, k3);
            
            x = h64_RK4(x, k1, k2, k3, k4, h);
            cout <<  left << setw(table_width) << setfill(separator) << x;
            e_R = (abs(x-x_t)/x_t);
            cout <<  left << setw(table_width) << setfill(separator) << e_R*100 ;
            err31 = h64_error31(k1, k2, k3, k4, h);
            cout <<  left << setw(table_width) << setfill(separator) << err31;
            step33 = h * pow((e_R/(abs(err31/x))),(1.0/3.0));
            cout <<  left << setw(table_width) << setfill(separator) << step33 << endl;
//            h = step33;
            
        }
        t += h;
    }
}

int main(int argc, const char * argv[]) {
//    Hacker practice 6.1
    cout << endl << "Hacker Practice 6.1" << endl << endl;
    h61();
    //    Hacker practice 6.2
    cout << endl << "Hacker Practice 6.2" << endl << endl;
    h62();
//    //    Hacker practice 6.3
//    cout << endl << "Hacker Practice 6.3" << endl << endl;
//    h63();
//    //    Hacker practice 6.4
//    cout << endl << "Hacker Practice 6.4" << endl << endl;
//    h64();
//    cout << endl;
    return 0;
}
