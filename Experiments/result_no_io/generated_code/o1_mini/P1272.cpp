#include <stdio.h>
#include <stdlib.h>

#define MAX 151

typedef struct Node {
    int children[MAX];
    int child_count;
} Node;

Node tree[MAX];
int subtree_size[MAX];
int N, P;
int count_result = 0;

void dfs(int current, int parent) {
    subtree_size[current] = 1;
    for(int i = 0; i < tree[current].child_count; i++) {
        int child = tree[current].children[i];
        if(child != parent){
            dfs(child, current);
            subtree_size[current] += subtree_size[child];
        }
    }
    if(subtree_size[current] == P && current != 1){
        count_result++;
    }
}

int main(){
    scanf("%d %d", &N, &P);
    for(int i = 0; i < N-1; i++){
        int I, J;
        scanf("%d %d", &I, &J);
        tree[I].children[tree[I].child_count++] = J;
    }
    dfs(1, -1);
    printf("%d\n", count_result);
    return 0;
}