CXX := g++
CXX_FLAGS := -Wall -std=c++1z
CXX_SRC = *.cpp controls/*.cpp
LINKER_FLAGS := -lSDL2 -lSDL2_ttf

all:
	$(CXX) $(CXX_FLAGS) $(CXX_SRC) $(LINKER_FLAGS) -o sdl
	./sdl