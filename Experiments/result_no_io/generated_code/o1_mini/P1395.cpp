#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node* next;
} Node;

#define MAX 50001

Node* adj[MAX];
long long res[MAX];
int count_nodes[MAX];
int n;

void addEdge(int a, int b) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = b;
    node->next = adj[a];
    adj[a] = node;
}

void dfs1(int u, int parent_u) {
    count_nodes[u] = 1;
    res[u] = 0;
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parent_u){
            dfs1(v, u);
            count_nodes[u] += count_nodes[v];
            res[u] += res[v] + count_nodes[v];
        }
        ptr = ptr->next;
    }
}

void dfs2(int u, int parent_u) {
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parent_u){
            res[v] = res[u] - count_nodes[v] + (n - count_nodes[v]);
            dfs2(v, u);
        }
        ptr = ptr->next;
    }
}

int main(){
    int a, b;
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    int min_node = 1;
    long long min_sum = res[1];
    for(int i=2;i<=n;i++){
        if(res[i] < min_sum){
            min_sum = res[i];
            min_node = i;
        }
        else if(res[i] == min_sum && i < min_node){
            min_node = i;
        }
    }
    printf("%d %lld\n", min_node, min_sum);
    // Free allocated memory
    for(int i=1;i<=n;i++){
        Node* ptr = adj[i];
        while(ptr){
            Node* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return 0;
}