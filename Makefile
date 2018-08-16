cc = g++
prgrm = game
source = main.cpp mySDL.cpp

$(prgrm): $(source)
	$(cc) -o $(prgrm) $(source) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer