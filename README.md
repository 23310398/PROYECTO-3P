# Juego de Pelea SFML

Este proyecto es un juego de pelea básico en C++ utilizando **SFML**. Incluye gráficos, texto, música y control de los personajes mediante el teclado.

## Requisitos

- **Visual Studio Code** o cualquier editor de C++.
- **MINGW64** (g++ compatible con C++17).
- **SFML 2.5 o superior** instalada y correctamente configurada.

## Estructura del Proyecto

```
proyecto_juego_pelea/
├── src/
│   └── main.cpp
├── assets/
│   ├── images/
│   │   └── personaje.png
|   |   └── Fondo.png
│   ├── music/
│   │   └── musica.ogg
│   └── fonts/
│       └── fuente.ttf
├── Makefile
└── README.md
```

## Instrucciones de Compilación y Ejecución

En la terminal MINGW64, dentro del directorio del proyecto, ejecuta:

```
make run
```

Esto compilará y ejecutará el juego. Asegúrate de que las rutas a los archivos de `assets/` estén correctas.

## Controles

- Flechas del teclado: movimiento del jugador

## Notas

- Asegúrate de que los archivos de música tengan extensión **.ogg** y estén en la carpeta correcta.
- Si el programa no carga imágenes, música o fuentes, revisa las rutas relativas.

## Créditos

Las imágenes utilizadas en este proyecto fueron obtenidas de diversas fuentes en Internet. A continuación, se listan los créditos correspondientes:

- **FONDO 1.jpg, FONDO.jpg, FONDO2.jpg, FONDO3.jpg**: Fondos genéricos descargados de bancos de imágenes gratuitos.
- **ninja.png, samurai.png**: Sprites de personajes obtenidos de recursos gratuitos para desarrolladores de videojuegos.
- **peleador1.png, peleador1,2.png, peleador2.png, peleador2,2.png**: Diseños de personajes adaptados de imágenes de dominio público.




