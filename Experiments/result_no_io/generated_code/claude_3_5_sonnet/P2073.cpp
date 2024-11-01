#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int beauty;
    int price;
} Flower;

Flower heap[MAX_N + 1];
int heap_size = 0;

void swap(Flower *a, Flower *b) {
    Flower temp = *a;
    *a = *b;
    *b = temp;
}

void push(Flower f) {
    heap[++heap_size] = f;
    int current = heap_size;
    while (current > 1 && heap[current].price > heap[current / 2].price) {
        swap(&heap[current], &heap[current / 2]);
        current /= 2;
    }
}

void pop() {
    if (heap_size == 0) return;
    heap[1] = heap[heap_size--];
    int current = 1;
    while (current * 2 <= heap_size) {
        int child = current * 2;
        if (child + 1 <= heap_size && heap[child + 1].price > heap[child].price) {
            child++;
        }
        if (heap[current].price >= heap[child].price) break;
        swap(&heap[current], &heap[child]);
        current = child;
    }
}

int main() {
    int op, w, c;
    long long total_beauty = 0, total_price = 0;
    int price_exists[1000001] = {0};

    while (1) {
        scanf("%d", &op);
        if (op == -1) break;

        switch (op) {
            case 1:
                scanf("%d %d", &w, &c);
                if (!price_exists[c]) {
                    Flower f = {w, c};
                    push(f);
                    price_exists[c] = 1;
                    total_beauty += w;
                    total_price += c;
                }
                break;
            case 2:
                if (heap_size > 0) {
                    price_exists[heap[1].price] = 0;
                    total_beauty -= heap[1].beauty;
                    total_price -= heap[1].price;
                    pop();
                }
                break;
            case 3:
                if (heap_size > 0) {
                    int min_idx = 1;
                    for (int i = 2; i <= heap_size; i++) {
                        if (heap[i].price < heap[min_idx].price) {
                            min_idx = i;
                        }
                    }
                    price_exists[heap[min_idx].price] = 0;
                    total_beauty -= heap[min_idx].beauty;
                    total_price -= heap[min_idx].price;
                    swap(&heap[min_idx], &heap[heap_size--]);
                }
                break;
        }
    }

    printf("%lld %lld\n", total_beauty, total_price);
    return 0;
}