// Group: The Powers (Karim, Jibran, Viktor)
// Date: Apr 16, 2019

#ifndef __SECTION_H__
#define __SECTION_H__

#include "VehicleBase.h"

using namespace std;

class Section {

		public:
                //Default constructor (section with no information)
                Section();
                //Constructor for all other sections
                Section(Section* forwardSection, Section* rightSection);
                //Copy constructor
                Section(const Section& other);
                //Deconstructor
                ~Section();
                // Puts a vehicle in the section (using a pointer to the vehicle)
                void putVehicle(VehicleBase* vehicle);
                // Tells section that it should allow right turn
                void setRight();
                // Gives a pointer to the section ahead
                void setForwardSection(Section* forwardSection);
                // Gives a pointer to the section to the right
                void setRightSection(Section* rightSection);
                // Gets the vehicle that is in the section (if there is any)
                VehicleBase* getVehicle();
                // Returns pointer to section to its right (if it's an intersection section)
                Section* getRightSection();
                // Returns pointer to section ahead
                Section* getForwardSection();
                // Removes vehicle from section
                void removeVehicle();
								// Removes vehicle from section and deletes the pointer
								void remdelVehicle();
                // Returns true if right turn is possible
                bool turnsRight();
                // Returns true if section is occupied by a vehicle
								bool isOccupied();
                inline int getVehicleID() { return vehicle->getVehicleID(); }

	private:
			// Stores pointer to section ahead
			Section* forwardSection;
			// Stores pointer to section on the right
			Section* rightSection;
			// Stores vehicle
			VehicleBase* vehicle;
	    // Boolean variable that is true if section is in intersection and allows right turn
			bool right;
			// Boolean variable that is true if section is occupied
			bool occupied;
};
#endif
