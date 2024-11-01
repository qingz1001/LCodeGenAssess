#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MOVES 9
#define NUM_CLOCKS 9

int initial[NUM_CLOCKS];
int moves_affect[NUM_MOVES][NUM_CLOCKS] = {
    // Move 1: ABDE -> 0,1,3,4
    {1,1,0,1,1,0,0,0,0},
    // Move 2: ABC -> 0,1,2
    {1,1,1,0,0,0,0,0,0},
    // Move 3: BCEF ->1,2,4,5
    {0,1,1,0,1,1,0,0,0},
    // Move 4: ADG ->0,3,6
    {1,0,0,1,0,0,1,0,0},
    // Move 5: BDEFH ->1,3,4,5,7
    {0,1,0,1,1,1,0,1,0},
    // Move 6: CFI ->2,5,8
    {0,0,1,0,0,1,0,0,1},
    // Move 7: DEGH ->3,4,6,7
    {0,0,0,1,1,0,1,1,0},
    // Move 8: GHI ->6,7,8
    {0,0,0,0,0,0,1,1,1},
    // Move 9: EFHI ->4,5,7,8
    {0,0,0,0,1,1,0,1,1}
};

int best_move_counts[NUM_MOVES];
int found = 0;
int min_total = 100;

int clocks[NUM_CLOCKS];

int better(int a_counts[], int b_counts[]) {
    for(int i=0;i<NUM_MOVES;i++) {
        if(a_counts[i] < b_counts[i]) return 1;
        if(a_counts[i] > b_counts[i]) return 0;
    }
    return 0;
}

void search(int move, int counts[], int total) {
    if(move == NUM_MOVES){
        for(int i=0;i<NUM_CLOCKS;i++) {
            if(clocks[i] != 0) return;
        }
        if(total < min_total || (total == min_total && better(counts, best_move_counts))) {
            min_total = total;
            memcpy(best_move_counts, counts, sizeof(int)*NUM_MOVES);
            found = 1;
        }
        return;
    }
    for(int cnt=0; cnt<=3; cnt++){
        counts[move] = cnt;
        int exceed = (total + cnt) > min_total;
        if(!exceed){
            for(int i=0;i<NUM_CLOCKS;i++) {
                clocks[i] = (clocks[i] + moves_affect[move][i]*cnt) % 4;
            }
            search(move+1, counts, total + cnt);
            for(int i=0;i<NUM_CLOCKS;i++) {
                clocks[i] = (clocks[i] - moves_affect[move][i]*cnt) % 4;
                if(clocks[i] < 0) clocks[i] += 4;
            }
        }
        counts[move] = 0;
    }
}

int main(){
    for(int i=0;i<NUM_CLOCKS;i++) {
        int x;
        scanf("%d", &x);
        initial[i] = (x / 3) %4;
        clocks[i] = initial[i];
    }
    int counts[NUM_MOVES] = {0};
    search(0, counts, 0);
    if(found){
        int first = 1;
        for(int i=0;i<NUM_MOVES;i++) {
            for(int j=0; j<best_move_counts[i]; j++) {
                if(!first) printf(" ");
                printf("%d", i+1);
                first = 0;
            }
        }
        printf("\n");
    }
    else{
        printf("\n");
    }
    return 0;
}