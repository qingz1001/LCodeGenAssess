#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 200
#define MAX_LINES 80000
#define MAX_EDGES_PER_LINE 20
#define MAX_TOTAL_LINES (MAX_N * MAX_M * 2)
#define INF 1000000000

typedef struct {
    int start;
    int end;
} Line;

int N, M;
char buffer[205];
Line front_lines[MAX_TOTAL_LINES];
int front_count = 0;
Line back_lines[MAX_TOTAL_LINES];
int back_count = 0;

// Graph for Hopcroft-Karp
int graph_adj[MAX_TOTAL_LINES];
int graph_ptr[MAX_TOTAL_LINES];
int graph_edges[MAX_TOTAL_LINES * MAX_EDGES_PER_LINE];
int pair_U[MAX_TOTAL_LINES];
int pair_V[MAX_TOTAL_LINES];
int dist_distance[MAX_TOTAL_LINES];
int head[MAX_TOTAL_LINES];
int tail[MAX_TOTAL_LINES];

int main(){
    scanf("%d %d", &N, &M);
    // Read front grid
    for(int i=0;i<N;i++){
        scanf("%s", buffer);
        for(int j=0;j<M;j++){
            char c = buffer[j];
            if(c == '/' || c == '\\' || c == 'X'){
                if(c == '/' || c == 'X'){
                    Line l;
                    l.start = i*(M+1) + (j+1);
                    l.end = (i+1)* (M+1) + j;
                    front_lines[front_count++] = l;
                }
                if(c == '\\' || c == 'X'){
                    Line l;
                    l.start = i*(M+1) + j;
                    l.end = (i+1)*(M+1) + (j+1);
                    front_lines[front_count++] = l;
                }
            }
        }
    }
    // Read back grid
    for(int i=0;i<N;i++){
        scanf("%s", buffer);
        for(int j=0;j<M;j++){
            char c = buffer[j];
            if(c == '/' || c == '\\' || c == 'X'){
                if(c == '/' || c == 'X'){
                    Line l;
                    l.start = i*(M+1) + (j+1);
                    l.end = (i+1)*(M+1) + j;
                    back_lines[back_count++] = l;
                }
                if(c == '\\' || c == 'X'){
                    Line l;
                    l.start = i*(M+1) + j;
                    l.end = (i+1)*(M+1) + (j+1);
                    back_lines[back_count++] = l;
                }
            }
        }
    }
    // Build adjacency
    memset(graph_adj, 0, sizeof(graph_adj));
    memset(graph_ptr, 0, sizeof(graph_ptr));
    for(int i=0;i<front_count;i++){
        for(int j=0;j<back_count;j++){
            if(front_lines[i].end == back_lines[j].start){
                graph_edges[graph_adj[i] * MAX_EDGES_PER_LINE + graph_ptr[i]] = j;
                graph_ptr[i]++;
            }
        }
    }
    // Initialize pairs
    for(int i=0;i<front_count;i++) pair_U[i] = -1;
    for(int i=0;i<back_count;i++) pair_V[i] = -1;
    // BFS and DFS for Hopcroft-Karp
    int queue[MAX_TOTAL_LINES];
    while(1){
        int front_q = 0, back_q = 0;
        // Level graph
        for(int i=0;i<front_count;i++) {
            if(pair_U[i]==-1){
                dist_distance[i] = 0;
                queue[back_q++] = i;
            }
            else{
                dist_distance[i] = INF;
            }
        }
        int dist = INF;
        for(int i=0;i<back_q;i++){
            int u = queue[i];
            if(dist_distance[u] < dist){
                for(int j=0; j<graph_ptr[u]; j++){
                    int v = graph_edges[u * MAX_EDGES_PER_LINE + j];
                    if(pair_V[v]==-1){
                        dist = dist_distance[u] + 1;
                    }
                    else if(dist_distance[pair_V[v]] == INF){
                        dist_distance[pair_V[v]] = dist_distance[u] + 1;
                        queue[back_q++] = pair_V[v];
                    }
                }
            }
        }
        if(dist == INF) break;
        // DFS
        for(int i=0;i<back_q;i++){
            int u = queue[i];
            if(dist_distance[u] < dist){
                // Implement DFS inline
                int stack[MAX_TOTAL_LINES];
                int top = 0;
                stack[top++] = u;
                while(top > 0){
                    int current = stack[--top];
                    for(int j=0; j<graph_ptr[current]; j++){
                        int v = graph_edges[current * MAX_EDGES_PER_LINE + j];
                        if(pair_V[v]==-1){
                            // Augment path
                            pair_U[current] = v;
                            pair_V[v] = current;
                            dist = dist_distance[current] + 1;
                        }
                        else if(dist_distance[pair_V[v]] == dist_distance[current] + 1){
                            stack[top++] = pair_V[v];
                        }
                    }
                }
            }
        }
    }
    // Count matching
    int matching = 0;
    for(int i=0;i<front_count;i++) if(pair_U[i]!=-1) matching++;
    printf("%d\n", front_count + back_count - matching);
    return 0;
}