CXX		= c++ -std=c++17
CXXFLAGS	= -g -Wall
OBJS		= lexer.o parser.o string.o
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) $(PROG) core *.o
