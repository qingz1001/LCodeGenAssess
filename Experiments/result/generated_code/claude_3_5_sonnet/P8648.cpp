#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define MAX_COORD 10001

int n;
int x1[MAX_N], y1[MAX_N], x2[MAX_N], y2[MAX_N];
int diff[MAX_COORD][MAX_COORD];

void add(int x1, int y1, int x2, int y2, int val) {
    diff[x1][y1] += val;
    diff[x2][y1] -= val;
    diff[x1][y2] -= val;
    diff[x2][y2] += val;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
        if (x1[i] > x2[i]) {
            int temp = x1[i];
            x1[i] = x2[i];
            x2[i] = temp;
        }
        if (y1[i] > y2[i]) {
            int temp = y1[i];
            y1[i] = y2[i];
            y2[i] = temp;
        }
        add(x1[i], y1[i], x2[i], y2[i], 1);
    }

    long long area = 0;
    for (int i = 0; i < MAX_COORD; i++) {
        for (int j = 0; j < MAX_COORD; j++) {
            if (i > 0) diff[i][j] += diff[i-1][j];
            if (j > 0) diff[i][j] += diff[i][j-1];
            if (i > 0 && j > 0) diff[i][j] -= diff[i-1][j-1];
            if (diff[i][j] > 0) area++;
        }
    }

    printf("%lld\n", area);
    return 0;
}