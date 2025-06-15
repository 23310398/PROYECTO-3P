run: build
	./game

build:
	g++ src/main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -f game
