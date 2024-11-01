#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    struct Node* children[300];
    int child_count;
} Node;

typedef struct Edge {
    int node;
    int size;
} Edge;

int n, p;
Node nodes[301];
int subtree[301];
int parent_node[301];
Edge available_edges[300];
int available_count = 0;

// Comparator for descending order
int cmp(const void* a, const void* b){
    Edge ea = *(Edge*)a;
    Edge eb = *(Edge*)b;
    if(ea.size != eb.size) return eb.size - ea.size;
    return ea.node - eb.node;
}

void build_tree(){
    for(int i=1;i<=n;i++){
        nodes[i].id = i;
        nodes[i].child_count = 0;
    }
    // BFS to assign parents
    int queue[301];
    int front=0, rear=0;
    queue[rear++] = 1;
    parent_node[1] = 0;
    while(front < rear){
        int u = queue[front++];
        for(int i=0;i<nodes[u].child_count;i++){
            // Already added
        }
    }
}

int dfs(int u){
    subtree[u] = 1;
    for(int i=0;i<nodes[u].child_count;i++){
        int v = nodes[u].children[i]->id;
        subtree[u] += dfs(v);
    }
    return subtree[u];
}

int main(){
    scanf("%d %d", &n, &p);
    // Initialize adjacency list
    for(int i=1;i<=n;i++){
        nodes[i].id = i;
        nodes[i].child_count = 0;
    }
    // Read edges
    int a, b;
    int adj[301][301];
    int degree[301];
    memset(degree, 0, sizeof(degree));
    for(int i=0;i<p;i++){
        scanf("%d %d", &a, &b);
        adj[a][degree[a]++] = b;
        adj[b][degree[b]++] = a;
    }
    // BFS to set parent and build tree
    int queue[301];
    int front=0, rear=0;
    queue[rear++] = 1;
    parent_node[1] = 0;
    while(front < rear){
        int u = queue[front++];
        for(int i=0;i<degree[u];i++){
            int v = adj[u][i];
            if(v != parent_node[u]){
                parent_node[v] = u;
                nodes[u].children[nodes[u].child_count++] = &nodes[v];
                queue[rear++] = v;
            }
        }
    }
    // DFS to compute subtree sizes
    dfs(1);
    // Initialize available edges with children of root
    for(int i=0;i<nodes[1].child_count;i++){
        available_edges[available_count].node = nodes[1].children[i]->id;
        available_edges[available_count].size = subtree[nodes[1].children[i]->id];
        available_count++;
    }
    // Sort available edges descending
    qsort(available_edges, available_count, sizeof(Edge), cmp);
    int total_infected =1;
    while(available_count >0){
        // Cut the first edge
        Edge cut = available_edges[0];
        // Shift the remaining edges
        int new_count = available_count -1;
        Edge infected_edges[300];
        int infected_count =0;
        for(int i=1;i<available_count;i++){
            infected_edges[infected_count++] = available_edges[i];
        }
        // Add their sizes to total_infected
        for(int i=0;i<infected_count;i++){
            total_infected += infected_edges[i].size;
        }
        // Collect new available edges from infected subtrees
        Edge new_available[300];
        int new_available_count =0;
        for(int i=0;i<infected_count;i++){
            int node = infected_edges[i].node;
            for(int j=0;j<nodes[node].child_count;j++){
                new_available[new_available_count].node = nodes[node].children[j]->id;
                new_available[new_available_count].size = subtree[nodes[node].children[j]->id];
                new_available_count++;
            }
        }
        // Sort new_available descending
        qsort(new_available, new_available_count, sizeof(Edge), cmp);
        // Replace available_edges with new_available
        memcpy(available_edges, new_available, new_available_count * sizeof(Edge));
        available_count = new_available_count;
    }
    printf("%d\n", total_infected);
    return 0;
}