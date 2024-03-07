# Name: Colin Friedel, David Thuita, Logan Calder, Kyle Samonte
# Email: aigreen@scu.edu, kpazmino@scu.edu, lcalder@scu.edu, wluo@scu.edu
# 
# Assignment: Create a container representing the
#             students in a class via a pointer to
#             an array and implement methods for
#             add removing and listing the students.
# 
# 0 of 4: Makefile

CXX = g++
CXXFLAGS = -std=c++17

SRCS = classmain.cpp scuclass.cpp student.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = a

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
