#include <stdio.h>
#include <string.h>

int n, m;
int enemy[101][101];
int enemy_count[101];
char current_set_arr[101];
char best_set_arr[101];
int best_size = 0;

// Recursive backtracking function
void backtrack(int pos, int current_size) {
    if (pos == 0) {
        if (current_size > best_size) {
            best_size = current_size;
            for(int i=1;i<=n;i++) best_set_arr[i] = current_set_arr[i];
        }
        else if (current_size == best_size) {
            int better = 0;
            for(int i=n;i>=1;i--){
                if(current_set_arr[i] > best_set_arr[i]){
                    better = 1;
                    break;
                }
                else if(current_set_arr[i] < best_set_arr[i]){
                    break;
                }
            }
            if(better){
                for(int i=1;i<=n;i++) best_set_arr[i] = current_set_arr[i];
            }
        }
        return;
    }
    if(current_size + pos < best_size)
        return;
    int u = pos;
    int conflict = 0;
    for(int k=0; k<enemy_count[u]; k++) {
        int v = enemy[u][k];
        if(current_set_arr[v]){
            conflict = 1;
            break;
        }
    }
    if(!conflict){
        current_set_arr[u] = 1;
        backtrack(pos-1, current_size+1);
        current_set_arr[u] = 0;
    }
    backtrack(pos-1, current_size);
}

int main(){
    // Read n and m
    scanf("%d %d", &n, &m);
    // Initialize enemy counts
    for(int i=1;i<=n;i++) enemy_count[i]=0;
    // Read enemy pairs
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        enemy[u][enemy_count[u]++] = v;
        enemy[v][enemy_count[v]++] = u;
    }
    // Initialize sets
    memset(current_set_arr, 0, sizeof(current_set_arr));
    memset(best_set_arr, 0, sizeof(best_set_arr));
    // Start backtracking from n
    backtrack(n, 0);
    // Output
    printf("%d\n", best_size);
    for(int i=1;i<=n;i++){
        printf("%d", best_set_arr[i]);
        if(i != n) printf(" ");
    }
    printf("\n");
    return 0;
}