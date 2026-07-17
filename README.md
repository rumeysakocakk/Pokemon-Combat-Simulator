# Pokémon Combat Simulator

## Overview

Pokémon Combat Simulator is a terminal-based, turn-based battle engine developed in C. The project simulates battles using Pokémon statistics, moves, elemental types, and type-effectiveness relationships loaded from external data files.

Rather than embedding game data directly into the source code, the application follows a data-driven architecture. This enables datasets to be updated or expanded without requiring changes to the core battle logic.

## Features

- Turn-based combat between two players
- Six Pokémon assigned to each player
- Attack and Pokémon-switching actions
- Physical and special damage calculations
- Elemental type-effectiveness system
- Active and fainted Pokémon tracking
- Automatic battle result detection
- Runtime loading of Pokémon, move, and type data
- Dynamic memory allocation for large datasets

## Dataset Coverage

The application is designed to process:

- 1,015 Pokémon
- 486 moves
- 18 elemental types
- Physical and special move categories
- Pokémon base statistics
- Type-effectiveness multipliers

The following Pokémon statistics are used during battle calculations:

- HP
- Attack
- Defense
- Special Attack
- Special Defense
- Speed

## Technical Design

### Data-Driven Architecture

Pokémon, move, and type information is loaded from external text files. The core battle engine is therefore separated from the dataset and does not require recompilation when compatible data records are updated.

### Dynamic Memory Management

The application uses dynamic memory allocation to create and manage data structures at runtime. Memory for Pokémon, moves, and type-effectiveness data is allocated according to the loaded datasets.

### Modular Structure

The source code is divided into modules with separate responsibilities. This structure improves readability, simplifies debugging, and supports future development.

### Structured Data Modeling

Custom C structures are used to represent:

- Pokémon attributes and battle statistics
- Move properties and categories
- Elemental types
- Type-effectiveness relationships
- Player teams and active Pokémon

## Battle System

Each player controls a team of six Pokémon. During a turn, a player can either perform an attack or switch the active Pokémon.

The battle engine tracks:

- Current active Pokémon
- Remaining HP
- Fainted Pokémon
- Available team members
- Move category
- Attacking and defensive statistics
- Elemental effectiveness

The battle ends automatically when one player has no usable Pokémon remaining.

## Project Structure

```text
Pokemon-Combat-Simulator/
├── main.c
├── pokemon.h
├── pokemon.c
├── moves.c
├── type.c
├── pokemon.txt
├── moves.txt
└── types.txt
```

| File | Responsibility |
|------|----------------|
| `main.c` | Initializes the application and controls the main battle loop. |
| `pokemon.h` | Contains constants, enumerations, structures, and function declarations. |
| `pokemon.c` | Manages Pokémon data and core battle operations. |
| `moves.c` | Loads and manages move data and move categories. |
| `type.c` | Manages elemental types and effectiveness calculations. |
| `pokemon.txt` | Contains Pokémon statistics and related data. |
| `moves.txt` | Contains move definitions and properties. |
| `types.txt` | Contains elemental type-effectiveness data. |

## Getting Started

### Prerequisites

A C compiler such as GCC is required to build the project.

You can verify that GCC is installed by running:

```bash
gcc --version
```

### Installation

Clone the repository:

```bash
git clone https://github.com/rumeysakocakk/Pokemon-Combat-Simulator.git
```

Navigate to the project directory:

```bash
cd Pokemon-Combat-Simulator
```

### Compilation

Compile the source files with GCC:

```bash
gcc main.c pokemon.c moves.c type.c -o pokemon-combat-simulator
```

### Running the Application

On Linux or macOS:

```bash
./pokemon-combat-simulator
```

On Windows:

```bash
pokemon-combat-simulator.exe
```

The data files must remain in the location expected by the application when the executable is started.

## Learning Outcomes

This project provided practical experience in:

- Procedural programming with C
- Dynamic memory allocation
- Pointer usage
- Custom structures and enumerations
- File reading and data parsing
- Modular software design
- Data-driven application architecture
- Implementation of turn-based game logic
- Management of large structured datasets

## Future Improvements

Potential improvements include:

- Releasing dynamically allocated memory through a complete cleanup process
- Improving validation for malformed or missing data files
- Adding computer-controlled opponents
- Implementing status effects and additional move mechanics
- Creating a graphical user interface
- Saving and loading battle progress
- Adding automated tests for damage and type calculations
- Introducing configurable battle rules

## Author

**Rumeysa Elif Koçak**  
Software Engineering Student

GitHub: [rumeysakocakk](https://github.com/rumeysakocakk)
