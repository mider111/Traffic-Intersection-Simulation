#include "Roadway.h"
#include "VehicleBase.h"


Roadway::Roadway(int initialSeed, int numSections_before_int, int green_north_south, int yellow_north_south,
                  int green_east_west, int yellow_east_west, double prob_new_vehicle_northbound,
                  double prob_new_vehicle_southbound, double prob_new_vehicle_eastbound,
                  double prob_new_vehicle_westbound, double proportion_of_cars, double proportion_of_SUVs,
                  double proportion_of_trucks, double prob_right_turn_cars,
                  double prob_left_turn_cars, double prob_right_turn_SUVs,
                  double prob_left_turn_SUVs,double prob_right_turn_trucks,
                  double prob_left_turn_trucks) {
		this->numSections_before_int = numSections_before_int;
		this->green_north_south = green_north_south;
		this->yellow_north_south = yellow_north_south;
		this->green_east_west = green_east_west;
		this->yellow_east_west = yellow_north_south;
		// Instantiating lanes
		nlane = Lane(Direction::north, numSections_before_int);
 		slane = Lane(Direction::south, numSections_before_int);
 		elane = Lane(Direction::east, numSections_before_int);
 		wlane = Lane(Direction::west, numSections_before_int);
 		nlane.getSection(numSections_before_int)->setRightSection(elane.getSection(numSections_before_int+2));
 		slane.getSection(numSections_before_int)->setRightSection(wlane.getSection(numSections_before_int+2));
 		elane.getSection(numSections_before_int)->setRightSection(slane.getSection(numSections_before_int+2));
 		wlane.getSection(numSections_before_int)->setRightSection(nlane.getSection(numSections_before_int+2));
 		gen = Generator(initialSeed, prob_new_vehicle_northbound, prob_new_vehicle_southbound,
                  prob_new_vehicle_eastbound, prob_new_vehicle_westbound,
                  proportion_of_cars, proportion_of_SUVs, proportion_of_trucks,
                  prob_right_turn_cars, prob_left_turn_cars, prob_right_turn_SUVs,
	    			      prob_left_turn_SUVs, prob_right_turn_trucks, prob_left_turn_trucks);

}

Roadway::~Roadway() { }

void Roadway::advance(int remain_ns, int remain_ew) {
    // Instead of returning null when a new vehicle doesn't spawn
    // we return a vehicle going the opposite direction (impossible)
    VehicleBase* temp1 = gen.genNorth();
    VehicleBase* temp2 = gen.genSouth();
    VehicleBase* temp3 = gen.genEast();
    VehicleBase* temp4 = gen.genWest();
    if (temp1->getVehicleOriginalDirection() == Direction::south) {
        delete temp1;
    } // exit loop
    else { nlane.insert(temp1); }
    nlane.advance(remain_ns, &elane);

    if (temp2->getVehicleOriginalDirection() == Direction::north) {
        delete temp2;
    } // exit loop
    else { slane.insert(temp2); }
    slane.advance(remain_ns, &wlane);

    if (temp3->getVehicleOriginalDirection() == Direction::west) {
        delete temp3;
    } // exit loop
    else { elane.insert(temp3); }
    elane.advance(remain_ew, &slane);

    if (temp4->getVehicleOriginalDirection() == Direction::east) {
        delete temp4;
    } // exit loop
    else { wlane.insert(temp4); }
    wlane.advance(remain_ew, &nlane);
}

Section* Roadway::getSection(Direction direction, int index) {
        if (direction==Direction::north) {
            return nlane.getSection(index);
        }
        else if (direction==Direction::south) {
            return slane.getSection(index);
        }
        else if (direction==Direction::east) {
            return elane.getSection(index);
        }
        else { // (direction==Direction::west)
            return wlane.getSection(index);
        }
}
