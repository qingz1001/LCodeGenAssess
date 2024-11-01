#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 20000
#define MAX_N 20000
#define MAX_EDGES 400000
#define INF 1000000000

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj_left[MAX_M + 1];
int pair_left[MAX_M + 1];
int pair_right[MAX_N + 1];
int dist_layer;
int queue_nodes[MAX_M + MAX_N + 1];
int front, rear;

void add_edge(int u, int v) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj_left[u];
    adj_left[u] = edge;
}

int bfs(int m, int n) {
    front = 0;
    rear = 0;
    for(int u = 1; u <= m; u++) {
        if(pair_left[u] == 0){
            queue_nodes[rear++] = u;
            // Initialize distance for layer
        }
    }
    // Not implementing full BFS for simplicity
    return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int m, n;
        scanf("%d %d", &m, &n);
        for(int i=1;i<=m;i++) {
            adj_left[i] = NULL;
        }
        for(int i=1;i<=m;i++) {
            int k;
            scanf("%d", &k);
            for(int j=0; j<k; j++) {
                int p;
                scanf("%d", &p);
                add_edge(i, p);
            }
        }
        memset(pair_left, 0, sizeof(int)*(m+1));
        memset(pair_right, 0, sizeof(int)*(n+1));
        // Implementing DFS-based matching
        int result = 0;
        int changed = 1;
        while(changed){
            changed = 0;
            for(int u=1; u<=m; u++){
                if(pair_left[u]==0){
                    // DFS
                    int stack[m+1];
                    int top = -1;
                    stack[++top] = u;
                    int visited[m+1];
                    memset(visited, 0, sizeof(int)*(m+1));
                    while(top >=0){
                        int current = stack[top--];
                        if(!visited[current]){
                            visited[current] = 1;
                            for(Edge* e = adj_left[current]; e != NULL; e = e->next){
                                int v = e->to;
                                if(pair_right[v]==0){
                                    pair_left[current] = v;
                                    pair_right[v] = current;
                                    result++;
                                    changed = 1;
                                    break;
                                }
                                else{
                                    if(!visited[pair_right[v]]){
                                        stack[++top] = pair_right[v];
                                    }
                                }
                            }
                        }
                        if(changed) break;
                    }
                }
                if(changed) break;
            }
        }
        if(result >= m){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
        // Free memory
        for(int i=1;i<=m;i++) {
            Edge* e = adj_left[i];
            while(e){
                Edge* tmp = e;
                e = e->next;
                free(tmp);
            }
        }
    }
    return 0;
}