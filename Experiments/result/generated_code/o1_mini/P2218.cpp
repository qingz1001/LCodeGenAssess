#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int x;
    int y;
} Point;

// Comparator for sorting points by x ascending, then y ascending
int cmp_points(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return pa->x - pb->x;
    return pa->y - pb->y;
}

// Deque structure for maintaining indices
typedef struct {
    int data[20000];
    int front;
    int back;
} Deque;

// Initialize deque
void deque_init(Deque *dq) {
    dq->front = 0;
    dq->back = -1;
}

// Push back to deque
void deque_push_back(Deque *dq, int val) {
    dq->back++;
    dq->data[dq->back] = val;
}

// Pop front from deque
void deque_pop_front(Deque *dq) {
    if (dq->front > dq->back) return;
    dq->front++;
}

// Pop back from deque
void deque_pop_back(Deque *dq) {
    if (dq->front > dq->back) return;
    dq->back--;
}

// Get front value
int deque_front_val(Deque *dq) {
    if (dq->front > dq->back) return -1;
    return dq->data[dq->front];
}

// Get back value
int deque_back_val(Deque *dq) {
    if (dq->front > dq->back) return -1;
    return dq->data[dq->back];
}

// Function to check if all points can be covered with 3 squares of size L
int can_cover(int n, Point *points, ll L) {
    // Initialize DP arrays
    int *dp_prev = (int*)calloc(n + 1, sizeof(int));
    int *dp_curr = (int*)calloc(n + 1, sizeof(int));
    dp_prev[0] = 1;
    
    for(int k = 1; k <=3; k++) {
        deque_init((Deque*)&(Deque){0});
        Deque min_dq;
        Deque max_dq;
        deque_init(&min_dq);
        deque_init(&max_dq);
        int j =0;
        for(int i=0; i<n; i++) {
            // Update j to maintain x[i] - x[j] <= L
            while(j <= i && ( (ll)(points[i].x) - (ll)(points[j].x) > L)) {
                if(deque_front_val(&min_dq) == j)
                    deque_pop_front(&min_dq);
                if(deque_front_val(&max_dq) == j)
                    deque_pop_front(&max_dq);
                j++;
            }
            // Maintain min deque
            while(min_dq.front <= min_dq.back && points[i].y <= points[min_dq.back].y)
                deque_pop_back(&min_dq);
            deque_push_back(&min_dq, i);
            // Maintain max deque
            while(max_dq.front <= max_dq.back && points[i].y >= points[max_dq.back].y)
                deque_pop_back(&max_dq);
            deque_push_back(&max_dq, i);
            // Adjust j to maintain y_max - y_min <= L
            while(j <= i && ((ll)(points[max_dq.data[min_dq.front]].y) - (ll)(points[min_dq.data[min_dq.front]].y)) > L) {
                if(deque_front_val(&min_dq) == j)
                    deque_pop_front(&min_dq);
                if(deque_front_val(&max_dq) == j)
                    deque_pop_front(&max_dq);
                j++;
                // Also ensure x difference
                while(j <= i && ( (ll)(points[i].x) - (ll)(points[j].x) > L)) {
                    if(deque_front_val(&min_dq) == j)
                        deque_pop_front(&min_dq);
                    if(deque_front_val(&max_dq) == j)
                        deque_pop_front(&max_dq);
                    j++;
                }
            }
            // Check if current window is valid
            if(j <= i && ((ll)(points[i].x) - (ll)(points[j].x) <= L) && 
               ((ll)(points[max_dq.data[min_dq.front]].y) - (ll)(points[min_dq.data[min_dq.front]].y) <= L)) {
                if(dp_prev[j]) {
                    dp_curr[i +1] =1;
                }
            }
        }
        // Reset dp_prev for next k
        for(int i=0; i<=n; i++) {
            dp_prev[i] = dp_curr[i];
            dp_curr[i] =0;
        }
    }
    int result = dp_prev[n];
    free(dp_prev);
    free(dp_curr);
    return result;
}

int main(){
    int N;
    scanf("%d", &N);
    Point *points = (Point*)malloc(sizeof(Point)*N);
    for(int i=0; i<N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    // Sort points by x ascending, then y ascending
    qsort(points, N, sizeof(Point), cmp_points);
    // Binary search for minimal L
    ll low =0, high =2000000000;
    while(low < high){
        ll mid = low + (high - low)/2;
        if(can_cover(N, points, mid)){
            high = mid;
        }
        else{
            low = mid +1;
        }
    }
    printf("%lld\n", low);
    free(points);
    return 0;
}