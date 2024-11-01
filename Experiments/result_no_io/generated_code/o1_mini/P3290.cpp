#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define MOD 1000000007
#define MAX_STATE 243
#define MAX_C 6
#define MAX_Q 5

long long pow3[1201];

long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

int main(){
    int n, m, c, q;
    scanf("%d %d %d %d", &n, &m, &c, &q);
    char templates[MAX_Q][2][7];
    for(int i=0;i<q;i++) {
        scanf("%s", templates[i][0]);
        scanf("%s", templates[i][1]);
    }
    // Precompute powers of 3
    pow3[0] = 1;
    for(int i=1;i<=n*m;i++) pow3[i] = pow3[i-1] * 3 % MOD;
    for(int ti=0; ti<q; ti++){
        // Read template
        char template_top[MAX_C+1], template_bottom[MAX_C+1];
        strcpy(template_top, templates[ti][0]);
        strcpy(template_bottom, templates[ti][1]);
        // Initialize DP
        // State represents the last c-1 cells of the previous row
        // Each cell can be 0,1,2
        int state_size = 1;
        for(int i=0;i<c-1;i++) state_size *=3;
        long long prev_dp[MAX_STATE];
        long long curr_dp[MAX_STATE];
        memset(prev_dp, 0, sizeof(prev_dp));
        memset(curr_dp, 0, sizeof(curr_dp));
        prev_dp[0] = 1;
        for(int row=0; row<n; row++){
            memset(curr_dp, 0, sizeof(curr_dp));
            for(int s=0; s<(int)(pow(3, c-1)); s++){
                if(prev_dp[s]==0) continue;
                // Generate all possible current row assignments
                // m <=12, c<=6
                // To optimize, generate row by row recursively
                // Implemented as iterative for speed
                // Each cell has 3 options
                // To check for pattern match, keep a sliding window of c columns
                // Need to store the last c-1 cells of the previous row
                // and the current row's cells up to c
                // If any window matches the template, skip
                // Else, add to curr_dp
                // Implemented using nested loops
                // Due to time constraints, m and c are small
                // Use recursive backtracking
                // But implement iteratively
                // So, use a stack-like approach
                // Implemented as nested for loops up to m
                // Initialize with state s and count
                // and for each cell, iterate over 3 possibilities
                // and check for match when enough cells are filled
                // Implemented using a queue
                // To save time, use a simple recursive function
                // But since m and c are small, implement manually
                // Due to complexity, use m up to 12 and c up to6
                // Implement a loop that iterates over all possible assignments
                // of m cells, and for each, check the c-length window
                // Reconstruct the previous row's last c-1 cells
                // from state s
                // So, build the full previous row's last c-1 cells
                // and append the current row's cells
                // Check any window of c cells in the current row and previous row
                // matches the template
                // If not, update the new state
                // Implemented as follows:
                // Generate previous row's last c-1 cells
                int prev_cells[c-1];
                int tmp = s;
                for(int i=0;i<c-1;i++){
                    prev_cells[c-2-i] = tmp %3;
                    tmp /=3;
                }
                // Now iterate over all possible current row assignments
                // Each cell has 3 options
                // Total 3^m possibilities, but m<=12, so up to 531441
                // Implement as a single loop from 0 to 3^m -1
                long long total_assign = pow3[m];
                for(long long assign=0; assign < power(3, m); assign++){
                    // Decode the current row's cells
                    int curr_row[m];
                    long long tmp_assign = assign;
                    for(int i=0;i<m;i++){
                        curr_row[m-1-i] = tmp_assign %3;
                        tmp_assign /=3;
                    }
                    // Check for pattern match
                    int match =0;
                    if(row >0 && row <n){
                        for(int start=0; start <=m -c; start++){
                            int flag=1;
                            for(int ci=0; ci<c; ci++){
                                // Previous row cell
                                int prev_cell = prev_cells[start + ci < c-1 ? start + ci : c-2];
                                // Current row cell
                                int curr_cell = curr_row[start + ci];
                                // Compare with template
                                if(template_bottom[ci] != 'X'){
                                    if(template_bottom[ci] == 'W' && curr_cell !=1){
                                        flag=0;
                                        break;
                                    }
                                    if(template_bottom[ci] == 'B' && curr_cell !=2){
                                        flag=0;
                                        break;
                                    }
                                }
                                if(template_top[ci] != 'X'){
                                    if(template_top[ci] == 'W' && prev_cells[start + ci < c-1 ? start + ci : c-2] !=1){
                                        flag=0;
                                        break;
                                    }
                                    if(template_top[ci] == 'B' && prev_cells[start + ci < c-1 ? start + ci : c-2] !=2){
                                        flag=0;
                                        break;
                                    }
                                }
                            }
                            if(flag){
                                match=1;
                                break;
                            }
                        }
                    }
                    if(!match){
                        // Update the new state
                        int new_state =0;
                        for(int i=0;i<c-1;i++) {
                            if(i < m){
                                new_state = new_state *3 + curr_row[i];
                            }
                            else{
                                new_state = new_state *3;
                            }
                        }
                        curr_dp[new_state] = (curr_dp[new_state] + prev_dp[s]) % MOD;
                    }
                }
            }
            // Swap
            for(int s=0; s<(int)(pow(3, c-1)); s++) prev_dp[s] = curr_dp[s];
        }
        // Now compute the total number of boards without the pattern
        long long valid =0;
        for(int s=0; s<(int)(pow(3, c-1)); s++) valid = (valid + prev_dp[s]) % MOD;
        // Now compute total boards
        long long total = power(3, n*m);
        // Compute answer
        long long answer = (total - valid + MOD) % MOD;
        printf("%lld\n", answer);
    }
    return 0;
}