#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long weight;
    int wear;
} Stack;

typedef struct {
    Stack data[200];
    int size;
} Heap;

// Swap two stacks
void swap_stack(Stack *a, Stack *b) {
    Stack temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapify_up(Heap *heap, int index) {
    while (index > 0) {
        int parent = (index -1) /2;
        if (heap->data[parent].weight > heap->data[index].weight) {
            swap_stack(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
        else {
            break;
        }
    }
}

// Heapify down
void heapify_down(Heap *heap, int index) {
    while (1) {
        int smallest = index;
        int left = 2*index +1;
        int right = 2*index +2;
        if (left < heap->size && heap->data[left].weight < heap->data[smallest].weight) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].weight < heap->data[smallest].weight) {
            smallest = right;
        }
        if (smallest != index) {
            swap_stack(&heap->data[smallest], &heap->data[index]);
            index = smallest;
        }
        else {
            break;
        }
    }
}

// Push a stack into the heap
void push_heap_stack(Heap *heap, Stack stack) {
    heap->data[heap->size] = stack;
    heap->size++;
    heapify_up(heap, heap->size -1);
}

// Pop the smallest stack from the heap
Stack pop_heap_stack(Heap *heap) {
    Stack top = heap->data[0];
    heap->data[0] = heap->data[heap->size -1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        Heap heap;
        heap.size =0;
        for(int i=0;i<n;i++){
            long long w;
            scanf("%lld", &w);
            Stack s;
            s.weight =w;
            s.wear =0;
            push_heap_stack(&heap, s);
        }
        long long total_cost=0;
        while(heap.size >1){
            Stack s1 = pop_heap_stack(&heap);
            Stack s2 = pop_heap_stack(&heap);
            long long cost = s1.weight + s1.wear + s2.wear;
            total_cost += cost;
            Stack new_stack;
            new_stack.weight = s1.weight + s2.weight;
            if(s1.wear > s2.wear){
                new_stack.wear = 2 * s1.wear +1;
            }
            else{
                new_stack.wear = 2 * s2.wear +1;
            }
            push_heap_stack(&heap, new_stack);
        }
        printf("%lld\n", total_cost);
    }
    return 0;
}