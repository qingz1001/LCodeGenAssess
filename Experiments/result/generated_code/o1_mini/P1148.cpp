#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Player {
    int S12;
    int C10;
    int D11;
    int H[14]; // H1 to H13
};

// Function to parse a single card and update player's flags
void parse_card(char* card, struct Player* p) {
    if (card[0] == 'H') {
        int num = atoi(card + 1);
        if (num >=1 && num <=13) {
            p->H[num] = 1;
        }
    }
    else if (card[0] == 'S') {
        if (strcmp(card, "S12") == 0) {
            p->S12 = 1;
        }
    }
    else if (card[0] == 'D') {
        if (strcmp(card, "D11") == 0) {
            p->D11 = 1;
        }
    }
    else if (card[0] == 'C') {
        if (strcmp(card, "C10") == 0) {
            p->C10 = 1;
        }
    }
}

int main(){
    char line[256];
    // Heart scores from H1 to H13
    int heart_score[14] = {0, -50, -2, -3, -4, -5, -6, -7, -8, -9, -10, -20, -30, -40};
    
    while(1){
        struct Player players[4];
        // Initialize players
        for(int i=0;i<4;i++){
            players[i].S12 = 0;
            players[i].C10 = 0;
            players[i].D11 = 0;
            for(int j=0; j<=13; j++) players[i].H[j] = 0;
        }
        int counts[4];
        int all_zero = 1;
        // Read four players
        for(int i=0;i<4;i++){
            if(!fgets(line, sizeof(line), stdin)){
                // EOF reached unexpectedly
                return 0;
            }
            // Remove trailing newline
            line[strcspn(line, "\n")] = 0;
            // Tokenize the line
            char *token = strtok(line, " ");
            if(token == NULL){
                counts[i] = 0;
            }
            else{
                counts[i] = atoi(token);
                if(counts[i] > 0){
                    all_zero = 0;
                }
                for(int j=0; j<counts[i]; j++){
                    token = strtok(NULL, " ");
                    if(token != NULL){
                        parse_card(token, &players[i]);
                    }
                }
            }
        }
        // Check termination condition
        if(all_zero){
            break;
        }
        // Check if any player holds all 16 scoring cards
        int all16_player = -1;
        for(int i=0;i<4;i++){
            int has_all = players[i].S12 && players[i].C10 && players[i].D11;
            for(int h=1; h<=13 && has_all; h++) {
                if(!players[i].H[h]){
                    has_all = 0;
                }
            }
            if(has_all){
                all16_player = i;
                break;
            }
        }
        if(all16_player != -1){
            // One player holds all 16
            for(int i=0;i<4;i++){
                if(i != all16_player){
                    printf("0 ");
                }
                else{
                    printf("+1000 ");
                }
            }
            printf("\n");
            continue;
        }
        // Check if any player holds all H1-H13
        int allH_player = -1;
        for(int i=0;i<4;i++){
            int has_allH = 1;
            for(int h=1; h<=13; h++) {
                if(!players[i].H[h]){
                    has_allH = 0;
                    break;
                }
            }
            if(has_allH){
                allH_player = i;
                break;
            }
        }
        // Initialize scores
        int scores[4] = {0,0,0,0};
        if(allH_player != -1){
            // Determine base score for the holder
            int base = 200;
            if(players[allH_player].S12 && players[allH_player].D11){
                base = 500;
            }
            // Check if player has C10 and other scoring cards
            int other_scoring = 0;
            if(base > 0 && players[allH_player].C10){
                other_scoring = 1;
            }
            if(other_scoring){
                base *= 2;
            }
            scores[allH_player] = base;
            // Calculate other players
            for(int i=0;i<4;i++){
                if(i == allH_player){
                    continue;
                }
                // Check if player has C10
                if(players[i].C10){
                    // Check if player has only C10
                    int has_other = players[i].S12 || players[i].D11;
                    for(int h=1; h<=13; h++) if(players[i].H[h]) { has_other = 1; break;}
                    if(!has_other){
                        scores[i] = 50;
                    }
                    else{
                        // Sum other scoring cards
                        int sum = 0;
                        if(players[i].S12) sum += -100;
                        if(players[i].D11) sum += 100;
                        for(int h=1; h<=13; h++) {
                            if(players[i].H[h]){
                                sum += heart_score[h];
                            }
                        }
                        sum *= 2;
                        scores[i] = sum;
                    }
                }
                else{
                    // Sum other scoring cards
                    int sum = 0;
                    if(players[i].S12) sum += -100;
                    if(players[i].D11) sum += 100;
                    for(int h=1; h<=13; h++) {
                        if(players[i].H[h]){
                            sum += heart_score[h];
                        }
                    }
                    scores[i] = sum;
                }
            }
        }
        else{
            // No player holds all H1-H13, calculate normally
            for(int i=0;i<4;i++){
                if(players[i].C10){
                    // Check if player has only C10
                    int has_other = players[i].S12 || players[i].D11;
                    for(int h=1; h<=13; h++) if(players[i].H[h]) { has_other = 1; break;}
                    if(!has_other){
                        scores[i] = 50;
                    }
                    else{
                        // Sum other scoring cards
                        int sum = 0;
                        if(players[i].S12) sum += -100;
                        if(players[i].D11) sum += 100;
                        for(int h=1; h<=13; h++) {
                            if(players[i].H[h]){
                                sum += heart_score[h];
                            }
                        }
                        sum *= 2;
                        scores[i] = sum;
                    }
                }
                else{
                    // Sum other scoring cards
                    int sum = 0;
                    if(players[i].S12) sum += -100;
                    if(players[i].D11) sum += 100;
                    for(int h=1; h<=13; h++) {
                        if(players[i].H[h]){
                            sum += heart_score[h];
                        }
                    }
                    scores[i] = sum;
                }
            }
        }
        // Print scores
        for(int i=0;i<4;i++){
            if(scores[i] > 0){
                printf("+%d", scores[i]);
            }
            else{
                printf("%d", scores[i]);
            }
            if(i !=3){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}