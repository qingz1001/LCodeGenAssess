#include <stdio.h>
#include <stdlib.h>

#define MAXHW 1000000
#define MAXQ 50000

int H, W, Q;
int R[MAXHW], C[MAXHW];
int A[MAXQ], B[MAXQ];
int seat[MAXHW];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int is_beautiful(int r1, int r2, int c1, int c2) {
    int count = 0;
    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            int idx = r * W + c;
            if (seat[idx] == count) {
                count++;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

int calculate_beauty() {
    int beauty = 0;
    for (int r1 = 0; r1 < H; r1++) {
        for (int r2 = r1; r2 < H; r2++) {
            for (int c1 = 0; c1 < W; c1++) {
                for (int c2 = c1; c2 < W; c2++) {
                    if (is_beautiful(r1, r2, c1, c2)) {
                        beauty++;
                    }
                }
            }
        }
    }
    return beauty;
}

void swap_seats(int a, int b) {
    int temp = seat[a];
    seat[a] = seat[b];
    seat[b] = temp;
}

int main() {
    scanf("%d %d %d", &H, &W, &Q);
    for (int i = 0; i < H * W; i++) {
        scanf("%d %d", &R[i], &C[i]);
        seat[R[i] * W + C[i]] = i;
    }
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    int beauty = calculate_beauty();
    printf("%d\n", beauty);

    for (int i = 0; i < Q; i++) {
        swap_seats(R[A[i]] * W + C[A[i]], R[B[i]] * W + C[B[i]]);
        beauty = calculate_beauty();
        printf("%d\n", beauty);
    }

    return 0;
}