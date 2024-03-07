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


SRCS= analysefreq.cxx countprint.cxx main.cxx savefreq.cxx
OBJS=$(SRCS:.cxx=.o)
ALL=freq readback

all: $(ALL)

freq: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

readback: readback.cxx
	$(CXX) -o $@ $(CXXFLAGS) $<

clean:
	/bin/rm -f $(OBJS) $(ALL)
	/bin/rm -f *.freq
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	/bin/rm -f $(TMPMAKE)
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $(TMPMAKE)
	echo '# DEPENDENTS' >> $(TMPMAKE)
	$(CXX) -MM $+ >> $(TMPMAKE)
	/bin/mv -f $(TMPMAKE) Makefile

# DEPENDENTS
analysefreq.o: analysefreq.cxx freq.h
countprint.o: countprint.cxx freq.h
main.o: main.cxx freq.h
savefreq.o: savefreq.cxx freq.h
