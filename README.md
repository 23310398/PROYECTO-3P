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

- Flechas del teclado: decicion del jugador en su turno
- 1: ataque
- 2: defensa
- 3: especial

## Notas

- Asegúrate de que los archivos de música tengan extensión **.ogg** y estén en la carpeta correcta.
- Si el programa no carga imágenes, música o fuentes, revisa las rutas relativas.

## Créditos

Este juego fue generado como base educativa para un proyecto de pelea en SFML.

---
¡Disfruta programando y mejorando tu juego!
