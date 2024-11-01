#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_T_MAX 1000000
#define MAX_D 100000

int n, t_max;
int d[MAX_N];

int check(int k) {
    int current_time = 0;
    int i = 0;
    while (current_time <= t_max && i < n) {
        current_time += d[i];
        i++;
    }
    return i == n;
}

int main() {
    scanf("%d %d", &n, &t_max);
    for (int i = 0; i < n; i++) {
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