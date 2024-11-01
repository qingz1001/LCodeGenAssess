#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 4
#define MAX_CARDS 20

typedef struct {
    int hearts[14]; // H1 to H13, index 1-13
    int has_S12;
    int has_D11;
    int has_C10;
    int total_scoring_cards;
} Player;

int main(){
    int n;
    while(1){
        Player players[MAX_PLAYERS];
        memset(players, 0, sizeof(players));
        int all_zero = 1;
        // Read four players
        for(int i=0; i<MAX_PLAYERS; i++){
            if(scanf("%d", &n)!=1){
                return 0;
            }
            if(n >0){
                all_zero = 0;
            }
            for(int j=0; j<n; j++){
                char card[10];
                scanf("%s", card);
                int len = strlen(card);
                if(len <2) continue;
                char suit = card[0];
                int num = atoi(card+1);
                if(suit == 'H'){
                    if(num >=1 && num <=13){
                        players[i].hearts[num] =1;
                        players[i].total_scoring_cards++;
                    }
                }
                else if(suit == 'S'){
                    if(num ==12){
                        players[i].has_S12 =1;
                        players[i].total_scoring_cards++;
                    }
                }
                else if(suit == 'D'){
                    if(num ==11){
                        players[i].has_D11 =1;
                        players[i].total_scoring_cards++;
                    }
                }
                else if(suit == 'C'){
                    if(num ==10){
                        players[i].has_C10 =1;
                        players[i].total_scoring_cards++;
                    }
                }
            }
        }
        if(all_zero){
            break;
        }
        // Check if any player holds all 16 scoring cards
        int has_all_16 = -1;
        for(int i=0; i<MAX_PLAYERS; i++){
            if(players[i].has_S12 && players[i].has_D11 && players[i].has_C10){
                int all_hearts =1;
                for(int h=1; h<=13; h++) {
                    if(players[i].hearts[h] ==0){
                        all_hearts =0;
                        break;
                    }
                }
                if(all_hearts && players[i].total_scoring_cards ==16){
                    has_all_16 = i;
                    break;
                }
            }
        }
        int scores[MAX_PLAYERS];
        memset(scores, 0, sizeof(scores));
        if(has_all_16 != -1){
            for(int i=0; i<MAX_PLAYERS; i++){
                if(i == has_all_16){
                    scores[i] = 1000;
                }
                else{
                    scores[i] =0;
                }
            }
        }
        else{
            // Check if any player holds all hearts
            int all_hearts_player = -1;
            for(int i=0; i<MAX_PLAYERS; i++){
                int holds_all_hearts =1;
                for(int h=1; h<=13; h++) {
                    if(players[i].hearts[h] ==0){
                        holds_all_hearts =0;
                        break;
                    }
                }
                if(holds_all_hearts){
                    all_hearts_player = i;
                    break;
                }
            }
            if(all_hearts_player != -1){
                // Handle player with all hearts
                int base =0;
                if(players[all_hearts_player].has_S12 && players[all_hearts_player].has_D11){
                    base = 500;
                }
                else{
                    base = 200;
                }
                if(players[all_hearts_player].has_C10){
                    base *=2;
                }
                scores[all_hearts_player] = base;
                // Handle other players
                for(int i=0; i<MAX_PLAYERS; i++){
                    if(i == all_hearts_player){
                        continue;
                    }
                    int sum =0;
                    // Sum scoring cards
                    for(int h=1; h<=13; h++){}
                    if(players[i].hearts[1]) {sum +=0;}
                    for(int h=1; h<=13; h++){
                        if(players[i].hearts[h]){
                            // Hearts are not all with one player, so scored negatively
                            // Scores as per rule4
                            int heart_score;
                            switch(h){
                                case 1: heart_score = -50; break;
                                case 2: heart_score = -2; break;
                                case 3: heart_score = -3; break;
                                case 4: heart_score = -4; break;
                                case 5: heart_score = -5; break;
                                case 6: heart_score = -6; break;
                                case 7: heart_score = -7; break;
                                case 8: heart_score = -8; break;
                                case 9: heart_score = -9; break;
                                case 10: heart_score = -10; break;
                                case 11: heart_score = -20; break;
                                case 12: heart_score = -30; break;
                                case 13: heart_score = -40; break;
                                default: heart_score =0;
                            }
                            sum += heart_score;
                        }
                    }
                    if(players[i].has_S12){
                        sum += -100;
                    }
                    if(players[i].has_D11){
                        sum += 100;
                    }
                    if(players[i].has_C10){
                        if(players[i].total_scoring_cards ==1){
                            sum +=50;
                        }
                        else{
                            sum -= players[i].has_C10 ? 0 :0; // Not needed
                            sum = sum *2;
                        }
                    }
                    scores[i] += sum;
                }
            }
            else{
                // All hearts scored as per rule4
                for(int i=0; i<MAX_PLAYERS; i++){
                    int sum =0;
                    for(int h=1; h<=13; h++){
                        if(players[i].hearts[h]){
                            // Negative scores
                            switch(h){
                                case 1: sum += -50; break;
                                case 2: sum += -2; break;
                                case 3: sum += -3; break;
                                case 4: sum += -4; break;
                                case 5: sum += -5; break;
                                case 6: sum += -6; break;
                                case 7: sum += -7; break;
                                case 8: sum += -8; break;
                                case 9: sum += -9; break;
                                case 10: sum += -10; break;
                                case 11: sum += -20; break;
                                case 12: sum += -30; break;
                                case 13: sum += -40; break;
                                default: break;
                            }
                        }
                    }
                    if(players[i].has_S12){
                        sum += -100;
                    }
                    if(players[i].has_D11){
                        sum += 100;
                    }
                    if(players[i].has_C10){
                        if(players[i].total_scoring_cards ==1){
                            sum +=50;
                        }
                        else{
                            sum = sum *2;
                        }
                    }
                    scores[i] += sum;
                }
            }
        }
        // Adjust scores for the case when a player holds all hearts
        if(has_all_16 == -1){
            // Check if any player holds all hearts
            int all_hearts_player = -1;
            for(int i=0; i<MAX_PLAYERS; i++){
                int holds_all_hearts =1;
                for(int h=1; h<=13; h++) {
                    if(players[i].hearts[h] ==0){
                        holds_all_hearts =0;
                        break;
                    }
                }
                if(holds_all_hearts){
                    all_hearts_player = i;
                    break;
                }
            }
            if(all_hearts_player != -1){
                // Recompute the scores for other players
                // Reset scores
                for(int i=0; i<MAX_PLAYERS; i++){
                    if(i == all_hearts_player){
                        continue;
                    }
                    int sum =0;
                    // Sum scoring cards
                    for(int h=1; h<=13; h++){
                        if(players[i].hearts[h]){
                            // Negative scores
                            switch(h){
                                case 1: sum += -50; break;
                                case 2: sum += -2; break;
                                case 3: sum += -3; break;
                                case 4: sum += -4; break;
                                case 5: sum += -5; break;
                                case 6: sum += -6; break;
                                case 7: sum += -7; break;
                                case 8: sum += -8; break;
                                case 9: sum += -9; break;
                                case 10: sum += -10; break;
                                case 11: sum += -20; break;
                                case 12: sum += -30; break;
                                case 13: sum += -40; break;
                                default: break;
                            }
                        }
                    }
                    if(players[i].has_S12){
                        sum += -100;
                    }
                    if(players[i].has_D11){
                        sum += 100;
                    }
                    if(players[i].has_C10){
                        if(players[i].total_scoring_cards ==1){
                            sum =50;
                        }
                        else{
                            sum = sum *2;
                        }
                    }
                    scores[i] = sum;
                }
                // Set score for all_hearts_player
                int base =0;
                if(players[all_hearts_player].has_S12 && players[all_hearts_player].has_D11){
                    base = 500;
                }
                else{
                    base = 200;
                }
                if(players[all_hearts_player].has_C10){
                    base *=2;
                }
                scores[all_hearts_player] = base;
            }
        }
        // Print the scores
        for(int i=0; i<MAX_PLAYERS; i++){
            if(scores[i] >0){
                printf("+%d", scores[i]);
            }
            else if(scores[i] <0){
                printf("%d", scores[i]);
            }
            else{
                printf("0");
            }
            if(i != MAX_PLAYERS-1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}