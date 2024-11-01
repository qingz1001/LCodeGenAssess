#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll sum;
    int i;
    int j;
} HeapNode;

int main(){
    int N;
    scanf("%d", &N);
    int *A = (int*)malloc(N * sizeof(int));
    int *B = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &A[i]);
    for(int i=0;i<N;i++) scanf("%d", &B[i]);

    // Initialize heap
    int heap_size =1;
    HeapNode *heap = (HeapNode*)malloc((2*N +2) * sizeof(HeapNode));
    heap[1].sum = (ll)A[0] + (ll)B[0];
    heap[1].i =0;
    heap[1].j =0;

    // To keep track of the next indices to push
    // Not using visited array

    // Function to swap two heap nodes
    #define SWAP(a,b) {HeapNode temp = heap[a]; heap[a] = heap[b]; heap[b] = temp;}

    // Function to percolate up
    auto percolate_up = [&](int idx) -> void {
        while(idx >1){
            int parent = idx /2;
            if(heap[parent].sum > heap[idx].sum){
                SWAP(parent, idx);
                idx = parent;
            }
            else break;
        }
    };

    // Function to percolate down
    auto percolate_down = [&](int idx) -> void {
        while(2*idx <= heap_size){
            int left = 2*idx;
            int right = left +1;
            int smallest = left;
            if(right <= heap_size && heap[right].sum < heap[left].sum){
                smallest = right;
            }
            if(heap[smallest].sum < heap[idx].sum){
                SWAP(smallest, idx);
                idx = smallest;
            }
            else break;
        }
    };

    // Output buffer
    // To optimize output, use a buffer
    #define BUFFER_SIZE 10000000
    char *buffer = (char*)malloc(BUFFER_SIZE);
    int buffer_pos =0;
    char num_str[20];

    for(int count=0; count < N; count++){
        if(heap_size <1){
            break;
        }
        // Get the smallest sum
        HeapNode current = heap[1];
        // Convert to string and add to buffer
        int len = sprintf(num_str, "%lld ", current.sum);
        if(buffer_pos + len >= BUFFER_SIZE){
            fwrite(buffer, 1, buffer_pos, stdout);
            buffer_pos =0;
        }
        for(int k=0; k<len; k++) buffer[buffer_pos++] = num_str[k];

        // Replace heap[1] with last element
        heap[1] = heap[heap_size];
        heap_size--;
        percolate_down(1);

        // Push (i+1, j) if possible
        if(current.i +1 < N){
            heap_size++;
            heap[heap_size].sum = (ll)A[current.i +1] + (ll)B[current.j];
            heap[heap_size].i = current.i +1;
            heap[heap_size].j = current.j;
            percolate_up(heap_size);
        }
        // Push (i, j+1) if possible
        if(current.j +1 < N){
            heap_size++;
            heap[heap_size].sum = (ll)A[current.i] + (ll)B[current.j +1];
            heap[heap_size].i = current.i;
            heap[heap_size].j = current.j +1;
            percolate_up(heap_size);
        }
    }
    // Print remaining buffer
    if(buffer_pos >0){
        fwrite(buffer,1, buffer_pos, stdout);
    }

    free(A);
    free(B);
    free(heap);
    free(buffer);
    return 0;
}