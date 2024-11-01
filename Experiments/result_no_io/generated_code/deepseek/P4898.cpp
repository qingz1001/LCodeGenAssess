#include <stdio.h>
#include <stdlib.h>

#define MAXHW 1000000
#define MAXQ 50000

int H, W, Q;
int R[MAXHW], C[MAXHW];
int A[MAXQ], B[MAXQ];
int beauty[MAXQ];

typedef struct {
    int r, c;
} Seat;

Seat seats[MAXHW];

int compareSeats(const void *a, const void *b) {
    Seat *seatA = (Seat *)a;
    Seat *seatB = (Seat *)b;
    if (seatA->r != seatB->r) return seatA->r - seatB->r;
    return seatA->c - seatB->c;
}

int countBeauty(Seat *sortedSeats, int size) {
    int beautyCount = 0;
    int minR = sortedSeats[0].r, maxR = sortedSeats[0].r;
    int minC = sortedSeats[0].c, maxC = sortedSeats[0].c;

    for (int i = 1; i < size; i++) {
        if (sortedSeats[i].r == minR && sortedSeats[i].c == minC + 1) {
            minC = sortedSeats[i].c;
        } else if (sortedSeats[i].r == minR + 1 && sortedSeats[i].c == minC) {
            minR = sortedSeats[i].r;
        } else {
            if (minR == maxR && minC == maxC) {
                beautyCount++;
            }
            minR = sortedSeats[i].r;
            minC = sortedSeats[i].c;
        }
        maxR = sortedSeats[i].r;
        maxC = sortedSeats[i].c;
    }
    if (minR == maxR && minC == maxC) {
        beautyCount++;
    }
    return beautyCount;
}

void processRequests() {
    for (int i = 0; i < Q; i++) {
        int a = A[i], b = B[i];
        Seat temp = seats[a];
        seats[a] = seats[b];
        seats[b] = temp;

        qsort(seats, H * W, sizeof(Seat), compareSeats);
        beauty[i] = countBeauty(seats, H * W);
    }
}

int main() {
    scanf("%d %d %d", &H, &W, &Q);
    for (int i = 0; i < H * W; i++) {
        scanf("%d %d", &R[i], &C[i]);
        seats[i].r = R[i];
        seats[i].c = C[i];
    }
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    qsort(seats, H * W, sizeof(Seat), compareSeats);
    beauty[0] = countBeauty(seats, H * W);

    processRequests();

    for (int i = 0; i < Q; i++) {
        printf("%d\n", beauty[i]);
    }

    return 0;
}