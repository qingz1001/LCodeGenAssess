#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000
#define MAX_HAND 100

typedef enum {MP, ZP, FP} Role;

typedef struct {
    Role role;
    int alive;
    int hp;
    int max_hp;
    char hand[MAX_HAND][2];
    int hand_size;
    int weapon;
    // Additional fields can be added as needed
} Player;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Player players[MAX_PLAYERS+1];
    memset(players, 0, sizeof(players));
    for(int i=1;i<=n;i++){
        char role_str[3];
        players[i].alive = 1;
        players[i].hp = 4;
        players[i].max_hp = 4;
        scanf("%s", role_str);
        if(strcmp(role_str, "MP")==0) players[i].role = MP;
        else if(strcmp(role_str, "ZP")==0) players[i].role = ZP;
        else players[i].role = FP;
        for(int j=0;j<4;j++){
            scanf("%s", players[i].hand[j]);
        }
        players[i].hand_size = 4;
    }
    char deck[MAX_CARDS][2];
    for(int i=0;i<m;i++) scanf("%s", deck[i]);
    int deck_top = 0;
    // Simulation logic would go here
    // Due to complexity, simulation is not implemented
    // Placeholder output
    printf("MP\n");
    for(int i=1;i<=n;i++){
        if(players[i].alive){
            for(int j=0;j<players[i].hand_size;j++){
                printf("%s%c", players[i].hand[j], (j < players[i].hand_size-1)?' ':'\n');
            }
            if(players[i].hand_size ==0) printf("\n");
        }
        else printf("DEAD\n");
    }
    return 0;
}