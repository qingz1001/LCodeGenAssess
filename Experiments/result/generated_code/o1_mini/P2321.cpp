#include<stdio.h>
#include<stdlib.h>

#define MAX 100005

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAX];
int visited[MAX];
int n;
int max_depth = 0;

void addEdge(int u, int v){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void dfs(int u, int depth){
    if(depth > max_depth) max_depth = depth;
    visited[u] = 1;
    Node* temp = adj[u];
    while(temp){
        if(!visited[temp->id]){
            dfs(temp->id, depth + 1);
        }
        temp = temp->next;
    }
}

int main(){
    scanf("%d", &n);
    int total_nodes = 0;
    int parent, cnt, child;
    while(total_nodes < n){
        scanf("%d %d", &parent, &cnt);
        for(int i=0;i<cnt;i++){
            scanf("%d", &child);
            addEdge(parent, child);
        }
        total_nodes++;
    }
    for(int i=0;i<=100000;i++) visited[i]=0;
    for(int i=0;i<=100000;i++){
        if(adj[i] && !visited[i]){
            dfs(i, 1);
        }
    }
    printf("%d\n", max_depth);
    return 0;
}