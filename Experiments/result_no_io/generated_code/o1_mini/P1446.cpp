#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of permutations to handle
#define MAX_GROUP_SIZE 1000000

typedef struct {
    int *perm;
} Permutation;

int main(){
    int S_r, S_b, S_g, m, P;
    scanf("%d %d %d %d %d", &S_r, &S_b, &S_g, &m, &P);
    int n = S_r + S_b + S_g;
    // Read generators
    Permutation generators[m];
    for(int i=0;i<m;i++){
        generators[i].perm = (int*)malloc(n * sizeof(int));
        for(int j=0;j<n;j++){
            scanf("%d", &generators[i].perm[j]);
            generators[i].perm[j]--; // zero-based
        }
    }
    // Initialize group
    Permutation group[MAX_GROUP_SIZE];
    int group_size = 1;
    group[0].perm = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) group[0].perm[i] = i;
    // BFS
    for(int i=0;i<group_size;i++){
        if(group_size >= MAX_GROUP_SIZE) break;
        for(int j=0;j<m;j++){
            // Apply generator j to group[i]
            Permutation new_p;
            new_p.perm = (int*)malloc(n * sizeof(int));
            for(int k=0;k<n;k++) new_p.perm[k] = group[i].perm[generators[j].perm[k]];
            // Check if new_p is in group
            int exists = 0;
            for(int l=0;l<group_size;l++){
                int match = 1;
                for(int k=0;k<n;k++) if(group[l].perm[k] != new_p.perm[k]) { match =0; break;}
                if(match){
                    exists =1;
                    break;
                }
            }
            if(!exists){
                if(group_size < MAX_GROUP_SIZE){
                    group[group_size++] = new_p;
                }
                else{
                    // Exceeded max group size
                    // Free memory and exit
                    for(int x=0;x<m;x++) free(generators[x].perm);
                    for(int x=0;x<group_size;x++) free(group[x].perm);
                    return 0;
                }
            }
            else{
                free(new_p.perm);
            }
        }
    }
    // Now, group_size is |G|
    // Compute |G| mod P
    long long G_mod = 0;
    for(int i=0;i<group_size;i++) G_mod = (G_mod + 1) % P;
    // Now, compute sum Fix(g)
    long long sum_fix = 0;
    // DP arrays
    int dp_size_r = S_r +1;
    int dp_size_b = S_b +1;
    long long dp_prev[21][21];
    long long dp_curr[21][21];
    for(int i=0;i<group_size;i++){
        // Find cycles in group[i]
        int visited_cycles[n];
        memset(visited_cycles, 0, sizeof(visited_cycles));
        int cycles_size[60];
        int cycle_count =0;
        for(int a=0;a<n;a++) if(!visited_cycles[a]){
            int size=0;
            int x = a;
            while(!visited_cycles[x]){
                visited_cycles[x]=1;
                size++;
                x = group[i].perm[x];
            }
            cycles_size[cycle_count++] = size;
        }
        // Initialize DP
        memset(dp_prev, 0, sizeof(dp_prev));
        dp_prev[0][0] =1;
        // Iterate over cycles
        for(int c=0;c<cycle_count;c++){
            int sz = cycles_size[c];
            memset(dp_curr, 0, sizeof(dp_curr));
            for(int r=0;r<=S_r;r++) for(int b=0;b<=S_b;b++) {
                if(dp_prev[r][b]==0) continue;
                // Assign to red
                if(r + sz <= S_r){
                    dp_curr[r+sz][b] = (dp_curr[r+sz][b] + dp_prev[r][b]) % P;
                }
                // Assign to blue
                if(b + sz <= S_b){
                    dp_curr[r][b+sz] = (dp_curr[r][b+sz] + dp_prev[r][b]) % P;
                }
                // Assign to green
                // No need to track green since S_g = n - S_r - S_b
                // Just ensure total assigned does not exceed S_r and S_b
                dp_curr[r][b] = (dp_curr[r][b] + dp_prev[r][b]) % P;
            }
            // Copy dp_curr to dp_prev
            for(int r=0;r<=S_r;r++) for(int b=0;b<=S_b;b++) dp_prev[r][b] = dp_curr[r][b];
        }
        // The number of valid assignments is dp_prev[S_r][S_b]
        sum_fix = (sum_fix + dp_prev[S_r][S_b]) % P;
    }
    // Compute inverse of G_mod mod P
    // Fermat's little theorem since P is prime
    long long inv =1;
    long long e = P-2;
    long long base = G_mod;
    while(e >0){
        if(e &1) inv = (inv * base) % P;
        base = (base * base) % P;
        e >>=1;
    }
    // If G_mod is 0, inverse doesn't exist, answer is undefined. Assume it won't happen.
    long long answer = (sum_fix * inv) % P;
    printf("%lld\n", answer);
    // Free memory
    for(int x=0;x<m;x++) free(generators[x].perm);
    for(int x=0;x<group_size;x++) free(group[x].perm);
    return 0;
}