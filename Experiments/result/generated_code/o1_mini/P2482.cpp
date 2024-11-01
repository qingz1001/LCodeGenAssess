#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000
#define MAX_HAND 1000

typedef struct {
    char role[3];
    int hp;
    int max_hp;
    char hand[MAX_HAND][3];
    int hand_cnt;
    int is_dead;
    int last_damage_source;
    char weapon[3];
} Player;

int n, m;
Player players[MAX_PLAYERS];
char deck[MAX_CARDS][3];
int deck_cnt;
int current;
int game_over = 0;
char game_result[3] = "MP";

void draw_card(int pid) {
    if (deck_cnt == 0) return;
    players[pid].hand[players[pid].hand_cnt][0] = deck[deck_cnt-1][0];
    players[pid].hand[players[pid].hand_cnt][1] = deck[deck_cnt-1][1];
    players[pid].hand_cnt++;
    deck_cnt--;
}

void remove_player(int pid) {
    players[pid].is_dead = 1;
    players[pid].hand_cnt = 0;
}

int find_next(int pid) {
    int start = (pid +1)%n;
    for(int i=0;i<n;i++) {
        int idx = (start +i)%n;
        if(!players[idx].is_dead) return idx;
    }
    return pid;
}

void check_victory() {
    int fp = 0;
    int mp_alive = !players[0].is_dead;
    for(int i=1;i<n;i++) if(!players[i].is_dead && strcmp(players[i].role, "FP") ==0) fp++;
    if(mp_alive && fp ==0){
        strcpy(game_result, "MP");
        game_over =1;
    }
    if(mp_alive ==0){
        strcpy(game_result, "FP");
        game_over =1;
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++){
        scanf("%s", players[i].role);
        players[i].hp = 4;
        players[i].max_hp =4;
        players[i].hand_cnt =0;
        players[i].is_dead =0;
        players[i].last_damage_source = -1;
        players[i].weapon[0] = '\0';
        for(int j=0;j<4;j++) {
            scanf("%s", players[i].hand[players[i].hand_cnt]);
            players[i].hand_cnt++;
        }
    }
    for(int i=0;i<m;i++) {
        scanf("%s", deck[i]);
    }
    deck_cnt = m;
    current =0;
    while(!game_over){
        // Start turn
        if(players[current].is_dead){
            current = (current +1)%n;
            continue;
        }
        // Draw phase
        draw_card(current);
        draw_card(current);
        // Play phase - simplified: do nothing
        // Check victory
        check_victory();
        if(game_over) break;
        current = (current +1)%n;
    }
    printf("%s\n", game_result);
    for(int i=0;i<n;i++) {
        if(players[i].is_dead){
            printf("DEAD\n");
            continue;
        }
        if(players[i].hand_cnt ==0){
            printf("\n");
            continue;
        }
        for(int j=0;j<players[i].hand_cnt;j++){
            printf("%s", players[i].hand[j]);
            if(j != players[i].hand_cnt-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}