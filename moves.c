#include "pokemon.h"

// ----------------------------------------------------
// FONKSİYON TANIMLARI (moves.c)
// ----------------------------------------------------

// 2.2.4 initializeMoves (Hareketleri Hazırlama)
void initializeMoves(Move *Moves, Type *Types) {
   
    FILE *file = fopen("C:/Users/asus/OneDrive/Belgeler/CPROJECTS/moves.txt", "r"); 
    if (file == NULL) {
       perror("CRITICAL ERROR: moves.txt could not be found at the specified path.");
        exit(EXIT_FAILURE);
    }

    char line[100];
    int moveIndex = 0;
    
    while (fgets(line, sizeof(line), file) && moveIndex < NUM_MOVES) {
        char name[30], typeName[20], categoryStr[10];
        int power;
        
        if (sscanf(line, "%s %s %s %d", name, typeName, categoryStr, &power) == 4) {
            
            strcpy(Moves[moveIndex].name, name);
            Moves[moveIndex].power = power;
            
            // Hareketin Türünü Bul ve Ata
            int typeIdx = getMoveTypeIndex(Types, typeName);
            if (typeIdx != -1) {
                Moves[moveIndex].type = Types[typeIdx];
            }
            
            // Kategori Atama
            if (strcmp(categoryStr, "Physical") == 0) {
                Moves[moveIndex].category = PHYSICAL;
            } else if (strcmp(categoryStr, "Special") == 0) {
                Moves[moveIndex].category = SPECIAL;
            }
            
            moveIndex++;
        }
    }

    fclose(file);
}