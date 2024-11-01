#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 26

bool add_edge(int adj[][MAX], int from, int to) {
    if (!adj[from][to]) {
        adj[from][to] = 1;
        return true;
    }
    return false;
}

bool topo_sort(int n, int adj[][MAX], char *order) {
    int in_degree[MAX];
    memset(in_degree, 0, sizeof(in_degree));
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(adj[i][j]) {
                in_degree[j]++;
            }
        }
    }

    char result[MAX+1];
    result[MAX] = '\0';
    int idx = 0;
    bool unique = true;

    bool selected[MAX];
    memset(selected, 0, sizeof(selected));

    for(int i=0;i<n;i++) {
        int cnt = 0;
        int current = -1;
        for(int j=0;j<n;j++) {
            if(!selected[j] && in_degree[j]==0) {
                cnt++;
                current = j;
            }
        }
        if(cnt == 0) {
            return false; // cycle
        }
        if(cnt > 1) {
            unique = false;
        }
        selected[current] = true;
        result[idx++] = 'A' + current;
        for(int j=0;j<n;j++) {
            if(adj[current][j]) {
                in_degree[j]--;
            }
        }
    }

    if(unique) {
        strcpy(order, result);
        return true;
    }
    return false;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int adj[MAX][MAX];
    memset(adj, 0, sizeof(adj));
    char relation[4];
    char order[MAX+1];
    bool determined = false;
    for(int i=1;i<=m;i++) {
        scanf("%s", relation);
        int from = relation[0] - 'A';
        int to = relation[2] - 'A';
        add_edge(adj, from, to);

        // Check for inconsistency or determined order
        char current_order[MAX+1];
        bool has_order = topo_sort(n, adj, current_order);
        // To check inconsistency, try to perform topo_sort and see if all nodes are included
        // If not all nodes are included and no unique order, check for cycle
        // Alternatively, perform topo_sort and see if it fails
        // Since topo_sort returns false if there's a cycle or multiple orders
        // We need to separately check for cycle
        // So let's check for cycle first
        // Implement a simple cycle check using DFS
        bool visited[MAX];
        bool rec_stack[MAX];
        memset(visited, false, sizeof(visited));
        memset(rec_stack, false, sizeof(rec_stack));
        bool cycle = false;
        // DFS for cycle detection
        for(int v=0; v<n && !cycle; v++) {
            if(!visited[v]) {
                // iterative DFS
                int stack[MAX];
                int top = -1;
                stack[++top] = v;
                while(top >=0 && !cycle){
                    int node = stack[top];
                    top--;
                    if(!visited[node]){
                        visited[node] = true;
                        rec_stack[node] = true;
                        for(int u=0; u<n; u++) {
                            if(adj[node][u]){
                                if(!visited[u]){
                                    stack[++top] = u;
                                }
                                else if(rec_stack[u]){
                                    cycle = true;
                                    break;
                                }
                            }
                        }
                    }
                    rec_stack[node] = false;
                }
            }
        }

        if(cycle){
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        }

        if(has_order){
            printf("Sorted sequence determined after %d relations: %s.\n", i, current_order);
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}