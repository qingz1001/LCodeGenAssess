#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int degree;
    int label;
} Node;

int cmp_nodes(const void *a, const void *b) {
    Node *n1 = (Node *)a;
    Node *n2 = (Node *)b;
    if (n1->degree != n2->degree)
        return n1->degree - n2->degree;
    return n1->id - n2->id;
}

int compare_int(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

long long intersect_count(int *a, int len_a, int *b, int len_b){
    long long count = 0;
    int i = 0, j = 0;
    while(i < len_a && j < len_b){
        if(a[i] == b[j]){
            count++;
            i++;
            j++;
        }
        else if(a[i] < b[j]){
            i++;
        }
        else{
            j++;
        }
    }
    return count;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    Node nodes[n+1];
    for(int i=1;i<=n;i++){
        nodes[i].id = i;
        nodes[i].degree = 0;
        nodes[i].label = 0;
    }
    
    int u, v;
    int edges[200000][2];
    for(int i=0;i<m;i++){
        scanf("%d %d", &u, &v);
        edges[i][0] = u;
        edges[i][1] = v;
        nodes[u].degree++;
        nodes[v].degree++;
    }
    
    Node sorted_nodes[n];
    for(int i=0;i<n;i++) {
        sorted_nodes[i] = nodes[i+1];
    }
    
    qsort(sorted_nodes, n, sizeof(Node), cmp_nodes);
    
    int label[n+1];
    for(int i=0;i<n;i++){
        label[sorted_nodes[i].id] = i;
    }
    
    int adj_sizes[n+1];
    for(int i=1;i<=n;i++) adj_sizes[i] = 0;
    
    for(int i=0;i<m;i++){
        u = edges[i][0];
        v = edges[i][1];
        if(label[u] < label[v]){
            adj_sizes[u]++;
        }
        else{
            adj_sizes[v]++;
        }
    }
    
    int adj_offsets[n+2];
    adj_offsets[1] = 0;
    for(int i=1;i<=n;i++){
        adj_offsets[i+1] = adj_offsets[i] + adj_sizes[i];
    }
    
    int total_adj = adj_offsets[n+1];
    int *adj = (int*)malloc(sizeof(int)*total_adj);
    int current_pos[n+1];
    for(int i=1;i<=n;i++) current_pos[i] = adj_offsets[i];
    
    for(int i=0;i<m;i++){
        u = edges[i][0];
        v = edges[i][1];
        if(label[u] < label[v]){
            adj[current_pos[u]++] = v;
        }
        else{
            adj[current_pos[v]++] = u;
        }
    }
    
    for(int i=1;i<=n;i++){
        qsort(adj + adj_offsets[i], adj_sizes[i], sizeof(int), compare_int);
    }
    
    long long triangle = 0;
    for(int i=1;i<=n;i++){
        for(int j=0; j<adj_sizes[i]; j++){
            int v = adj[adj_offsets[i] + j];
            triangle += intersect_count(adj + adj_offsets[i], adj_sizes[i], adj + adj_offsets[v], adj_sizes[v]);
        }
    }
    
    printf("%lld\n", triangle);
    free(adj);
    return 0;
}