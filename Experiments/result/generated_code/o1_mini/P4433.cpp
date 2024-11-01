#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for qsort
int cmp(const void *a, const void *b){
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

// Function to remove duplicates
int unique_pos(ll *pos, int size){
    if(size ==0) return 0;
    int j =0;
    for(int i=1;i<size;i++){
        if(pos[j] != pos[i]){
            j++;
            pos[j] = pos[i];
        }
    }
    return j+1;
}

// Function to compute floor_sum
ll floor_sum_func(ll n, ll m, ll a, ll b){
    ll res = 0;
    while (n > 0){
        if(a >= m){
            res += ((a / m) * (n-1) * n)/2;
            a %= m;
        }
        if(b >= m){
            res += (b / m) * n;
            b %= m;
        }
        ll y_max = a * n + b;
        if(y_max < m){
            break;
        }
        ll new_n = y_max / m;
        ll new_b = y_max % m;
        // swap a and m
        ll tmp = a;
        a = m;
        m = tmp;
        n = new_n;
        b = new_b;
    }
    return res;
}

int main(){
    int q;
    ll n;
    scanf("%lld %d", &n, &q);
    ll ops_q[50000][5];
    int type_q[50000];
    ll L_q[50000];
    ll R_q[50000];
    ll A_q[50000];
    ll B_q[50000];
    int size =0;
    // Collect all points
    ll pos_array[100002];
    int pos_size =0;
    pos_array[pos_size++] =1;
    pos_array[pos_size++] =n+1;
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        type_q[i] = type;
        if(type ==1){
            ll L, R, A, B;
            scanf("%lld %lld %lld %lld", &L, &R, &A, &B);
            L_q[i] = L;
            R_q[i] = R;
            A_q[i] = A;
            B_q[i] = B;
            pos_array[pos_size++] = L;
            pos_array[pos_size++] = R+1;
        }
        else{
            ll L, R;
            scanf("%lld %lld", &L, &R);
            L_q[i] = L;
            R_q[i] = R;
            pos_array[pos_size++] = L;
            pos_array[pos_size++] = R+1;
        }
    }
    // Sort and unique
    qsort(pos_array, pos_size, sizeof(ll), cmp);
    pos_size = unique_pos(pos_array, pos_size);
    // Number of segments
    int m_seg = pos_size -1;
    // Initialize sum array
    ll *sum_arr = (ll*)calloc(m_seg, sizeof(ll));
    for(int i=0;i<m_seg;i++) sum_arr[i]=0;
    // Process operations
    for(int i=0;i<q;i++){
        if(type_q[i]==1){
            ll L = L_q[i];
            ll R = R_q[i];
            ll A = A_q[i];
            ll B = B_q[i];
            // Find start index
            int start =0, end = pos_size;
            while(start < end){
                int mid = (start + end)/2;
                if(pos_array[mid] <= L) start = mid +1;
                else end = mid;
            }
            int idx_start = start -1;
            // Find end index
            start =0; end = pos_size;
            while(start < end){
                int mid = (start + end)/2;
                if(pos_array[mid] <= R) start = mid +1;
                else end = mid;
            }
            int idx_end = start -1;
            for(int j=idx_start; j<idx_end; j++){
                ll seg_l = pos_array[j];
                ll seg_r = pos_array[j+1]-1;
                ll y_start = seg_l - L +1;
                ll y_end = seg_r - L +1;
                if(y_start <1) y_start =1;
                ll m = y_end - y_start +1;
                ll sum_y = (y_start + y_end) * m /2;
                ll sum_floor = floor_sum_func(y_end, B, A, 0) - floor_sum_func(y_start -1, B, A, 0);
                ll sum_mod = A * sum_y - B * sum_floor;
                sum_arr[j] = sum_mod;
            }
        }
        else{
            ll L = L_q[i];
            ll R = R_q[i];
            // Find start index
            int start =0, end = pos_size;
            while(start < end){
                int mid = (start + end)/2;
                if(pos_array[mid] <= L) start = mid +1;
                else end = mid;
            }
            int idx_start = start -1;
            // Find end index
            start =0; end = pos_size;
            while(start < end){
                int mid = (start + end)/2;
                if(pos_array[mid] <= R) start = mid +1;
                else end = mid;
            }
            int idx_end = start -1;
            ll total =0;
            for(int j=idx_start; j<idx_end; j++) total += sum_arr[j];
            printf("%lld\n", total);
        }
    }
    free(sum_arr);
    return 0;
}