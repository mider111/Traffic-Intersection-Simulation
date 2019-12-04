#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "VehicleBase.h"
#include "Section.h"
#include "Lane.h"


	Lane::Lane() {
			numSections_before_int = 10;
			length = numSections_before_int*2 + 2;
			int_ind1 = numSections_before_int;
			int_ind2 = numSections_before_int + 1;
			for (int i = 0; i < length; i++) {
					lane.push_back(Section());
			}
			for (int i = 1; i < length; i++) {
					lane[i-1].setForwardSection(&lane[i]);
			}
			direction = Direction::north;
			enterSpace.push_back(Section());
			for (int i = 1; i < 5; i++) {
					enterSpace.push_back(Section());
					enterSpace[i-1].setForwardSection(&enterSpace[i]);
			}
			enterSpace[4].setForwardSection(&lane[0]);
	}


    Lane::Lane(Direction direction, int numSections_before_int) {
				this->numSections_before_int = numSections_before_int;
				length = numSections_before_int*2 + 2;
				int_ind1 = numSections_before_int;
				int_ind2 = numSections_before_int + 1;
				for (int i = 0; i < length; i++) {
						lane.push_back(Section());
				}
				for (int i = 1; i < length; i++) {
						lane[i-1].setForwardSection(&lane[i]);
				}
				this->direction = direction;
				enterSpace.push_back(Section());
				for (int i = 1; i < 5; i++) {
						enterSpace.push_back(Section());
						enterSpace[i-1].setForwardSection(&enterSpace[i]);
				}
				enterSpace[4].setForwardSection(&lane[0]);
    }


    Lane::Lane(const Lane& other) {
				this->numSections_before_int = other.numSections_before_int;
				length = other.length;
				int_ind1 = other.int_ind1;
				int_ind2 = other.int_ind2;
				for (int i = 0; i < length; i++) {
						// use copy constructor of section to copy sections to lane
						lane.push_back(Section(other.lane[i]));
				}
				this->direction = other.direction;
				enterSpace.push_back(Section());
				for (int i = 1; i < 5; i++) {
						enterSpace.push_back(Section());
						enterSpace[i-1].setForwardSection(&enterSpace[i]);
				}
				enterSpace[4].setForwardSection(&lane[0]);
    }


    Lane::~Lane() { }


    void Lane::insert(VehicleBase* vehicle) {
			// here we see if there is space for vehicle
			int i = 0;
			while (i < 4) {
					if (enterSpace[4-i].isOccupied()) {
							i++;
					}
					else {
							break;
					}
			}
			if (5-i < vehicle->size()) {
				delete vehicle;
				return;
			}
			for (int j = 0; j < vehicle->size(); j++) {
					enterSpace[4-i-j].putVehicle(vehicle);
			}
		}


		void Lane::advance(int remaining_time, Lane* rightLane) {

				// Empty last section to make room
				if (lane[length-1].isOccupied()){
					if (lane[length-2].isOccupied()) {
						if (lane[length-1].getVehicle() == lane[length-2].getVehicle()) {
							lane[length-1].remdelVehicle();
						} else {
							lane[length-1].removeVehicle();
						}
					} else {
						lane[length-1].remdelVehicle();
					}
				}

				// Move everything after the interection
				for (int i = length-1; i > numSections_before_int+1; i--) {
						lane[i].putVehicle(lane[i-1].getVehicle());
						lane[i-1].removeVehicle();
				}

				// Inside intersection (first index... the second is handled above)
				if (lane[numSections_before_int].getVehicle() != nullptr) {
						if (lane[numSections_before_int].getVehicle()->getVehicleOriginalDirection() != this->direction) {
								// we now want to turn right
								(lane[numSections_before_int].getRightSection())->putVehicle(lane[numSections_before_int].getVehicle());
								lane[numSections_before_int].removeVehicle();
						}
						else {
								// going straight
								lane[numSections_before_int+1].putVehicle(lane[numSections_before_int].getVehicle());
								lane[numSections_before_int].removeVehicle();
						}
				}

				// Moving everything behind the intersection
				int count = 0;
				for (int i = numSections_before_int-1; i >= 0; i--) {
						if (i == numSections_before_int-1) {
								// count how much of vehicle is left
								count = 0;
								int i = 0;
								if (lane[numSections_before_int-1-count].getVehicle()) {
										int vehicleID = lane[numSections_before_int-1-count].getVehicle()->getVehicleID();
										count = 1;
										while (i < 4) {  // max size is 4
												if (lane[numSections_before_int-2-i].getVehicle()) {
														if (lane[numSections_before_int-2-i].getVehicle()->getVehicleID() == vehicleID) {
																count++;
														}
												}
												i++;
										}
								}
								// can the vehicle proceed?
								if (lane[numSections_before_int-1].getVehicle()) {
										// if it is turning right, it needs its remaining size + 1
										if ((lane[numSections_before_int-1].getVehicle()->getVehicleOriginalDirection()!=direction) && count+1 <= remaining_time) {
												rightLane->lane[numSections_before_int+1].putVehicle(lane[numSections_before_int-1].getVehicle());
												lane[numSections_before_int-1].remdelVehicle();
										}
										// if it is going straight, it needs its remaining size + 2
										if (count+2 <= remaining_time) {
												lane[numSections_before_int].putVehicle(lane[numSections_before_int-1].getVehicle());
												lane[numSections_before_int-1].removeVehicle();
										}
								}
						}
						else {
						// Now, we are at the sections not directly before the intersection
						// Vehicles can move forward if the forwardSection is not occupied
						if (!lane[i+1].isOccupied()) {
							if (lane[i].isOccupied()) {
								lane[i+1].putVehicle(lane[i].getVehicle());
								lane[i].removeVehicle();
							}
						}
					}
				}

				// Now we handle the vehicles in enterSpace (buffer zone)
				if (!lane[0].isOccupied()) {
					if (enterSpace[4].isOccupied()) {
						lane[0].putVehicle(enterSpace[4].getVehicle());
						enterSpace[4].removeVehicle();
					}
				}

				for (int i = 4; i > 0; i--) {
					if (!enterSpace[i].isOccupied()) {
						if (enterSpace[i-1].isOccupied()) {
							enterSpace[i].putVehicle(enterSpace[i-1].getVehicle());
							enterSpace[i-1].removeVehicle();
						}
					}
				}
		}

#endif
