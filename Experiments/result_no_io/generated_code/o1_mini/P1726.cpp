#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5001
#define MAXM 50000
#define MAX_NEIGHBORS 100

typedef struct {
    int nodes[MAXN];
    int size;
} Component;

int N, M;
int adj_main[MAXN][MAX_NEIGHBORS];
int adj_main_size[MAXN];
int adj_reverse[MAXN][MAX_NEIGHBORS];
int adj_reverse_size[MAXN];
int visited[MAXN];
int order[MAXN];
int order_idx = 0;
Component components[MAXN];
int component_count = 0;

// Stack-based DFS to prevent stack overflow
void dfs1(int u) {
    int stack[MAXN];
    int top = -1;
    stack[++top] = u;
    while (top >= 0) {
        int v = stack[top];
        if (!visited[v]) {
            visited[v] = 1;
            for(int i = 0; i < adj_main_size[v]; i++) {
                int to = adj_main[v][i];
                if(!visited[to]) {
                    stack[++top] = to;
                }
            }
        } else {
            order[order_idx++] = v;
            top--;
        }
    }
}

void dfs2(int u, Component *comp) {
    int stack[MAXN];
    int top = -1;
    stack[++top] = u;
    visited[u] = 1;
    while (top >= 0) {
        int v = stack[top--];
        comp->nodes[comp->size++] = v;
        for(int i = 0; i < adj_reverse_size[v]; i++) {
            int to = adj_reverse[v][i];
            if(!visited[to]) {
                visited[to] = 1;
                stack[++top] = to;
            }
        }
    }
}

int cmp_int(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int compare_components(const Component *a, const Component *b) {
    for(int i = 0; i < a->size && i < b->size; i++) {
        if(a->nodes[i] < b->nodes[i]) return -1;
        if(a->nodes[i] > b->nodes[i]) return 1;
    }
    if(a->size < b->size) return -1;
    if(a->size > b->size) return 1;
    return 0;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        if(t == 1){
            adj_main[a][adj_main_size[a]++] = b;
            adj_reverse[b][adj_reverse_size[b]++] = a;
        }
        else{
            adj_main[a][adj_main_size[a]++] = b;
            adj_main[b][adj_main_size[b]++] = a;
            adj_reverse[a][adj_reverse_size[a]++] = b;
            adj_reverse[b][adj_reverse_size[b]++] = a;
        }
    }
    for(int u = 1; u <= N; u++) {
        if(!visited[u]){
            dfs1(u);
        }
    }
    memset(visited, 0, sizeof(visited));
    for(int i = order_idx-1; i >=0; i--){
        int u = order[i];
        if(!visited[u]){
            components[component_count].size = 0;
            dfs2(u, &components[component_count]);
            qsort(components[component_count].nodes, components[component_count].size, sizeof(int), cmp_int);
            component_count++;
        }
    }
    // Find the largest component(s)
    int max_size = 0;
    for(int i = 0; i < component_count; i++) {
        if(components[i].size > max_size){
            max_size = components[i].size;
        }
    }
    // Collect all components with max_size
    Component best;
    best.size = 0;
    for(int i = 0; i < component_count; i++) {
        if(components[i].size == max_size){
            if(best.size == 0){
                for(int j = 0; j < components[i].size; j++) best.nodes[j] = components[i].nodes[j];
                best.size = components[i].size;
            }
            else{
                // Compare lex order
                int cmp = compare_components(&components[i], &best);
                if(cmp < 0){
                    for(int j = 0; j < components[i].size; j++) best.nodes[j] = components[i].nodes[j];
                    best.size = components[i].size;
                }
            }
        }
    }
    printf("%d\n", best.size);
    for(int i = 0; i < best.size; i++) {
        printf("%d%c", best.nodes[i], (i == best.size-1) ? '\n' : ' ');
    }
    return 0;
}