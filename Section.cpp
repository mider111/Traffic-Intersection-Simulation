// Group: The Powers (Karim, Jibran, Viktor)
// Date: Apr 16, 2019

#include <iostream>
#include "Section.h"
#include "VehicleBase.h"


Section::Section() {
		// all will be set by default to false or NULL
		this->forwardSection 	= nullptr;
		this->rightSection 		= nullptr;
		this->vehicle 			= nullptr;
		this->right 			= false;
		this->occupied 			= false;
}


//Copy constructor
Section::Section(const Section& other){
    this->forwardSection = other.forwardSection;
    this->rightSection   = other.rightSection;
    this->vehicle	  	 = other.vehicle;
    this->right 	 	 = other.right;
    this->occupied 	 	 = other.occupied;
}


Section::Section(Section* forwardSection, Section* rightSection){
		// will be set by default to false and NULL
		this->occupied = false;
    this->vehicle = nullptr;

    // sets the pointer to the section ahead
    this->forwardSection = forwardSection;

		// if rightSection is not a NULL pointer, then right turn is an option so...
		if(rightSection){

				this->right = true; // right turn is possible (intersection)
				this->rightSection = rightSection; // sets the pointer to the section to the right
		}
		else {
				this->right = false; // right turn is not possible
				this->rightSection = nullptr; // sets the pointer to the section to the right to NULL
		}
}


// Puts a vehicle in the section (using a pointer to the vehicle)
void Section::putVehicle(VehicleBase* vehicle){
		this->vehicle = vehicle;
		// will be set to true
		this->occupied = true;

}


// Tells section that it should allow right turn
void Section::setRight(){
		this->right = true;
}


// Sets a pointer to the section ahead
void Section::setForwardSection(Section* forwardSection){
		this->forwardSection = forwardSection;
}


// Sets a pointer to the section to the right
void Section::setRightSection(Section* rightSection){
		this->rightSection = rightSection;
		this->right = true;
}


// Gets the vehicle that is in the section (if there is any)
VehicleBase* Section::getVehicle(){
		if (vehicle != nullptr) {
				return this->vehicle;
		}
		return nullptr;
}


// Returns pointer to section to its right (if it's an intersection section)
Section* Section::getRightSection(){
		return this->rightSection;
}


// Returns pointer to section ahead
Section* Section::getForwardSection(){
		return this->forwardSection;
}


// Removes vehicle from section
void Section::removeVehicle(){
		if(this->occupied){
			this->vehicle = nullptr;
			this->occupied = false;
		}
}

// Removes vehicle from section and deletes pointer
void Section::remdelVehicle(){
		if(this->occupied){
			this->vehicle = nullptr;
			delete this->vehicle;
			this->occupied = false;
		}
}

// Returns true if right turn is possible
bool Section::turnsRight(){
		return this->right;
}


// Returns true if section is occupied by a vehicle
bool Section::isOccupied(){
		return this->occupied;
}


Section::~Section(){
}
