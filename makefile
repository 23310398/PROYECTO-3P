# Makefile para compilar y ejecutar el juego

# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Archivos fuente y binario
SRC = main.cpp
BIN = juego

# Regla principal
all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC)

# Regla para ejecutar el programa
run: $(BIN)
	./$(BIN)

# Regla para limpiar archivos generados
clean:
	rm -f $(BIN)

.PHONY: all run clean