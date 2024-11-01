#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODES 52
#define MAX_EDGES 1326
#define MAX_STACK 2000
#define MAX_PATH 2000

// Mapping from character to node index
int char_to_node(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    return -1;
}

// Mapping from node index to character
char node_to_char_func(int node) {
    if (node < 26) return 'A' + node;
    return 'a' + (node - 26);
}

// Sort adjacency lists in ascending order
void sort_adj(int adj[][MAX_NODES], int degree[]) {
    for(int i = 0; i < MAX_NODES; i++) {
        for(int j = 0; j < degree[i]-1; j++) {
            for(int k = j+1; k < degree[i]; k++) {
                if(adj[i][j] > adj[i][k]) {
                    int temp = adj[i][j];
                    adj[i][j] = adj[i][k];
                    adj[i][k] = temp;
                }
            }
        }
    }
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        printf("No Solution");
        return 0;
    }
    int adj[MAX_NODES][MAX_NODES];
    int degree[MAX_NODES];
    memset(degree, 0, sizeof(degree));
    for(int i=0;i<n;i++){
        char pair[3];
        if(scanf("%2s", pair)!=1){
            printf("No Solution");
            return 0;
        }
        int u = char_to_node(pair[0]);
        int v = char_to_node(pair[1]);
        if(u==-1 || v==-1){
            printf("No Solution");
            return 0;
        }
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }
    sort_adj(adj, degree);
    // Check connectivity
    int visited[MAX_NODES];
    memset(visited, 0, sizeof(visited));
    int start = -1;
    for(int i=0;i<MAX_NODES;i++) if(degree[i]>0){ start = i; break;}
    if(start == -1){
        printf("No Solution");
        return 0;
    }
    // DFS
    int stack_dfs[MAX_NODES];
    int top_dfs = 0;
    stack_dfs[top_dfs++] = start;
    visited[start] = 1;
    while(top_dfs >0){
        int node = stack_dfs[--top_dfs];
        for(int i=0;i<degree[node];i++){
            int neighbor = adj[node][i];
            if(!visited[neighbor]){
                visited[neighbor] =1;
                stack_dfs[top_dfs++] = neighbor;
            }
        }
    }
    // Count nodes with degree >0
    int count_deg =0;
    for(int i=0;i<MAX_NODES;i++) if(degree[i]>0) count_deg++;
    // Count visited nodes
    int count_vis =0;
    for(int i=0;i<MAX_NODES;i++) if(degree[i]>0 && visited[i]) count_vis++;
    if(count_vis != count_deg){
        printf("No Solution");
        return 0;
    }
    // Check degrees
    int odd_nodes[2];
    int odd_count=0;
    for(int i=0;i<MAX_NODES;i++) if(degree[i]%2==1){
        if(odd_count<2) odd_nodes[odd_count++] = i;
        else { odd_count++; break;}
    }
    if(odd_count !=0 && odd_count !=2){
        printf("No Solution");
        return 0;
    }
    // Determine start node
    if(odd_count ==2){
        if(odd_nodes[0] < odd_nodes[1]) start = odd_nodes[0];
        else start = odd_nodes[1];
    }
    else{
        // Start from smallest node with degree >0
        start = -1;
        for(int i=0;i<MAX_NODES;i++) if(degree[i]>0){ start = i; break;}
    }
    // Copy adjacency and degree to temp
    int temp_adj[MAX_NODES][MAX_NODES];
    int temp_degree[MAX_NODES];
    for(int i=0;i<MAX_NODES;i++){
        temp_degree[i] = degree[i];
        for(int j=0;j<degree[i];j++) temp_adj[i][j] = adj[i][j];
    }
    // Hierholzer's algorithm
    int stack_euler[MAX_STACK];
    int top_euler =0;
    stack_euler[top_euler++] = start;
    int path[MAX_PATH];
    int path_len =0;
    while(top_euler >0){
        int current = stack_euler[top_euler-1];
        if(temp_degree[current] >0){
            int next = temp_adj[current][0];
            // Remove the edge from current to next
            // Shift left in current's adjacency
            for(int i=0;i<temp_degree[current]-1;i++) temp_adj[current][i] = temp_adj[current][i+1];
            temp_degree[current]--;
            // Remove the edge from next to current
            int found = 0;
            for(int i=0;i<temp_degree[next];i++) {
                if(temp_adj[next][i] == current){
                    for(int j=i; j<temp_degree[next]-1; j++) temp_adj[next][j] = temp_adj[next][j+1];
                    temp_degree[next]--;
                    found =1;
                    break;
                }
            }
            stack_euler[top_euler++] = next;
        }
        else{
            path[path_len++] = stack_euler[--top_euler];
        }
    }
    // Check if path is valid
    if(path_len != n+1){
        printf("No Solution");
        return 0;
    }
    // Reverse the path
    char result[MAX_PATH +1];
    for(int i=0;i<n+1;i++) result[i] = node_to_char_func(path[path_len-1-i]);
    result[n+1] = '\0';
    printf("%s", result);
    return 0;
}