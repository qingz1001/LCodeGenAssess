#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

long long merge(long long *heap, int *size) {
    long long a, b, result;
    
    a = heap[1];
    heap[1] = heap[*size];
    (*size)--;
    
    int i = 1, child;
    while (2 * i <= *size) {
        child = 2 * i;
        if (child < *size && heap[child + 1] < heap[child]) {
            child++;
        }
        if (heap[i] <= heap[child]) {
            break;
        }
        long long temp = heap[i];
        heap[i] = heap[child];
        heap[child] = temp;
        i = child;
    }
    
    b = heap[1];
    heap[1] = heap[*size];
    (*size)--;
    
    i = 1;
    while (2 * i <= *size) {
        child = 2 * i;
        if (child < *size && heap[child + 1] < heap[child]) {
            child++;
        }
        if (heap[i] <= heap[child]) {
            break;
        }
        long long temp = heap[i];
        heap[i] = heap[child];
        heap[child] = temp;
        i = child;
    }
    
    result = a * b + 1;
    
    (*size)++;
    heap[*size] = result;
    i = *size;
    while (i > 1 && heap[i / 2] > heap[i]) {
        long long temp = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = temp;
        i /= 2;
    }
    
    return result;
}

int main() {
    int n, size;
    long long heap[MAX_N + 1];
    long long result = 0;
    
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        heap[i] = 1;
    }
    size = n;
    
    while (size > 1) {
        result = merge(heap, &size);
    }
    
    printf("%lld\n", result);
    
    return 0;
}