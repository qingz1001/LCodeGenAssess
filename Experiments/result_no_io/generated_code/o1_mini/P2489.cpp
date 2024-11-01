#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Maximum limits
#define MAX_M 30
#define MAX_N 30
#define MAX_K 5
#define MAX_H 5
#define MAX_POW3 243
#define MAX_POW2 32

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Global variables
int m, n, k, H;
char grid[MAX_M][MAX_N + 1];
long long p_array[MAX_POW2];
double p_normalized[MAX_POW2];
long long S = 0;
int trap_map[MAX_POW2]; // Map trap character to index
int pow3_table[6]; // pow3_table[i] = 3^i
int trap_indices[MAX_POW2]; // 'A'-'E' to 0-4

// Memoization table
double memo_table[30][30][6][243];
int computed[30][30][6][243];

// Function to set trap status in knowledge
int set_trap(int knowledge, int t, int status) {
    // status: 1 for safe, 2 for harmful
    // Each trap has a trit (0,1,2)
    // knowledge is in base 3
    int new_knowledge = knowledge;
    new_knowledge += (status - ((knowledge / pow3_table[t]) % 3)) * pow3_table[t];
    return new_knowledge;
}

// Function to get trap status in knowledge
int get_trap_status(int knowledge, int t) {
    return (knowledge / pow3_table[t]) % 3;
}

// DFS with memoization
double dfs(int x, int y, int h, int knowledge) {
    if (x < 0 || x >= m || y < 0 || y >= n)
        return 0.0;
    if (grid[x][y] == '@')
        return 1.0;
    if (h <= 0)
        return 0.0;
    if (computed[x][y][h][knowledge])
        return memo_table[x][y][h][knowledge];
    computed[x][y][h][knowledge] = 1;
    double best = 0.0;

    for(int dir=0; dir<4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx <0 || nx >=m || ny <0 || ny >=n)
            continue;
        char cell = grid[nx][ny];
        if(cell == '#')
            continue;
        if(cell == '.' || cell == '$' || cell == '@') {
            double val = dfs(nx, ny, h, knowledge);
            if(val > best)
                best = val;
        }
        else {
            // It's a trap
            int t = cell - 'A';
            if(t <0 || t >=k){
                // Invalid trap, treat as wall
                continue;
            }
            int status = get_trap_status(knowledge, t);
            if(status ==1) {
                // Known safe
                double val = dfs(nx, ny, h, knowledge);
                if(val > best)
                    best = val;
            }
            else if(status ==2) {
                // Known harmful
                if(h >1){
                    double val = dfs(nx, ny, h-1, knowledge);
                    if(val > best)
                        best = val;
                }
                else{
                    // Dies
                    double val = 0.0;
                    if(val > best)
                        best = val;
                }
            }
            else {
                // Unknown
                double P_safe =0.0, P_harm=0.0;
                for(int i=0; i<(1<<k); i++) {
                    // Check consistency with knowledge
                    int consistent =1;
                    for(int tt=0; tt<k; tt++) {
                        int ks = get_trap_status(knowledge, tt);
                        if(ks ==1 && ((i & (1<<tt)) !=0))
                        { consistent =0; break;}
                        if(ks ==2 && ((i & (1<<tt)) ==0))
                        { consistent =0; break;}
                    }
                    if(!consistent)
                        continue;
                    if((i & (1<<t)) )
                        P_harm += p_normalized[i];
                    else
                        P_safe += p_normalized[i];
                }
                double total = P_safe + P_harm;
                if(total ==0.0){
                    continue;
                }
                P_safe /= total;
                P_harm /= total;
                // If trap is safe
                int new_knowledge_safe = set_trap(knowledge, t, 1);
                double prob_safe = dfs(nx, ny, h, new_knowledge_safe);
                // If trap is harmful
                double prob_harm =0.0;
                if(h >1){
                    int new_knowledge_harm = set_trap(knowledge, t, 2);
                    prob_harm = dfs(nx, ny, h-1, new_knowledge_harm);
                }
                double val = P_safe * prob_safe + P_harm * prob_harm;
                if(val > best)
                    best = val;
            }
        }
    }
    memo_table[x][y][h][knowledge] = best;
    return best;
}

int main(){
    // Initialize pow3_table
    pow3_table[0] =1;
    for(int i=1;i<=5;i++)
        pow3_table[i] = pow3_table[i-1]*3;

    // Read input
    scanf("%d %d %d %d", &m, &n, &k, &H);
    int start_x, start_y;
    for(int i=0;i<m;i++){
        scanf("%s", grid[i]);
        for(int j=0;j<n;j++){
            if(grid[i][j] == '$'){
                start_x = i;
                start_y = j;
            }
        }
    }
    int size_p = 1<<k;
    for(int i=0;i<size_p;i++){
        scanf("%lld", &p_array[i]);
        S += p_array[i];
    }
    for(int i=0;i<size_p;i++){
        p_normalized[i] = (double)p_array[i] / (double)S;
    }
    // Initialize memo_table and computed
    memset(computed, 0, sizeof(computed));
    // Compute the answer
    double answer = dfs(start_x, start_y, H, 0);
    // Print with 3 decimal places
    printf("%.3lf\n", answer);
    return 0;
}