#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500001

typedef struct Node {
    int *children;
    int size;
    int capacity;
} Node;

int n;
Node tree[MAXN];
int contains_n[MAXN];
int stack1[MAXN];
int top1;
int stack2[MAXN];
int top2;
int parent[MAXN];
int order[MAXN];
int idx = 0;

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        tree[i].children = NULL;
        tree[i].size = 0;
        tree[i].capacity = 0;
    }
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        if(tree[u].size == tree[u].capacity){
            tree[u].capacity = tree[u].capacity ? tree[u].capacity * 2 : 2;
            tree[u].children = realloc(tree[u].children, tree[u].capacity * sizeof(int));
        }
        tree[u].children[tree[u].size++] = v;
        if(tree[v].size == tree[v].capacity){
            tree[v].capacity = tree[v].capacity ? tree[v].capacity * 2 : 2;
            tree[v].children = realloc(tree[v].children, tree[v].capacity * sizeof(int));
        }
        tree[v].children[tree[v].size++] = u;
    }
    // First DFS to mark contains_n
    memset(contains_n, 0, sizeof(int)*(n+1));
    top1 = 0;
    stack1[top1++] = 1;
    parent[1] = -1;
    while(top1){
        int u = stack1[top1-1];
        top1--;
        contains_n[u] = (u == n);
        for(int i=0;i<tree[u].size;i++){
            int v = tree[u].children[i];
            if(v != parent[u]){
                parent[v] = u;
                stack1[top1++] = v;
            }
        }
    }
    // Reset for second DFS
    top1 = 0;
    stack1[top1++] = 1;
    int ptr[MAXN];
    for(int i=1;i<=n;i++) ptr[i] = 0;
    // Second DFS to order children with contains_n last
    while(top1){
        int u = stack1[top1-1];
        if(ptr[u] < tree[u].size){
            int v = tree[u].children[ptr[u]++];
            if(v != parent[u]){
                stack1[top1++] = v;
            }
        }
        else{
            top1--;
        }
    }
    // Now perform DFS with children containing n last
    top2 = 0;
    stack2[top2++] = 1;
    idx = 0;
    memset(parent, 0, sizeof(int)*(n+1));
    while(top2){
        int u = stack2[top2-1];
        if(ptr[u] < tree[u].size){
            int v = tree[u].children[ptr[u]++];
            if(v != parent[u]){
                parent[v] = u;
                stack2[top2++] = v;
            }
        }
        else{
            order[idx++] = u;
            top2--;
        }
    }
    // Check if last node is n
    if(order[idx-1] != n){
        printf("BRAK\n");
        return 0;
    }
    // Print the order
    for(int i=0;i<idx;i++) printf("%d\n", order[i]);
    return 0;
}