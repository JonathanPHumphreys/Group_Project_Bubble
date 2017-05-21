SRC = src/main.cpp src/Control.cpp src/graphics.cpp src/UI.cpp
LINKER = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all : $(SRC)
	g++ $(SRC) -w -std=c++11 $(LINKER) -o game

clean :
	rm game
