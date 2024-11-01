#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Structure for cells
typedef struct {
    ll x;
    ll s;
} Cell;

// Deque structure for sliding window
typedef struct {
    int *data;
    int front;
    int back;
    int size;
    int capacity;
} Deque;

// Initialize deque
Deque* initDeque(int capacity){
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->data = (int*)malloc(sizeof(int)*capacity);
    dq->front = 0;
    dq->back = 0;
    dq->size = 0;
    dq->capacity = capacity;
    return dq;
}

// Push back
void pushBack(Deque* dq, int val){
    while(dq->size >0 && val >= dq->data[dq->back-1]){
        dq->back--;
        dq->size--;
    }
    dq->data[dq->back++] = val;
    dq->size++;
}

// Pop front
void popFront(Deque* dq){
    if(dq->size >0){
        dq->front++;
        dq->size--;
    }
}

// Get front
int getFront(Deque* dq){
    if(dq->size >0){
        return dq->data[dq->front];
    }
    return -1;
}

// Free deque
void freeDeque(Deque* dq){
    free(dq->data);
    free(dq);
}

int n;
ll d, k;
Cell *cells;

// Comparison function for qsort (not needed as input is sorted)
int cmp(const void *a, const void *b){
    ll x1 = ((Cell*)a)->x;
    ll x2 = ((Cell*)b)->x;
    if(x1 <x2) return -1;
    if(x1 >x2) return 1;
    return 0;
}

// Binary search to check if possible with given g
int possible(ll g){
    // Define L and R based on g
    ll L, R;
    if(g < d){
        L = d - g;
        if(L <1) L =1;
    }
    else{
        L =1;
    }
    R = d + g;
    // Initialize DP
    ll *DP = (ll*)malloc((n+1)*sizeof(ll));
    for(int i=0;i<=n;i++) DP[i] = -1e18;
    DP[0] =0;
    // Initialize deque
    Deque* dq = initDeque(n+1);
    // Initialize pointers
    int l =0, r =0;
    // Push the first element
    if(cells[0].x >=0 && cells[0].x <=R){
        pushBack(dq,0);
        r++;
    }
    for(int i=1;i<=n;i++){
        // Update L and R for current i
        ll curr_x = cells[i].x;
        ll lower = curr_x - R;
        ll upper = curr_x - L;
        // Move l
        while(l <=n && cells[l].x < lower){
            if(dq->size >0 && dq->data[dq->front] == l){
                popFront(dq);
            }
            l++;
        }
        // Move r
        while(r <=n && cells[r].x <=upper){
            while(dq->size >0 && DP[r] >= DP[dq->data[dq->back-1]]){
                dq->back--;
                dq->size--;
            }
            dq->data[dq->back++] = r;
            dq->size++;
            r++;
        }
        // Get max DP[j] in window
        if(dq->size >0 && cells[dq->data[dq->front]].x >= lower && cells[dq->data[dq->front]].x <=upper){
            DP[i] = DP[dq->data[dq->front]] + cells[i].s;
        }
        else{
            DP[i] = -1e18;
        }
        // Maintain deque
        if(DP[i] != -1e18){
            while(dq->size >0 && DP[i] >= DP[dq->data[dq->back-1]]){
                dq->back--;
                dq->size--;
            }
            dq->data[dq->back++] = i;
            dq->size++;
        }
    }
    // Find the maximum DP[i]
    ll maxSum = -1e18;
    for(int i=1;i<=n;i++) {
        if(DP[i] > maxSum) maxSum = DP[i];
    }
    free(DP);
    freeDeque(dq);
    return maxSum >=k;
}

int main(){
    // Read n, d, k
    scanf("%d %lld %lld", &n, &d, &k);
    // Allocate cells with n+1 (including start)
    cells = (Cell*)malloc((n+1)*sizeof(Cell));
    // Start cell
    cells[0].x =0;
    cells[0].s =0;
    // Read cells
    for(int i=1;i<=n;i++) scanf("%lld %lld", &cells[i].x, &cells[i].s);
    // Binary search for g
    ll left =0, right =1000000000, answer =-1;
    while(left <=right){
        ll mid = left + (right -left)/2;
        if(possible(mid)){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    // Check answer
    if(answer != -1){
        printf("%lld\n", answer);
    }
    else{
        printf("-1\n");
    }
    free(cells);
    return 0;
}