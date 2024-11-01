#include <stdio.h>
#include <stdlib.h>

#define MAX_HW 1000000
#define MAX_Q 50000

int H, W, Q;
int R[MAX_HW], C[MAX_HW];
int seat_count[1001][1001];

void update(int x1, int y1, int x2, int y2, int delta) {
    seat_count[x1][y1] += delta;
    if (x2 + 1 < H) seat_count[x2 + 1][y1] -= delta;
    if (y2 + 1 < W) seat_count[x1][y2 + 1] -= delta;
    if (x2 + 1 < H && y2 + 1 < W) seat_count[x2 + 1][y2 + 1] += delta;
}

int query(int x, int y) {
    int sum = 0;
    for (int i = 0; i <= x; i++) {
        sum += seat_count[i][y];
    }
    return sum;
}

int main() {
    scanf("%d %d %d", &H, &W, &Q);
    for (int i = 0; i < H * W; i++) {
        scanf("%d %d", &R[i], &C[i]);
        update(R[i], C[i], R[i], C[i], 1);
    }

    for (int i = 0; i < Q; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        int rx1 = R[A], cx1 = C[A], rx2 = R[B], cx2 = C[B];
        int count_before = query(rx2, cx2) - query(rx2, cx1 - 1) - query(rx1 - 1, cx2) + query(rx1 - 1, cx1 - 1);

        update(rx1, cx1, rx1, cx1, -1);
        update(rx2, cx2, rx2, cx2, -1);
        R[A] = rx2, C[A] = cx2;
        R[B] = rx1, C[B] = cx1;
        update(rx1, cx1, rx1, cx1, 1);
        update(rx2, cx2, rx2, cx2, 1);

        int count_after = query(rx2, cx2) - query(rx2, cx1 - 1) - query(rx1 - 1, cx2) + query(rx1 - 1, cx1 - 1);
        printf("%d\n", count_before + 1 == count_after ? count_before : count_before + 1);
    }

    return 0;
}