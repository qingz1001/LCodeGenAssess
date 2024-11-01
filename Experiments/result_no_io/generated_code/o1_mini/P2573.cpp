#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000000000000LL

typedef struct {
    int id;
    int h;
} Node;

typedef struct {
    int to;
    int k;
} Edge;

// Comparator for sorting nodes in decreasing order of h, then increasing id
int cmp_nodes(const void *a, const void *b) {
    Node *na = (Node*)a;
    Node *nb = (Node*)b;
    if (na->h != nb->h)
        return nb->h - na->h;
    return na->id - nb->id;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *h = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &h[i]);
    
    // Initialize adjacency list
    int *head = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) head[i] = -1;
    Edge *edges = (Edge*)malloc(MAXM * sizeof(Edge));
    int *next_edge = (int*)malloc(MAXM * sizeof(int));
    int e = 0;
    
    for(int i=0;i<m;i++){
        int u, v, k;
        scanf("%d %d %d", &u, &v, &k);
        if(h[u] >= h[v]){
            edges[e].to = v;
            edges[e].k = k;
            next_edge[e] = head[u];
            head[u] = e++;
        }
        if(h[v] >= h[u] && u != v){
            edges[e].to = u;
            edges[e].k = k;
            next_edge[e] = head[v];
            head[v] = e++;
        }
    }
    
    // Create and sort nodes
    Node *nodes = (Node*)malloc(n * sizeof(Node));
    for(int i=0;i<n;i++) { nodes[i].id = i+1; nodes[i].h = h[i+1]; }
    qsort(nodes, n, sizeof(Node), cmp_nodes);
    
    // Initialize DP arrays
    int *dp_count = (int*)malloc((n+1) * sizeof(int));
    long long *dp_dist = (long long*)malloc((n+1) * sizeof(long long));
    for(int i=1;i<=n;i++) { dp_count[i] = 0; dp_dist[i] = INF; }
    dp_count[1] = 1;
    dp_dist[1] = 0;
    
    // Process nodes in sorted order
    for(int i=0;i<n;i++){
        int u = nodes[i].id;
        if(dp_count[u] == 0) continue;
        for(int j = head[u]; j != -1; j = next_edge[j]){
            int v = edges[j].to;
            long long new_dist = dp_dist[u] + edges[j].k;
            if(dp_count[u] +1 > dp_count[v]){
                dp_count[v] = dp_count[u] +1;
                dp_dist[v] = new_dist;
            }
            else if(dp_count[u] +1 == dp_count[v]){
                if(new_dist < dp_dist[v]){
                    dp_dist[v] = new_dist;
                }
            }
        }
    }
    
    // Find the answer
    int max_count = 0;
    long long min_dist = INF;
    for(int i=1;i<=n;i++){
        if(dp_count[i] > max_count){
            max_count = dp_count[i];
            min_dist = dp_dist[i];
        }
        else if(dp_count[i] == max_count && dp_count[i] !=0){
            if(dp_dist[i] < min_dist){
                min_dist = dp_dist[i];
            }
        }
    }
    
    printf("%d %lld\n", max_count, min_dist);
    
    // Free memory
    free(h);
    free(head);
    free(edges);
    free(next_edge);
    free(nodes);
    free(dp_count);
    free(dp_dist);
    
    return 0;
}