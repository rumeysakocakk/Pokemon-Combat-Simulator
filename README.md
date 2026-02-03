# 🎮 PokemonGame (C Language)

A highly structured, terminal-based RPG battle engine developed in **C**.  
This project demonstrates advanced **procedural programming**, **manual heap memory management**, and a **data-driven, modular architecture** capable of handling large-scale datasets efficiently.

---

## 📌 Project Overview

PokemonGame is a turn-based battle simulation inspired by classic Pokémon mechanics.  
Instead of hardcoding game data into the source code, the engine dynamically loads all Pokémon, move, and type information from external files. This design highlights low-level system programming skills such as memory management, modular design, and scalable data handling in C.

---

## 🛠️ Technical Implementation

### 🔹 Manual Heap Memory Management
- Extensive use of `malloc` for dynamic memory allocation
- Large datasets allocated at runtime:
  - Pokémon
  - Moves
  - Type-effectiveness tables
- Ensures efficient memory usage and flexibility for large simulations

### 🔹 Modular Codebase
The project is organized into independent modules to maintain a clean separation of concerns:
- Improved readability
- Easier debugging
- High maintainability and extensibility

### 🔹 Data-Driven Architecture (Not Hardcoded)
- All game data is loaded from external `.txt` files
- Pokémon stats, move definitions, and type multipliers are **not hardcoded**
- The core game logic remains unchanged even if data is updated or expanded

### 🔹 Complex Data Structures
- Uses nested `struct` definitions to represent:
  - Pokémon attributes
  - Move categories (Physical / Special)
  - Elemental type-effectiveness multipliers

---

## ⚔️ Game Mechanics

### 🔁 Turn-Based Combat System
- Each round allows players to:
  - Attack
  - Switch Pokémon
- Automatic win/loss detection based on remaining active Pokémon

### 🧪 Comprehensive Simulations
- **1015 Pokémon**
  - HP, Attack, Defense
  - Special Attack, Special Defense
  - Speed
- **486 Moves**
  - Physical and Special damage calculation
- **18 Elemental Types**
  - Fully implemented type-effectiveness matrix

### 🔄 Dynamic Battle Flow
- Each player controls a party of **6 Pokémon**
- The engine continuously tracks:
  - Active Pokémon
  - Fainted Pokémon
- The game ends automatically when one party is defeated

---

## 📂 Project Structure

```text
├── main.c        // Core game loop and heap memory initialization
├── pokemon.h    // Central header file (constants, enums, structs)
├── pokemon.c    // Pokémon initialization and battle mechanics
├── moves.c      // Move loading and category management
├── type.c       // Elemental type system and effectiveness multipliers
├── pokemon.txt  // Pokémon data
├── moves.txt    // Move data
└── types.txt    // Type-effectiveness data
