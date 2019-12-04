#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{}

VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection)
{}

VehicleBase::~VehicleBase() {}

// we added this
int VehicleBase::size() const {
		if (vehicleType==VehicleType::car) {
				return 2;
		}
		if (vehicleType==VehicleType::suv) {
				return 3;
		}
		if (vehicleType==VehicleType::truck) {
				return 4;
		}
		return -1;
}



#endif
