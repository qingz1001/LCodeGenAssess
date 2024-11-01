#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Heap structure
typedef struct {
    int *heap;    // Stores j indices
    int size;
    int capacity;
} MinHeap;

// Function to swap two elements in the heap
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Comparison function: return 1 if j1 has higher priority than j2
int compare(int j1, int j2, ll *P, ll *prefix_M, ll *prefix_C){
    ll cost1 = P[j1] - prefix_M[j1-1] - prefix_C[j1-1];
    ll cost2 = P[j2] - prefix_M[j2-1] - prefix_C[j2-1];
    if(cost1 < cost2) return 1;
    if(cost1 == cost2 && j1 < j2) return 1;
    return 0;
}

// Heapify up
void heapify_up(MinHeap *h, int j, ll *P, ll *prefix_M, ll *prefix_C){
    while(j > 1){
        int parent = j / 2;
        if(compare(h->heap[j-1], h->heap[parent-1], P, prefix_M, prefix_C)){
            swap(&h->heap[j-1], &h->heap[parent-1]);
            j = parent;
        }
        else break;
    }
}

// Heapify down
void heapify_down(MinHeap *h, int j, ll *P, ll *prefix_M, ll *prefix_C){
    while(1){
        int smallest = j;
        int left = 2*j;
        int right = 2*j +1;
        if(left <= h->size && compare(h->heap[left-1], h->heap[smallest-1], P, prefix_M, prefix_C)){
            smallest = left;
        }
        if(right <= h->size && compare(h->heap[right-1], h->heap[smallest-1], P, prefix_M, prefix_C)){
            smallest = right;
        }
        if(smallest != j){
            swap(&h->heap[j-1], &h->heap[smallest-1]);
            j = smallest;
        }
        else break;
    }
}

// Push into heap
void push_heap(MinHeap *h, int j, ll *P, ll *prefix_M, ll *prefix_C){
    if(h->size +1 > h->capacity){
        // Should not happen as capacity is set to N
        return;
    }
    h->heap[h->size] = j;
    h->size++;
    heapify_up(h, h->size, P, prefix_M, prefix_C);
}

// Pop the top of the heap
int pop_heap_min(MinHeap *h){
    if(h->size ==0){
        return -1; // Should not happen
    }
    int min_j = h->heap[0];
    h->heap[0] = h->heap[h->size-1];
    h->size--;
    heapify_down(h, 1, NULL, NULL, NULL); // NULLs not used inside heapify_down
    return min_j;
}

int main(){
    int N;
    scanf("%d", &N);
    
    // Allocate arrays
    ll *D = (ll*)malloc((N+1) * sizeof(ll));
    ll *U = (ll*)malloc((N+1) * sizeof(ll));
    ll *P = (ll*)malloc((N+1) * sizeof(ll));
    ll *M = (ll*)malloc((N) * sizeof(ll)); // M[0] to M[N-1]
    ll *C = (ll*)malloc((N) * sizeof(ll)); // C[0] to C[N-1]
    ll *prefix_M = (ll*)malloc((N+1) * sizeof(ll));
    ll *prefix_C = (ll*)malloc((N+1) * sizeof(ll));
    ll *remaining_U = (ll*)malloc((N+1) * sizeof(ll));
    
    // Read D
    for(int i=1;i<=N;i++) scanf("%lld", &D[i]);
    
    // Read U
    for(int i=1;i<=N;i++) scanf("%lld", &U[i]);
    
    // Read P
    for(int i=1;i<=N;i++) scanf("%lld", &P[i]);
    
    // Read M
    for(int i=0;i<N-1;i++) scanf("%lld", &M[i]);
    
    // Read C
    for(int i=0;i<N-1;i++) scanf("%lld", &C[i]);
    
    // Compute prefix_M and prefix_C
    prefix_M[0] = 0;
    prefix_C[0] = 0;
    for(int i=1;i<=N;i++){
        if(i <= N-1){
            prefix_M[i] = prefix_M[i-1] + M[i-1];
            prefix_C[i] = prefix_C[i-1] + C[i-1];
        }
        else{
            prefix_M[i] = prefix_M[i-1];
            prefix_C[i] = prefix_C[i-1];
        }
    }
    
    // Initialize remaining_U
    for(int i=1;i<=N;i++) remaining_U[i] = U[i];
    
    // Initialize heap
    MinHeap heap;
    heap.capacity = N;
    heap.size =0;
    heap.heap = (int*)malloc((N) * sizeof(int));
    
    ll total_cost =0;
    
    for(int i=1;i<=N;i++){
        // Push j=i into heap
        push_heap(&heap, i, P, prefix_M, prefix_C);
        
        while(D[i] >0){
            if(heap.size ==0){
                // Should not happen as per problem statement
                break;
            }
            int j = heap.heap[0];
            ll available = remaining_U[j];
            if(available ==0){
                // Should not happen, but just in case
                pop_heap_min(&heap);
                continue;
            }
            ll x = (D[i] < available) ? D[i] : available;
            // Compute cost_per_unit
            ll cost_per_unit = P[j] + (prefix_M[i-1] - prefix_M[j-1]) + (prefix_C[i-1] - prefix_C[j-1]);
            total_cost += x * cost_per_unit;
            D[i] -=x;
            remaining_U[j] -=x;
            if(remaining_U[j] ==0){
                // Remove j from heap
                pop_heap_min(&heap);
            }
        }
    }
    
    printf("%lld\n", total_cost);
    
    // Free memory
    free(D);
    free(U);
    free(P);
    free(M);
    free(C);
    free(prefix_M);
    free(prefix_C);
    free(remaining_U);
    free(heap.heap);
    
    return 0;
}