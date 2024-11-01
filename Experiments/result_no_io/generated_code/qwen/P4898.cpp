#include <stdio.h>
#include <stdlib.h>

#define MAX_H 1000
#define MAX_W 1000
#define MAX_Q 50000

int H, W, Q;
int seats[MAX_H][MAX_W];
int seat_ids[MAX_H * MAX_W];

void read_input() {
    scanf("%d %d %d", &H, &W, &Q);
    for (int i = 0; i < H * W; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        seats[r][c] = i;
        seat_ids[i] = r * W + c;
    }
    for (int i = 0; i < Q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        // Convert to zero-based index
        a--;
        b--;
        // Swap the seats of participants a and b
        int ra = seat_ids[a] / W, ca = seat_ids[a] % W;
        int rb = seat_ids[b] / W, cb = seat_ids[b] % W;
        seat_ids[a] = rb * W + cb;
        seat_ids[b] = ra * W + ca;
        seats[ra][ca] = b;
        seats[rb][cb] = a;
    }
}

int main() {
    read_input();
    return 0;
}