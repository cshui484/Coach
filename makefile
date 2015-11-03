CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCoach
	rm -f RunCoach.tmp
	rm -f TestCoach
	rm -f TestCoach.tmp
	rm -f solution
	rm -f *~

config:
	git config -l

scrub:
	make  clean
	rm -f  Coach.log
	rm -rf coach-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCoach.tmp TestCoach.tmp

solution: solution.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) solution.cpp -o solution

shi: shi.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) shi.cpp -o shi

#RunCoach: Coach.h Coach.c++ RunCoach.c++
#	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Coach.c++ RunCoach.c++ -o RunCoach
RunCoach: Coach.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Coach.c++ -o RunCoach

RunCoach.tmp: RunCoach
	./RunCoach < RunCoach.in > RunCoach.tmp
	diff -w RunCoach.tmp RunCoach.out

#TestCoach: Coach.h Coach.c++ TestCoach.c++
TestCoach: TestCoach.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TestCoach.c++ -o TestCoach $(LDFLAGS)

TestCoach.tmp: TestCoach
	$(VALGRIND) ./TestCoach                                       >  TestCoach.tmp 2>&1
	$(GCOV) -b Coach.c++     | grep -A 5 "File 'Coach.c++'"     >> TestCoach.tmp
	$(GCOV) -b TestCoach.c++ | grep -A 5 "File 'TestCoach.c++'" >> TestCoach.tmp
	cat TestCoach.tmp
