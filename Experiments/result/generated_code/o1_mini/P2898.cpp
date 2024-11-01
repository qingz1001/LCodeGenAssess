#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int r;
    int x;
    int idx;
} Condition;

int cmp(const void *a, const void *b) {
    Condition *ca = (Condition *)a;
    Condition *cb = (Condition *)b;
    if (ca->x != cb->x)
        return cb->x - ca->x;
    return ca->idx - cb->idx;
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    Condition *conds = (Condition *)malloc(q * sizeof(Condition));
    for(int i=0;i<q;i++){
        scanf("%d %d %d", &conds[i].l, &conds[i].r, &conds[i].x);
        conds[i].idx = i+1;
    }
    // Sort conditions in decreasing order of x
    qsort(conds, q, sizeof(Condition), cmp);
    // Union-Find setup
    int *parent = (int *)malloc((n+2) * sizeof(int));
    for(int i=0;i<=n+1;i++) parent[i] = i;
    // Array to store assigned x's
    int *assigned = (int *)calloc(n+1, sizeof(int));
    // Assign x's
    for(int i=0;i<q;i++){
        // Find the position to assign
        int pos = conds[i].r;
        // Find the latest available position <= r
        while(pos >= conds[i].l && parent[pos] != pos){
            pos = parent[pos];
        }
        if(pos < conds[i].l){
            // Inconsistency found
            printf("%d\n", conds[i].idx);
            free(conds);
            free(parent);
            free(assigned);
            return 0;
        }
        // Assign x to pos
        assigned[pos] = conds[i].x;
        // Union pos with pos-1
        parent[pos] = pos -1;
    }
    // Now, check for each condition in original order
    // Reconstruct the assignment
    // To map x to position
    // Since x's are unique, we can traverse the assigned array
    // and for each condition, ensure that within [l,r], min is x
    // Find min in [l,r] and check if it's x
    // To do it efficiently, build an array of assigned values and prefix min
    // Since n <=1e6, it's manageable
    int *A = (int *)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) A[i] = assigned[i];
    // Build prefix min
    int *prefix_min = (int *)malloc((n+1) * sizeof(int));
    prefix_min[0] = 1000000001;
    for(int i=1;i<=n;i++) {
        if(A[i]==0) prefix_min[i] = prefix_min[i-1];
        else if(A[i] < prefix_min[i-1]) prefix_min[i] = A[i];
        else prefix_min[i] = prefix_min[i-1];
    }
    // Re-read the conditions in input order
    rewind(stdin);
    scanf("%d %d", &n, &q);
    for(int i=1;i<=q;i++){
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        // Find min in [l,r]
        int current_min = 1000000001;
        // To find min in [l,r], use prefix_min
        // current_min = min(A[l..r])
        // Since prefix_min[r] is min(A[1..r]), and prefix_min[l-1] is min(A[1..l-1])
        // If prefix_min[r] < prefix_min[l-1], current_min = prefix_min[r]
        // Else, need to scan from l to r
        if(l == 1){
            current_min = prefix_min[r];
        }
        else{
            if(prefix_min[r] < prefix_min[l-1]){
                current_min = prefix_min[r];
            }
            else{
                current_min = 1000000001;
                for(int j=l;j<=r;j++) {
                    if(A[j] < current_min){
                        current_min = A[j];
                        if(current_min == x) break;
                    }
                }
            }
        }
        if(current_min != x){
            printf("%d\n", i);
            free(conds);
            free(parent);
            free(assigned);
            free(A);
            free(prefix_min);
            return 0;
        }
    }
    printf("0\n");
    free(conds);
    free(parent);
    free(assigned);
    free(A);
    free(prefix_min);
    return 0;
}