OBJS = readFrameRootSimMain.C DictOutput.cxx
EXE = readFrameRootSimMain

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

DICTHEADERS = edm4hep/MCParticleData.h edm4hep/SimCalorimeterHitData.h edm4hep/CaloHitContributionData.h LinkDef.h

INCFLAGS = -I${ROOTSYS}/include -I${ROOTSYS}/include/root/
LDFLAGS = -L${ROOTSYS}/lib -L${ROOTSYS}/lib/root -lpodio -ledm4hep -ledm4hepDict -ledm4eic -ledm4eicDict -lpodioRootIO -lpodioDict -lpodioRootIODict -lfmt
# -shared -fPIC

#rootcling -f DictOutput.cxx -c edm4hep/MCParticleData.h edm4hep/SimCalorimeterHitData.h edm4hep/CaloHitContributionData.h LinkDef.h

#-L${PODIO}/lib

#CXX = g++ -m32 -std=c++20
CXX = g++ -std=c++20
FLAGS = -Wall -g -fPIC $(INCFLAGS) $(LDFLAGS)

COMPILE = $(CXX) $(FLAGS) -c 

all: $(EXE)

#$(EXE): $(OBJS)
#	$(CXX) -o $(EXE) $(OBJS) $(ROOTFLAGS) $(ROOTLIBS)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(ROOTFLAGS) $(ROOTLIBS) $(FLAGS)

DictOutput.cxx :
	rootcint -f $@ -c $(DICTHEADERS)
	
#%.o: %.C
	$(COMPILE) $<	
	
clean:
	rm $(EXE)

	