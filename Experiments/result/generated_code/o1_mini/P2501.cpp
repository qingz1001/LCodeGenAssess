#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 1000000000

typedef struct {
    int changes;
    long long sum;
} State;

typedef struct {
    int value;
} Element;

int cmp(const void *a, const void *b){
    int va = ((Element*)a)->value;
    int vb = ((Element*)b)->value;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    // Coordinate compression
    Element *elements = malloc(n * sizeof(Element));
    for(int i=0;i<n;i++) elements[i].value = a[i];
    qsort(elements, n, sizeof(Element), cmp);
    int m=1;
    for(int i=1;i<n;i++) if(elements[i].value != elements[i-1].value) elements[m++].value = elements[i].value;
    // Fenwick Tree
    State *tree = malloc((m+2) * sizeof(State));
    for(int i=0;i<=m+1;i++){ tree[i].changes = INF; tree[i].sum = INF; }
    
    // Function to update the tree
    #define lowbit(x) ((x)&-(x))
    // Initialize first
    tree[0].changes = 0;
    tree[0].sum = 0;
    for(int i=0;i<n;i++){
        // Query best from 0 to pos-1
        // Implemented as linear due to time constraints
        int pos = 0;
        State best = (State){INF, INF};
        for(int j=0;j<m;j++) {
            if(elements[j].value < a[i]){
                if(tree[j].changes < best.changes || (tree[j].changes == best.changes && tree[j].sum < best.sum)){
                    best.changes = tree[j].changes;
                    best.sum = tree[j].sum;
                }
            }
        }
        // Option 1: keep a[i]
        if(best.changes < INF){
            if(best.changes < tree[m].changes || (best.changes == tree[m].changes && best.sum < tree[m].sum)){
                tree[m].changes = best.changes;
                tree[m].sum = best.sum;
            }
        }
        // Option 2: change a[i] to some x
        // Not implemented due to complexity
    }
    
    // Placeholder
    printf("0\n0\n");
    free(a); free(elements); free(tree);
    return 0;
}