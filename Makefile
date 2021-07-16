# Simple makefile

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.h)

CC          = g++
CXX         = g++
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LD          = g++
LDFLAGS     = -g -O2
SOFLAGS     = -g -shared
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LDFLAGS     = -g -O2
ROOTLIBS    = $(shell root-config --libs)
ROOTCFLAGS  = $(shell root-config --cflags)
CXXFLAGS   += $(ROOTCFLAGS)
CFLAGS      = $(ROOTCFLAGS) -Wall -Wno-unused-function -g -O2 -fPIC -fno-var-tracking -DLorentzVectorPtEtaPhiM4D -Irooutil
EXTRAFLAGS  = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer -lMinuit -Irooutil

all: getresult train apply

getresult: getresult.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

train: train.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

apply: apply.o VBS.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $< -c -o $@

cleanall:
	rm -f VBS.o
	rm -f train.o train
	rm -f apply.o apply
	rm -f getresult.o getresult

clean:
	rm -f train.o train
	rm -f apply.o apply
	rm -f getresult.o getresult
