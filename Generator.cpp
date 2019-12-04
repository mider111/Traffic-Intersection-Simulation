#include "Generator.h"
#include <iostream>

using namespace std;


Generator::Generator(int initialSeed, double prob_new_vehicle_northbound, double prob_new_vehicle_southbound,
	 										double prob_new_vehicle_eastbound, double prob_new_vehicle_westbound,
	                		double proportion_of_cars, double proportion_of_SUVs,
	                		double proportion_of_trucks, double prob_right_turn_cars,
	   									double prob_left_turn_cars, double prob_right_turn_SUVs,
	    								double prob_left_turn_SUVs,double prob_right_turn_trucks,
											double prob_left_turn_trucks) {
		this->prob_new_vehicle_northbound = prob_new_vehicle_northbound;
		this->prob_new_vehicle_southbound = prob_new_vehicle_southbound;
	 	this->prob_new_vehicle_eastbound = prob_new_vehicle_eastbound;
	 	this->prob_new_vehicle_westbound = prob_new_vehicle_westbound;
	  this->proportion_of_cars = proportion_of_cars;
	  this->proportion_of_SUVs = proportion_of_SUVs;
	  this->proportion_of_trucks = proportion_of_trucks;
		this->prob_right_turn_cars = prob_right_turn_cars;
	  this->prob_left_turn_cars = prob_left_turn_cars;
	  this->prob_right_turn_SUVs = prob_left_turn_SUVs,
	  this->prob_left_turn_SUVs = prob_left_turn_SUVs;
	  this->prob_right_turn_trucks = prob_right_turn_trucks;
		this->prob_left_turn_trucks = prob_left_turn_trucks;
		this->initialSeed = initialSeed;
		rng.seed(initialSeed);
}


Generator::Generator() { }


Generator::~Generator() {	}


VehicleBase* Generator::genNorth() {
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  VehicleBase* temp;
	  if(p >= prob_new_vehicle_northbound*100) {
				// no vehicle spawns, return opposite direction because of required return type -- (return type used to be VehicleBase)
				// when using: check if direction opposite...
			temp = new VehicleBase(VehicleType::car, Direction::south);
		    return temp;
	  }
	  VehicleType type = generateType();
	  bool turn = isTurn(type);
	  if(turn) {
			temp = new VehicleBase(type, Direction::east);
		    return temp;
	  }
		else {
			temp = new VehicleBase(type, Direction::north);
		    return temp;
	  }
}


VehicleBase* Generator::genSouth() {
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  VehicleBase* temp;
	  if(p >= prob_new_vehicle_southbound*100) {
				// no vehicle spawns, return opposite direction because of required return type
				// when using: check if direction opposite...
			temp = new VehicleBase(VehicleType::car, Direction::north);
		    return temp;
	  }
	  VehicleType type = generateType();
	  bool turn = isTurn(type);
	  if(turn) {
			temp = new VehicleBase(type, Direction::west);
		    return temp;
	  }
	  else {
			temp = new VehicleBase(type, Direction::south);
		    return temp;
	  }
}

VehicleBase* Generator::genEast() {
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  VehicleBase* temp;
	  if(p >= prob_new_vehicle_eastbound*100) {
				// no vehicle spawns, return opposite direction because of required return type
				// when using: check if direction opposite...
			temp = new VehicleBase(VehicleType::car, Direction::west);
		    return temp;
	  }
	  VehicleType type = generateType();
	  bool turn = isTurn(type);
	  if(turn) {
			temp = new VehicleBase(type, Direction::south);
		    return temp;
	  }
	  else {
			temp = new VehicleBase(type, Direction::east);
		    return temp;
	  }
}


VehicleBase* Generator::genWest() {
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  VehicleBase* temp;
	  if(p >= prob_new_vehicle_westbound*100) {
				// no vehicle spawns, return opposite direction because of required return type
				// when using: check if direction opposite...
		    temp = new VehicleBase(VehicleType::car, Direction::east);
		    return temp;
	  }
	  VehicleType type = generateType();
	  bool turn = isTurn(type);
	  if(turn) {
	    	temp = new VehicleBase(type, Direction::north);
	    	return temp;
	  }
	  else {
	    	temp = new VehicleBase(type, Direction::west);
	    	return temp;
	  }
}

bool Generator::isTurn(VehicleType type) {
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  if(type == VehicleType::car) {
		    if(p < (int)(prob_right_turn_cars*100)) {
		      	return true;
		    }
	  		else {
	  				return false;
	  		}
	  }
	  else if(type == VehicleType::suv) {
	    if(p < (int)(prob_right_turn_SUVs*100)) {
	      	return true;
	    }
	    else {
	      	return false;
	    }
	  }
	  else if(type == VehicleType::truck) {
	    if(p < (int)(prob_right_turn_trucks*100)) {
	      	return true;
	    }
	    else {
	      	return false;
	    }
	  }
	  else {
	    	return false;
	  }
}

VehicleType Generator::generateType()
{
	  uniform_int_distribution<int> rng_int(1, 100);
	  int p = rng_int(rng);
	  if(p < (int)(proportion_of_cars*100)) {
	    	return VehicleType::car;
		}
	  else if(((int)(proportion_of_cars*100) <= p) && (p < (int)((proportion_of_cars + proportion_of_SUVs)*100))) {
	    	return VehicleType::suv;
		}
	  else {
	    return VehicleType::truck;
		}
}
