#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2005
#define MAXM 10005

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAXN];
int indegree[MAXN];
int k_val[MAXN];
int n, m;

// Queue for Kahn's algorithm
int queue[MAXN];
int front = 0, rear = 0;

// Function to add edge
void add_edge(int a, int b){
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = b;
    node->next = adj[a];
    adj[a] = node;
    indegree[b]++;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        scanf("%d", &k_val[i]);
    }
    for(int i=0;i<m;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }
    // Initialize queue with nodes having indegree 0
    for(int i=1;i<=n;i++) {
        if(indegree[i]==0){
            queue[rear++] = i;
        }
    }
    int schedule[MAXN];
    int pos = 0;
    while(front < rear){
        // Find a node in queue[front..rear-1] with k_val >= pos+1
        int selected = -1;
        for(int i=front;i<rear;i++){
            if(k_val[queue[i]] >= pos +1){
                selected = i;
                break;
            }
        }
        if(selected == -1){
            // Should not happen as per problem statement
            break;
        }
        int u = queue[selected];
        // Move u to schedule
        schedule[pos++] = u;
        // Swap selected with front
        queue[selected] = queue[front];
        front++;
        // Decrease indegree of neighbors
        Node* ptr = adj[u];
        while(ptr){
            indegree[ptr->id]--;
            if(indegree[ptr->id]==0){
                queue[rear++] = ptr->id;
            }
            ptr = ptr->next;
        }
    }
    for(int i=0;i<n;i++){
        printf("%d%c", schedule[i], i<n-1?' ':'\n');
    }
    // Compute earliest positions
    // Initialize earliest positions to 1
    int earliest[MAXN];
    for(int i=1;i<=n;i++) earliest[i] = 1;
    // Topological order from schedule
    for(int i=0;i<n;i++){
        int u = schedule[i];
        Node* ptr = adj[u];
        while(ptr){
            if(earliest[ptr->id] < earliest[u] +1){
                earliest[ptr->id] = earliest[u] +1;
            }
            ptr = ptr->next;
        }
    }
    for(int i=1;i<=n;i++){
        if(earliest[i] > k_val[i]){
            earliest[i] = k_val[i];
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d%c", earliest[i], i<n?' ':'\n');
    }
    // Free memory
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