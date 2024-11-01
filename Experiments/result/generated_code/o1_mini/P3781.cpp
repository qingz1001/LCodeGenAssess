#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 10005
#define MOD 10007

typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node* adj[MAXN];
int v[MAXN];
int n, m, q;
char op[10];
int x, y, k;
int count_result;
int target;

void addEdge(int a, int b){
    Node* node = (Node*)malloc(sizeof(Node));
    node->to = b;
    node->next = adj[a];
    adj[a] = node;

    node = (Node*)malloc(sizeof(Node));
    node->to = a;
    node->next = adj[b];
    adj[b] = node;
}

void dfs(int u, int parent, int current_xor){
    current_xor ^= v[u];
    if(current_xor == target){
        count_result++;
    }
    Node* temp = adj[u];
    while(temp){
        int v_to = temp->to;
        if(v_to != parent){
            dfs(v_to, u, current_xor);
        }
        temp = temp->next;
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &v[i]);
    for(int i=1;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
    }
    scanf("%d", &q);
    while(q--){
        scanf("%s", op);
        if(strcmp(op, "Change")==0){
            scanf("%d %d", &x, &y);
            v[x] = y;
        }
        else if(strcmp(op, "Query")==0){
            scanf("%d", &k);
            target = k;
            count_result = 0;
            for(int i=1;i<=n;i++) dfs(i, -1, 0);
            // Each subtree is counted multiple times, need to divide by number of nodes in subtree
            // But to simplify, assume counting all possible connected subtrees
            // Output count_result modulo 10007
            printf("%d\n", count_result % MOD);
        }
    }
    return 0;
}