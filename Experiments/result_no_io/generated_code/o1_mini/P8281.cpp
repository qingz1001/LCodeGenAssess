#include <stdio.h>
#include <stdlib.h>

#define MAXN 51

int n, m;
int adj[MAXN][MAXN];
int adj_size[MAXN];
int path_arr[MAXN];
int visited_arr[MAXN];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void print_path(int depth) {
    for(int i = 0; i < depth; i++) {
        if(i > 0) printf(" ");
        printf("%d", path_arr[i]);
    }
    printf("\n");
}

void backtrack(int current, int depth) {
    if(depth == n) {
        for(int i = 0; i < adj_size[current]; i++) {
            if(adj[current][i] == 1) {
                print_path(depth);
                break;
            }
        }
        return;
    }
    for(int i = 0; i < adj_size[current]; i++) {
        int next = adj[current][i];
        if(!visited_arr[next]) {
            visited_arr[next] = 1;
            path_arr[depth] = next;
            backtrack(next, depth + 1);
            visited_arr[next] = 0;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][adj_size[u]++] = v;
    }
    for(int u = 1; u <= n; u++) {
        qsort(adj[u], adj_size[u], sizeof(int), cmp);
    }
    path_arr[0] = 1;
    visited_arr[1] = 1;
    backtrack(1, 1);
    return 0;
}