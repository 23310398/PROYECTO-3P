run: build
	./game


build:
	g++ src/main.cpp src/Peleador.cpp src/Particula.cpp -o game.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	del /f game.exe
