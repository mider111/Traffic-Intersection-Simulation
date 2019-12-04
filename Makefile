EXECS = RoadSim
OBJS = RoadSim.o Animator.o Generator.o VehicleBase.o Lane.o Roadway.o Section.o

#### use next two lines for mathcs* machines:
CC = g++
CCFLAGS = -std=c++11 -Wall -g

all: $(EXECS)

$(EXECS): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f $(OBJS) $(EXECS)
