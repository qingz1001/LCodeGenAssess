#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_K 1000
#define MAX_N 55

int is_square[MAX_K * 2 + 2];
int adj[MAX_K +1][MAX_K +1];
int match_to[MAX_K +1];
int used[MAX_K +1];
int n_pillars;

// Precompute perfect squares
void precompute_squares(int max_sum) {
    memset(is_square, 0, sizeof(is_square));
    for(int i=1; i*i <= max_sum; i++) {
        is_square[i*i] = 1;
    }
}

// Maximum Bipartite Matching using DFS
int bpm(int u, int k, int left_size, int right_size) {
    for(int v=1; v<=right_size; v++) {
        if(adj[u][v] && !used[v]) {
            used[v] = 1;
            if(match_to[v] == 0 || bpm(match_to[v], k, left_size, right_size)) {
                match_to[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int max_matching(int k) {
    memset(match_to, 0, sizeof(match_to));
    int result = 0;
    for(int u=1; u<=k; u++) {
        memset(used, 0, sizeof(used));
        if(bpm(u, k, k, k)) result++;
    }
    return result;
}

// Reconstruct paths
void reconstruct_paths(int k, int match, int paths[][MAX_K +1], int *path_count) {
    // Build reverse mapping
    int rev_match[MAX_K +1];
    memset(rev_match, 0, sizeof(rev_match));
    for(int v=1; v<=k; v++) {
        if(match_to[v]) {
            rev_match[match_to[v]] = v;
        }
    }
    // Find starts
    int starts[MAX_K +1];
    int s =0;
    for(int u=1; u<=k; u++) {
        int found = 0;
        for(int v=1; v<=k; v++) {
            if(adj[u][v] && match_to[v] == u) {
                found =1;
                break;
            }
        }
        if(rev_match[u]==0) {
            starts[s++] = u;
        }
    }
    // Build paths
    *path_count =0;
    for(int i=0; i<s; i++) {
        int current = starts[i];
        while(current !=0) {
            paths[*path_count][current] =1;
            int next = rev_match[current];
            if(next ==0) break;
            current = next;
        }
        (*path_count)++;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    // Precompute squares up to 2*MAX_K
    precompute_squares(2*MAX_K);
    // Binary search to find maximum k
    int low=1, high=MAX_K, best=1;
    while(low <= high){
        int mid = (low + high)/2;
        // Build adjacency
        for(int i=1;i<=mid;i++) {
            for(int j=1;j<=mid;j++) {
                adj[i][j] = (i < j && is_square[i + j]);
            }
        }
        int matching = max_matching(mid);
        int path_cover = mid - matching;
        if(path_cover <= n){
            best = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    // Now find the path cover for best
    int k = best;
    // Rebuild adjacency
    for(int i=1;i<=k;i++) {
        for(int j=1;j<=k;j++) {
            adj[i][j] = (i < j && is_square[i + j]);
        }
    }
    max_matching(k);
    // Reconstruct paths
    int paths[MAX_N][MAX_K +1];
    memset(paths, 0, sizeof(paths));
    int path_count =0;
    reconstruct_paths(k, 0, paths, &path_count);
    // Assign paths to pillars
    int pillars[MAX_N][MAX_K +1];
    int pillar_sizes[MAX_N];
    memset(pillar_sizes, 0, sizeof(pillar_sizes));
    for(int i=0;i<path_count;i++) {
        for(int j=1;j<=k;j++) {
            if(paths[i][j]) {
                pillars[i][pillar_sizes[i]++] = j;
            }
        }
    }
    // If there are more pillars than paths, they remain empty
    // Output
    printf("%d\n", k);
    for(int i=0;i<n;i++) {
        if(i < path_count){
            for(int j=0;j<pillar_sizes[i];j++){
                if(j>0) printf(" ");
                printf("%d", pillars[i][j]);
            }
            printf("\n");
        }
        else{
            printf("\n");
        }
    }
    return 0;
}