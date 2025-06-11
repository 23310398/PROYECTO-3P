# Nombre del ejecutable
TARGET = pelea.exe

# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -std=c++11 -mconsole

# Archivos fuente
SRC = main.cpp

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

clean:
	del /Q *.exe 2>nul || true

.PHONY: all clean run