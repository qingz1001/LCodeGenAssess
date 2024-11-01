#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int W;
    int C;
} Flower;

typedef struct {
    Flower *flowers;
    int size;
    int capacity;
} FlowerArray;

void initFlowerArray(FlowerArray *arr, int capacity) {
    arr->flowers = (Flower *)malloc(capacity * sizeof(Flower));
    arr->size = 0;
    arr->capacity = capacity;
}

void addFlower(FlowerArray *arr, int W, int C) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->flowers[i].C == C) {
            return;
        }
    }
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->flowers = (Flower *)realloc(arr->flowers, arr->capacity * sizeof(Flower));
    }
    arr->flowers[arr->size].W = W;
    arr->flowers[arr->size].C = C;
    arr->size++;
}

void removeMostExpensive(FlowerArray *arr) {
    if (arr->size == 0) return;
    int maxIndex = 0;
    for (int i = 1; i < arr->size; i++) {
        if (arr->flowers[i].C > arr->flowers[maxIndex].C) {
            maxIndex = i;
        }
    }
    arr->flowers[maxIndex] = arr->flowers[arr->size - 1];
    arr->size--;
}

void removeCheapest(FlowerArray *arr) {
    if (arr->size == 0) return;
    int minIndex = 0;
    for (int i = 1; i < arr->size; i++) {
        if (arr->flowers[i].C < arr->flowers[minIndex].C) {
            minIndex = i;
        }
    }
    arr->flowers[minIndex] = arr->flowers[arr->size - 1];
    arr->size--;
}

int main() {
    FlowerArray flowers;
    initFlowerArray(&flowers, 100000);

    int operation, W, C;
    while (1) {
        scanf("%d", &operation);
        if (operation == -1) break;
        if (operation == 1) {
            scanf("%d %d", &W, &C);
            addFlower(&flowers, W, C);
        } else if (operation == 2) {
            removeMostExpensive(&flowers);
        } else if (operation == 3) {
            removeCheapest(&flowers);
        }
    }

    int totalBeauty = 0, totalCost = 0;
    for (int i = 0; i < flowers.size; i++) {
        totalBeauty += flowers.flowers[i].W;
        totalCost += flowers.flowers[i].C;
    }

    printf("%d %d\n", totalBeauty, totalCost);

    free(flowers.flowers);
    return 0;
}