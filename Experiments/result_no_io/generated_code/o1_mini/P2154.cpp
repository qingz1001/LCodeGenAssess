#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int x;
    int y;
} Tree;

typedef struct {
    int y;
    int x;
    uint64_t val;
    int type; // 1 for add, -1 for remove
} Event;

typedef struct {
    int y;
    int num;
    int *xs;
} Row;

int cmp_tree_y(const void *a, const void *b) {
    Tree *ta = (Tree *)a;
    Tree *tb = (Tree *)b;
    if (ta->y != tb->y)
        return ta->y - tb->y;
    return ta->x - tb->x;
}

int cmp_tree_x(const void *a, const void *b) {
    Tree *ta = (Tree *)a;
    Tree *tb = (Tree *)b;
    if (ta->x != tb->x)
        return ta->x - tb->x;
    return ta->y - tb->y;
}

int cmp_event(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->y != eb->y)
        return ea->y - eb->y;
    return ea->type - eb->type; // add before remove if same y
}

int cmp_int(const void *a, const void *b) {
    int ia = *(int *)a;
    int ib = *(int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

// Binary search to find first >= key
int lower_bound_int(int *arr, int size, int key){
    int left=0, right=size;
    while(left < right){
        int mid = left + (right - left)/2;
        if(arr[mid] < key) left = mid+1;
        else right = mid;
    }
    return left;
}

// Binary search to find last <= key
int upper_bound_int(int *arr, int size, int key){
    int left=0, right=size;
    while(left < right){
        int mid = left + (right - left)/2;
        if(arr[mid] <= key) left = mid+1;
        else right = mid;
    }
    return left-1;
}

typedef struct {
    int size;
    uint64_t *tree;
} BIT;

// Initialize BIT
BIT* bit_init(int size){
    BIT *b = (BIT*)malloc(sizeof(BIT));
    b->size = size;
    b->tree = (uint64_t*)calloc(size+2, sizeof(uint64_t));
    return b;
}

// Update BIT at index with value
void bit_update(BIT *b, int index, uint64_t val){
    while(index <= b->size){
        b->tree[index] += val;
        index += index & (-index);
    }
}

// Query BIT up to index
uint64_t bit_query(BIT *b, int index){
    uint64_t res = 0;
    while(index > 0){
        res += b->tree[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int W;
    scanf("%d", &W);
    Tree *trees = (Tree*)malloc(W * sizeof(Tree));
    for(int i=0;i<W;i++) scanf("%d %d", &trees[i].x, &trees[i].y);
    int k;
    // Read all trees first
    // Read k after trees
    // To handle, store trees first
    // But problem says k is last line, let's adjust
    // So read trees first, then read k
    // After trees, read k
    // So adjust input reading
    // First read N, M, W and W trees, then read k
    // Re-read W trees
    // Now sort trees by y then x
    qsort(trees, W, sizeof(Tree), cmp_tree_y);
    
    // Collect rows
    // First count number of unique y's
    int unique_rows = 0;
    for(int i=0;i<W;i++) {
        if(i==0 || trees[i].y != trees[i-1].y) unique_rows++;
    }
    Row *rows = (Row*)malloc(unique_rows * sizeof(Row));
    int current = 0;
    rows[current].y = trees[0].y;
    rows[current].num = 1;
    rows[current].xs = (int*)malloc(W * sizeof(int));
    rows[current].xs[0] = trees[0].x;
    for(int i=1;i<W;i++){
        if(trees[i].y == rows[current].y){
            rows[current].xs[rows[current].num++] = trees[i].x;
        }
        else{
            current++;
            rows[current].y = trees[i].y;
            rows[current].num = 1;
            rows[current].xs = (int*)malloc(W * sizeof(int));
            rows[current].xs[0] = trees[i].x;
        }
    }
    
    // Now sort trees by x then y
    qsort(trees, W, sizeof(Tree), cmp_tree_x);
    
    // Collect columns
    int unique_cols = 0;
    for(int i=0;i<W;i++) {
        if(i==0 || trees[i].x != trees[i-1].x) unique_cols++;
    }
    // Allocate maximum possible
    Tree **cols = (Tree**)malloc(unique_cols * sizeof(Tree*));
    int *col_sizes = (int*)calloc(unique_cols, sizeof(int));
    for(int i=0;i<unique_cols;i++) cols[i] = NULL;
    current = -1;
    for(int i=0;i<W;i++){
        if(i==0 || trees[i].x != trees[i-1].x){
            current++;
            cols[current] = (Tree*)malloc(W * sizeof(Tree));
            col_sizes[current] = 0;
        }
        cols[current][col_sizes[current]].y = trees[i].y;
        col_sizes[current]++;
    }
    
    // Read k
    scanf("%d", &k);
    
    // Precompute C[n][k]
    // C[m][n] where m up to k and n up to W
    uint64_t **C = (uint64_t**)malloc((k+1) * sizeof(uint64_t*));
    for(int m=0;m<=k;m++) {
        C[m] = (uint64_t*)calloc(W+1, sizeof(uint64_t));
        C[m][0] = (m==0)?1:0;
    }
    for(int n=1;n<=W;n++){
        C[0][n] = 1;
        for(int m=1;m<=k;m++){
            if(m > n){
                C[m][n] = 0;
            }
            else{
                C[m][n] = C[m][n-1] + C[m-1][n-1];
            }
        }
    }
    
    // Create column events
    Event *events = (Event*)malloc(2 * W * sizeof(Event));
    int event_count = 0;
    for(int i=0;i<unique_cols;i++){
        if(col_sizes[i] < 2*k) continue;
        for(int j=k; j <= col_sizes[i]-k; j++){
            uint64_t cb = (C[k][j] * C[k][col_sizes[i]-j]) ;
            if(cb ==0) continue;
            int y_start = cols[i][j-1].y +1;
            int y_end;
            if(j < col_sizes[i]-k){
                y_end = cols[i][j].y -1;
            }
            else{
                y_end = M;
            }
            events[event_count].y = y_start;
            events[event_count].x = trees[i*W + j-1].x; // Not correct, need correct x
            // To get x, it's cols[i][j-1].x, but cols stored y's
            // x is unique, which is the i-th column
            int x = trees[i*W + 0].x; // All trees in column i have same x
            events[event_count].x = x;
            events[event_count].val = cb;
            events[event_count].type = 1;
            event_count++;
            events[event_count].y = y_end+1;
            events[event_count].x = x;
            events[event_count].val = cb;
            events[event_count].type = -1;
            event_count++;
        }
    }
    
    // Collect unique x's from events
    int *unique_x = (int*)malloc(2 * W * sizeof(int));
    int ux_count =0;
    for(int i=0;i<event_count;i++) unique_x[ux_count++] = events[i].x;
    // Remove duplicates
    qsort(unique_x, ux_count, sizeof(int), cmp_int);
    int final_ux =0;
    for(int i=0;i<ux_count;i++) {
        if(i==0 || unique_x[i] != unique_x[i-1]) unique_x[final_ux++] = unique_x[i];
    }
    // Sort events by y
    qsort(events, event_count, sizeof(Event), cmp_event);
    
    // Sort rows by y ascending
    qsort(rows, unique_rows, sizeof(Row), cmp_tree_y);
    
    // Initialize BIT
    BIT *bit = bit_init(final_ux);
    
    // Sweep through events and rows
    uint64_t total_sum =0;
    int e_ptr=0, r_ptr=0;
    for(int current_y=0; current_y <= M; current_y++){
        // Process all events at current_y
        while(e_ptr < event_count && events[e_ptr].y == current_y){
            // Find x index
            int x = events[e_ptr].x;
            int idx = lower_bound_int(unique_x, final_ux, x);
            if(idx < final_ux && unique_x[idx] == x){
                if(events[e_ptr].type ==1){
                    bit_update(bit, idx+1, events[e_ptr].val);
                }
                else{
                    bit_update(bit, idx+1, (uint64_t)(-((int64_t)events[e_ptr].val)));
                }
            }
            e_ptr++;
        }
        // Process row if exists
        if(r_ptr < unique_rows && rows[r_ptr].y == current_y){
            Row current_row = rows[r_ptr];
            // Iterate through possible j
            for(int j=k; j <= current_row.num -k; j++){
                uint64_t row_val = C[k][j] * C[k][current_row.num -j];
                if(row_val ==0) continue;
                int x_start, x_end;
                if(j ==0){
                    x_start =0;
                }
                else{
                    x_start = current_row.xs[j-1]+1;
                }
                if(j < current_row.num -k){
                    x_end = current_row.xs[j];
                }
                else{
                    x_end = N;
                }
                // Find left_idx and right_idx in unique_x
                int left = lower_bound_int(unique_x, final_ux, x_start);
                int right = upper_bound_int(unique_x, final_ux, x_end);
                if(left <= right){
                    uint64_t sum_cols = bit_query(bit, right+1) - bit_query(bit, left);
                    total_sum += row_val * sum_cols;
                }
            }
            r_ptr++;
        }
        // Break early if all events and rows processed
        if(e_ptr >= event_count && r_ptr >= unique_rows) break;
    }
    
    // Read k after trees
    // But already read k before
    
    // Output the result modulo 2147483648
    uint64_t MOD = 2147483648ULL;
    printf("%llu\n", total_sum % MOD);
    
    // Free memory
    free(trees);
    for(int i=0;i<unique_rows;i++) free(rows[i].xs);
    free(rows);
    for(int i=0;i<unique_cols;i++) free(cols[i]);
    free(cols);
    for(int m=0;m<=k;m++) free(C[m]);
    free(C);
    free(events);
    free(unique_x);
    free(bit->tree);
    free(bit);
    
    return 0;
}