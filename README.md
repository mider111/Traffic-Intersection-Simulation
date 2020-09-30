Traffic Intersection Simulation

Compilation instructions: This program can be compiled by using the command
'make' in UNIX. It was tested on Mac OSX and Windows Subsystem for Linux.

Execution instructions: This program may be executed as follows:
./RoadSim input_file_format.txt [boolean]' -- the boolean (true or false) denotes whether or
not the user wishes to use pause-and-step-by-keystroke functionality to proceed
one time unit at a time. Within the folder is a sample for the input format.

Traffic-related design decisions: This program simulates an intersection between
two roads, with 4 lanes, and 2 traffic lights. The lanes, which exist in four
directions - northbound, southbound, eastbound, westbound - are divided into
sections which may be occupied by vehicles. There are three types of vehicles
simulated - Car, SUV, and Truck, taking up 2,3, and 4 sections respectively.
These vehicles may proceed through the intersection only when the light is
green or yellow, conditional on there being enough time to completely clear
the intersection before the traffic light turns right. Vehicles are able to
proceed straight or turn right. A vehicle may proceed forward or turn right
one section on each time-step, which is done using an integer-based clock.

Object oriented programming design decisions: This simulation uses 5 classes,
and an animator class. These are: VehicleBase{.h, .cpp}, Section{.h, .cpp}
Lane{.h, .cpp}, Roadway{.h, .cpp}, Generator{.h, .cpp}, and RoadSim{.cpp}.
Descriptions for each of these classes can be found below.

VehicleBase{.h, .cpp}: Each vehicle has a unique ID, a type {Car, SUV, Truck},
and a size. VehicleBase given by Dr. Barry Lawson, with modifications.

Section{.h, .cpp}: Sections hold a pointer to an instance of vehicle. A vehicle
may occupy two or more of these sections. Each section has a pointer to the
forwardSection (in front of it in the lane), and a rightSection (if one exists).

Lane{.h, .cpp}: Each lane is constructed with a unique direction (north, south,
east, west), and has a number of sections from user input. Vehicles are randomly
spawned into the lane using the Generator class. If a vehicle spawns, it is
placed in the 'enterSpace' of 5 sections, before entering the lane one section
at a time. This insertion is done using the insert method. The crucial method of
this class is the advance method. This method is called from Roadway and takes
the remaining time before the traffic light turns red, if any, and a pointer
to the lane to which vehicles would turn right into. The advancement of vehicles
through the sections in a lane is done using pointers. Each section, as
described above has a pointer to the section in front of it, and the one to
its right if any exists. Before the intersection and after it, a vehicle will
proceed forward if it can, when the section in front is unoccupied. At the
intersection, if time permits it will enter it, and turn right if its final
direction of travel is not the same as the direction of the lane.

Roadway{.h, .cpp}: Each roadway consists of four lanes in each direction.
Roadway sets up the lanes such that the appropriate sections are linked for
right turns. It also creates an instance of Generator so that vehicles can be
randomly generated. The advance function generates a vehicle for each lane
using Generator. It inserts the vehicle if one does spawn using Lane's insert,
and calls advance on each lane.

Generator{.h, .cpp}: This class handles all random spawning of vehicles. We use
a clock-based initialSeed for our random integer generation. Each lane, by
direction, has its own generation method since probabilities differ. this
method will always return an appropriate vehicle, its type, and whether it will
turn right or not all based on probabilities from the input. Because of a prior
design choice, a vehicle is always returned, but if one isn't supposed to
it is returned with a final direction opposition to that of the lane, which
is not possible and handled on the end of Lane's insert method.

RoadSim{.cpp}: RoadSim is the main class of this simulation. It reads the input
file, constructs an instance of Roadway, and runs the simulation on it. For the
time clock, we use a while loop and increment time on each run. It constructs
an instance of animator to illustrate the simulation. Initially lights are set
to red for NorthSouth, and green for EastWest. Using the input data on the
time each traffic light is activated, this class appropriately switches the
traffic lights using the time-clock. The rest is done entirely by calling
Roadway's advance function, and passing the time remaining on each of the
traffic lights.

Animator{.h, .cpp}: Animator is used to illustrate this simulation.

