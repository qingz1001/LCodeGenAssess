#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int a;
    int b;
    int c;
} Query;

int cmp_int(const void *a, const void *b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    
    // Allocate memory for tasks
    int *s = (int*)malloc(sizeof(int)*m);
    int *e = (int*)malloc(sizeof(int)*m);
    int *p = (int*)malloc(sizeof(int)*m);
    int *p_values = (int*)malloc(sizeof(int)*m);
    
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &s[i], &e[i], &p[i]);
        p_values[i] = p[i];
    }
    
    // Read queries and store in query[x]
    Query *query = (Query*)malloc(sizeof(Query)*(n+1));
    for(int i=0;i<n;i++){
        int x_i, a_i, b_i, c_i;
        scanf("%d %d %d %d", &x_i, &query[x_i].a, &query[x_i].b, &query[x_i].c);
    }
    
    // Sort and unique p_values
    qsort(p_values, m, sizeof(int), cmp_int);
    int total_p = 0;
    int *sorted_p = (int*)malloc(sizeof(int)*m);
    if(m >0){
        sorted_p[total_p++] = p_values[0];
        for(int i=1;i<m;i++) {
            if(p_values[i] != sorted_p[total_p-1]){
                sorted_p[total_p++] = p_values[i];
            }
        }
    }
    
    // Initialize start_counts and remove_counts
    int *start_counts = (int*)calloc(n+2, sizeof(int));
    int *remove_counts = (int*)calloc(n+2, sizeof(int));
    for(int i=0;i<m;i++){
        start_counts[s[i]]++;
        if(e[i]+1 <=n){
            remove_counts[e[i]+1]++;
        }
    }
    
    // Compute start_p_idx and remove_p_idx
    int *start_p_idx = (int*)malloc(sizeof(int)*(n+2));
    int *remove_p_idx = (int*)malloc(sizeof(int)*(n+2));
    start_p_idx[1] = 0;
    for(int x=2;x<=n+1;x++) start_p_idx[x] = start_p_idx[x-1] + start_counts[x-1];
    remove_p_idx[1] = 0;
    for(int x=2;x<=n+1;x++) remove_p_idx[x] = remove_p_idx[x-1] + remove_counts[x-1];
    
    // Allocate start_p_arr and remove_p_arr
    int *start_p_arr = (int*)malloc(sizeof(int)*m);
    int *remove_p_arr = (int*)malloc(sizeof(int)*m);
    
    // Temporary counters
    int *current_start = (int*)malloc(sizeof(int)*(n+2));
    int *current_remove = (int*)malloc(sizeof(int)*(n+2));
    for(int x=1;x<=n+1;x++) {
        current_start[x] = start_p_idx[x];
        current_remove[x] = remove_p_idx[x];
    }
    
    // Assign p_idx to start_p_arr and remove_p_arr
    for(int i=0;i<m;i++){
        // Find p_idx via binary search
        int low=0, high=total_p-1, mid, p_idx;
        while(low <= high){
            mid = (low + high)/2;
            if(sorted_p[mid] < p[i]){
                low = mid +1;
            }
            else if(sorted_p[mid] > p[i]){
                high = mid -1;
            }
            else{
                break;
            }
        }
        p_idx = mid +1; // 1-based
        // Assign to start_p_arr
        start_p_arr[current_start[s[i]]++] = p_idx;
        // Assign to remove_p_arr if needed
        if(e[i]+1 <=n){
            remove_p_arr[current_remove[e[i]+1]++] = p_idx;
        }
    }
    
    // Initialize BIT
    ll *BIT_sum = (ll*)calloc(total_p+2, sizeof(ll));
    int *BIT_count_arr = (int*)calloc(total_p+2, sizeof(int));
    
    // Function to update BIT
    auto update = [&](void *BIT_sum_ptr, void *BIT_count_ptr, int idx, ll val_sum, int val_count) -> void {
        while(idx <= total_p){
            ((ll*)BIT_sum_ptr)[idx] += val_sum;
            ((int*)BIT_count_ptr)[idx] += val_count;
            idx += idx & -idx;
        }
    };
    
    // Function to query BIT_sum
    auto query_sum = [&](ll *BIT_sum_ptr, int idx) -> ll {
        ll res =0;
        while(idx >0){
            res += ((ll*)BIT_sum_ptr)[idx];
            idx -= idx & -idx;
        }
        return res;
    };
    
    // Function to query BIT_count
    auto query_count = [&](int *BIT_count_ptr, int idx) -> int{
        int res=0;
        while(idx >0){
            res += ((int*)BIT_count_ptr)[idx];
            idx -= idx & -idx;
        }
        return res;
    };
    
    // Function to get k sum
    auto get_k_sum = [&](int k) -> ll{
        int idx=0;
        int bit_mask = 1 << 17;
        int temp_count =0;
        ll temp_sum =0;
        while(bit_mask >0){
            if(idx + bit_mask <= total_p && temp_count + BIT_count_arr[idx + bit_mask] <k){
                idx += bit_mask;
                temp_count += BIT_count_arr[idx];
                temp_sum += BIT_sum[idx];
            }
            bit_mask >>=1;
        }
        idx +=1;
        if(idx > total_p) idx = total_p;
        temp_sum += sorted_p[idx-1];
        temp_count += BIT_count_arr[idx];
        if(temp_count >k){
            temp_sum -= (ll)(temp_count -k) * sorted_p[idx-1];
        }
        return temp_sum;
    };
    
    ll pre =1;
    for(int x=1;x<=n;x++){
        // Add start tasks
        for(int i=start_p_idx[x]; i < start_p_idx[x+1]; i++){
            int p_idx = start_p_arr[i];
            update(BIT_sum, BIT_count_arr, p_idx, (ll)sorted_p[p_idx-1], 1);
        }
        // Remove tasks
        for(int i=remove_p_idx[x]; i < remove_p_idx[x+1]; i++){
            int p_idx = remove_p_arr[i];
            update(BIT_sum, BIT_count_arr, p_idx, -(ll)sorted_p[p_idx-1], -1);
        }
        // Perform query
        int a = query[x].a;
        int b = query[x].b;
        int c = query[x].c;
        int k = 1 + ((a * (int)pre + b) % c);
        // Get total count
        int total_count = query_count(BIT_count_arr, total_p);
        ll sum;
        if(k >= total_count){
            sum = query_sum(BIT_sum, total_p);
        }
        else{
            sum = get_k_sum(k);
        }
        printf("%lld\n", sum);
        pre = sum;
    }
    
    // Free memory
    free(s);
    free(e);
    free(p);
    free(p_values);
    free(query);
    free(sorted_p);
    free(start_counts);
    free(remove_counts);
    free(start_p_idx);
    free(remove_p_idx);
    free(start_p_arr);
    free(remove_p_arr);
    free(current_start);
    free(current_remove);
    free(BIT_sum);
    free(BIT_count_arr);
    
    return 0;
}