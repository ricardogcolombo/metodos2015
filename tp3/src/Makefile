export LC_ALL=C
CXXFLAGS= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

OBJS=bilineal.o splines.o ventanas.o
MAIN=main.o

.PHONY: all
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) 

main.o: main.cpp common.h
bilineal.o: bilineal.cpp bilineal.h
splines.o: splines.cpp splines.h
ventanas.o: ventanas.cpp ventanas.h


.PHONY: clean
clean:
	rm -f $(OBJS) $(MAIN)

.PHONY: new
new: clean all
