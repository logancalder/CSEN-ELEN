TMPMAKE=tmpMake
STD=-std=c++11
OPT=-g
CXXFLAGS=${STD} ${OPT}
CFLAGS=${OPT}

%.o: %.c
	$(CC) -c $(CFLAGS) $<

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

%: %.c
	$(CC) -o $@ $(CFLAGS) $<

%: %.cxx
	$(CXX) -o $@ $(CXXFLAGS) $<

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<


SRCS=main.cxx palindrome.cxx
OBJS=$(SRCS:.cxx=.o)
ALL=palindrome

palindrome: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(OBJS) $(ALL)
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	/bin/rm -f $(TMPMAKE)
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $(TMPMAKE)
	echo '# DEPENDENTS' >> $(TMPMAKE)
	$(CXX) -MM $+ >> $(TMPMAKE)
	/bin/mv -f $(TMPMAKE) Makefile

# DEPENDENTS
main.o: main.cxx palindrome.h
palindrome.o: palindrome.cxx palindrome.h
