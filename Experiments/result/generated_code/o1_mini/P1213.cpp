#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int s[9];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int val;
            scanf("%d", &val);
            if(val == 12) s[i*3 + j] = 0;
            else s[i*3 + j] = (val / 3) %4;
        }
    }
    // Define which moves affect which clocks
    // Moves are 0-indexed
    int clock_to_moves[9][5] = {
        {0,1,3,-1,-1},        // A: Move1, Move2, Move4
        {0,1,2,4,-1},         // B: Move1, Move2, Move3, Move5
        {1,2,5,-1,-1},        // C: Move2, Move3, Move6
        {0,3,4,6,-1},         // D: Move1, Move4, Move5, Move7
        {0,2,4,6,8},          // E: Move1, Move3, Move5, Move7, Move9
        {2,4,5,8,-1},         // F: Move3, Move5, Move6, Move9
        {3,6,7,-1,-1},        // G: Move4, Move7, Move8
        {4,6,7,8,-1},         // H: Move5, Move7, Move8, Move9
        {5,7,8,-1,-1}         // I: Move6, Move8, Move9
    };
    int clock_move_count[9] = {3,4,3,4,5,4,3,4,3};
    // Initialize best sequence
    int best_length = 28;
    int best_seq[27];
    // Iterate over all possible combinations
    for(unsigned int num=0; num < (1<<18); num++){
        int counts[9];
        unsigned int tmp = num;
        for(int m=0; m<9; m++) {
            counts[m] = tmp & 3;
            tmp >>=2;
        }
        // Check all clocks
        int valid = 1;
        for(int c=0; c<9 && valid; c++){
            int total =0;
            for(int k=0; k<clock_move_count[c]; k++){
                int move = clock_to_moves[c][k];
                if(move == -1) break;
                total += counts[move];
            }
            total %=4;
            if((s[c] + total) %4 !=0){
                valid =0;
            }
        }
        if(valid){
            // Collect move sequence
            int temp_seq[27];
            int cnt =0;
            for(int m=0; m<9; m++){
                for(int t=0; t<counts[m]; t++){
                    temp_seq[cnt++] = m+1;
                }
            }
            if(cnt < best_length){
                best_length = cnt;
                memcpy(best_seq, temp_seq, cnt * sizeof(int));
            }
            else if(cnt == best_length){
                int smaller = 0;
                for(int i=0;i<cnt && !smaller;i++){
                    if(temp_seq[i] < best_seq[i]){
                        smaller =1;
                    }
                    else if(temp_seq[i] > best_seq[i]){
                        break;
                    }
                }
                if(smaller){
                    memcpy(best_seq, temp_seq, cnt * sizeof(int));
                }
            }
        }
    }
    // Print the best sequence
    if(best_length ==28){
        // No solution, though problem says it always exists
    }
    else{
        for(int i=0;i<best_length;i++){
            if(i>0) printf(" ");
            printf("%d", best_seq[i]);
        }
        printf("\n");
    }
    return 0;
}