#include "pokemon.h"

// ----------------------------------------------------
// FONKSİYON TANIMLARI (types.c)
// ----------------------------------------------------

// Yardımcı fonksiyon: Bir Type ismi verilen array içindeki indexi bulur
int getMoveTypeIndex(Type *Types, char* typeName) {
    for (int i = 0; i < NUM_TYPES; i++) {
        if (strcmp(Types[i].name, typeName) == 0) {
            return i;
        }
    }
    return -1; 
}

// 2.2.3 initializeTypes (Türleri Hazırlama)
void initializeTypes(Type *Types) {
    // BURASI GÜNCELLENDİ: MUTLAK YOL KULLANILDI. LÜTFEN KENDİ YOLUNUZU KONTROL EDİN!
    FILE *file = fopen("C:/Users/asus/OneDrive/Belgeler/CPROJECTS/types.txt", "r");
    if (file == NULL) {
        // Hata mesajını daha anlaşılır hale getirdim
        perror("KRİTİK HATA: types.txt dosyası TAM YOLUNDA bulunamadi.");
        exit(EXIT_FAILURE);
    }

    int typeIndex = 0;
    int effectIndex = 0;
    char line[100];
    
    while (fgets(line, sizeof(line), file) && typeIndex < NUM_TYPES) {
        if (effectIndex == 0) {
            sscanf(line, "%s", Types[typeIndex].name);
        } 
        else {
            char defName[20];
            double multiplier;
            if (sscanf(line, "%s %lf", defName, &multiplier) == 2) {
                strcpy(Types[typeIndex].effects[effectIndex - 1].atkName, Types[typeIndex].name);
                strcpy(Types[typeIndex].effects[effectIndex - 1].defName, defName);
                Types[typeIndex].effects[effectIndex - 1].multiplier = multiplier;
            }
        }
        
        effectIndex++;
        
        if (effectIndex == NUM_TYPES + 1) { // 1 (tür adı) + 18 (efektler) = 19
            typeIndex++;
            effectIndex = 0;
        }
    }
    
    fclose(file);
}