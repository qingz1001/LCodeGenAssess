#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef long long ll;

ll heap[MAX_N];
int heap_size = 0;

void swap(ll *a, ll *b) {
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void push(ll x) {
    int i = heap_size++;
    heap[i] = x;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

ll pop() {
    ll res = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    while (2 * i + 1 < heap_size) {
        int j = 2 * i + 1;
        if (j + 1 < heap_size && heap[j + 1] < heap[j]) j++;
        if (heap[i] <= heap[j]) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        push(1);
    }
    
    ll total_energy = 0;
    while (heap_size > 1) {
        ll a = pop();
        ll b = pop();
        total_energy += a * b + 1;
        push(a + b + 1);
    }
    
    printf("%lld\n", total_energy);
    
    return 0;
}