#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Min Heap structure
typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
MinHeap* initHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (long long*)malloc(sizeof(long long) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two elements
void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

// Push a value into the heap
void pushHeap(MinHeap *heap, long long val) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (long long*)realloc(heap->data, sizeof(long long) * heap->capacity);
    }
    heap->data[heap->size] = val;
    int i = heap->size;
    heap->size++;
    // Heapify up
    while (i > 0) {
        int parent = (i -1)/2;
        if (heap->data[parent] > heap->data[i]) {
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

// Pop the minimum value from the heap
long long popHeap(MinHeap *heap) {
    if (heap->size == 0) return -1;
    long long top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    // Heapify down
    int i = 0;
    while (1) {
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
        if (left < heap->size && heap->data[left] < heap->data[smallest])
            smallest = left;
        if (right < heap->size && heap->data[right] < heap->data[smallest])
            smallest = right;
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

// Check if heap is empty
int isEmpty(MinHeap *heap) {
    return heap->size == 0;
}

// Free the heap
void freeHeap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}

int main(){
    int k, m;
    scanf("%d %d", &k, &m);
    
    // Initialize heap
    MinHeap *heap = initHeap(100000);
    pushHeap(heap, 1);
    
    // To store first k elements
    long long *elements = (long long*)malloc(sizeof(long long) * (k +1));
    int count =0;
    
    while(count <k && !isEmpty(heap)){
        long long current = popHeap(heap);
        elements[count++] = current;
        // Generate next elements
        pushHeap(heap, 2*current +1);
        pushHeap(heap, 4*current +5);
    }
    freeHeap(heap);
    
    // Concatenate digits
    // Assuming maximum digits could be around 30000 * 10 = 300000
    char *concat = (char*)malloc(sizeof(char) * 3000005);
    int pos =0;
    for(int i=0;i<k;i++){
        char buffer[20];
        sprintf(buffer, "%lld", elements[i]);
        int len = strlen(buffer);
        memcpy(concat + pos, buffer, len);
        pos += len;
    }
    concat[pos] = '\0';
    
    // Print original number
    printf("%s\n", concat);
    
    // Now delete m digits to make the number largest
    // Use a stack approach
    int n = pos;
    char *stack = (char*)malloc(sizeof(char) * (n+1));
    int top_stack =0;
    for(int i=0;i<n;i++){
        while(top_stack >0 && stack[top_stack-1] < concat[i] && m >0){
            top_stack--;
            m--;
        }
        stack[top_stack++] = concat[i];
    }
    // If still m >0, remove from the end
    while(m >0 && top_stack >0){
        top_stack--;
        m--;
    }
    stack[top_stack] = '\0';
    
    // Print the remaining number
    printf("%s\n", stack);
    
    // Free memory
    free(elements);
    free(concat);
    free(stack);
    
    return 0;
}