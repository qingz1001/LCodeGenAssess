#include <stdio.h>
#include <stdlib.h>

#define MAX_C 1000000

typedef struct {
    int W;
    int C;
} Flower;

Flower flowers[MAX_C + 1];
int flowerCount[MAX_C + 1];
int maxC = 0;

void addFlower(int W, int C) {
    if (flowerCount[C] == 0) {
        flowers[C].W = W;
        flowers[C].C = C;
        flowerCount[C]++;
        if (C > maxC) maxC = C;
    }
}

void deleteMaxFlower() {
    while (flowerCount[maxC] == 0) {
        maxC--;
    }
    flowerCount[maxC]--;
}

void deleteMinFlower() {
    while (flowerCount[1] == 0) {
        for (int i = 1; i <= maxC; i++) {
            flowers[i] = flowers[i + 1];
            flowerCount[i] = flowerCount[i + 1];
        }
        maxC--;
    }
    flowerCount[1]--;
}

int main() {
    int operation, W, C;
    int totalBeauty = 0, totalPrice = 0;

    while (1) {
        scanf("%d", &operation);
        if (operation == -1) break;

        if (operation == 1) {
            scanf("%d %d", &W, &C);
            addFlower(W, C);
        } else if (operation == 2) {
            deleteMaxFlower();
        } else if (operation == 3) {
            deleteMinFlower();
        }
    }

    for (int i = 1; i <= maxC; i++) {
        if (flowerCount[i] > 0) {
            totalBeauty += flowers[i].W * flowerCount[i];
            totalPrice += flowers[i].C * flowerCount[i];
        }
    }

    printf("%d %d\n", totalBeauty, totalPrice);

    return 0;
}