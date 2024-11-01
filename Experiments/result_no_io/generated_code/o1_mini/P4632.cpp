#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
    int x;
} Store;

typedef struct {
    int y;
    int l;
    int q_id;
} Query;

int cmp_query(const void *a, const void *b) {
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if (qa->y != qb->y)
        return (qa->y < qb->y) ? -1 : 1;
    return 0;
}

int cmp_a(const void *a, const void *b) {
    Store *sa = *(Store **)a;
    Store *sb = *(Store **)b;
    if (sa->a != sb->a)
        return (sa->a < sb->a) ? -1 : 1;
    return 0;
}

int cmp_b(const void *a, const void *b) {
    Store *sa = *(Store **)a;
    Store *sb = *(Store **)b;
    if (sa->b != sb->b)
        return (sa->b < sb->b) ? -1 : 1;
    return 0;
}

int cmp_x(const void *a, const void *b) {
    int xa = *(int *)a;
    int xb = *(int *)b;
    if (xa != xb)
        return (xa < xb) ? -1 : 1;
    return 0;
}

int main(){
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    // Allocate memory for types
    Store **types = (Store **)malloc(k * sizeof(Store *));
    int *type_sizes = (int *)calloc(k, sizeof(int));
    int **type_a = (int **)malloc(k * sizeof(int *));
    int **type_b = (int **)malloc(k * sizeof(int *));
    int **type_x = (int **)malloc(k * sizeof(int *));
    
    for(int i = 0; i < k; i++){
        types[i] = NULL;
    }
    
    // Read stores
    for(int i = 0; i < n; i++){
        int x, t, a, b;
        scanf("%d %d %d %d", &x, &t, &a, &b);
        t -= 1; // 0-based index
        type_sizes[t]++;
        types[t] = (Store *)realloc(types[t], type_sizes[t] * sizeof(Store));
        types[t][type_sizes[t]-1].a = a;
        types[t][type_sizes[t]-1].b = b;
        types[t][type_sizes[t]-1].x = x;
    }
    
    // Read queries
    Query *queries = (Query *)malloc(q * sizeof(Query));
    for(int i = 0; i < q; i++){
        scanf("%d %d", &queries[i].l, &queries[i].y);
        queries[i].q_id = i;
    }
    
    // Sort queries by y ascending
    qsort(queries, q, sizeof(Query), cmp_query);
    
    // Prepare sorted_a, sorted_b, sorted_x for each type
    for(int t = 0; t < k; t++){
        if(type_sizes[t] == 0){
            continue;
        }
        // Sort stores[t] by a ascending
        qsort(types[t], type_sizes[t], sizeof(Store), cmp_a);
        // Allocate and store sorted a
        type_a[t] = (int *)malloc(type_sizes[t] * sizeof(int));
        for(int i = 0; i < type_sizes[t]; i++) type_a[t][i] = types[t][i].a;
        // Sort stores[t] by b ascending
        qsort(types[t], type_sizes[t], sizeof(Store), cmp_b);
        // Allocate and store sorted b
        type_b[t] = (int *)malloc(type_sizes[t] * sizeof(int));
        for(int i = 0; i < type_sizes[t]; i++) type_b[t][i] = types[t][i].b;
        // Sort stores[t] by x ascending
        // First, extract x's
        type_x[t] = (int *)malloc(type_sizes[t] * sizeof(int));
        for(int i = 0; i < type_sizes[t]; i++) type_x[t][i] = types[t][i].x;
        qsort(type_x[t], type_sizes[t], sizeof(int), cmp_x);
    }
    
    // Initialize answer and count arrays
    long long *answer = (long long *)calloc(q, sizeof(long long));
    int *count_q = (int *)calloc(q, sizeof(int));
    
    // Temporary arrays for active x's
    // Since per type active_x is small, use a small buffer
    int *active_x = (int *)malloc(k * sizeof(int)); // current size
    int **active_x_list = (int **)malloc(k * sizeof(int *));
    int *active_size = (int *)calloc(k, sizeof(int));
    for(int t = 0; t < k; t++) active_x_list[t] = NULL;
    
    // Iterate through each type
    for(int t = 0; t < k; t++){
        if(type_sizes[t] == 0){
            continue;
        }
        int na = type_sizes[t];
        int nb = type_sizes[t];
        int nx = type_sizes[t];
        // Pointers for a and b
        int pa = 0, pb = 0;
        // Initialize active_x_list for type t
        active_x_list[t] = (int *)malloc(type_sizes[t] * sizeof(int));
        active_size[t] = 0;
        for(int j = 0; j < q; j++){
            int y = queries[j].y;
            // Add to active
            while(pa < na && type_a[t][pa] <= y){
                // Insert type_x[t][pa] into active_x_list[t] in sorted order
                int x = type_x[t][pa];
                // Binary insert
                int pos = 0;
                int low = 0, high = active_size[t];
                while(low < high){
                    int mid = (low + high) / 2;
                    if(active_x_list[t][mid] < x){
                        low = mid + 1;
                    }
                    else{
                        high = mid;
                    }
                }
                pos = low;
                // Shift right
                for(int s = active_size[t]; s > pos; s--){
                    active_x_list[t][s] = active_x_list[t][s-1];
                }
                active_x_list[t][pos] = x;
                active_size[t]++;
                pa++;
            }
            // Remove from active
            while(pb < nb && type_b[t][pb] < y){
                int x = type_x[t][pb];
                // Find x in active_x_list[t]
                int pos = 0;
                int low = 0, high = active_size[t];
                while(low < high){
                    int mid = (low + high) / 2;
                    if(active_x_list[t][mid] < x){
                        low = mid + 1;
                    }
                    else{
                        high = mid;
                    }
                }
                pos = low;
                if(pos < active_size[t] && active_x_list[t][pos] == x){
                    // Shift left
                    for(int s = pos; s < active_size[t]-1; s++){
                        active_x_list[t][s] = active_x_list[t][s+1];
                    }
                    active_size[t]--;
                }
                pb++;
            }
            // If active, find min distance
            if(active_size[t] > 0){
                int l = queries[j].l;
                // Binary search for closest
                int low = 0, high = active_size[t]-1;
                int best = -1;
                while(low <= high){
                    int mid = (low + high) / 2;
                    if(active_x_list[t][mid] < l){
                        low = mid + 1;
                    }
                    else{
                        high = mid - 1;
                    }
                }
                int min_d = 100000000;
                if(low < active_size[t]){
                    int diff = active_x_list[t][low] - l;
                    if(diff < 0) diff = -diff;
                    if(diff < min_d) min_d = diff;
                }
                if(low-1 >= 0){
                    int diff = active_x_list[t][low-1] - l;
                    if(diff < 0) diff = -diff;
                    if(diff < min_d) min_d = diff;
                }
                // Update answer and count
                if(count_q[queries[j].q_id] == 0 || min_d > answer[queries[j].q_id]){
                    answer[queries[j].q_id] = min_d;
                }
                count_q[queries[j].q_id]++;
            }
        }
        free(active_x_list[t]);
    }
    
    // Now, output answers
    // Read queries in original order
    // Create an array to hold the answers in original order
    long long *final_ans = (long long *)malloc(q * sizeof(long long));
    for(int i = 0; i < q; i++) final_ans[i] = -1;
    for(int j = 0; j < q; j++){
        int qid = queries[j].q_id;
        if(count_q[qid] == k){
            if(final_ans[qid] < answer[qid]){
                final_ans[qid] = answer[qid];
            }
        }
    }
    // Set final_ans to -1 where count_q != k
    for(int i = 0; i < q; i++){
        if(count_q[i] != k){
            final_ans[i] = -1;
        }
    }
    // Print the answers in order
    for(int i = 0; i < q; i++){
        printf("%lld", final_ans[i]);
        if(i != q-1) printf(" ");
    }
    printf("\n");
    
    // Free allocated memory
    for(int t = 0; t < k; t++){
        if(type_sizes[t] > 0){
            free(type_a[t]);
            free(type_b[t]);
            free(type_x[t]);
        }
    }
    free(types);
    free(type_sizes);
    free(type_a);
    free(type_b);
    free(type_x);
    free(queries);
    free(answer);
    free(count_q);
    free(active_x);
    free(active_x_list);
    free(active_size);
    free(final_ans);
    
    return 0;
}