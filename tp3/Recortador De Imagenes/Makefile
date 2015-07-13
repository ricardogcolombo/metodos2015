export LC_ALL=C
CXXFLAGS= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

MAIN=recortador

.PHONY: all
all: $(MAIN)

$(MAIN):
	$(CXX) -o $@ recortador.cpp $(CXXFLAGS) 

.PHONY: clean
clean:
	rm -f $(MAIN)

.PHONY: new
new: clean all
