#include "pokemon.h"

// ----------------------------------------------------
// YARDIMCI VE MEKANİK FONKSİYONLAR (pokemon.c)
// ----------------------------------------------------

// Yardımcı fonksiyon: Canı 0'dan büyük ilk Pokemon'un indexini bulur.
int getAvailablePokemonIndex(Player *player) {
    for (int i = 0; i < PLAYER_POKEMONS; i++) {
        if (player->Pokemons[i].currentHP > 0) {
            return i + 1; // 1 tabanlı index döndür
        }
    }
    return 0; // Hiç Pokemon kalmamışsa
}

// 2.2.5 initializePokemons (Pokemonları Hazırlama)
void initializePokemons(Pokemon *Pokemons, Type *Types, Move *Moves) {
   
    FILE *file = fopen("C:/Users/asus/OneDrive/Belgeler/CPROJECTS/pokemon.txt", "r");
    if (file == NULL) {
       perror("CRITICAL ERROR: pokemon.txt could not be found at the specified path.");
        exit(EXIT_FAILURE);
    }

    char line[100];
    int pokeIndex = 0;
    
    while (fgets(line, sizeof(line), file) && pokeIndex < NUM_POKEMONS) {
        char name[30], type1Name[20], type2Name[20];
        int maxHP, attack, defense, spAtk, spDef, speed;
        
        if (sscanf(line, "%s %s %s %d %d %d %d %d %d", 
                      name, type1Name, type2Name, 
                      &maxHP, &attack, &defense, &spAtk, &spDef, &speed) == 9) {
            
            // Statları Ata
            strcpy(Pokemons[pokeIndex].name, name);
            Pokemons[pokeIndex].maxHP = maxHP;
            Pokemons[pokeIndex].currentHP = maxHP;
            Pokemons[pokeIndex].attack = attack;
            Pokemons[pokeIndex].defense = defense;
            Pokemons[pokeIndex].spAtk = spAtk;
            Pokemons[pokeIndex].spDef = spDef;
            Pokemons[pokeIndex].speed = speed;
            
            // Tür 1'i Ata
            int type1Idx = getMoveTypeIndex(Types, type1Name);
            if (type1Idx != -1) {
                Pokemons[pokeIndex].types[0] = Types[type1Idx];
            }
            
            // Tür 2'yi Ata
            int type2Idx = -1;
            if (strcmp(type2Name, "-") != 0) {
                type2Idx = getMoveTypeIndex(Types, type2Name);
            }
            
            if (type2Idx != -1) {
                Pokemons[pokeIndex].types[1] = Types[type2Idx];
            } else if (strcmp(type2Name, "-") == 0) {
                // Tek türlüyse, 2. türü de 1. tür olarak ayarla
                Pokemons[pokeIndex].types[1] = Pokemons[pokeIndex].types[0];
            }
            
            // Rastgele 4 Hareket Ata
            int chosenMoves[4] = {-1, -1, -1, -1};
            for (int i = 0; i < 4; i++) {
                int randomMoveIndex;
                int isDuplicate;
                do {
                    isDuplicate = 0;
                    randomMoveIndex = rand() % NUM_MOVES;
                    for (int j = 0; j < i; j++) {
                        if (chosenMoves[j] == randomMoveIndex) {
                            isDuplicate = 1;
                            break;
                        }
                    }
                } while (isDuplicate);
                
                chosenMoves[i] = randomMoveIndex;
                Pokemons[pokeIndex].moves[i] = Moves[randomMoveIndex];
            }

            pokeIndex++;
        }
    }

    fclose(file);
}

// 2.2.2 initialize (Hazırlık)
void initialize(Type *Types, Move *Moves, Pokemon *Pokemons, Player *Player1, Player *Player2) {
    printf("<<<<<   GAME IS LOADING... >>>>>\n");
    
    // Veri Yükleme
   initializeTypes(Types);
   printf("1. Types ready.\n");

   initializeMoves(Moves, Types);
   printf("2. Moves ready.\n");

   initializePokemons(Pokemons, Types, Moves);
   printf("3. Pokemons ready.\n");


    // Oyuncu Bilgilerini ve Takımları Oluştur
    strcpy(Player1->name, "Ash Ketchum");
    strcpy(Player2->name, "Gary Oak");
    
    int isUsed[NUM_POKEMONS] = {0}; 
    
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < PLAYER_POKEMONS; i++) {
            int randomIndex;
            do {
                randomIndex = rand() % NUM_POKEMONS;
            } while (isUsed[randomIndex]);

            isUsed[randomIndex] = 1; 

            if (p == 0) {
                Player1->Pokemons[i] = Pokemons[randomIndex];
            } else {
                Player2->Pokemons[i] = Pokemons[randomIndex];
            }
        }
    }
    
    Player1->currentIndex = 1;
    Player2->currentIndex = 1;

   printf("4. Players & teams ready.\n");
   printf("*** Preparation Finished ***\n\n");

}

// 2.2.8 calculateDamage (Hasar Hesaplama)
double calculateDamage(Pokemon attacker, Pokemon defender, Move move, Type *Types) {
    // 1. Saldırı/Savunma İstatistiklerini Seç
    double attackStat, defenseStat;
    if (move.category == PHYSICAL) {
        attackStat = attacker.attack;
        defenseStat = defender.defense;
    } else {
        attackStat = attacker.spAtk;
        defenseStat = defender.spDef;
    }
    
    // 0'a bölme hatasını önle
    if (defenseStat == 0) {
        defenseStat = 1;
    }

    // 2. Tür Etkisi (Type Effectiveness) Hesaplaması
    double typeEffect1 = 1.0;
    int defType1Index = getMoveTypeIndex(Types, defender.types[0].name);

    if (defType1Index != -1) {
        for(int i = 0; i < NUM_TYPES; i++) {
            // Saldıran Hareketin türünü, savunan Pokemon'un 1. türüne karşı ara
            if(strcmp(Types[defType1Index].effects[i].atkName, move.type.name) == 0) {
                typeEffect1 = Types[defType1Index].effects[i].multiplier;
                break;
            }
        }
    }
    
    double typeEffect2 = 1.0;
    int defType2Index = getMoveTypeIndex(Types, defender.types[1].name);

    if (defType2Index != -1 && defType2Index != defType1Index) {
        for(int i = 0; i < NUM_TYPES; i++) {
            // Saldıran Hareketin türünü, savunan Pokemon'un 2. türüne karşı ara
            if(strcmp(Types[defType2Index].effects[i].atkName, move.type.name) == 0) {
                typeEffect2 = Types[defType2Index].effects[i].multiplier;
                break;
            }
        }
    }
    
    // 3. STAB (Same Type Attack Bonus) Hesaplaması
    double STAB = 1.0;
    if (strcmp(attacker.types[0].name, move.type.name) == 0 ||
        strcmp(attacker.types[1].name, move.type.name) == 0) {
        STAB = 1.5;
    }

    // 4. Nihai Hasar Formülü (Basitleştirilmiş)
    // Damage = MovePower * (Attack/Defense) * TypeEffect1 * TypeEffect2 * STAB
    double damage = (double)move.power * (attackStat / defenseStat) * typeEffect1 * typeEffect2 * STAB;
    
    // Negatif veya sıfır hasarı önle
    return (damage > 0) ? damage : 1.0;
}

// 2.2.8 applyDamage (Hasar Uygulama)
void applyDamage(Player *player1, int p1_choice, int p1_moveIndex, 
                 Player *player2, int p2_choice, int p2_moveIndex, 
                 Type *Types) {

    Pokemon *p1_current = &player1->Pokemons[player1->currentIndex - 1];
    Pokemon *p2_current = &player2->Pokemons[player2->currentIndex - 1];

    // Hız Karşılaştırması ve Sıra Belirleme
    Pokemon *firstAttacker = NULL;
    Player *firstPlayer = NULL;
    Pokemon *secondAttacker = NULL;
    Player *secondPlayer = NULL;
    int p1_goes_first = 0;

    if (p1_current->speed > p2_current->speed) {
        p1_goes_first = 1;
    } else if (p2_current->speed > p1_current->speed) {
        p1_goes_first = 0;
    } else {
        p1_goes_first = (rand() % 2 == 0); // Hızlar eşitse rastgele
    }

    if (p1_goes_first) {
        firstAttacker = p1_current;
        firstPlayer = player1;
        secondAttacker = p2_current;
        secondPlayer = player2;
    } else {
        firstAttacker = p2_current;
        firstPlayer = player2;
        secondAttacker = p1_current;
        secondPlayer = player1;
    }

    // Seçimlerin Yerel Kopyaları
    int first_player_choice = (firstPlayer == player1) ? p1_choice : p2_choice;
    int first_player_move = (firstPlayer == player1) ? p1_moveIndex : p2_moveIndex;
    int second_player_choice = (secondPlayer == player1) ? p1_choice : p2_choice;
    int second_player_move = (secondPlayer == player1) ? p1_moveIndex : p2_moveIndex;

    // --- 1. Saldırı (Hızlı Olan) ---
    if (first_player_choice == 1) { 
        Move move = firstAttacker->moves[first_player_move - 1];
        double damage = calculateDamage(*firstAttacker, *secondAttacker, move, Types);
        
        printf("\n[%s]'s [%s] Pokemon used [%s]!", firstPlayer->name, firstAttacker->name, move.name);

        
        secondAttacker->currentHP -= (int)damage;
        if (secondAttacker->currentHP < 0) secondAttacker->currentHP = 0;

        printf(" Opponent [%s] took %d damage. HP left: %d/%d\n", 
       secondAttacker->name, (int)damage, 
       secondAttacker->currentHP, secondAttacker->maxHP);


        if (secondAttacker->currentHP == 0) {
           printf(">>> Opponent [%s] fainted! <<<\n", secondAttacker->name);

            secondPlayer->currentIndex = getAvailablePokemonIndex(secondPlayer); // Yeni Pokemon seçimi için işaretle
            return; // Dövüş bitti, 2. saldırıya geçme
        }
    } else if (first_player_choice == 2) {
        // Pokemon değişimi zaten playRound'da yapıldı, burada sadece bilgilendirme
        printf("\n%s changed their Pokemon.\n", firstPlayer->name);

    }


    // --- 2. Saldırı (Yavaş Olan) ---
    if (second_player_choice == 1) { 
        Pokemon *currentDefender = (secondPlayer == player1) ? p2_current : p1_current;

        // İkinci saldıranın ve hedefin hala oyunda olup olmadığını kontrol et
        if (secondAttacker->currentHP > 0 && currentDefender->currentHP > 0) {
            Move move = secondAttacker->moves[second_player_move - 1];
            double damage = calculateDamage(*secondAttacker, *currentDefender, move, Types);
            
            printf("\n[%s]'s [%s] Pokemon used [%s]!", secondPlayer->name, secondAttacker->name, move.name);

            
            currentDefender->currentHP -= (int)damage;
            if (currentDefender->currentHP < 0) currentDefender->currentHP = 0;

            printf(" Opponent [%s] took %d damage. HP left: %d/%d\n",
            currentDefender->name, (int)damage,
            currentDefender->currentHP, currentDefender->maxHP);


            if (currentDefender->currentHP == 0) {
                printf(">>> Opponent [%s] fainted! <<<\n", currentDefender->name);

                firstPlayer->currentIndex = getAvailablePokemonIndex(firstPlayer); // Yeni Pokemon seçimi için işaretle
            }
        }
    } else if (second_player_choice == 2) {
       printf("\n%s changed their Pokemon.\n", secondPlayer->name);

    }
}

// 2.2.7 playRound (Bir Tur Oynama)
void playRound(Player *Player1, Player *Player2, Type *Types) {
    int p1_choice, p2_choice;
    int p1_moveIndex = 0, p2_moveIndex = 0;
    int p1_pokeSwitchIndex = -1, p2_pokeSwitchIndex = -1;

    printf("\n**** NEW ROUND IS STARTING ****\n");
    printf("%s's Pokemon: %s (HP: %d/%d)\n", Player1->name, Player1->Pokemons[Player1->currentIndex - 1].name, Player1->Pokemons[Player1->currentIndex - 1].currentHP, Player1->Pokemons[Player1->currentIndex - 1].maxHP);
    printf("%s's Pokemon: %s (HP: %d/%d)\n", Player2->name, Player2->Pokemons[Player2->currentIndex - 1].name, Player2->Pokemons[Player2->currentIndex - 1].currentHP, Player2->Pokemons[Player2->currentIndex - 1].maxHP);
    
    // --- Oyuncu 1'in Hamlesini Al ---
   printf("\n[%s] choose a move:\n1 - Attack\n2 - Change Pokemon\nChoice: ", Player1->name);

    // Basit Input Kontrolü
    if (scanf("%d", &p1_choice) != 1 || (p1_choice != 1 && p1_choice != 2)) {
         p1_choice = 1;
         while(getchar() != '\n'); // Kalan karakterleri temizle
    }

   if (p1_choice == 1) { 
        // --- BU KISIM DEGISTI: 1-4 arasi gecerli seçim yapana kadar döner ---
        while (1) {
           printf("Choose a move to use (1-4):\n");
            for (int i = 0; i < 4; i++) {
                printf("%d - %s (Power: %d)\n", i + 1, Player1->Pokemons[Player1->currentIndex - 1].moves[i].name, Player1->Pokemons[Player1->currentIndex - 1].moves[i].power);
            }
            printf("Choice: ");
            if (scanf("%d", &p1_moveIndex) == 1 && p1_moveIndex >= 1 && p1_moveIndex <= 4) {
                break; // Gecerli seçim, döngüden çık
            }
           printf(">>> Invalid move! Choice must be between 1 and 4. <<<\n");
            while(getchar() != '\n'); // Yanlış girişi temizle
        }
    } else if (p1_choice == 2) { 
        // Pokemon değiştirme 
       printf("Which Pokemon do you want to use?\n");
        for (int i = 0; i < PLAYER_POKEMONS; i++) {
            if (Player1->Pokemons[i].currentHP > 0) {
                printf("%d - %s (HP: %d/%d) (Current Pokemon %s)\n", i + 1, Player1->Pokemons[i].name, Player1->Pokemons[i].currentHP, Player1->Pokemons[i].maxHP, 
                       (i + 1 == Player1->currentIndex) ? "YES" : "NO");
            } else {
                printf("%d - %s (FAINTED)\n", i + 1, Player1->Pokemons[i].name);
            }
        }
        scanf("%d", &p1_pokeSwitchIndex);
        
        // Geçerli Pokemon seçildiyse değiştir
        if (p1_pokeSwitchIndex >= 1 && p1_pokeSwitchIndex <= PLAYER_POKEMONS && 
            Player1->Pokemons[p1_pokeSwitchIndex - 1].currentHP > 0 &&
            p1_pokeSwitchIndex != Player1->currentIndex) {
            Player1->currentIndex = p1_pokeSwitchIndex; 
            printf(">>> %s sent %s to the field! <<<\n", Player1->name, Player1->Pokemons[Player1->currentIndex - 1].name);
        } else {
            // Hatalı veya aynı Pokemon seçimi
            printf("Invalid or same choice. %s chose to attack.\n", Player1->name);
            p1_choice = 1; // Saldırıya dön
            p1_moveIndex = 1;
        }
    }

    // --- Oyuncu 2'nin Hamlesini Al ---
    printf("\n[%s] choose a move:\n1 - Attack\n2 - Change Pokemon\nChoice: ", Player2->name);
    if (scanf("%d", &p2_choice) != 1 || (p2_choice != 1 && p2_choice != 2)) {
         p2_choice = 1;
         while(getchar() != '\n');
    }

    if (p2_choice == 1) {
        // 1-4 arasi gecerli seçim yapana kadar döner ---
        while (1) {
            printf("Choose a move to use (1-4):\n");
            for (int i = 0; i < 4; i++) {
                printf("%d - %s (Power: %d)\n", i + 1, Player2->Pokemons[Player2->currentIndex - 1].moves[i].name, Player2->Pokemons[Player2->currentIndex - 1].moves[i].power);
            }
            printf("Choice: ");
            if (scanf("%d", &p2_moveIndex) == 1 && p2_moveIndex >= 1 && p2_moveIndex <= 4) {
                break; // Gecerli seçim
            }
             printf(">>> Invalid move! Choice must be between 1 and 4. <<<\n");
            while(getchar() != '\n');
        }
    } else if (p2_choice == 2) {
        // Pokemon değiştirme
         printf("Which Pokemon do you want to use?\n");
        for (int i = 0; i < PLAYER_POKEMONS; i++) {
            if (Player2->Pokemons[i].currentHP > 0) {
                printf("%d - %s (HP: %d/%d) (Current Pokemon: %s)\n", i + 1, Player2->Pokemons[i].name, Player2->Pokemons[i].currentHP, Player2->Pokemons[i].maxHP,
                       (i + 1 == Player2->currentIndex) ? "YES" : "NO");
            } else {
                printf("%d - %s (FAINTED)\n", i + 1, Player2->Pokemons[i].name);
            }
        }
        printf("Choice: ");
        scanf("%d", &p2_pokeSwitchIndex);
        
        // Geçerli Pokemon seçildiyse değiştir
        if (p2_pokeSwitchIndex >= 1 && p2_pokeSwitchIndex <= PLAYER_POKEMONS && 
            Player2->Pokemons[p2_pokeSwitchIndex - 1].currentHP > 0 &&
            p2_pokeSwitchIndex != Player2->currentIndex) {
            Player2->currentIndex = p2_pokeSwitchIndex;
            printf(">>> %s sent %s to the field! <<<\n", Player2->name, Player2->Pokemons[Player2->currentIndex - 1].name);
        } else {
            // Hatalı veya aynı Pokemon seçimi
            printf("Invalid or same choice. %s chose to attack.\n", Player2->name);
            p2_choice = 1; // Saldırıya dön
            p2_moveIndex = 1;
        }
    }
    
    // Hasar Uygula
    applyDamage(Player1, p1_choice, p1_moveIndex, Player2, p2_choice, p2_moveIndex, Types);

    // Bayılan Pokemon varsa yeni birini seç
    // Eğer oyuncu saldırı seçtiyse, bayılma kontrolü applyDamage sonunda yapılır
    if (Player1->Pokemons[Player1->currentIndex - 1].currentHP == 0) {
        Player1->currentIndex = getAvailablePokemonIndex(Player1);
        if (Player1->currentIndex != 0) {
            printf("\n[%s]'s Pokemon fainted! New Pokemon: [%s]\n", Player1->name, Player1->Pokemons[Player1->currentIndex - 1].name);
        }
    }
    if (Player2->Pokemons[Player2->currentIndex - 1].currentHP == 0) {
        Player2->currentIndex = getAvailablePokemonIndex(Player2);
        if (Player2->currentIndex != 0) {
            printf("\n[%s]'s Pokemon fainted! New Pokemon: [%s]\n", Player2->name, Player2->Pokemons[Player2->currentIndex - 1].name);
        }
    }
}