#ifndef __LANE__
#define __LANE__

#include <vector>
#include <iostream>
#include "VehicleBase.h"
#include "Section.h"


class Lane {

    private:
        int numSections_before_int;
        int length;
        // indices of intesection (=numSections_before_int, numSections_before_int+1)
        int int_ind1;
        int int_ind2;
        vector<Section> lane;
        Direction direction;

    public:
        Lane();

        Lane(Direction direction, int numSections_before_int);

        Lane(const Lane& other);

        ~Lane();

        vector<Section> enterSpace; // holds newly spawned vehicles

        void insert(VehicleBase* vehicle);

        void advance(int remaining_time, Lane* rightLane);

        inline Section get(int index) { return (lane[index]);  }

        inline int getLength() const { return this->length; }

        inline int getNumSections_before_int() const { return this->numSections_before_int; }

        inline Section* getSection(int index) { return &(lane[index]); }
};

#endif
