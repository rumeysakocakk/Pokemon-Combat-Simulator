#include "pokemon.h"


void game(Player *Player1, Player *Player2, Type *Types) {
    
    printf("\n********************\n");
    printf(" GAME IS STARTING :)\n");
    printf("%s vs %s\n", Player1->name, Player2->name);
    printf("**********************\n");

    int p1_has_pokemon = 1;
    int p2_has_pokemon = 1;

    while (p1_has_pokemon && p2_has_pokemon) {
        
        playRound(Player1, Player2, Types);

        // Tur sonunda her iki oyuncunun da Pokemon'u kalıp kalmadığını kontrol et
        if (getAvailablePokemonIndex(Player1) == 0) {
            p1_has_pokemon = 0;
        }
        if (getAvailablePokemonIndex(Player2) == 0) {
            p2_has_pokemon = 0;
        }
    }
    
    printf("\n********************\n");
    printf(" GAME OVER :(\n");
    if (p1_has_pokemon) {
        printf("WINNER: %s\n", Player1->name);
    } else if (p2_has_pokemon) {
        printf("WINNER: %s\n", Player2->name);
    } else {
        printf("DRAW.\n");
    }
    printf("*************************\n");
}

// 2.2.1 main (ANA FONKSİYON - HEAP BELLEĞİ KULLANILDI)
int main() {
    // Rastgele sayı üreteci başlangıcı
    srand(time(NULL)); 

    // BÜYÜK DİZİLERİ HEAP BELLEĞİNDE AYIR (malloc)
    Type *Types = (Type*)malloc(NUM_TYPES * sizeof(Type));
    Move *Moves = (Move*)malloc(NUM_MOVES * sizeof(Move));
    Pokemon *Pokemons = (Pokemon*)malloc(NUM_POKEMONS * sizeof(Pokemon));
    
    // Bellek ayırma hatası kontrolü
    if (Types == NULL || Moves == NULL || Pokemons == NULL) {
        printf("ERROR: Memory allocation failed. The program is being terminated.\n");
        if (Types) free(Types);
        if (Moves) free(Moves);
        if (Pokemons) free(Pokemons);
        return 1;
    }

    Player Player1;
    Player Player2;

    // Tüm verileri yükle ve oyuncuları hazırla
    initialize(Types, Moves, Pokemons, &Player1, &Player2);

    // Oyunu başlat
    game(&Player1, &Player2, Types);

    // Belleği serbest bırak
    free(Types);
    free(Moves);
    free(Pokemons);

    return 0;
}