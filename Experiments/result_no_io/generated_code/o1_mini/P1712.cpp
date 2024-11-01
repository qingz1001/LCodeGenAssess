#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long len;
    long long l;
    long long r;
} Interval;

int cmp_len(const void *a, const void *b){
    Interval *ia = (Interval*)a;
    Interval *ib = (Interval*)b;
    if (ia->len < ib->len) return -1;
    if (ia->len > ib->len) return 1;
    return 0;
}

int cmp_event(const void *a, const void *b){
    long long x1 = *((long long*)a);
    long long x2 = *((long long*)b);
    if(x1 < x2) return -1;
    if(x1 > x2) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Interval *arr = (Interval*)malloc(n * sizeof(Interval));
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &arr[i].l, &arr[i].r);
        arr[i].len = arr[i].r - arr[i].l;
    }
    qsort(arr, n, sizeof(Interval), cmp_len);
    
    // Binary search between 0 and max possible D
    long long low = 0, high = 1000000000, answer = -1;
    while(low <= high){
        long long mid = low + (high - low)/2;
        // Sliding window
        int left = 0, right = 0;
        // Sorted r_i list
        long long *sorted_r = (long long*)malloc(n * sizeof(long long));
        int sr_size = 0;
        int feasible = 0;
        for(right=0; right<n; right++){
            // Insert arr[right].r into sorted_r
            int pos = 0, l_ptr = 0, r_ptr = sr_size;
            // Binary search to find insert position
            int lo = 0, hi = sr_size;
            while(lo < hi){
                int mid_p = lo + (hi - lo)/2;
                if(sorted_r[mid_p] < arr[right].r) lo = mid_p +1;
                else hi = mid_p;
            }
            pos = lo;
            // Shift and insert
            for(int k=sr_size; k>pos; k--){
                sorted_r[k] = sorted_r[k-1];
            }
            sorted_r[pos] = arr[right].r;
            sr_size++;
            
            // Slide the window
            while(left <= right && (arr[right].len - arr[left].len) > mid){
                // Remove arr[left].r from sorted_r
                // Binary search to find the position
                int remove_pos = -1;
                lo = 0;
                hi = sr_size;
                while(lo < hi){
                    int mid_p = lo + (hi - lo)/2;
                    if(sorted_r[mid_p] < arr[left].r) lo = mid_p +1;
                    else hi = mid_p;
                }
                if(lo < sr_size && sorted_r[lo] == arr[left].r){
                    // Shift left
                    for(int k=lo; k<sr_size-1; k++) sorted_r[k] = sorted_r[k+1];
                    sr_size--;
                }
                left++;
            }
            // Check feasibility
            if((right - left +1) >= m){
                if(sr_size >= m){
                    long long x = sorted_r[m-1];
                    // Count how many intervals in [left, right] have l <=x
                    int cnt =0;
                    for(int k=left; k<=right && cnt < m; k++){
                        if(arr[k].l <= x) cnt++;
                    }
                    if(cnt >=m){
                        feasible =1;
                        break;
                    }
                }
            }
        }
        free(sorted_r);
        if(feasible){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    // Verify the answer
    if(answer != -1){
        // Check if feasible
        // If no feasible, set answer to -1
        // Already handled in binary search
        printf("%lld\n", answer);
    }
    else{
        printf("-1\n");
    }
    free(arr);
    return 0;
}