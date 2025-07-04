# Juego de Pelea SFML

Este proyecto es un juego de pelea básico en C++ utilizando **SFML**. Incluye gráficos, texto, música y control de los personajes mediante el teclado. El código está completamente modularizado y orientado a objetos.

## Requisitos

- **Visual Studio Code** o cualquier editor de C++.
- **MINGW64** (g++ compatible con C++17).
- **SFML 2.5 o superior** instalada y correctamente configurada.

## Estructura del Proyecto

```
PROYECTO-3P/
├── src/
│   ├── main.cpp
│   ├── Juego.cpp
│   ├── Peleador.cpp
│   └── Particula.cpp
├── include/
│   ├── Juego.hpp
│   ├── Peleador.hpp
│   └── Particula.hpp
├── assets/
│   ├── images/
│   │   ├── FONDO 1.jpg
│   │   ├── FONDO.jpg
│   │   ├── FONDO2.jpg
│   │   ├── FONDO3.jpg
│   │   ├── ninja.png
│   │   ├── samurai.png
│   │   ├── peleador1.png
│   │   ├── peleador1,2.png
│   │   ├── peleador2.png
│   │   └── peleador2,2.png
│   ├── music/
│   │   └── musica.ogg
│   └── fonts/
│       └── Minecraft.ttf
├── ejecutables/
│   └── game.exe
├── makefile
├── README.md
└── docs/
    └── diagrama.puml
```

## Instrucciones de Compilación y Ejecución

En la terminal MINGW64, dentro del directorio del proyecto, ejecuta:

```
mingw32-make
./game.exe
```
![Image](https://github.com/user-attachments/assets/fc925fd2-a810-416e-a514-1634f1ccc85b)

Esto compilará y ejecutará el juego. Asegúrate de que las rutas a los archivos de `assets/` estén correctas.

## Controles

- Jugador 1 y Jugador 2: seleccionan personaje en el menú con teclas E y B.
![Image](https://github.com/user-attachments/assets/44b2f6e7-1b96-43e0-ace2-8238d12d724a)
- Durante el combate:
    - `Num1`: Ataque
    - `Num2`: Defensa
    - `Num3`: Ataque especial (requiere energía)
![Image](https://github.com/user-attachments/assets/b84cfc18-c319-42ff-b5a5-525c207a3b86)
![Image](https://github.com/user-attachments/assets/585003a0-e445-4bbc-8192-483e533edc63)
    - `R`: Reiniciar en pantalla de Game Over
    - `ESC`: Salir
![Image](https://github.com/user-attachments/assets/2b44b954-1c2a-4b70-afda-e141801ab6e5)


## Notas

- Asegúrate de que los archivos de música tengan extensión **.ogg** y estén en la carpeta correcta.
- Si el programa no carga imágenes, música o fuentes, revisa las rutas relativas.
- El fondo y los sprites se escalan automáticamente al tamaño de la ventana.
- El código sigue buenas prácticas de POO y está modularizado en clases.

## Créditos

Las imágenes utilizadas en este proyecto fueron obtenidas de diversas fuentes en Internet. A continuación, se listan los créditos correspondientes:

- **FONDO 1.jpg, FONDO.jpg, FONDO2.jpg, FONDO3.jpg**: Fondos genéricos descargados de bancos de imágenes gratuitos.
- **ninja.png, samurai.png**: Sprites de personajes obtenidos de recursos gratuitos para desarrolladores de videojuegos.
- **peleador1.png, peleador1,2.png, peleador2.png, peleador2,2.png**: Diseños de personajes adaptados de imágenes de dominio público.




