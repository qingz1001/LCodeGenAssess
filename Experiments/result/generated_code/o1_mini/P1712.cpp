#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long l;
    long long r;
    long long len;
} Interval;

// Comparator for sorting by length, then by l and r
int cmp(const void *a, const void *b){
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if(ia->len != ib->len)
        return (ia->len < ib->len) ? -1 : 1;
    if(ia->l != ib->l)
        return (ia->l < ib->l) ? -1 : 1;
    if(ia->r != ib->r)
        return (ia->r < ib->r) ? -1 : 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &arr[i].l, &arr[i].r);
        arr[i].len = arr[i].r - arr[i].l;
    }
    qsort(arr, n, sizeof(Interval), cmp);

    // Initialize deques for max_l and min_r
    int *deque_maxl = (int *)malloc(n * sizeof(int));
    int dq_maxl_size = 0;
    int *deque_minr = (int *)malloc(n * sizeof(int));
    int dq_minr_size = 0;

    long long min_cost = -1;
    int left = 0;
    for(int right=0; right<n; right++){
        // Update deque_maxl
        while(dq_maxl_size > 0 && arr[deque_maxl[dq_maxl_size-1]].l <= arr[right].l){
            dq_maxl_size--;
        }
        deque_maxl[dq_maxl_size++] = right;

        // Update deque_minr
        while(dq_minr_size > 0 && arr[deque_minr[dq_minr_size-1]].r >= arr[right].r){
            dq_minr_size--;
        }
        deque_minr[dq_minr_size++] = right;

        // Move left to maintain max_l <= min_r
        while(left <= right){
            long long current_maxl = arr[deque_maxl[0]].l;
            long long current_minr = arr[deque_minr[0]].r;
            if(current_maxl <= current_minr){
                break;
            }
            if(deque_maxl[0] == left){
                dq_maxl_size--;
                for(int i=0;i<dq_maxl_size;i++) deque_maxl[i] = deque_maxl[i+1];
            }
            if(deque_minr[0] == left){
                dq_minr_size--;
                for(int i=0;i<dq_minr_size;i++) deque_minr[i] = deque_minr[i+1];
            }
            left++;
        }

        // Check if current window has at least m intervals
        if(right - left + 1 >= m){
            long long current_cost = arr[right].len - arr[left].len;
            if(min_cost == -1 || current_cost < min_cost){
                min_cost = current_cost;
            }
        }
    }

    printf("%lld\n", min_cost);
    free(arr);
    free(deque_maxl);
    free(deque_minr);
    return 0;
}