#ifndef __Roadway__
#define __Roadway__

#include "Lane.h"
#include "Generator.h"

class Roadway {

    private:
        Lane nlane;
        Lane slane;
        Lane elane;
        Lane wlane;
        int numSections_before_int;
        int green_north_south;
        int yellow_north_south;
        int green_east_west;
        int yellow_east_west;
        Generator gen;

    public:
        Roadway(int initialSeed, int numSections_before_int, int green_north_south, int yellow_north_south,
                  int green_east_west, int yellow_east_west, double prob_new_vehicle_northbound,
                  double prob_new_vehicle_southbound, double prob_new_vehicle_eastbound,
                  double prob_new_vehicle_westbound, double proportion_of_cars, double proportion_of_SUVs,
                  double proportion_of_trucks, double prob_right_turn_cars,
                  double prob_left_turn_cars, double prob_right_turn_SUVs,
                  double prob_left_turn_SUVs,double prob_right_turn_trucks,
                  double prob_left_turn_trucks);

        ~Roadway();

        // The advance function will be our grab-all function whenever time increases
        void advance(int remain_ns, int remain_ew);

        Section* getSection(Direction direction, int index);

};

#endif
