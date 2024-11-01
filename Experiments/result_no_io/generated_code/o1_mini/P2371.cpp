#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

typedef long long ll;

// Structure for heap nodes
typedef struct {
    ll sum;
    int r;
} Node;

// Min-heap structure
typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;

// Initialize heap
MinHeap* initHeap(int capacity){
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (Node*)malloc(sizeof(Node) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two nodes
void swap(Node *a, Node *b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Push a node into the heap
void pushHeap(MinHeap *heap, Node node){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (Node*)realloc(heap->data, sizeof(Node) * heap->capacity);
    }
    heap->data[heap->size] = node;
    int i = heap->size;
    heap->size++;
    // Bubble up
    while(i > 0){
        int parent = (i -1)/2;
        if(heap->data[parent].sum <= heap->data[i].sum) break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

// Pop the smallest node from the heap
Node popHeap(MinHeap *heap){
    Node top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    // Bubble down
    while(1){
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
        if(left < heap->size && heap->data[left].sum < heap->data[smallest].sum){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].sum < heap->data[smallest].sum){
            smallest = right;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Function to compute gcd
ll gcd_func(ll a, ll b){
    while(b){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    int n;
    ll l, r;
    scanf("%d %lld %lld", &n, &l, &r);
    ll a_original[n];
    int count_nonzero =0;
    for(int i=0;i<n;i++){
        scanf("%lld", &a_original[i]);
        if(a_original[i] >0) count_nonzero++;
    }
    if(count_nonzero ==0){
        if(l <=0 && r >=0){
            printf("1\n");
        }
        else{
            printf("0\n");
        }
        return 0;
    }
    // Collect a_i >0
    ll a[12];
    int m_n =0;
    for(int i=0;i<n;i++) if(a_original[i]>0) a[m_n++] = a_original[i];
    // Compute gcd
    ll d = a[0];
    for(int i=1;i<m_n;i++) d = gcd_func(d, a[i]);
    // Adjust a_i, l, r
    // Check if there exists b divisible by d in [l,r]
    ll l_div = (l + d -1)/d;
    ll r_div = r/d;
    if(l_div > r_div){
        printf("0\n");
        return 0;
    }
    // Adjust a_i
    for(int i=0;i<m_n;i++) a[i] /= d;
    // Find m = min a_i
    ll m_val = a[0];
    for(int i=1;i<m_n;i++) if(a[i] < m_val) m_val = a[i];
    int m = (int)m_val;
    // Initialize min_b
    ll *min_b = (ll*)malloc(sizeof(ll)*m);
    for(int i=0;i<m;i++) min_b[i] = LLONG_MAX;
    min_b[0] = 0;
    // Initialize heap
    MinHeap *heap = initHeap(1<<20);
    Node start = {0, 0};
    pushHeap(heap, start);
    // Dijkstra
    while(heap->size >0){
        Node current = popHeap(heap);
        if(current.sum > min_b[current.r]) continue;
        for(int i=0;i<m_n;i++){
            ll new_sum = current.sum + a[i];
            int new_r = (current.r + a[i]) % m;
            if(new_sum < min_b[new_r]){
                min_b[new_r] = new_sum;
                Node new_node = {new_sum, new_r};
                pushHeap(heap, new_node);
            }
        }
    }
    free(heap->data);
    free(heap);
    // Now compute the answer
    ll answer =0;
    for(int r_mod=0;r_mod<m;r_mod++){
        if(min_b[r_mod] == LLONG_MAX) continue;
        ll min_b_r = min_b[r_mod];
        if(min_b_r > r_div) continue;
        ll lower = l_div > min_b_r ? l_div : min_b_r;
        // Find the smallest b >= lower with b ≡ r_mod mod m
        ll rem = lower % m;
        ll add = (r_mod - rem + m) % m;
        ll b_low = lower + add;
        if(b_low < min_b_r){
            b_low += m;
        }
        if(b_low > r_div) continue;
        // Find the largest b <= r_div with b ≡ r_mod mod m
        ll b_high = r_div - ((r_div - r_mod) % m);
        if(b_high < min_b_r) continue;
        if(b_high > r_div) b_high -= m;
        if(b_high < b_low) continue;
        ll cnt = ((b_high - b_low)/m) +1;
        answer += cnt;
    }
    free(min_b);
    printf("%lld\n", answer);
    return 0;
}