#ifndef POKEMON_H
#define POKEMON_H

// Gerekli Kütüphaneler (main.c ve diğer .c dosyaları kullanacak)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// --- Sabitler (Oyunun Boyutları) ---
#define NUM_TYPES 18
#define NUM_MOVES 486
#define NUM_POKEMONS 1015
#define PLAYER_POKEMONS 6

// 2.1.3 Move - Kategori için enum
typedef enum {
    PHYSICAL, // Fiziksel saldırı (attack ve defense kullanır)
    SPECIAL   // Özel saldırı (spAtk ve spDef kullanır)
} Category;

// --- 2.1.1 TypeEffect (Tür Etkisi Kutusu) ---
typedef struct {
    char atkName[20];       // Saldıran türün adı (Örn: "Ateş")
    char defName[20];       // Savunan türün adı (Örn: "Çimen")
    double multiplier;      // Hasar çarpma sayısı (Örn: 2.0)
} TypeEffect;

// --- 2.1.2 Type (Tür Kutusu) ---
typedef struct {
    char name[20];          // Türün adı (Örn: "Su")
    TypeEffect effects[NUM_TYPES]; // Diğer 18 türe karşı etkileri
} Type;

// --- 2.1.3 Move (Hareket Kutusu) ---
typedef struct {
    char name[30];          // Hareketin adı (Örn: "Ateş Püskürtme")
    Type type;              // Hareketin türü
    Category category;      // Saldırının türü (Fiziksel/Özel)
    int power;              // Saldırının gücü
} Move;

// --- 2.1.4 Pokemon (Pokemon Kutusu) ---
typedef struct {
    char name[30];          // Adı (Örn: "Pikachu")
    Type types[2];          // En fazla iki türü olabilir
    int maxHP;              // En yüksek canı
    int currentHP;          // Şu anki canı
    int attack;             // Fiziksel Saldırı gücü
    int defense;            // Fiziksel Savunma gücü
    int spAtk;              // Özel Saldırı gücü
    int spDef;              // Özel Savunma gücü
    int speed;              // Hızı
    Move moves[4];          // Kullanabileceği 4 hareket
} Pokemon;

// --- 2.1.5 Player (Oyuncu Kutusu) ---
typedef struct {
    char name[30];          // Oyuncunun adı
    Pokemon Pokemons[PLAYER_POKEMONS]; // Elindeki 6 Pokemon
    int currentIndex;       // Şu an dövüşen Pokemon'un sırası (1'den 6'ya)
} Player;


// ----------------------------------------------------
// FONKSİYON PROTOTİPLERİ 
// ----------------------------------------------------

// types.c
void initializeTypes(Type *Types);
int getMoveTypeIndex(Type *Types, char* typeName);

// moves.c
void initializeMoves(Move *Moves, Type *Types);

// pokemon.c
void initializePokemons(Pokemon *Pokemons, Type *Types, Move *Moves);
void initialize(Type *Types, Move *Moves, Pokemon *Pokemons, Player *Player1, Player *Player2);
double calculateDamage(Pokemon attacker, Pokemon defender, Move move, Type *Types);
void applyDamage(Player *player1, int p1_choice, int p1_moveIndex, Player *player2, int p2_choice, int p2_moveIndex, Type *Types);
void playRound(Player *Player1, Player *Player2, Type *Types);
int getAvailablePokemonIndex(Player *player);

// main.c (game)
void game(Player *Player1, Player *Player2, Type *Types);

#endif // POKEMON_H