:WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wformat=2\
 -Winit-self -Wmissing-declarations -Wredundant-decls -Wshadow\
 -Wstrict-overflow=5 -Wswitch-default -Wundef

FLAGS = $(WARNINGS) -std=c++14

SRC = Huita.cpp

build:
	g++ $(SRC) -o main -pthread -std=c++14

test:
	g++ $(SRC) -DTESTS -o main -pthread -std=c++14
