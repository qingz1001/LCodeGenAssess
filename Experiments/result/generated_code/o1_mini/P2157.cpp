#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int T;
    int B;
    int index;
} Student;

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        int N;
        scanf("%d", &N);
        Student students[N];
        for(int i=0;i<N;i++){
            scanf("%d %d", &students[i].T, &students[i].B);
            students[i].index = i;
        }
        // Initialize a list to keep track of remaining students
        int remaining[N];
        for(int i=0;i<N;i++) remaining[i] = 1;
        int total_time = 0;
        int last_flavor = -1;
        for(int step=0; step<N; step++){
            // Look ahead up to 8 positions
            int max_window = (N < 8) ? N : 8;
            int best_idx = -1;
            int best_xor = -1;
            for(int i=0;i<N;i++){
                if(remaining[i]){
                    // Calculate how many can be ahead
                    int allowed = 1;
                    // Determine if this student can be placed now
                    // Number of students after i that have been taken is step - i
                    // It should be <= B_i
                    int count = 0;
                    for(int j=0; j<i; j++) {
                        if(!remaining[j]) count++;
                    }
                    if(count <= students[i].B){
                        // Calculate XOR
                        int current_xor;
                        if(last_flavor == -1){
                            current_xor = 0;
                        }
                        else{
                            current_xor = (last_flavor ^ students[i].T);
                        }
                        if(best_idx == -1 || current_xor < best_xor){
                            best_idx = i;
                            best_xor = current_xor;
                            if(best_xor ==0) break;
                        }
                    }
                    // Limit the window
                    if(i >= max_window) break;
                }
            }
            if(best_idx == -1){
                // Fallback to first available
                for(int i=0;i<N;i++) if(remaining[i]){
                    best_idx = i;
                    if(last_flavor == -1){
                        best_xor =0;
                    }
                    else{
                        best_xor = (last_flavor ^ students[i].T);
                    }
                    break;
                }
            }
            // Update total_time
            if(last_flavor != -1){
                total_time += (last_flavor ^ students[best_idx].T);
            }
            // Update last_flavor
            last_flavor = students[best_idx].T;
            // Mark as taken
            remaining[best_idx] = 0;
        }
        printf("%d\n", total_time);
    }
    return 0;
}