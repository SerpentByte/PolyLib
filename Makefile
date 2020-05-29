CXX=/usr/bin/g++
CXXFLAGS= -O3 -g -lm -fopenmp
IDIR=./headers
BIN_DIR=./bin
CPP_DIR=./scripts

all: $(BIN_DIR)/rnd $(BIN_DIR)/box $(BIN_DIR)/sph $(BIN_DIR)/spcl $(BIN_DIR)/re

$(BIN_DIR)/rnd: $(CPP_DIR)/rand_walk.cpp $(IDIR)/gromos87_io.h $(IDIR)/rand_walk.h $(IDIR)/xyz.h
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/rnd $(CPP_DIR)/rand_walk.cpp $(IDIR)/gromos87_io.h $(IDIR)/rand_walk.h $(IDIR)/xyz.h

$(BIN_DIR)/box: $(CPP_DIR)/box.cpp $(IDIR)/gromos87_io.h $(IDIR)/box.h $(IDIR)/xyz.h
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/box $(CPP_DIR)/box.cpp $(IDIR)/gromos87_io.h $(IDIR)/box.h $(IDIR)/xyz.h

$(BIN_DIR)/sph: $(CPP_DIR)/sphere.cpp $(IDIR)/gromos87_io.h $(IDIR)/sphere.h $(IDIR)/xyz.h
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/sph $(CPP_DIR)/sphere.cpp $(IDIR)/gromos87_io.h $(IDIR)/sphere.h $(IDIR)/xyz.h

$(BIN_DIR)/spcl: $(CPP_DIR)/spherocylinder.cpp $(IDIR)/gromos87_io.h $(IDIR)/spherocylinder.h $(IDIR)/xyz.h
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/spcl $(CPP_DIR)/spherocylinder.cpp $(IDIR)/gromos87_io.h $(IDIR)/spherocylinder.h $(IDIR)/xyz.h

$(BIN_DIR)/re: $(CPP_DIR)/Re.cpp $(IDIR)/Re.h $(IDIR)/xyz.h $(IDIR)/functions.h
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/re $(CPP_DIR)/Re.cpp $(IDIR)/Re.h $(IDIR)/xyz.h $(IDIR)/functions.h

clean:
	rm -rf bin/* log/* *.gro
