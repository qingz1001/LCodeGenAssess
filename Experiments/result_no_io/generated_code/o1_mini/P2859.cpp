#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
    int idx;
} Cow;

typedef struct {
    int end;
    int stall_no;
} Stall;

int compare_cows(const void *a, const void *b) {
    Cow *ca = (Cow *)a;
    Cow *cb = (Cow *)b;
    if (ca->A != cb->A)
        return ca->A - cb->A;
    return ca->B - cb->B;
}

void heapify_down(Stall heap[], int heap_size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index;
        int right = 2 * index + 1;
        if (left <= heap_size && heap[left].end < heap[smallest].end)
            smallest = left;
        if (right <= heap_size && heap[right].end < heap[smallest].end)
            smallest = right;
        if (smallest != index) {
            Stall temp = heap[smallest];
            heap[smallest] = heap[index];
            heap[index] = temp;
            index = smallest;
        }
        else {
            break;
        }
    }
}

void heapify_up(Stall heap[], int index) {
    while (index > 1) {
        int parent = index / 2;
        if (heap[parent].end > heap[index].end) {
            Stall temp = heap[parent];
            heap[parent] = heap[index];
            heap[index] = temp;
            index = parent;
        }
        else {
            break;
        }
    }
}

int main(){
    int N;
    scanf("%d", &N);
    Cow *cows = (Cow *)malloc(N * sizeof(Cow));
    for(int i=0;i<N;i++){
        scanf("%d %d", &cows[i].A, &cows[i].B);
        cows[i].idx = i;
    }

    qsort(cows, N, sizeof(Cow), compare_cows);

    Stall *heap = (Stall *)malloc((N+2) * sizeof(Stall));
    int heap_size = 0;
    int next_stall = 1;
    int *answer = (int *)malloc(N * sizeof(int));

    for(int i=0;i<N;i++){
        if(heap_size > 0 && heap[1].end < cows[i].A){
            // Reuse stall
            int stall_no = heap[1].stall_no;
            answer[cows[i].idx] = stall_no;
            heap[1].end = cows[i].B;
            heapify_down(heap, heap_size, 1);
        }
        else{
            // Assign new stall
            answer[cows[i].idx] = next_stall;
            heap_size++;
            heap[heap_size].end = cows[i].B;
            heap[heap_size].stall_no = next_stall;
            heapify_up(heap, heap_size);
            next_stall++;
        }
    }

    printf("%d\n", next_stall-1);
    for(int i=0;i<N;i++){
        printf("%d\n", answer[i]);
    }

    free(cows);
    free(heap);
    free(answer);
    return 0;
}