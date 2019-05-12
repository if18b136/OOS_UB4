all: fight_club

fight_club: *.cpp
	g++ -std=c++11 -ggdb -o fight_club *.cpp

tests: *.cpp
	g++ -std=c++11 -DTESTS -I../gtest-linux/include ../gtest-linux/lib/gtest_main.a -lpthread -ggdb -o UEB4_tests *.cpp

run: fight_club
	"../DrMemory/bin64/drmemory" -- fight_club

run_tests: tests
	../DrMemory/bin64/drmemory -- UEB4_tests

clean:
	rm -f fight_club.exe fight_club UEB*_tests.exe UEB*_tests *.o
