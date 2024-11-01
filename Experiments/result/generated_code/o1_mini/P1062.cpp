#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Heap node structure
typedef struct {
    ll sum;
    int idx;
} HeapNode;

// Min heap structure
typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

// Initialize heap
MinHeap* initHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two HeapNodes
void swap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push a node into the heap
void pushHeap(MinHeap *heap, HeapNode node){
    if(heap->size >= heap->capacity){
        // Reallocate more space if needed
        heap->capacity *=2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode)*(heap->capacity +1));
    }
    heap->size++;
    heap->data[heap->size] = node;
    // Sift up
    int current = heap->size;
    while(current >1){
        int parent = current /2;
        if(heap->data[parent].sum > heap->data[current].sum){
            swap(&heap->data[parent], &heap->data[current]);
            current = parent;
        }
        else{
            break;
        }
    }
}

// Pop the smallest node from the heap
HeapNode popHeap(MinHeap *heap){
    HeapNode min = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    // Sift down
    int current =1;
    while(1){
        int left = current *2;
        int right = current *2 +1;
        int smallest = current;
        if(left <= heap->size && heap->data[left].sum < heap->data[smallest].sum){
            smallest = left;
        }
        if(right <= heap->size && heap->data[right].sum < heap->data[smallest].sum){
            smallest = right;
        }
        if(smallest != current){
            swap(&heap->data[smallest], &heap->data[current]);
            current = smallest;
        }
        else{
            break;
        }
    }
    return min;
}

// Binary search to check existence and find insertion point
int binarySearch(ll *arr, int size, ll target){
    int left=0, right = size -1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(arr[mid]==target){
            return mid;
        }
        else if(arr[mid] < target){
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    return -1;
}

int main(){
    int k, N;
    scanf("%d %d", &k, &N);
    
    // Compute powers of k
    ll powers[60];
    int m=0;
    powers[m++] =1;
    while(1){
        if(m >=60) break;
        if(powers[m-1] > 1e18 /k) break;
        powers[m] = powers[m-1]*k;
        m++;
    }
    
    // Initialize min heap
    MinHeap *heap = initHeap(100000);
    HeapNode first;
    first.sum = powers[0];
    first.idx =0;
    pushHeap(heap, first);
    
    // Initialize visited list
    ll visited[100000];
    int vis_size=0;
    visited[vis_size++] = first.sum;
    
    // Initialize sequence list
    ll sequence[1000];
    int seq_size=0;
    
    while(seq_size < N){
        HeapNode current = popHeap(heap);
        sequence[seq_size++] = current.sum;
        // For each possible next power
        for(int i = current.idx; i < m; i++){
            ll new_sum = current.sum + powers[i];
            // Binary search to check if new_sum is visited
            int left=0, right=vis_size-1, found=0;
            while(left <= right){
                int mid = left + (right -left)/2;
                if(visited[mid] == new_sum){
                    found=1;
                    break;
                }
                else if(visited[mid] < new_sum){
                    left = mid +1;
                }
                else{
                    right = mid -1;
                }
            }
            if(!found){
                // Insert new_sum into visited list
                // Shift to make space
                for(int j=vis_size; j>left; j--){
                    visited[j] = visited[j-1];
                }
                visited[left] = new_sum;
                vis_size++;
                // Push into heap
                HeapNode new_node;
                new_node.sum = new_sum;
                new_node.idx = i;
                pushHeap(heap, new_node);
            }
        }
    }
    
    printf("%lld\n", sequence[N-1]);
    
    // Free heap memory
    free(heap->data);
    free(heap);
    
    return 0;
}