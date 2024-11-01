#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int n, m;
int d1[MAX_N], d2[MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int check(int mid) {
    int modules1 = 0, modules2 = 0;
    for (int i = 0; i < n; i++) {
        int x = mid / d1[i];
        int y = mid / d2[i];
        modules1 += x;
        modules2 += y;
        if (modules1 >= m && modules2 >= m) {
            return 1;
        }
    }
    return 0;
}

int binary_search(int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    int max_d = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
        max_d = max(max_d, max(d1[i], d2[i]));
    }

    int result = binary_search(0, m * max_d);
    printf("%d\n", result);

    return 0;
}