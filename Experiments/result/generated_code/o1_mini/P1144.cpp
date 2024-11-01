#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001
#define MAXM 4000001
#define MOD 100003

int N, M;
unsigned int xs[2000001];
unsigned int ys[2000001];
unsigned int degrees[MAXN];
unsigned int offset_arr[MAXN + 1];
unsigned int edges_arr[MAXM];
int distance_arr_val[MAXN];
unsigned short paths_arr_val[MAXN];
unsigned int queue_arr_val[MAXN];
int head, tail;

int main(){
    // Read N and M
    scanf("%d %d", &N, &M);
    
    // Read all edges and count degrees
    for(int i = 0; i < M; i++){
        unsigned int x, y;
        scanf("%u %u", &x, &y);
        xs[i] = x;
        ys[i] = y;
        degrees[x]++;
        degrees[y]++;
    }
    
    // Compute offsets
    offset_arr[1] = 0;
    for(int i = 1; i <= N; i++){
        offset_arr[i+1] = offset_arr[i] + degrees[i];
    }
    
    // Reset degrees to use as current index
    memset(degrees, 0, sizeof(unsigned int) * (N + 1));
    
    // Fill adjacency list
    for(int i = 0; i < M; i++){
        unsigned int x = xs[i];
        unsigned int y = ys[i];
        edges_arr[offset_arr[x] + degrees[x]] = y;
        degrees[x]++;
        if(x != y){
            edges_arr[offset_arr[y] + degrees[y]] = x;
            degrees[y]++;
        }
    }
    
    // Initialize distance and paths
    for(int i = 1; i <= N; i++){
        distance_arr_val[i] = -1;
        paths_arr_val[i] = 0;
    }
    distance_arr_val[1] = 0;
    paths_arr_val[1] = 1;
    
    // Initialize BFS queue
    head = 0;
    tail = 1;
    queue_arr_val[0] = 1;
    
    // BFS
    while(head < tail){
        unsigned int u = queue_arr_val[head++];
        unsigned int start = offset_arr[u];
        unsigned int end = offset_arr[u+1];
        for(unsigned int i = start; i < end; i++){
            unsigned int v = edges_arr[i];
            if(distance_arr_val[v] == -1){
                distance_arr_val[v] = distance_arr_val[u] + 1;
                paths_arr_val[v] = paths_arr_val[u];
                queue_arr_val[tail++] = v;
            }
            else if(distance_arr_val[v] == distance_arr_val[u] + 1){
                paths_arr_val[v] += paths_arr_val[u];
                if(paths_arr_val[v] >= MOD){
                    paths_arr_val[v] -= MOD;
                }
            }
        }
    }
    
    // Print results
    for(int i = 1; i <= N; i++){
        printf("%hu\n", paths_arr_val[i]);
    }
    
    return 0;
}