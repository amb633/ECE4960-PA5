# ECE4960-PA5 - Programming Assignment 5 n-body Simulation using ODE Solvers

**Summary**
This program focuses on using ODE solvers for the n-body problem. Specificially, ODE solvers will be used to simulate the behavior of th Solar System over time. Five different ODE solvers were implemented: Euler, Heun One Step, Heun Iterative, Standard Runge-Kutta, and Adaptive Runge-Kutta. The main program builds all relevant functions in the C++ language. Plotting and visualization is done through MATLAB.

***************************************************************************
### Usage
***************************************************************************
The program is simple to use for users looking to simulate any arbitary astronomical system.  The user will have to first define all the bodies with a name, mass, and initial starting positions and velocities in a .txt file. Running the program will result in a series of prompts to the user:

**`./main`**

- **Enter file path for planetary system's data**: Enter the directory where the above .txt file is stored
- **Enter which ODE Solver to use**: the available solvers are: `FORWARD_EULER` , `HEUN_ONE`, `HEUN_ITR`, `RK34` and `RK34A`
- **Enter the time duration to run your system**: Enter the desired duration in days
- **Enter the time duration to run your system**: Enter the desired time-step in days
- **Enter the output file name**: Enter the file to which data will be stored

***************************************************************************
### Part 0 - Utility Functions
***************************************************************************
**Overview:** Common utility functions that will be accessed and used commonly throughout the assignment. All functions have been resused from previous programming assignments.

***************************************************************************
### Part 1 - Celestial Body Functions
***************************************************************************
**Overview:** Implementation of the astronomical system that will be solved using the five methods discussed in Part 2.

**Documentation:**
On the user interface side, the astronomical system will be defined in a body-specific manner - i.e. for each body there will be a name, mass, position, velocity and acceleration. This will then be converted to a flattened vector structure for handling by the ODE solvers.

**`body()`** is the the primary structure that will be used to define each body in the system

**`space_system()`** is the flattened vector form that fits the standard function signature required by the ODE solvers

**`create_system()`** transforms the user-friendly body specific information to solver-friendly flattened information

**`resolve_system()`** transforms the flattened information back to body specific information

**`find_state_dot()`** defines the time-varying behavious of the system:
- `time`: `double` value for sending the current time step
- `parameters`: `vector<double>` for sending in user-defined parameters of the system (in this case the mass of each body)
- `input`: `vector<double` for sending the state of the system at the current time step
- `output`: `vector<double` for storing the calculated slope of the system at the current time step

In the `wrapper` files, the `simulate_system()` function is defined. This is the primary function that will be called to find the updated state of the system at each time step.


***************************************************************************
### Part 2 - ODE Solver Methods
***************************************************************************
**Overview:** Implementation of ODE Solver methods that solve the astronomical system defined in Part 1. A bulk of this code is reused from PA4.

**Documentation:**
All functions have to create/ call the these variables:
- `function` : a function pointer to the ODE function that needs to be resolved, in this case, the `find_state_dot()` function.
- `time`: `double` value for sending the current time value
- `march`: `double` value for sending the time interval (h) value at each iteration
- `parameters`: `vector<double>` for sending user defined parameters
- `input`: `vector<double>` for sending in the current state of the system
- `output` : `vector<double>` for storing the calculated slope of the system

**`forward_euler()`**: solves for the slope at each time step using the forward euler method and the system's ODE given as a pointer.

**`heun_oneStep()`**: solves for the slope using the Heun method without iteration

**`heun_iterative()`**: solves for the slope using the iterative Heun method, using a default error tolerance of 1e-7

**`rk34()`**: solves for the slope using the Runge-Kutta 34 method. Optional parameters include a boolean flag for time-stepping adaptivity, and error tolerance values. There are two helper functions for the RK34 method:

`rk34_error()` calculates the error between the 3rd order and 4th order estimates

`rk34_new_march()` calculates the adaptive time-step based on the error above


**`ODE_Solver()`**: parent function to switch between the five different solvers based on user-input. Default is RK34.
