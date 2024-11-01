#include <stdio.h>
#include <stdlib.h>

int a[4][2], b[4][2], minarea = 1000000, ans[100][2];
int n;

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void rotate(int i) {
    swap(&b[i][0], &b[i][1]);
    b[i][0] = 50 - b[i][0];
}

void mirror(int i) {
    b[i][0] = 50 - b[i][0];
}

void check(int i) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for (int j = 0; j < 4; j++) {
        if (b[j][0] > x1) x1 = b[j][0];
        if (b[j][0] < x2) x2 = b[j][0];
        if (b[j][1] > y1) y1 = b[j][1];
        if (b[j][1] < y2) y2 = b[j][1];
    }
    int area = (x1 - x2) * (y1 - y2);
    if (area < minarea) {
        minarea = area;
        n = 0;
        ans[n][0] = x2;
        ans[n][1] = y2;
        n++;
    } else if (area == minarea) {
        int i;
        for (i = 0; i < n; i++) {
            if (ans[i][0] == x2 && ans[i][1] == y2) break;
        }
        if (i == n) {
            ans[n][0] = x2;
            ans[n][1] = y2;
            n++;
        }
    }
}

void dfs(int i) {
    if (i == 4) {
        check(i);
        return;
    }
    b[i][0] = a[i][0];
    b[i][1] = a[i][1];
    dfs(i + 1);
    rotate(i);
    check(i + 1);
    rotate(i);
    rotate(i);
    check(i + 1);
    rotate(i);
    mirror(i);
    check(i + 1);
    rotate(i);
    check(i + 1);
}

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d%d", &a[i][0], &a[i][1]);
        if (a[i][0] > a[i][1]) {
            swap(&a[i][0], &a[i][1]);
        }
    }
    dfs(0);
    printf("%d\n", minarea);
    for (int i = 0; i < n; i++) {
        if (ans[i][0] <= ans[i][1]) {
            printf("%d %d\n", ans[i][0], ans[i][1]);
        } else {
            printf("%d %d\n", ans[i][1], ans[i][0]);
        }
    }
    return 0;
}