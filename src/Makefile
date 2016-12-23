EXENAME = xcscore
OBJS = score.o xc.o

CXX = g++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LD = g++
LDFLAGS = -std=c++1y -stdlib=libc++

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

score.o : score.cpp xc.h
	$(CXX) $(CXXFLAGS) score.cpp

xc.o : xc.cpp xc.h
	$(CXX) $(CXXFLAGS) xc.cpp

clean :
	rm -f *.o $(EXENAME)
