#include <stdio.h>
#include <stdlib.h>

// Structure to hold operation details
typedef struct {
    int op;
    int l;
    int r;
} Operation;

// Comparator for ascending sort
int cmp_asc(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

// Comparator for descending sort
int cmp_desc(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if(x > y) return -1;
    if(x < y) return 1;
    return 0;
}

// Comparator for positions ascending
int cmp_pasc(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

#define MAX_N 100005
#define MAX_M 100005

Operation operations[MAX_M];
int A[MAX_N];
int last_op_p[MAX_N];
int uf_parent[MAX_N +1];
int count_op[MAX_M];
long long op_start[MAX_M +2];
int list_p[MAX_N];
int list_values[MAX_N];
int final_a[MAX_N];

int find_set(int p){
    if(uf_parent[p] != p){
        uf_parent[p] = find_set(uf_parent[p]);
    }
    return uf_parent[p];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    for(int i=1;i<=n;i++){
        scanf("%d", &A[i]);
    }
    
    for(int i=1;i<=m;i++){
        scanf("%d %d %d", &operations[i].op, &operations[i].l, &operations[i].r);
    }
    
    // Initialize Union-Find
    for(int i=1;i<=n+1;i++){
        uf_parent[i] = i;
    }
    
    // Assign last_op for each position
    for(int i=m;i>=1;i--){
        int l = operations[i].l;
        int r = operations[i].r;
        int p = find_set(l);
        while(p <= r){
            last_op_p[p] = i;
            uf_parent[p] = find_set(p +1);
            p = find_set(p);
        }
    }
    
    // Count number of positions per operation
    for(int p=1;p<=n;p++){
        int i = last_op_p[p];
        if(i !=0){
            count_op[i]++;
        }
    }
    
    // Compute op_start
    op_start[1] = 0;
    for(int i=2;i<=m+1;i++){
        op_start[i] = op_start[i-1] + count_op[i-1];
    }
    
    // Assign list_p and list_values
    int current_count[MAX_M] = {0};
    for(int p=1;p<=n;p++){
        int i = last_op_p[p];
        if(i !=0){
            int idx = op_start[i] + current_count[i];
            list_p[idx] = p;
            list_values[idx] = A[p];
            current_count[i]++;
        }
    }
    
    // Initialize final_a with original values
    for(int p=1;p<=n;p++){
        final_a[p] = A[p];
    }
    
    // Temporary arrays for sorting
    int temp_size;
    int temp_vals[MAX_N];
    int temp_ps[MAX_N];
    
    // Process each operation
    for(int i=1;i<=m;i++){
        if(count_op[i] >0){
            long long s = op_start[i];
            long long e = s + count_op[i] -1;
            temp_size = count_op[i];
            for(int j=0; j < temp_size; j++){
                temp_vals[j] = list_values[s + j];
                temp_ps[j] = list_p[s + j];
            }
            if(operations[i].op == 0){
                qsort(temp_vals, temp_size, sizeof(int), cmp_asc);
            }
            else{
                qsort(temp_vals, temp_size, sizeof(int), cmp_desc);
            }
            qsort(temp_ps, temp_size, sizeof(int), cmp_pasc);
            for(int j=0; j < temp_size; j++){
                final_a[temp_ps[j]] = temp_vals[j];
            }
        }
    }
    
    int q;
    scanf("%d", &q);
    printf("%d\n", final_a[q]);
    
    return 0;
}