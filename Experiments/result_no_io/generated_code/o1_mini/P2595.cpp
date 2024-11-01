#include <stdio.h>
#include <string.h>
#define MOD 19901013
#define MAX_MASK (1 << 15)

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[16][16];
    for(int i=0;i<n;i++) scanf("%s", grid[i]);
    // Ensure n <= m for optimization
    if(n > m){
        // Transpose the grid
        char tmp[16][16];
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) tmp[j][i] = grid[i][j];
        int tmpn = m, tmpm = n;
        n = tmpn;
        m = tmpm;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) grid[i][j] = tmp[i][j];
    }
    // Precompute valid masks for each row
    int mask_valid[n];
    for(int i=0;i<n;i++){
        mask_valid[i] = 0;
        for(int j=0;j<m;j++) if(grid[i][j] == '.') mask_valid[i] |= (1 << j);
    }
    // DP[prev_mask][h_constraints][v_constraints]
    // Due to constraints, it's complex. Simplify by ensuring constraints during placement
    // Use dynamic programming with current mask and additional flags
    unsigned long long dp_prev[MAX_MASK] = {0};
    unsigned long long dp_next[MAX_MASK] = {0};
    dp_prev[0] = 1;
    for(int i=0;i<n;i++){
        memset(dp_next, 0, sizeof(dp_next));
        for(int mask=0; mask<(1<<m); mask++){
            if(dp_prev[mask] == 0) continue;
            // Try to place tiles on row i with mask
            // Use backtracking to try all possibilities
            // Define a recursive function
            // To avoid recursion, use stack simulation
            // Each state: position, current_mask, next_mask, count
            int stack_pos[1<<m], stack_curr_mask[1<<m], stack_next_mask[1<<m];
            int top = 0;
            stack_pos[top] = 0;
            stack_curr_mask[top] = mask;
            stack_next_mask[top] = 0;
            top++;
            while(top > 0){
                top--;
                int pos = stack_pos[top];
                int curr_mask = stack_curr_mask[top];
                int nxt_mask = stack_next_mask[top];
                if(pos >= m){
                    dp_next[nxt_mask] = (dp_next[nxt_mask] + dp_prev[mask]) % MOD;
                    continue;
                }
                if(curr_mask & (1 << pos)){
                    stack_pos[top] = pos + 1;
                    stack_curr_mask[top] = curr_mask;
                    stack_next_mask[top] = nxt_mask;
                    top++;
                }
                else{
                    // Try placing vertically
                    if(i < n-1 && grid[i+1][pos] == '.' && !(curr_mask & (1 << pos))){
                        // Place vertical domino
                        stack_pos[top] = pos + 1;
                        stack_curr_mask[top] = curr_mask | (1 << pos);
                        stack_next_mask[top] = nxt_mask;
                        top++;
                    }
                    // Try placing horizontally
                    if(pos < m-1 && grid[i][pos+1] == '.' && !(curr_mask & (1 << (pos+1)))){
                        stack_pos[top] = pos + 2;
                        stack_curr_mask[top] = curr_mask | (1 << pos) | (1 << (pos+1));
                        stack_next_mask[top] = nxt_mask;
                        top++;
                    }
                    // Leave it empty
                    stack_pos[top] = pos + 1;
                    stack_curr_mask[top] = curr_mask;
                    stack_next_mask[top] = nxt_mask;
                    top++;
                }
            }
        }
        // Swap
        for(int mask=0; mask<(1<<m); mask++) dp_prev[mask] = dp_next[mask];
    }
    unsigned long long result = 0;
    for(int mask=0; mask<(1<<m); mask++) result = (result + dp_prev[mask]) % MOD;
    printf("%llu\n", result);
}