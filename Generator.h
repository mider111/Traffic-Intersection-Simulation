#ifndef __GENERATOR_H__
#define __GENERATOR_H__
#include "VehicleBase.h"
#include <random>

using namespace std;

class Generator {

	private:
			double prob_new_vehicle_northbound;
	    double prob_new_vehicle_southbound;
	    double prob_new_vehicle_eastbound;
	    double prob_new_vehicle_westbound;
	    double proportion_of_cars;
	    double proportion_of_SUVs;
	    double proportion_of_trucks;
	    double prob_right_turn_cars;
	    double prob_left_turn_cars;
	    double prob_right_turn_SUVs;
	    double prob_left_turn_SUVs;
	    double prob_right_turn_trucks;
	    double prob_left_turn_trucks;
			int initialSeed;
			mt19937 rng;

	public:
			Generator();

			Generator(int initialSeed, double prob_new_vehicle_northbound, double prob_new_vehicle_southbound,
		 							double prob_new_vehicle_eastbound, double prob_new_vehicle_westbound,
		              double proportion_of_cars, double proportion_of_SUVs,
		              double proportion_of_trucks, double prob_right_turn_cars,
		   						double prob_left_turn_cars, double prob_right_turn_SUVs,
		    					double prob_left_turn_SUVs,double prob_right_turn_trucks,
									double prob_left_turn_trucks);

			~Generator();

			VehicleBase* genNorth();

			VehicleBase* genSouth();

			VehicleBase* genEast();

			VehicleBase* genWest();

			bool isTurn(VehicleType type);

			VehicleType generateType();
};

#endif
