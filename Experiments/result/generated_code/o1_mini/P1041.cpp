#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 301

typedef struct Node {
    int children[MAX];
    int child_count;
} Node;

int n, p;
Node tree[MAX];
int subtree_size[MAX];
int parent[MAX];
int visited[MAX];
int queue[MAX];
int head, tail;

// Function to add a child to a node
void add_edge(int u, int v) {
    tree[u].children[tree[u].child_count++] = v;
}

// DFS to compute parent and subtree sizes
int dfs(int u) {
    subtree_size[u] = 1;
    for(int i=0;i<tree[u].child_count;i++) {
        int v = tree[u].children[i];
        parent[v] = u;
        subtree_size[u] += dfs(v);
    }
    return subtree_size[u];
}

int main(){
    scanf("%d %d", &n, &p);
    for(int i=0;i<p;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    // Build the tree with root 1
    memset(parent, -1, sizeof(parent));
    // Convert to tree rooted at 1
    // Remove back edges
    // Using DFS
    head = 0; tail = 0;
    queue[tail++] = 1;
    while(head < tail){
        int u = queue[head++];
        for(int i=0;i<tree[u].child_count;i++){
            int v = tree[u].children[i];
            if(parent[u] == v) continue;
            parent[v] = u;
            // Rebuild children
            tree[u].children[i] = v;
            queue[tail++] = v;
        }
    }

    // Recompute children based on parent array
    for(int i=1;i<=n;i++) {
        tree[i].child_count = 0;
    }
    for(int i=1;i<=n;i++) {
        if(parent[i]!=-1 && i!=1){
            add_edge(parent[i], i);
        }
    }

    dfs(1);

    // Simulation
    memset(visited, 0, sizeof(visited));
    visited[1] = 1;
    head = 0; tail = 0;
    queue[tail++] = 1;
    int total = 1;

    while(head < tail){
        int current_cycle_nodes = tail - head;
        // Collect all possible edges to cut
        int max_size = -1;
        int cut_parent = -1, cut_child = -1;
        for(int i=0;i<current_cycle_nodes;i++){
            int u = queue[head + i];
            for(int j=0; j < tree[u].child_count; j++){
                int v = tree[u].children[j];
                if(!visited[v]){
                    if(subtree_size[v] > max_size){
                        max_size = subtree_size[v];
                        cut_parent = u;
                        cut_child = v;
                    }
                }
            }
        }
        // If there's an edge to cut
        if(cut_child != -1){
            // Remove the edge
            int new_count = 0;
            for(int j=0; j < tree[cut_parent].child_count; j++){
                if(tree[cut_parent].children[j] != cut_child){
                    tree[cut_parent].children[new_count++] = tree[cut_parent].children[j];
                }
            }
            tree[cut_parent].child_count = new_count;
        }

        // Now, infect the children not cut
        for(int i=0;i<current_cycle_nodes;i++){
            int u = queue[head + i];
            for(int j=0; j < tree[u].child_count; j++){
                int v = tree[u].children[j];
                if(!visited[v]){
                    visited[v] = 1;
                    total++;
                    queue[tail++] = v;
                }
            }
        }
        head += current_cycle_nodes;
    }

    printf("%d\n", total);
    return 0;
}