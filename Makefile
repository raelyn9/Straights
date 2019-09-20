CXX = g++ -std=c++14
#CXXFLAGS = -Wall -MMD # use -MMD to generate dependencies 
CXXFLAGS = -Wall -g -MMD # use -MMD to generate dependencies 
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
SOURCES = $(wildcard *.cc) # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o} # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}  # .d file is list of dependencies for corresponding .cc file
EXEC=straights

# First target in the makefile is the default target.
# Note that the GTKFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(GTKFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(GTKFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)