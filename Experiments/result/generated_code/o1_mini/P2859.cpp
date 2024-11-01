#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int A;
    int B;
} Cow;

typedef struct {
    int end;
    int stall;
} HeapEntry;

int compare_cows(const void *a, const void *b) {
    Cow *c1 = (Cow *)a;
    Cow *c2 = (Cow *)b;
    if (c1->A != c2->A)
        return c1->A - c2->A;
    return c1->B - c2->B;
}

int main(){
    int N;
    scanf("%d", &N);
    Cow *cows = (Cow *)malloc(N * sizeof(Cow));
    for(int i=0;i<N;i++){
        scanf("%d %d", &cows[i].A, &cows[i].B);
        cows[i].index = i;
    }
    qsort(cows, N, sizeof(Cow), compare_cows);
    HeapEntry *heap = (HeapEntry *)malloc(N * sizeof(HeapEntry));
    int heap_size = 0;
    int next_stall = 1;
    int stall_count = 0;
    int *assigned = (int *)malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        if(heap_size > 0 && heap[0].end < cows[i].A){
            // Reuse stall
            int stall = heap[0].stall;
            assigned[cows[i].index] = stall;
            // Replace root with last element and heapify
            heap[0].end = cows[i].B;
            // Heapify down
            int pos = 0;
            while(1){
                int smallest = pos;
                int left = 2*pos +1;
                int right = 2*pos +2;
                if(left < heap_size && heap[left].end < heap[smallest].end)
                    smallest = left;
                if(right < heap_size && heap[right].end < heap[smallest].end)
                    smallest = right;
                if(smallest != pos){
                    HeapEntry temp = heap[pos];
                    heap[pos] = heap[smallest];
                    heap[smallest] = temp;
                    pos = smallest;
                }
                else break;
            }
        }
        else{
            // Assign new stall
            int stall = next_stall++;
            assigned[cows[i].index] = stall;
            heap[heap_size].end = cows[i].B;
            heap[heap_size].stall = stall;
            heap_size++;
            // Heapify up
            int pos = heap_size -1;
            while(pos >0){
                int parent = (pos -1)/2;
                if(heap[pos].end < heap[parent].end){
                    HeapEntry temp = heap[pos];
                    heap[pos] = heap[parent];
                    heap[parent] = temp;
                    pos = parent;
                }
                else break;
            }
            if(next_stall -1 > stall_count)
                stall_count = next_stall -1;
        }
    }
    printf("%d\n", stall_count);
    for(int i=0;i<N;i++) printf("%d\n", assigned[i]);
    free(cows);
    free(heap);
    free(assigned);
    return 0;
}