#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

struct Treatment {
    int T, L, R, C;
} treatments[MAXM];

int compare(const void *a, const void *b) {
    struct Treatment *treatmentA = (struct Treatment *)a;
    struct Treatment *treatmentB = (struct Treatment *)b;
    return treatmentA->T - treatmentB->T;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &treatments[i].T, &treatments[i].L, &treatments[i].R, &treatments[i].C);
    }

    qsort(treatments, M, sizeof(struct Treatment), compare);

    int minCost = -1;
    int currentLeft = 1, currentRight = N;

    for (int i = 0; i < M; i++) {
        if (currentLeft > currentRight) {
            break;
        }

        if (treatments[i].L <= currentLeft && treatments[i].R >= currentRight) {
            if (minCost == -1 || minCost > treatments[i].C) {
                minCost = treatments[i].C;
            }
            break;
        }

        int nextLeft = treatments[i].L, nextRight = treatments[i].R;

        if (treatments[i].L <= currentLeft) {
            nextLeft = currentLeft;
        }
        if (treatments[i].R >= currentRight) {
            nextRight = currentRight;
        }

        int cost = treatments[i].C;
        if (minCost != -1) {
            cost += minCost;
        }

        if (nextLeft < currentLeft || nextRight > currentRight) {
            if (minCost == -1 || minCost > cost) {
                minCost = cost;
            }
        }

        if (treatments[i].L <= currentLeft && treatments[i].R >= currentLeft) {
            currentLeft = treatments[i].R + 1;
        }
        if (treatments[i].L <= currentRight && treatments[i].R >= currentRight) {
            currentRight = treatments[i].L - 1;
        }
    }

    if (currentLeft <= currentRight) {
        printf("-1\n");
    } else {
        printf("%d\n", minCost);
    }

    return 0;
}