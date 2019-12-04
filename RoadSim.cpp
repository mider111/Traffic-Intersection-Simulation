#include <iostream>
#include <fstream>
#include "VehicleBase.h"
#include "Roadway.h"
#include "Animator.h"
#include <chrono>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]) {

    // ********************
    // Read Input
    // ********************
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        return 0;
    }

    bool step = false;
    if(!strcmp(argv[2], "true")) {
        step = true;
    }
    else {
        step = false;
    }
    char dummy;

    ifstream inputFile;

    inputFile.open(argv[1]);
    if(!inputFile.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 0;
    }

    long count = 0;
    double input [18];
    string temp;
    while (inputFile.good()) {
        inputFile >> temp;
        inputFile >> input[count];
        if (inputFile.fail()) {
            if (inputFile.eof()) {
                // exit loop
            }
            else {
                cerr << "Error reading an integer or string..." << endl;
                return 1;
            }
        }
        else {
            count++;
        }
    }
    inputFile.close();

    int maximum_simulated_time = input[0];
    int number_of_sections_before_intersection = input[1];
    int green_north_south = input[2];
    int yellow_north_south = input[3];
    int green_east_west = input[4];
    int yellow_east_west = input[5];
    double prob_new_vehicle_northbound = input[6];
    double prob_new_vehicle_southbound = input[7];
    double prob_new_vehicle_eastbound = input[8];
    double prob_new_vehicle_westbound = input[9];
    double proportion_of_cars = input[10];
    double proportion_of_SUVs = input[11];
    double proportion_of_trucks = 1 - proportion_of_cars - proportion_of_SUVs;
    double prob_right_turn_cars = input[12];
    double prob_left_turn_cars = input[13];
    double prob_right_turn_SUVs = input[14];
    double prob_left_turn_SUVs = input[15];
    double prob_right_turn_trucks = input[16];
    double prob_left_turn_trucks = input[17];

    int t = 0;

    int initialSeed = chrono::system_clock::now().time_since_epoch().count() + 10;

    Roadway roadway(initialSeed, number_of_sections_before_intersection,  green_north_south, yellow_north_south,
               green_east_west,  yellow_east_west, prob_new_vehicle_northbound,
               prob_new_vehicle_southbound, prob_new_vehicle_eastbound,
               prob_new_vehicle_westbound, proportion_of_cars, proportion_of_SUVs,
               proportion_of_trucks, prob_right_turn_cars,
               prob_left_turn_cars, prob_right_turn_SUVs,
               prob_left_turn_SUVs, prob_right_turn_trucks,
               prob_left_turn_trucks);

    int halfSize = number_of_sections_before_intersection;  // number of sections before intersection

    Animator anim(halfSize);

    // construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase*> westbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> eastbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> southbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> northbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    for (int i = 0; i < number_of_sections_before_intersection * 2 + 2; i++) {
        westbound[i] = roadway.getSection(Direction::west, i)->getVehicle();
        eastbound[i] = roadway.getSection(Direction::east, i)->getVehicle();
        northbound[i] = roadway.getSection(Direction::north, i)->getVehicle();
        southbound[i] = roadway.getSection(Direction::south, i)->getVehicle();
    }

    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    LightColor LightNorthSouth = LightColor::red;
    LightColor LightEastWest = LightColor::green;

    int remaining_time_NorthSouth;
    int remaining_time_EastWest;

    int counter = 0;
    while (t <= maximum_simulated_time) {
        for (int i = 0; i < number_of_sections_before_intersection * 2 + 2; i++) {
            westbound[i] = roadway.getSection(Direction::west, i)->getVehicle();
            eastbound[i] = roadway.getSection(Direction::east, i)->getVehicle();
            northbound[i] = roadway.getSection(Direction::north, i)->getVehicle();
            southbound[i] = roadway.getSection(Direction::south, i)->getVehicle();
        }
        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        anim.setVehiclesWestbound(westbound);
        anim.draw(t);

        // This below handles the traffic lights
        if (counter == green_east_west) {
            anim.setLightEastWest(LightColor::yellow);
            LightEastWest = LightColor::yellow;
        }
        if (counter == green_east_west + yellow_east_west) {
            anim.setLightEastWest(LightColor::red);
            anim.setLightNorthSouth(LightColor::green);
            LightEastWest = LightColor::red;
            LightNorthSouth = LightColor::green;
        }
        if (counter == green_east_west + yellow_east_west + green_north_south) {
            anim.setLightNorthSouth(LightColor::yellow);
            LightNorthSouth = LightColor::yellow;
        }
        if (counter == green_east_west + yellow_east_west + green_north_south + yellow_north_south) {
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
            LightEastWest = LightColor::green;
            LightNorthSouth = LightColor::red;
            counter = 0;
        }
        counter++;
        // *******************
        if (green_east_west + yellow_east_west - counter >= 0) {
            remaining_time_EastWest = green_east_west + yellow_east_west - counter;
        }
        else {
            remaining_time_EastWest = 0;
        }

        if (remaining_time_EastWest == 0) {
            remaining_time_NorthSouth = green_east_west + yellow_east_west + green_north_south + yellow_north_south - counter;
        }
        else {
            remaining_time_NorthSouth = 0;
        }
        roadway.advance(remaining_time_NorthSouth, remaining_time_EastWest);

        t++;
        if (step) {
            cin.get();
        }
    }

    return 0;
}
