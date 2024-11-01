#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000000
#define LOG 20
#define MOD 1000000007

int log_table_val[1000001];
int c_max_table_val[LOG][1000001];
int d_min_table_val[LOG][1000001];
int c_val[1000001];
int d_val[1000001];
int dp_val[1000001];
long long count_val_[1000001];

// Iterative Segment Tree
int size;
int *st_max;
long long *st_cnt;

// Function to build log_table
void build_log_table(int n){
    log_table_val[1] = 0;
    for(int i=2;i<=n;i++){
        log_table_val[i] = log_table_val[i/2] +1;
    }
}

// Function to build Sparse Tables for c_max and d_min
void build_sparse_tables(int n){
    // Initialize level 0
    for(int i=1;i<=n;i++){
        c_max_table_val[0][i] = c_val[i];
        d_min_table_val[0][i] = d_val[i];
    }
    // Build higher levels
    for(int k=1;k<LOG;k++){
        for(int i=1;i + (1<<k) -1 <=n;i++){
            if(c_max_table_val[k-1][i] > c_max_table_val[k-1][i + (1<<(k-1))]){
                c_max_table_val[k][i] = c_max_table_val[k-1][i];
            }
            else{
                c_max_table_val[k][i] = c_max_table_val[k-1][i + (1<<(k-1))];
            }
            if(d_min_table_val[k-1][i] < d_min_table_val[k-1][i + (1<<(k-1))]){
                d_min_table_val[k][i] = d_min_table_val[k-1][i];
            }
            else{
                d_min_table_val[k][i] = d_min_table_val[k-1][i + (1<<(k-1))];
            }
        }
    }
}

// Function to get max_c in range [l, r]
int get_max_c(int l, int r){
    int j = log_table_val[r - l +1];
    if(c_max_table_val[j][l] > c_max_table_val[j][r - (1<<j) +1]){
        return c_max_table_val[j][l];
    }
    else{
        return c_max_table_val[j][r - (1<<j) +1];
    }
}

// Function to get min_d in range [l, r]
int get_min_d(int l, int r){
    int j = log_table_val[r - l +1];
    if(d_min_table_val[j][l] < d_min_table_val[j][r - (1<<j) +1]){
        return d_min_table_val[j][l];
    }
    else{
        return d_min_table_val[j][r - (1<<j) +1];
    }
}

// Initialize the Segment Tree
void init_segment_tree(int n){
    size = 1;
    while(size < n+1) size <<=1;
    st_max = (int*)malloc(2*size*sizeof(int));
    st_cnt = (long long*)malloc(2*size*sizeof(long long));
    for(int i=0;i<2*size;i++){
        st_max[i] = -1;
        st_cnt[i] = 0;
    }
    // Set dp[0] =0 and count[0]=1
    st_max[size +0] = 0;
    st_cnt[size +0] =1;
    for(int i=size +0 +1;i<2*size;i++){
        st_max[i] = -1;
        st_cnt[i] =0;
    }
    // Build the tree
    for(int i=size -1;i>=1;i--){
        if(st_max[2*i] > st_max[2*i +1]){
            st_max[i] = st_max[2*i];
            st_cnt[i] = st_cnt[2*i];
        }
        else if(st_max[2*i] < st_max[2*i +1]){
            st_max[i] = st_max[2*i +1];
            st_cnt[i] = st_cnt[2*i +1];
        }
        else{
            st_max[i] = st_max[2*i];
            st_cnt[i] = st_cnt[2*i] + st_cnt[2*i +1];
            if(st_cnt[i] >= MOD) st_cnt[i] -= MOD;
        }
    }
}

// Update the Segment Tree at position pos with dp and count
void update_segment_tree(int pos, int dp_new, long long cnt_new){
    pos += size;
    st_max[pos] = dp_new;
    st_cnt[pos] = cnt_new;
    pos >>=1;
    while(pos >=1){
        if(st_max[2*pos] > st_max[2*pos +1]){
            if(st_max[pos] != st_max[2*pos]){
                st_max[pos] = st_max[2*pos];
                st_cnt[pos] = st_cnt[2*pos];
            }
            else{
                break;
            }
        }
        else if(st_max[2*pos] < st_max[2*pos +1]){
            if(st_max[pos] != st_max[2*pos +1]){
                st_max[pos] = st_max[2*pos +1];
                st_cnt[pos] = st_cnt[2*pos +1];
            }
            else{
                break;
            }
        }
        else{
            long long new_cnt = st_cnt[2*pos] + st_cnt[2*pos +1];
            if(new_cnt >= MOD) new_cnt -= MOD;
            if(st_max[pos] != st_max[2*pos]){
                st_max[pos] = st_max[2*pos];
                st_cnt[pos] = st_cnt[2*pos];
            }
            else{
                st_cnt[pos] = new_cnt;
            }
        }
        pos >>=1;
    }
}

// Query the Segment Tree in range [l, r]
void query_segment_tree(int l, int r, int n, int *res_max, long long *res_cnt){
    l += size;
    r += size;
    int temp_max = -1;
    long long temp_cnt =0;
    while(l <=r){
        if(l%2 ==1){
            if(st_max[l] > temp_max){
                temp_max = st_max[l];
                temp_cnt = st_cnt[l];
            }
            else if(st_max[l] == temp_max){
                temp_cnt += st_cnt[l];
                if(temp_cnt >= MOD) temp_cnt -= MOD;
            }
            l++;
        }
        if(r%2 ==0){
            if(st_max[r] > temp_max){
                temp_max = st_max[r];
                temp_cnt = st_cnt[r];
            }
            else if(st_max[r] == temp_max){
                temp_cnt += st_cnt[r];
                if(temp_cnt >= MOD) temp_cnt -= MOD;
            }
            r--;
        }
        l >>=1;
        r >>=1;
    }
    *res_max = temp_max;
    *res_cnt = temp_cnt;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%d %d", &c_val[i], &d_val[i]);
    }
    build_log_table(n);
    build_sparse_tables(n);
    // Initialize dp and count
    dp_val[0] =0;
    count_val_[0] =1;
    // Initialize Segment Tree
    init_segment_tree(n);
    // Iterate through each child
    for(int i=1;i<=n;i++){
        // Binary search for k_min
        int left =1, right =i;
        int k_low = i+1;
        while(left <=right){
            int mid = left + (right -left)/2;
            int j = i -mid +1;
            if(j <1){
                left = mid +1;
                continue;
            }
            int max_c = get_max_c(j, i);
            int min_d = get_min_d(j, i);
            if(max_c <= mid && min_d >= mid){
                k_low = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        // Binary search for k_max
        left =1;
        right =i;
        int k_high =0;
        while(left <=right){
            int mid = left + (right -left)/2;
            int j = i -mid +1;
            if(j <1){
                right = mid -1;
                continue;
            }
            int max_c = get_max_c(j, i);
            int min_d = get_min_d(j, i);
            if(max_c <= mid && min_d >= mid){
                k_high = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(k_low >k_high){
            continue;
        }
        // Calculate j_min and j_max
        int j_min = i -k_high;
        int j_max = i -k_low;
        if(j_min <0) j_min =0;
        if(j_max <0) j_max =0;
        if(j_min > j_max){
            continue;
        }
        // Query the segment tree for [j_min, j_max]
        int res_max = -1;
        long long res_cnt =0;
        query_segment_tree(j_min, j_max, n, &res_max, &res_cnt);
        if(res_max == -1){
            continue;
        }
        // Update dp and count
        dp_val[i] = res_max +1;
        count_val_[i] = res_cnt % MOD;
        // Update the segment tree
        update_segment_tree(i, dp_val[i], count_val_[i]);
    }
    if(dp_val[n] >0){
        printf("%d %lld\n", dp_val[n], count_val_[n]);
    }
    else{
        printf("NIE\n");
    }
    // Free allocated memory
    free(st_max);
    free(st_cnt);
    return 0;
}