#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

typedef struct {
    int beauty;
    int price;
} Flower;

Flower heap[MAX_N];
int heap_size = 0;

void swap(Flower *a, Flower *b) {
    Flower temp = *a;
    *a = *b;
    *b = temp;
}

void push(Flower f) {
    int i = ++heap_size;
    heap[i] = f;
    while (i > 1 && heap[i].price > heap[i/2].price) {
        swap(&heap[i], &heap[i/2]);
        i = i/2;
    }
}

void pop() {
    heap[1] = heap[heap_size--];
    int i = 1, child;
    while (2*i <= heap_size) {
        child = 2*i;
        if (child < heap_size && heap[child+1].price > heap[child].price) {
            child++;
        }
        if (heap[i].price >= heap[child].price) break;
        swap(&heap[i], &heap[child]);
        i = child;
    }
}

int main() {
    int op, w, c;
    int total_beauty = 0, total_price = 0;
    int price_exists[1000001] = {0};

    while (1) {
        scanf("%d", &op);
        if (op == -1) break;

        switch (op) {
            case 1:
                scanf("%d %d", &w, &c);
                if (!price_exists[c]) {
                    push((Flower){w, c});
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
                    int min_price_idx = 1;
                    for (int i = 2; i <= heap_size; i++) {
                        if (heap[i].price < heap[min_price_idx].price) {
                            min_price_idx = i;
                        }
                    }
                    price_exists[heap[min_price_idx].price] = 0;
                    total_beauty -= heap[min_price_idx].beauty;
                    total_price -= heap[min_price_idx].price;
                    swap(&heap[min_price_idx], &heap[heap_size]);
                    heap_size--;
                }
                break;
        }
    }

    printf("%d %d\n", total_beauty, total_price);
    return 0;
}