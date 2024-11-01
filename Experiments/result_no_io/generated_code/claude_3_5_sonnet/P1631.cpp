#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int sum;
    int i;
    int j;
} Node;

Node heap[MAX_N];
int heapSize = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node node) {
    int current = heapSize++;
    heap[current] = node;
    
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap[parent].sum <= heap[current].sum) break;
        swap(&heap[parent], &heap[current]);
        current = parent;
    }
}

Node pop() {
    Node result = heap[0];
    heap[0] = heap[--heapSize];
    
    int current = 0;
    while (1) {
        int leftChild = 2 * current + 1;
        int rightChild = 2 * current + 2;
        int smallest = current;
        
        if (leftChild < heapSize && heap[leftChild].sum < heap[smallest].sum)
            smallest = leftChild;
        if (rightChild < heapSize && heap[rightChild].sum < heap[smallest].sum)
            smallest = rightChild;
        
        if (smallest == current) break;
        swap(&heap[current], &heap[smallest]);
        current = smallest;
    }
    
    return result;
}

int main() {
    int N;
    int A[MAX_N], B[MAX_N];
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);
    for (int i = 0; i < N; i++) scanf("%d", &B[i]);
    
    for (int i = 0; i < N; i++) {
        push((Node){A[i] + B[0], i, 0});
    }
    
    for (int k = 0; k < N; k++) {
        Node node = pop();
        printf("%d ", node.sum);
        
        if (node.j + 1 < N) {
            push((Node){A[node.i] + B[node.j + 1], node.i, node.j + 1});
        }
    }
    
    return 0;
}