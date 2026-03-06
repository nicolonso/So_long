# So_long

*This project has been created as part of the 42 curriculum by nalfonso.*

# so_long

## Description

**so_long** is a small 2D game written in C using the **MiniLibX** graphics library.

The goal of the game is simple:
The player must collect all collectibles (`C`) on the map and then reach the exit (`E`).

The map is loaded from a `.ber` file and rendered using textures.

This project focuses on learning:

* Window management
* Event handling
* Texture rendering
* Map parsing and validation
* Pathfinding algorithms (Flood Fill)
* Memory management
* Working with the MiniLibX graphics library

---

## Instructions

### Compilation

Compile the project using:

```bash
make
```

### Run the program

```bash
./so_long maps/map.ber
```

Example:

```bash
./so_long maps/test.ber
```

---

## Controls

| Key | Action        |
| --- | ------------- |
| W   | Move up       |
| A   | Move left     |
| S   | Move down     |
| D   | Move right    |
| ESC | Exit the game |

The number of movements is displayed in the terminal.

---

## Map Rules

The map must follow these rules:

* The map must be **rectangular**
* The map must be **closed by walls**
* The map must contain:

  * **1 Player (P)**
  * **1 Exit (E)**
  * **At least 1 Collectible (C)**

Allowed characters:

```
0 = empty space
1 = wall
C = collectible
E = exit
P = player
```

Example map:

```
111111
1P0C01
100001
100E01
111111
```

If the map is invalid, the program will display:

```
Error
<message>
```

---

## Project Structure

```
so_long/
│
├── Makefile
├── README.md
├── hdr/
│   └── so_long.h
├── src/
├── maps/
├── textures/
└── libft/
```

---

## Resources

MiniLibX documentation
https://harm-smits.github.io/42docs/libs/minilibx

Flood Fill algorithm
https://en.wikipedia.org/wiki/Flood_fill

Valgrind documentation
https://valgrind.org/docs/manual/quick-start.html
