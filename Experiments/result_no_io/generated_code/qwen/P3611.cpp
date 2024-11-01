#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_T_MAX 1000000
#define MAX_D 100000

int n, t_max;
int d[MAX_N + 1];

int check(int k) {
    int time = 0;
    int i = 1;
    while (i <= n) {
        int j = 0;
        while (j < k && i <= n) {
            time += d[i];
            i++;
            j++;
        }
        if (time > t_max) return 0;
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &t_max);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }

    int left = 1, right = n;
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);

    return 0;
}